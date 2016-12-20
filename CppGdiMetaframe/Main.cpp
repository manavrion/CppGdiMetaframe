// MetaFrame.cpp: определяет точку входа для приложения.
//

#include "stdafx.h"
#include "Main.h"
#include "Dfs.h"
#include "Bfs.h"
#include "Rgr.h"
DWORD WINAPI threaddfs(LPVOID t);
DWORD WINAPI threadbfs(LPVOID t);
DWORD WINAPI threadrgr(LPVOID t);

GraphArea *graphArea = new GraphArea();
Label *stateLine;
Window *mainWindow;

OutTable *outtable = new OutTable();

GraphNode *startingNode = null;

void enabledAll(bool enabled) {
    for (auto &ob : mainWindow->getChilds()) {
        ob->setEnabled(enabled);
    }
}


using namespace MetaFrame;
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, 
                      _In_opt_ HINSTANCE hPrevInstance,
                      _In_ LPWSTR    lpCmdLine,
                      _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    // Initialize GDI+.
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR           gdiplusToken;
    Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);


    
    mainWindow = new Window(L"ManaevRuslanGraph", L"Manaev Ruslan Graph", Size(800, 400), Color(60, 60, 60), hInstance);

    
    stateLine = (Label*)(new Label())
        ->setText(L"На поле 0 вершин.")
        ->setHorizontalAlignment(HorizontalAlignment::Left)
        ->setVerticalAlignment(VerticalAlignment::Center)
        ->setMargin(10, 0, 0, 0);

    Point prepos = Point();
    

    bool innodedragMode = false;
    GraphLine *line = null;

    Table *tableAdjacency = new Table();

    
    mainWindow->add(graphArea
        ->setBackgroundColor(Color(100, 100, 100))
        ->setMargin(Margin(10, 200, 10, 250))
        ->addMouseDoubleClickedEvent([&](MouseEvent event, FrameElement *sender) {
            if (event.shiftDown) return;
            for (auto &node : graphArea->getNodesCollection()) {
                Rect tmprect = node->getRect();
                tmprect.inflate(Point(15, 15));
                if (tmprect.contains(Point(event.x, event.y))) {
                    return;
                }
            }

            
            graphArea->addNode((GraphNode *)(new GraphNode())
                ->setWidth(40)
                ->setHeight(40)
                ->setX(event.x - 15)
                ->setY(event.y - 15)
                ->addMousePressedEvent([&](MouseEvent event, FrameElement *sender) {
                    if (event.shiftDown) {
                        if (startingNode == (GraphNode*)sender) {
                            startingNode = null;
                        }

                        graphArea->eraseNode((GraphNode *)sender);
                        


                        stateLine->setText(L"На поле " + String(graphArea->getNodesCollection().size()) + L" вершин.");
                        tableAdjacency->getTable() = graphArea->getAdjacencyMatrix();
                        tableAdjacency->refrash();
                        sender->update();
                        sender->getParent()->erase(sender);
                        delete sender;
                    } else {
                        startingNode = (GraphNode*)sender;
                        stateLine->setText(L"Начальная вершина - " + startingNode->getLabel());
                        mainWindow->update();
                    }
                })
            );
            stateLine->setText(L"На поле " + String(graphArea->getNodesCollection().size()) + L" вершин.");


            tableAdjacency->getTable() = graphArea->getAdjacencyMatrix();
            tableAdjacency->refrash();


            sender->update();
        })
        ->addMouseReleasedEvent([&](MouseEvent event, FrameElement *sender) { 
            innodedragMode = false; 
            prepos = Point();
            
            if (line == null) {
                return;
            }
            for (auto &node : graphArea->getNodesCollection()) {
                if (node->getRect().contains( Point(line->getPointOfEnd()) + Point(sender->getX(), sender->getY()))) {

                    line->setPointOfEnd(PointF(node->getX() + node->getWidth() / 2 - sender->getX(), node->getY() + node->getHeight() / 2 - sender->getY()));
                    graphArea->addLineComplite(line);
                    line = null;
                    tableAdjacency->getTable() = graphArea->getAdjacencyMatrix();
                    tableAdjacency->refrash();
                    //mainWindow->pack();
                    mainWindow->update();
                    return;
                }
            }

            for (auto it = graphArea->getChilds().begin(); it != graphArea->getChilds().end(); it++) {
                if (*it == line) {
                    graphArea->getChilds().erase(it);
                    break;
                }
            }
            
            //mainWindow->pack();
            graphArea->update();
        })
        ->addMouseDraggedEvent([&](MouseEvent event, FrameElement *sender) {

            if (innodedragMode) {
                line->setPointOfEnd(PointF(event.x - sender->getX(), event.y - sender->getY()));
                //graphArea->addLineComplite(line);
                
                //mainWindow->update();
                //sender->invalidateRect(Rect(1, 1, sender->getWidth() - 3, sender->getHeight() - 3));
                sender->update();
                return;
            }

            if (prepos == Point()) {
                prepos = Point(event.x, event.y);
                return;
            }
            for (auto &node : graphArea->getNodesCollection()) {
                if (node->getRect().contains(Point(event.x, event.y))) {
                    innodedragMode = true;
                    line = new GraphLine();
                    graphArea->addLine(line
                        ->setColor(Color(255, 255, 255))
                        ->setLineWidth(4)
                    );
                    line->setPointOfBegin(PointF(node->getX() + node->getWidth() / 2 - sender->getX(), node->getY() + node->getHeight() / 2 - sender->getY()))
                        ->setPointOfEnd(PointF(event.x - sender->getX(), event.y - sender->getY()));

                    sender->update();
                    return;
                }
            }
            Point shift(prepos.x - event.x, prepos.y - event.y);

            std::vector<Rect> pts;
            for (auto &object : graphArea->getChilds()) {
                Rect r(object->getRect());
                r.inflate(Point(1, 1));
                pts.push_back(r);
                object->setX(object->getX() - shift.x);
                object->setY(object->getY() - shift.y);
            }
            //mainWindow->update();

            
            sender->update();
            

            prepos = Point(event.x, event.y);
        })
    );
    
    mainWindow->add(
        (new Panel())
        ->setBackgroundColor(Color(100, 100, 100))
        ->setMargin(Margin(10, 10, 10, 10))
        ->setVerticalAlignment(VerticalAlignment::Bottom)
        ->setAutoHeight(false)
        ->setHeight(20)
        ->add(stateLine)
    );


    //delete all button
    mainWindow->add((new Button())
        ->setLabel(L"Очитска")
        ->setBackgroundColor(Color(100, 100, 100))
        ->setMargin(Margin(10, 10, 10, 40))
        ->setVerticalAlignment(VerticalAlignment::Bottom)
        ->setHorizontalAlignment(HorizontalAlignment::Right)
        ->setAutoHeight(false)
        ->setAutoWidth(false)
        ->setHeight(30)
        ->setWidth(180)
        ->addMousePressedEvent([&](MouseEvent event, FrameElement *sender) {
            graphArea->clear();
            stateLine->setText(L"На поле " + String(graphArea->getNodesCollection().size()) + L" вершин.");
            tableAdjacency->getTable() = graphArea->getAdjacencyMatrix();
            tableAdjacency->refrash();
            mainWindow->pack();
            mainWindow->update();
        })
    );
    
    mainWindow->add((new Panel())
        ->setBackgroundColor(Color(100, 100, 100))
        ->setMargin(Margin(10, 200, 10, 40))
        ->setVerticalAlignment(VerticalAlignment::Bottom)
        ->setAutoHeight(false)
        ->setHeight(200)
        ->add((new Label())
              ->setText(L"Матрица смежности:")
              ->setMargin(0, 0, 0, 0)
        )
        ->add(tableAdjacency
              ->setColomnsNumber(3)
              ->setStringsNumber(3)
              ->setMargin(5, 5, 20, 5)
        )
    );

    mainWindow->add((new Panel())
                    ->setBackgroundColor(Color(100, 100, 100))
                    ->setMargin(Margin(10, 10, 10, 290))
                    ->setVerticalAlignment(VerticalAlignment::Stretch)
                    ->setHorizontalAlignment(HorizontalAlignment::Right)
                    ->setAutoWidth(false)
                    ->setWidth(180)
                    ->setAutoHeight(true)
                    ->add((new Label())
                          ->setText(L"Вывод:")
                          ->setMargin(0, 0, 0, 0)
                    )
                    ->add(outtable
                          ->setColomnsNumber(1)
                          ->setStringsNumber(3)
                          ->setMargin(5, 5, 20, 5)
                    )
    );



    //bfs
    mainWindow->add((new Button())
                    ->setLabel(L"BFS")
                    ->setBackgroundColor(Color(100, 100, 100))
                    ->setMargin(Margin(10, 10, 10, 80))
                    ->setVerticalAlignment(VerticalAlignment::Bottom)
                    ->setHorizontalAlignment(HorizontalAlignment::Right)
                    ->setAutoHeight(false)
                    ->setAutoWidth(false)
                    ->setHeight(30)
                    ->setWidth(85)
                    ->addMousePressedEvent([&](MouseEvent event, FrameElement *sender) {
                        if (startingNode == null) {
                            stateLine->setText(L"Выберите начальную вершину!");
                            mainWindow->update();
                            return;
                        }
                        enabledAll(false);
                        //brrep = false;
                        stateLine->setText(L"Поиск в ширину запущен...");
                        //HANDLE thread = CreateThread(NULL, 0, rep, NULL, 0, NULL);
                        HANDLE threadr = CreateThread(NULL, 0, threadbfs, NULL, 0, NULL);
                    })
    );
    
    //dfs
    mainWindow->add((new Button())
                    ->setLabel(L"DFS")
                    ->setBackgroundColor(Color(100, 100, 100))
                    ->setMargin(Margin(10, 105, 10, 80))
                    ->setVerticalAlignment(VerticalAlignment::Bottom)
                    ->setHorizontalAlignment(HorizontalAlignment::Right)
                    ->setAutoHeight(false)
                    ->setAutoWidth(false)
                    ->setHeight(30)
                    ->setWidth(85)
                    ->addMousePressedEvent([&](MouseEvent event, FrameElement *sender) {
                        if (startingNode == null) {
                            stateLine->setText(L"Выберите начальную вершину!");
                            mainWindow->update();
                            return;
                        }
                        enabledAll(false);
                        //brrep = false;
                        stateLine->setText(L"Поиск в глубину запущен...");
                        //HANDLE thread = CreateThread(NULL, 0, rep, NULL, 0, NULL);
                        HANDLE threadr = CreateThread(NULL, 0, threaddfs, NULL, 0, NULL);
                    })
    );

    //Cycle
    mainWindow->add((new Button())
                    ->setLabel(L"Эйлеров цикл")
                    ->setBackgroundColor(Color(100, 100, 100))
                    ->setMargin(Margin(10, 10, 10, 120))
                    ->setVerticalAlignment(VerticalAlignment::Bottom)
                    ->setHorizontalAlignment(HorizontalAlignment::Right)
                    ->setAutoHeight(false)
                    ->setAutoWidth(false)
                    ->setHeight(30)
                    ->setWidth(180)
                    ->addMousePressedEvent([&](MouseEvent event, FrameElement *sender) {
                        /*if (startingNode == null) {
                            stateLine->setText(L"Выберите начальную вершину!");
                            mainWindow->update();
                            return;
                        }
                        //brrep = false;
                        stateLine->setText(L"Поиск в глубину запущен...");
                        //HANDLE thread = CreateThread(NULL, 0, rep, NULL, 0, NULL);
                        HANDLE threadr = CreateThread(NULL, 0, threaddfs, NULL, 0, NULL);*/
                    })
    );

    
    mainWindow->add((new Button())
                    ->setLabel(L"Дейкстра")
                    ->setBackgroundColor(Color(100, 100, 100))
                    ->setMargin(Margin(10, 10, 10, 160))
                    ->setVerticalAlignment(VerticalAlignment::Bottom)
                    ->setHorizontalAlignment(HorizontalAlignment::Right)
                    ->setAutoHeight(false)
                    ->setAutoWidth(false)
                    ->setHeight(30)
                    ->setWidth(180)
                    ->addMousePressedEvent([&](MouseEvent event, FrameElement *sender) {
                        /*if (startingNode == null) {
                            stateLine->setText(L"Выберите начальную вершину!");
                            mainWindow->update();
                            return;
                        }
                        //brrep = false;
                        stateLine->setText(L"Поиск в глубину запущен...");
                        //HANDLE thread = CreateThread(NULL, 0, rep, NULL, 0, NULL);
                        HANDLE threadr = CreateThread(NULL, 0, threaddfs, NULL, 0, NULL);*/
                    })
    );

    mainWindow->add((new Button())
                    ->setLabel(L"Ргр")
                    ->setBackgroundColor(Color(100, 100, 100))
                    ->setMargin(Margin(10, 10, 10, 200))
                    ->setVerticalAlignment(VerticalAlignment::Bottom)
                    ->setHorizontalAlignment(HorizontalAlignment::Right)
                    ->setAutoHeight(false)
                    ->setAutoWidth(false)
                    ->setHeight(30)
                    ->setWidth(180)
                    ->addMousePressedEvent([&](MouseEvent event, FrameElement *sender) {
                        if (startingNode == null) {
                            stateLine->setText(L"Выберите начальную вершину!");
                            mainWindow->update();
                            return;
                        }
                        enabledAll(false);
                        stateLine->setText(L"Поиск максимального подграфа запущен...");
                        HANDLE threadr = CreateThread(NULL, 0, threadrgr, NULL, 0, NULL);
                    })
    );

    mainWindow->add((new Button())
                    ->setLabel(L"Матр. инцидентности")
                    ->setBackgroundColor(Color(100, 100, 100))
                    ->setMargin(Margin(10, 10, 10, 240))
                    ->setVerticalAlignment(VerticalAlignment::Bottom)
                    ->setHorizontalAlignment(HorizontalAlignment::Right)
                    ->setAutoHeight(false)
                    ->setAutoWidth(false)
                    ->setHeight(30)
                    ->setWidth(180)
                    ->addMousePressedEvent([&](MouseEvent event, FrameElement *sender) {
                        Window *matr = new Window(L"matrix", L"matrix", Size(400, 400), Color(60, 60, 60), hInstance);
                        Table *tableAcidentaly = new Table();

                        matr->add(tableAcidentaly->setColomnsNumber(3)
                                  ->setStringsNumber(3)
                                  ->setMargin(5, 5, 40, 5));

                        tableAcidentaly->getTable() = graphArea->getAcidentalyMatrix();
                        tableAcidentaly->refrash();

                        

                        matr->pack();
                        matr->run();
                    })
    );



    mainWindow->pack();
    mainWindow->run();
    
    delete mainWindow;

    

    return 0;
}

DWORD WINAPI threaddfs(LPVOID t) {
    DfsClass d(graphArea->getGraph(), mainWindow, outtable, startingNode);
    stateLine->setText(L"Поиск в глубину выполнен!");
    outtable->getTable()[0].push_back(L"Done!");
    outtable->refrash();
    Sleep(400);
    enabledAll(true);
    mainWindow->update();
    return 0;
}


DWORD WINAPI threadbfs(LPVOID t) {
    BfsClass d(graphArea->getGraph(), mainWindow, outtable, startingNode);
    stateLine->setText(L"Поиск в ширину выполнен!");
    outtable->getTable()[0].push_back(L"Done!");
    outtable->refrash();
    Sleep(400);
    enabledAll(true);
    mainWindow->update();
    return 0;
}


DWORD WINAPI threadrgr(LPVOID t) {
    RgrClass d(graphArea->getGraph(), mainWindow, outtable, startingNode);
    stateLine->setText(L"Поиск максимального подграфа выполнен!");
    outtable->getTable()[0].push_back(L"Done!");
    outtable->refrash();
    Sleep(400);
    enabledAll(true);
    mainWindow->update();
    return 0;
}
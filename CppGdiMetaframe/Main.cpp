// MetaFrame.cpp: определяет точку входа для приложения.
//

#include "stdafx.h"
#include "Main.h"

using namespace MetaFrame;
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, 
                      _In_opt_ HINSTANCE hPrevInstance,
                      _In_ LPWSTR    lpCmdLine,
                      _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);



    Window *mainWindow = new Window(L"ManaevRuslanGraph", L"Manaev Ruslan Graph", Size(800, 400), Color(60, 60, 60), hInstance);
    GraphArea *graphArea = new GraphArea();
    
    Label *stateLine = (Label*)(new Label())
        ->setText(L"На поле 0 вершин.")
        ->setHorizontalAlignment(HorizontalAlignment::Left)
        ->setVerticalAlignment(VerticalAlignment::Center)
        ->setMargin(10, 0, 0, 0);

    Point prepos = Point();


    bool innodedragMode = false;
    GraphLine *line = null;

    mainWindow->add(graphArea
        ->setBackgroundColor(Color(100, 100, 100))
        ->setMargin(Margin(10, 200, 10, 150))
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
                ->setWidth(30)
                ->setHeight(30)
                ->setX(event.x - 15)
                ->setY(event.y - 15)
                ->addMousePressedEvent([&](MouseEvent event, FrameElement *sender) {
                    if (event.shiftDown) {
                        graphArea->eraseNode((GraphNode *)sender);
                    }
                    stateLine->setText(L"На поле " + String(graphArea->getNodesCollection().size()) + L" вершин.");
                    mainWindow->update();
                })
            );
            stateLine->setText(L"На поле " + String(graphArea->getNodesCollection().size()) + L" вершин.");
            mainWindow->update();
        })
        ->addMouseReleasedEvent([&](MouseEvent event, FrameElement *sender) { 
            innodedragMode = false; 
            prepos = Point();
            
            if (line == null) {
                return;
            }
            for (auto &node : graphArea->getNodesCollection()) {
                if (node->getRect().contains((Point)line->getPointOfEnd())) {
                    line->setPointOfEnd(PointF(node->getX() + node->getWidth() / 2, node->getY() + node->getHeight() / 2));
                    mainWindow->pack();
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

            mainWindow->pack();
            mainWindow->update();
        })
        ->addMouseDraggedEvent([&](MouseEvent event, FrameElement *sender) {

            if (innodedragMode) {
                line->setPointOfEnd(PointF(event.x, event.y));
                graphArea->addLineComplite(line);
                /*Rect r = line->getRect();
                r.inflate(Point(30, 30));
                sender->invalidateRect(r);*/
                //mainWindow->update();
                sender->invalidateRect(Rect(1, 1, sender->getWidth() - 3, sender->getHeight() - 3));
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
                        ->setPointOfBegin(PointF(node->getX() + node->getWidth() / 2, node->getY() + node->getHeight() / 2))
                        ->setPointOfEnd(PointF(event.x, event.y))
                        ->setLineWidth(4)
                    );
                    /*Rect r = line->getRect();
                    r.inflate(Point(30, 30));
                    sender->invalidateRect(r);*/
                    //mainWindow->update();
                    sender->invalidateRect(Rect(1, 1, sender->getWidth() - 3, sender->getHeight() - 3));
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
            //sender->invalidateRect(sender->getRect());
            /*for (auto &object : graphArea->getChilds()) {
                sender->invalidateRect(old.back());
                old.pop_back();
            }*/
            //mainWindow->update();
            /*
            for (auto &object : pts) {
                sender->invalidateRect(object);
            }
            for (auto &object : graphArea->getChilds()) {
                sender->invalidateRect(object->getRect());
            }*/
            
            sender->invalidateRect(Rect(1, 1, sender->getWidth(), sender->getHeight()));
            

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
        ->setHeight(40)
        ->setWidth(180)
        ->addMousePressedEvent([&](MouseEvent event, FrameElement *sender) {
            graphArea->clear();
            stateLine->setText(L"На поле " + String(graphArea->getNodesCollection().size()) + L" вершин.");
            mainWindow->pack();
            mainWindow->update();
        })
    );

    mainWindow->add((new Panel())
        ->setBackgroundColor(Color(100, 100, 100))
        ->setMargin(Margin(10, 200, 10, 40))
        ->setVerticalAlignment(VerticalAlignment::Bottom)
        ->setAutoHeight(false)
        ->setHeight(100)
        ->add((new Label())
              ->setText(L"Матрица смежности:")
              ->setMargin(0, 0, 0, 0)
        )
        ->add((new Table())
              ->setColomnsNumber(3)
              ->setStringsNumber(3)
              ->setCell(L"00", 0, 0)
              ->setCell(L"01", 0, 1)
              ->setCell(L"02", 0, 2)
              ->setCell(L"10", 1, 0)
              ->setCell(L"11", 1, 1)
              ->setCell(L"12", 1, 2)
              ->setCell(L"20", 2, 0)
              ->setCell(L"21", 2, 1)
              ->setCell(L"22", 2, 2)
              ->setMargin(1, 1, 20, 1)
        )
    );



    //bfs
    mainWindow->add((new Button())
                    ->setLabel(L"Запуск bfs")
                    ->setBackgroundColor(Color(100, 100, 100))
                    ->setMargin(Margin(10, 10, 10, 90))
                    ->setVerticalAlignment(VerticalAlignment::Bottom)
                    ->setHorizontalAlignment(HorizontalAlignment::Right)
                    ->setAutoHeight(false)
                    ->setAutoWidth(false)
                    ->setHeight(40)
                    ->setWidth(180)
                    ->addMousePressedEvent([&](MouseEvent event, FrameElement *sender) {
                        graphArea->clear();
                        mainWindow->pack();
                        mainWindow->update();
                    })
    );

    //dfs
    mainWindow->add((new Button())
                    ->setLabel(L"Запуск dfs")
                    ->setBackgroundColor(Color(100, 100, 100))
                    ->setMargin(Margin(10, 10, 10, 140))
                    ->setVerticalAlignment(VerticalAlignment::Bottom)
                    ->setHorizontalAlignment(HorizontalAlignment::Right)
                    ->setAutoHeight(false)
                    ->setAutoWidth(false)
                    ->setHeight(40)
                    ->setWidth(180)
                    ->addMousePressedEvent([&](MouseEvent event, FrameElement *sender) {
        graphArea->clear();
        mainWindow->pack();
        mainWindow->update();
    })
    );







    

    mainWindow->pack();
    mainWindow->run();
    
    delete mainWindow;

    return 0;
}
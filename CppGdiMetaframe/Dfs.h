#pragma once

using namespace MetaFrame;
using namespace std;
typedef GraphNode* Node;
typedef GraphLine* Line;
//DFS


class DfsClass {
public:
    DfsClass(map<GraphNode*, map<GraphNode*, set<GraphLine*>>> graph, 
             Window *mainWindow, 
             OutTable *outtable,
             Node start
    ) 
        : mainWindow(mainWindow), 
        outtable(outtable)
    {
        this->graph = graph;
        for (auto &ob : graph) { color[ob.first] = 0; }
        outtable->getTable() = vector<vector<String>>();
        outtable->refrash();
        updateScreen();

        dfs(start);

    };
    int num = 0;
    OutTable *outtable;
    Window *mainWindow;
    vector<String> out;



    map<Node, map<Node, set<Line>>> graph; // граф

    map<Node, int> color; // цвет вершины (0, 1, или 2)

    void dfs(Node node) {
        out.push_back(String(num++) + L" -> " + node->getLabel());

        color[node] = 1;
        updateScreen();
        for (auto &v : graph[node]) {
            if (color[v.first] == 0 && v.second.size() != 0)
                dfs(v.first);
        }
        color[node] = 2;
        updateScreen();
        return;
    }




    void updateScreen() {
        outtable->getTable() = vector<vector<String>>({out});
        outtable->refrash();
        for (auto &ob : color) {
            switch (ob.second) {
                case 0:
                    ob.first->setColor(Color(160, 160, 160));
                    break;
                case 1:
                    ob.first->setColor(Color(160, 160, 0));
                    break;
                case 2:
                    ob.first->setColor(Color(50, 50, 50));
                    break;
                default:
                    break;
            }
            
        }
        Sleep(400);
        mainWindow->update();
    }

    ~DfsClass() {};

};




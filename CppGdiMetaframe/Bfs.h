#pragma once

using namespace MetaFrame;
using namespace std;
typedef GraphNode* Node;
typedef GraphLine* Line;
//Bfs


class BfsClass {
public:
    BfsClass(map<GraphNode*, map<GraphNode*, set<GraphLine*>>> graph, 
             Window *mainWindow, 
             OutTable *outtable,
             Node start
    )
        : mainWindow(mainWindow), 
        outtable(outtable)
    {
        this->graph = graph;
        for (auto &ob : graph) { used[ob.first] = 0; }
        outtable->getTable() = vector<vector<String>>();
        outtable->refrash();
        updateScreen();
        bfs(start);
    };
    int num = 0;
    OutTable *outtable;
    Window *mainWindow;
    vector<String> out;


    map<Node, map<Node, set<Line>>> graph; // граф

    map<Node, int> used; // цвет вершины (0, 1, или 2)

    void bfs(Node node) {

        queue<Node> q;
        q.push(node);
        used[node] = 1;
        while (!q.empty()) {
            Node v = q.front();
            out.push_back(String(num++) + L" -> " + v->getLabel());
            used[v] = 2;
            q.pop();
            updateScreen();
            for (auto &u : graph[v]) {
                if (used[u.first] == 0 && u.second.size() != 0) {
                    q.push(u.first);
                    used[u.first] = 1;
                    updateScreen();
                }
            }
        }
        return;
    }


    void updateScreen() {
        outtable->getTable() = vector<vector<String>>({ out });
        outtable->refrash();
        for (auto &ob : used) {
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

    ~BfsClass() {};

};




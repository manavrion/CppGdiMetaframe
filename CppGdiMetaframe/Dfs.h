#pragma once

using namespace MetaFrame;
using namespace std;
typedef GraphNode* Node;
typedef GraphLine* Line;
//DFS


class DfsClass {
public:
    DfsClass(map<GraphNode*, map<GraphNode*, set<GraphLine*>>> graph, Window *mainWindow) : mainWindow(mainWindow){
        this->graph = graph;
    };
    Window *mainWindow;


    map<GraphNode*, map<GraphNode*, set<GraphLine*>>> graph; // ����

    map<Node, int> color; // ���� ������� (0, 1, ��� 2)

    void dfs(Node node) {
        color[node] = 1;
        updateScreen();
        for (auto &v : graph[node]) {
            if (v.second.size() == 0) {
                continue;
            }
            updateScreen(v.first);
            if (color[v.first] == 0)
                dfs(v.first);
        }
        color[node] = 2;
        updateScreen();
        return;
    }


    void updateScreen(Node node) {
        Color color = node->getColor();
        node->setColor(Color(0, 255, 255));
        mainWindow->update();
        Sleep(250);
        node->setColor(color);
    }

    void updateScreen() {

        for (auto &ob : color) {
            switch (ob.second) {
                case 0:
                    ob.first->setColor(Color(0, 0, 0));
                    break;
                case 1:
                    ob.first->setColor(Color(160, 0, 0));
                    break;
                case 2:
                    ob.first->setColor(Color(50, 50, 50));
                    break;
                default:
                    break;
            }
            
        }
        Sleep(250);
        mainWindow->update();
    }

    ~DfsClass() {};

};




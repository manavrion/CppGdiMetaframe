#pragma once

#include "Panel.h"

namespace MetaFrame {

    class GraphArea : public FrameElement {
    public:

        GraphArea() {
            
        };

        virtual std::set<GraphNode*> &getNodesCollection() {
            return nodes;
        }

        virtual GraphArea *addLine(GraphLine* line) {
            this->addToBack(line);
            lines.insert(line);
            return this;
        }

        virtual GraphArea *addLineComplite(GraphLine* line) {

            GraphNode *a, *b;

            for (auto &node : nodes) {
                if (node->getRect().contains(line->getPointOfBegin())) {
                    a = node;
                }
                if (node->getRect().contains(line->getPointOfEnd())) {
                    b = node;
                }
            }

            graph[a][b].insert(line);
            graph[b][a].insert(line);



            return this;
        }


        virtual GraphArea *addNode(GraphNode* node) {
            add(node);
            nodes.insert(node);
            String a(L"a");
            while (true) {
                if (names.count(a) == 1) {
                    if (a.back() == L'z') {
                        /*if (a[0] == L'z') {
                            a.push_back(L'a');
                            for (auto &ch : a) ch = L'a';
                        }
                        a.back() = L'a';
                        a[0]++;*/
                    } else {
                        a.back()++;
                    }
                    continue;
                }
                names.insert(a);
                node->setLabel(a);
                break;
            }
            return this;
        }


        virtual GraphArea *eraseNode(GraphNode* node) {
            names.erase(node->getLabel());
            //delete node;
            
            for (auto it = childs.begin(); it != childs.end(); it++) {
                if (*it == node) {
                    childs.erase(it);
                    break;
                }
            }

            for (auto &key1 : graph) {
                for (auto &key2 : key1.second) {
                    if (key1.first == node || key2.first == node) {
                        for (auto &line : key2.second) {
                            for (auto it = childs.begin(); it != childs.end(); it++) {
                                if (*it == line) {
                                    childs.erase(it);
                                    line->getParent()->erase(line);
                                    delete line;
                                    break;
                                }
                            }

                            lines.erase(line);
                        }
                        key2.second.clear();
                    }
                }
                key1.second.erase(node);
            }
            graph.erase(node);



            nodes.erase(node);

            return this;
        }


        virtual GraphArea *eraseLine(GraphLine* line) {

            for (auto it = childs.begin(); it != childs.end(); it++) {
                if (*it == line) {
                    childs.erase(it);
                    break;
                }
            }

            lines.erase(line);

            for (auto &key1 : graph) {
                for (auto &key2 : key1.second) {
                    key2.second.erase(line);
                }
            }
            return this;
        }




    private:

        std::set<String> names;

        std::set<GraphNode*> nodes;
        std::set<GraphLine*> lines;

        std::map<GraphNode*, std::map<GraphNode*, std::set<GraphLine*>>> graph;
        
        virtual void repaint() {
            mygraphics_newGraphSys->FillRectangle(&Gdiplus::SolidBrush(this->getBackgroundColor()), Rect(0, 0, width, height));
            mygraphics_newGraphSys->DrawRectangle(&Gdiplus::Pen(Color(255, 255, 255)), Rect(0, 0, width - 1, height - 1));
            //graphics->fillRectangle(Rect(0, 0, width, height), this->getBackgroundColor());
           // graphics->drawRectangle(Rect(0, 0, width, height), Color(255, 255, 255));
        };

    public:

        std::map<GraphNode*, std::map<GraphNode*, std::set<GraphLine*>>> &getGraph() {
            return graph;
        };


        GraphNode* getSelect() {
            
            for (auto &ob : nodes) {
                if (ob->getLabel() == L"a") {
                    return ob;
                }
            }
            return null;
        }


        std::vector<std::vector<String>> getAdjacencyMatrix() {
            std::vector<std::vector<String>> matrix(nodes.size() + 1, std::vector<String>(nodes.size() + 1));

            for (auto &vec : matrix) {
                vec.resize(nodes.size() + 1);
            }

            int i = 1;
            for (auto &node : nodes) {
                matrix[0][i] = node->getLabel();
                matrix[i][0] = node->getLabel();

                int j = 1;
                for (auto &annode : nodes) {
                    if (graph[node][annode].size() >= 1) {
                        matrix[i][j] = graph[node][annode].size();
                        matrix[j][i] = graph[node][annode].size();
                    } else {
                        matrix[i][j] =graph[node][annode].size();
                        matrix[j][i] =graph[node][annode].size();
                    }
                    j++;
                }
                i++;
            }
            return matrix;
        }


        void clear() {
            childs.clear();
            nodes.clear();
            lines.clear();
            graph.clear();
            names.clear();
        }

        ~GraphArea() {
            clear();
        };
    };

}
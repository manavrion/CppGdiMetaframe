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


            int i = 1;
            while (true) {
                if (names.count(i) == 1) {
                    i++;
                    continue;
                }
                names.insert(i);
                node->setLabel(i);
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

            
            std::vector<GraphNode*> graphSorted; // sorted
            for (auto &ob : nodes) { graphSorted.push_back(ob); }
            //sort(graphSorted.begin(), graphSorted.end(), [](auto a, auto b) {return a->getLabel() < b->getLabel(); });
            sort(graphSorted.begin(), graphSorted.end(), [](auto a, auto b) {return a->getLabel().toValueInt() < b->getLabel().toValueInt(); });
            
            for (auto &node : graphSorted) {
                matrix[0][i] = node->getLabel();
                matrix[i][0] = node->getLabel();

                int j = 1;
                for (auto &annode : graphSorted) {
                    if (graph[node][annode].size() >= 1) {
                        matrix[i][j] = graph[node][annode].size();
                        matrix[j][i] = graph[node][annode].size();
                    } else {
                        matrix[i][j] = graph[node][annode].size();
                        matrix[j][i] = graph[node][annode].size();
                    }
                    j++;
                }
                i++;
            }
            return matrix;
        }


        std::vector<std::vector<String>> getAcidentalyMatrix() {
            

            std::set<std::pair<GraphNode*, GraphNode*>> lines;
            for (auto &key1 : graph) {
                for (auto &key2 : key1.second) {
                    if (key1.first == key2.first) {
                        continue;
                    }
                    if (graph[key1.first][key2.first].size() != 0) {
                        if (lines.count({ key1.first, key2.first }) == 0 && lines.count({ key2.first, key1.first }) == 0) {
                            lines.insert({ key1.first, key2.first });
                        }
                    }
                }
            }

            std::vector<GraphNode*> graphSorted; // sorted
            for (auto &ob : nodes) { graphSorted.push_back(ob); }
            //sort(graphSorted.begin(), graphSorted.end(), [](auto a, auto b) {return a->getLabel() < b->getLabel(); });
            sort(graphSorted.begin(), graphSorted.end(), [](auto a, auto b) {return a->getLabel().toValueInt() < b->getLabel().toValueInt(); });



            std::vector<std::vector<String>> matrix(lines.size() + 2, std::vector<String>(nodes.size() + 2));



            int i = 1;
            for (auto &line : lines) {
                //matrix[i][0] = graphSorted[i - 1]->getLabel();
                matrix[i][0] = line.first->getLabel() + L"-" + line.second->getLabel();

                for (int j = 0; j < graphSorted.size(); j++) {
                    matrix[0][j + 1] = graphSorted[j]->getLabel();
                    if (line.first ==  graphSorted[j] || line.second == graphSorted[j]) {
                        matrix[i][j + 1] = L"1";
                    } else {
                        matrix[i][j + 1] = L"0";
                    }
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
#pragma once

#include "Panel.h"

namespace MetaFrame {

    class GraphArea : public Panel {
    public:

        GraphArea() {};

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
            names.erase(node->getLabel().toValueInt());
            
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
                                    break;
                                }
                            }

                            lines.erase(line);
                        }
                        key2.second.clear();
                    }
                }
            }


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
        
        virtual void repaintRect(Graphics *graphics) {
            graphics->fillRectangle(Rect(0, 0, width, height), this->getBackgroundColor());
            graphics->drawRectangle(Rect(0, 0, width, height), Color(255, 255, 255));
        };

    public:

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
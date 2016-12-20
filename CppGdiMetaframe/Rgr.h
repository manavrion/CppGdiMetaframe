#pragma once

using namespace MetaFrame;
using namespace std;
typedef GraphNode* Node;
typedef GraphLine* Line;
//Rgr

struct Click : public set<Node> {
    bool operator==(const Click &c) const {
        if (c.size() == this->size()) {
            for (auto &ob : c) {
                if (this->count(ob) == 0) {
                    return false;
                }
            }
            return true;
        } else {
            return false;
        }
    }
    bool operator!=(const Click &c) const {
        return !(this->operator==(c));
    }
    bool operator<(const Click &c) const {
        if (c.size() < this->size()) {
            return true;
        } else if (c.size() > this->size()){
            return false;
        } else {
            String th;
            String cc;
            for (auto &ob : *this) {
                th += ob->getLabel();
            }
            for (auto &ob : c) {
                cc += ob->getLabel();
            }
            return th < cc;
        }
    }
    bool operator>(const Click &c) const {
        if (c.size() > this->size()) {
            return true;
        } else if (c.size() < this->size()) {
            return false;
        } else {
            String th;
            String cc;
            for (auto &ob : *this) {
                th += ob->getLabel();
            }
            for (auto &ob : c) {
                cc += ob->getLabel();
            }
            return th > cc;
        }
    }
};


class RgrClass {
public:
    RgrClass(map<GraphNode*, map<GraphNode*, set<GraphLine*>>> graph,
             Window *mainWindow,
             OutTable *outtable,
             Node start
    )
        : mainWindow(mainWindow),
        outtable(outtable) {
        this->graph = graph;
        for (auto &ob : graph) { used[ob.first] = 0; ob.first->setorder = -1; }
        outtable->getTable() = vector<vector<String>>();
        outtable->refrash();
        updateScreen();

        for (auto &ob : graph) { graphSorted.push_back(ob.first); }

        //sort(graphSorted.begin(), graphSorted.end(), [](Node &a, Node &b) {return a->getLabel() < b->getLabel(); });
        sort(graphSorted.begin(), graphSorted.end(), [](Node &a, Node &b) {return a->getLabel().toValueInt() < b->getLabel().toValueInt(); });

        Click ans = rgr();

        bool commonans = false;
        for (auto &click : unic) {
            if (click.size() == unic.begin()->size() && click != ans) {
                String ans;
                for (auto &node : click) {
                    ans += node->getLabel() + L" ";
                }
                if (!ans.empty()) {
                    if (commonans == false) {
                        out.push_back(L"ƒоп. ответы:");
                        commonans = true;
                    }
                    out.push_back(ans);
                }
            }
        }



        for (auto &ob : graph) { 
            if (ans.count(ob.first) != 0) {
                used[ob.first] = 5;
            } else {
                used[ob.first] = 0;
            }
        }
        updateScreen();

    };
    int num = 0;
    OutTable *outtable;
    Window *mainWindow;
    vector<String> out;

    vector<Node> graphSorted; // sorted

    map<Node, map<Node, set<Line>>> graph; // граф

    map<Node, int> used; // цвет вершины (0, 1, или 2)






    //alg

    set<Click> unic;//проверка на уникальность множеств

    queue<const Click*> q;

    //O(n^3 * logn)
    Click rgr() {

        //O(n)
        //ввод в очередь одноэлементных клик
        for (auto &ob : graphSorted) {
            Click c;
            c.insert(ob);
            unic.insert(c);
            q.push(&(*(unic.find(c))));
        }

        //O(n)
        while (!q.empty()) {

            const Click *nowClick = q.front();
            q.pop();
            updateScreen(*nowClick);

            set<Node> candidates;

            //O(n)
            for (auto &node : *nowClick) {

                //O(n)
                for (auto &incnode : graphSorted) {
                    //O(logn)
                    //проверка наличи€ ребра и отсутстви€ вершины в клике
                    if (graph[node][incnode].size() != 0 && nowClick->count(incnode) == 0) {
                        candidates.insert(incnode);
                    }
                }
            }

            set<Node> deleting; //удал€емые вершины
            //O(n)
            for (auto &candidate : candidates) {
                //O(n)
                //проверка на наличие дорог ко всем элементам из клики
                for (auto &nodeIntoClick : *nowClick) {
                    //O(logn)
                    if (graph[nodeIntoClick][candidate].size() == 0) {
                        deleting.insert(candidate);
                    }
                }
            }

            for (auto &del : deleting) {
                candidates.erase(del);
            }





            int nwsize = -1;
            //O(m)
            //все кандидаты валидны, сделаем новые клики
            for (auto &candidatenode : candidates) {
                Click nwclick = *nowClick;
                //O(logn)
                nwclick.insert(candidatenode);

                if (unic.count(nwclick) == 0) {
                    unic.insert(nwclick);
                    q.push(&(*(unic.find(nwclick))));
                    nwsize = nwclick.size();
                }
            }

            if (nwsize != -1) {
                unic.erase(*nowClick);
            }
            
        }

        //завершение работы
        return *(unic.begin());
    }


    void updateScreen(const Click &click, Node node) {
        for (auto &ob : graph) {
            if (click.count(ob.first) != 0) {
                used[ob.first] = 5;
            } else {
                used[ob.first] = 0;
            }
        }
        used[node] = 1;
        updateScreen();
    }

    void updateScreen(const Click &click) {
        for (auto &ob : graph) {
            if (click.count(ob.first) != 0) {
                used[ob.first] = 5;
            } else {
                used[ob.first] = 0;
            }
        }
        updateScreen();
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
                case 5:
                    ob.first->setColor(Color(160, 50, 50));
                    break;
                default:
                    break;
            }

        }
        Sleep(600);
        mainWindow->update();
    }

    ~RgrClass() {};

};




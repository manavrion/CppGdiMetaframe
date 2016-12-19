#pragma once
#include "Panel.h"
namespace MetaFrame {

    class OutTable : public Panel {

    public:
        OutTable() : n(), m() {};

        OutTable *setColomnsNumber(int m) {
            this->m = m;
            for (auto &ob : table) {
                ob.resize(m);
            }
            build();
            return this;
        }

        OutTable *setStringsNumber(int n) {
            this->n = n;
            table.resize(n);
            for (auto &ob : table) {
                ob.resize(m);
            }
            build();
            return this;
        }

        OutTable *setCell(String s, int i, int j) {
            table[i][j] = s;
            labeltable[i][j]
                ->setText(s)
                ->setX(40 * i)
                ->setY(20 * j)
                ->setHorizontalAlignment(HorizontalAlignment::Absolute)
                ->setVerticalAlignment(VerticalAlignment::Absolute);
            return this;
        }


        void refrash() {
            n = table.size();
            m = (n == 0 ? 0 : table[0].size());
            build();
            for (int i = 0; i < table.size(); i++) {
                for (int j = 0; j < table[i].size(); j++) {
                    setCell(table[i][j], i, j);
                }
            }
        }

    protected:
        int n;
        int m;
        std::vector<std::vector<String>> table;
        std::vector<std::vector<Label*>> labeltable;


        OutTable *build() {
            childs.clear();
            labeltable.clear();
            labeltable.resize(n);
            for (auto &ob : labeltable) {
                ob.resize(m);
                for (auto &obj : ob) {
                    obj = new Label();
                    add(obj);
                }
            }
            return this;
        }

        virtual void repaint(Graphics *graphics) {
            //graphics->fillRectangle(Rect(0, 0, width, height), this->getBackgroundColor());
            //graphics->drawRectangle(Rect(0, 0, width, height), Color(255, 255, 255));
            //graphics->drawLine(PointF(3, 20), PointF(40 * n, 20), Color(255, 255, 255), 1);
            //graphics->drawLine(PointF(40, 3), PointF(40, 20 * m), Color(255, 255, 255), 1);
        };

    public:
        std::vector<std::vector<String>>& getTable() {
            return table;
        };

        ~OutTable() {
            childs.clear();
            labeltable.clear();
        };

    };

}
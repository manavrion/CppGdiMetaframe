#pragma once

#include "FrameElement.h"

namespace MetaFrame {


    class GraphNode : public FrameElement {
    public:
        GraphNode() : label(null){
            this->setHorizontalAlignment(HorizontalAlignment::Absolute);
            this->setVerticalAlignment(VerticalAlignment::Absolute);
            this->setAutoWidth(false);
            this->setAutoHeight(false);
        };

        Label *label;

        GraphNode *setLabel(String text) {
            if (label == nullptr) {
                label = new Label();
                this->add(label);
                label->setColor(Color(0, 0, 0))
                    ->setMargin(10, 10, 10, 10)
                    ->setHorizontalAlignment(HorizontalAlignment::Center)
                    ->setVerticalAlignment(VerticalAlignment::Center)
                    ->setY(15)
                    ->setX(15)
                    ->setAutoHeight(false)
                    ->setAutoWidth(false);
            }
            label->setText(text);
            this->pack();
            return this;
        }
        String getLabel() {
            return label->getText();
        };

        
        void setDefColor() {
            
        }

        void setColor(Color color = Color(120, 120, 120)) {
            this->color = color;
        }

        Color getColor() {
            return color;
        }

        int setorder = -1;
    private:

        Color color = Color(120, 120, 120);
        virtual void repaint() {
            mygraphics_newGraphSys->Clear(Color(0, 0, 0, 0));

            mygraphics_newGraphSys->SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);
            mygraphics_newGraphSys->FillEllipse(&Gdiplus::SolidBrush(Color(0, 0, 0)), Rect(7, 7, width - 7*2, height - 7*2));
            mygraphics_newGraphSys->FillEllipse(&Gdiplus::SolidBrush(color), Rect(8, 8, width -8*2, height- 8*2));

            if (label != null) {
                if (Color(50, 50, 50) == color) {
                    label->setColor(Color(255, 255, 255));
                } else {
                    label->setColor(Color(0, 0, 0));
                }
            }
            



            //mygraphics_newGraphSys->Clear(Color(0, 0, 0, 0));
            if (setorder != -1) {
                mygraphics_newGraphSys->SetTextRenderingHint(Gdiplus::TextRenderingHint::TextRenderingHintAntiAlias);
                mygraphics_newGraphSys->DrawString(String(setorder), -1, new Gdiplus::Font(L"Arial", 12), PointF(0, 0), &Gdiplus::SolidBrush(Color(170, 0, 0)));

            }


            //graphics->fillEllipse(Rect(0, 0, width, height), Color(0, 0, 0));
            
            //graphics->fillEllipse(Rect(1, 1, width - 2, height - 2), color);
        };

    public:
        ~GraphNode() {
            delete label;
        };
    };


}
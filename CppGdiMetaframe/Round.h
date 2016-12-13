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

        GraphNode *setLabel(String text);
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

    private:
        Color color = Color(120, 120, 120);
        virtual void repaintRect(Graphics *graphics) {
            graphics->fillEllipse(Rect(0, 0, width, height), Color(0, 0, 0));
            
            graphics->fillEllipse(Rect(1, 1, width - 2, height - 2), color);
        };

    public:
        ~GraphNode() {
            delete label;
        };
    };


}
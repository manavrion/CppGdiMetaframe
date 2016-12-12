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

        virtual void repaintRect(Graphics *graphics) {
            graphics->fillEllipse(Rect(0, 0, width, height), Color(0, 0, 0));
            
            graphics->fillEllipse(Rect(1, 1, width - 2, height - 2), this->getBackgroundColor());
        };

        ~GraphNode() {
            delete label;
        };
    };


}
#include "stdafx.h"
#include "Round.h"


namespace MetaFrame {

    GraphNode *GraphNode::setLabel(String text) {
        if (label == nullptr) {
            label = new Label();
            this->add(label);
            label->setColor(Color(0, 0, 0))
                ->setMargin(10, 10, 10, 10)
                ->setHorizontalAlignment(HorizontalAlignment::Center)
                ->setVerticalAlignment(VerticalAlignment::Absolute)
                ->setY(7)
                ->setAutoHeight(false)
                ->setAutoWidth(false);
        }
        label->setText(text);
        this->pack();
        return this;
    }
}
#pragma once

#include "FrameElement.h"

namespace MetaFrame {

    class Panel : public FrameElement {
    public:
        Panel() : FrameElement() {};

        virtual void repaintRect(Graphics *graphics) {
            graphics->fillRectangle(Rect(0, 0, width, height), this->getBackgroundColor());
            graphics->drawRectangle(Rect(0, 0, width, height), Color(255, 255, 255));
        };

        ~Panel() {};
    };

}
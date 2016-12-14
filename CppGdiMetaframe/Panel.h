#pragma once

#include "FrameElement.h"

namespace MetaFrame {

    class Panel : public FrameElement {
    public:
        Panel() : FrameElement() {};

        virtual void repaintMyRect() {
            mygraphics_newGraphSys->Clear(Color(0, 0, 0, 0));
            mygraphics_newGraphSys->FillRectangle(&Gdiplus::SolidBrush(this->getBackgroundColor()), Rect(0, 0, width, height));
            mygraphics_newGraphSys->DrawRectangle(&Gdiplus::Pen(Color(255, 255, 255)), Rect(0, 0, width-1, height-1));

            //mygraphics->FillRectangle(&Gdiplus::Brush(this->getBackgroundColor()), Rect(0, 0, width, height));

           // mygraphics->DrawRectangle(Rect(0, 0, width, height), Color(255, 255, 255));
        };

        ~Panel() {};
    };

}
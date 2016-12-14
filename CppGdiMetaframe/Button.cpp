#include "stdafx.h"
#include "Button.h"

namespace MetaFrame {


    Button::Button() 
        : FrameElement(), label(nullptr)
    {
        state = ElementState::NORMAL;
        registerMouseEnteredEvent;
        registerMouseExitedEvent;
        registerMousePressedEvent;
        registerMouseReleasedEvent;
    }

   Button *Button::setLabel(String text) {
        if (label == nullptr) {
            label = new Label();
            this->add(label);
            label->setColor(Color(0, 0, 0))
                ->setMargin(10, 10, 10, 10)
                ->setHorizontalAlignment(HorizontalAlignment::Center)
                ->setVerticalAlignment(VerticalAlignment::Center)
                ->setAutoHeight(false)
                ->setAutoWidth(false);
        }
        label->setText(text);
        this->pack();
        return this;
    }

    void Button::repaintMyRect() {
        mygraphics_newGraphSys->Clear(Color(0, 0, 0, 0));
        switch (state) {
            case MetaFrame::ElementState::NORMAL:
                mygraphics_newGraphSys->FillRectangle(&Gdiplus::SolidBrush(normal), Rect(0, 0, width, height));
                break;
            case MetaFrame::ElementState::SELECTED:
                mygraphics_newGraphSys->FillRectangle(&Gdiplus::SolidBrush(selected), Rect(0, 0, width, height));
                break;
            case MetaFrame::ElementState::PRESSED:
                mygraphics_newGraphSys->FillRectangle(&Gdiplus::SolidBrush(pressed), Rect(0, 0, width, height));
                break;
            case MetaFrame::ElementState::FOCUSED:
                mygraphics_newGraphSys->FillRectangle(&Gdiplus::SolidBrush(focused), Rect(0, 0, width, height));
                break;
            case MetaFrame::ElementState::DISABLED:
                mygraphics_newGraphSys->FillRectangle(&Gdiplus::SolidBrush(disabled), Rect(0, 0, width, height));
                break;
            default:
                break;
        }
    }


    void Button::mouseEntered(const MouseEvent &event, FrameElement *sender) {
        state = ElementState::SELECTED;
        update();
        //invalidateRect(Rect(0, 0, width, height));
    }

    void Button::mouseExited(const MouseEvent &event, FrameElement *sender) {
        state = ElementState::NORMAL;
        update();
        //invalidateRect(Rect(0, 0, width, height));
    }

    void Button::mousePressed(const MouseEvent &event, FrameElement *sender) {
        state = ElementState::PRESSED;
        update();
        //invalidateRect(Rect(0, 0, width, height));
    }

    void Button::mouseReleased(const MouseEvent &event, FrameElement *sender) {
        state = ElementState::SELECTED;
        update();
        //invalidateRect(Rect(0, 0, width, height));
    }

    Button::~Button() {
        if (label != null) {
            delete label;
        }
    }

}
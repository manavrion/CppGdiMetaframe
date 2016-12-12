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

    void Button::repaintRect(Graphics *graphics) {
        switch (state) {
            case MetaFrame::ElementState::NORMAL:
                graphics->fillRectangle(Rect(0, 0, width, height), normal);
                break;
            case MetaFrame::ElementState::SELECTED:
                graphics->fillRectangle(Rect(0, 0, width, height), selected);
                break;
            case MetaFrame::ElementState::PRESSED:
                graphics->fillRectangle(Rect(0, 0, width, height), pressed);
                break;
            case MetaFrame::ElementState::FOCUSED:
                graphics->fillRectangle(Rect(0, 0, width, height), focused);
                break;
            case MetaFrame::ElementState::DISABLED:
                graphics->fillRectangle(Rect(0, 0, width, height), disabled);
                break;
            default:
                break;
        }
    }


    void Button::mouseEntered(const MouseEvent &event, FrameElement *sender) {
        state = ElementState::SELECTED;
        invalidateRect(Rect(0, 0, width, height));
    }

    void Button::mouseExited(const MouseEvent &event, FrameElement *sender) {
        state = ElementState::NORMAL;
        invalidateRect(Rect(0, 0, width, height));
    }

    void Button::mousePressed(const MouseEvent &event, FrameElement *sender) {
        state = ElementState::PRESSED;
        invalidateRect(Rect(0, 0, width, height));
    }

    void Button::mouseReleased(const MouseEvent &event, FrameElement *sender) {
        state = ElementState::SELECTED;
        invalidateRect(Rect(0, 0, width, height));
    }

    Button::~Button() {
        if (label != null) {
            delete label;
        }
    }

}
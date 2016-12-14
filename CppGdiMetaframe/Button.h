#pragma once
#include "KeyEvent.h"
#include "ThemeManager.h"
#include "Label.h"
namespace MetaFrame {

    class Button : public FrameElement {

    public:
        Button();

        Button *setLabel(String text);

    protected:

        ElementState state;
        Color normal = Color(160, 160, 160);
        Color selected = Color(190, 190, 190);
        Color pressed = Color(120, 120, 120);
        Color focused;
        Color disabled;

        Label *label;


        void repaintMyRect();

        //event
        void mouseEntered(const MouseEvent &event, FrameElement *sender);
        void mouseExited(const MouseEvent &event, FrameElement *sender);
        void mousePressed(const MouseEvent &event, FrameElement *sender);
        void mouseReleased(const MouseEvent &event, FrameElement *sender);

    public:
        ~Button();

    };

}
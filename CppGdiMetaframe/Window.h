#pragma once
namespace MetaFrame {

    class Window  : public FrameElement, public SystemWindow {

    public:
        Window(String windowClassName, String title, Size size, Color background, HINSTANCE hInstance);

        virtual FrameElement *setRect(Rect r);
        virtual FrameElement *setLocation(Point p);
        virtual FrameElement *setSize(Size p);

        void update();

    protected:

        void invalidateRect(Rect invalidRect);

        void repaintRect(Graphics *graphics);

    private:
        Size oldSize;

        void wmPaintBackBufferEvent();
        void wmSize(Size &size);

        void wmKeyDown(const KeyEvent &event);
        void wmKeyUp(const KeyEvent &event);
        void wmKeyTyped(const KeyEvent &event);

        void wmMouseDoubleClick(const MouseEvent &event);
        void wmMouseEnter(const MouseEvent &event);
        void wmMouseExit(const MouseEvent &event);
        void wmMousePress(const MouseEvent &event);
        void wmMouseRelease(const MouseEvent &event);

        void wmMouseDrag(const MouseEvent &event);
        void wmMouseMove(const MouseEvent &event);

        void wmMouseWheelMove(const MouseEvent &event);



    public:
        ~Window();
    };


}
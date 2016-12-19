#pragma once
namespace MetaFrame {

    class Window  : public FrameElement, public SystemWindow {

    public:
        Window(String windowClassName, String title, Size size, Color background, HINSTANCE hInstance);

        virtual FrameElement *setRect(Rect r);
        virtual FrameElement *setLocation(Point p);
        virtual FrameElement *setSize(Size p);



        //////////////////////////////////////////////
        //render
        //��� ����
        void paintBackBuffer() {
            return;
        };

        void hWindowBind(HWND hWindow) {
            hwndhhhg = hWindow; //�������� ������
        }

        /*virtual void update() {
            isvalid = true;
            invalidateScreenRectEvent();
        }*/

        virtual void invalidateScreenRectEvent() {
            invalidateScreenRect();
        }

    protected:
        //��� �����
        virtual void repaint() {
            repaintMyRect();
            for (size_t i = 0; i < childs.size(); i++) {
                childs[i]->repaint();
            }
            
            //parent->mygraphics_newGraphSys->DrawImage(bitmap, getRect());
        };

        virtual void repaintMyRect() {
            mygraphics_newGraphSys->FillRectangle(&Gdiplus::SolidBrush(this->getBackgroundColor()), Rect(0, 0, width, height));
        };

        /*
        void update();

        void updateAsync();

        bool ggblock = false;
        */
    protected:

        //void invalidateRect(Rect invalidRect);

        //void repaintMyRect(Graphics *graphics);

    private:
        Size oldSize;

        void wmPaintBackBufferEvent();

    public:
        //void wmRepaintAll();

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
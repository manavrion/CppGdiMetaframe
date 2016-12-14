#pragma once
#include <windows.h>

namespace MetaFrame {

    struct SystemEventInfo {
        SystemEventInfo(HWND hWindows, UINT message, WPARAM wParam, LPARAM lParam)
            : hWindow(hWindows), message(message), wParam(wParam), lParam(lParam) {
        }
        HWND hWindow;
        UINT message;
        WPARAM wParam;
        LPARAM lParam;
    };


    class SystemWindow {
    public:
        SystemWindow(String windowClassName, String title, Size size, Color background, HINSTANCE hInstance);

        String title;           // текст строки заголовка
        String windowClassName; // им€ класса главного окна
    protected:
        Graphics *graphics;

        void invalidateScreenRect(const Rect &rect);
        void invalidateScreenRect();

        void setWindowRect(const Rect &rect);
        Rect getWindowRect();
        HWND hWindow; //дескриптор экземпл€ра окна
    private:
        HINSTANCE hInstance;    // текущий экземпл€р
        HACCEL hAccelTable;     // таблица гор€чих клавиш



        virtual void wmPaintBackBufferEvent() = 0;
        virtual void wmSize(Size &size) = 0;

        virtual void wmRepaintAll() = 0;

        //input events
        virtual void wmKeyDown(const KeyEvent &event) = 0;
        virtual void wmKeyUp(const KeyEvent &event) = 0;
        virtual void wmKeyTyped(const KeyEvent &event) = 0;

        virtual void wmMouseDoubleClick(const MouseEvent &event) = 0;
        virtual void wmMouseEnter(const MouseEvent &event) = 0;
        virtual void wmMouseExit(const MouseEvent &event) = 0;
        virtual void wmMousePress(const MouseEvent &event) = 0;
        virtual void wmMouseRelease(const MouseEvent &event) = 0;

        virtual void wmMouseDrag(const MouseEvent &event) = 0;
        virtual void wmMouseMove(const MouseEvent &event) = 0;

        virtual void wmMouseWheelMove(const MouseEvent &event) = 0;


        MouseEvent createMouseEvent(SystemEventInfo eventInfo);
    public:
        int run();
        int runWithNewStream();




    private:
        static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
        LRESULT WndProcLocal(SystemEventInfo &eventInfo);
    public:
        ~SystemWindow();
    };

}
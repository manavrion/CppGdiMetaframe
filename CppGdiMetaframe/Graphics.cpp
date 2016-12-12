#include "stdafx.h"
#include <windows.h>
#include <ctime>
#include "Graphics.h"

#include "MetaFrame.h"
#include "MetaTypes.h"



namespace MetaFrame {
    void Graphics::paintBackBuffer(const Rect & rect) {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWindow, &ps);

        //int tm = System.timeOfBeginingPaint;
        graphics->FillRectangle(&Gdiplus::SolidBrush(Color(0, 0, 80)), Rect(0, 0, 70, 40));
        graphics->DrawString(String(clock() - System.timeOfBeginingPaint) + String(L" ms  \n~") + String(1000 / (clock() - System.timeOfBeginingPaint + 1)) + String(L" fps"), -1, &Gdiplus::Font(L"Arial", 12), (Gdiplus::RectF)Rect(0, 0, 300, 50), &Gdiplus::StringFormat(), &Gdiplus::SolidBrush(Color(255, 255, 255)));
        System.timeOfBeginingPaint = 0;

        BitBlt(hdc, 0, 0, size.width, size.height, backBufferHDC, 0, 0, SRCCOPY);


        EndPaint(hWindow, &ps);
    }
}
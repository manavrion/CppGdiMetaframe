#include "stdafx.h"
#include "MetaFrame.h"
#include "System.h"



namespace MetaFrame {

    SystemImpl System;

    SystemImpl::SystemImpl() : timeOfBeginingPaint(0), graphics(null){
        // Initialize GDI+.
        Gdiplus::GdiplusStartupInput gdiplusStartupInput;
        ULONG_PTR           gdiplusToken;
        Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
    }




    SystemImpl::~SystemImpl() {
    }
}

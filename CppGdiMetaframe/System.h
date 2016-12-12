#pragma once
#include "Graphics.h"
namespace MetaFrame {

    class SystemImpl {
    public:
        SystemImpl();

        int timeOfBeginingPaint;

        Graphics *graphics;

        ~SystemImpl();
    };

    extern SystemImpl System;

}



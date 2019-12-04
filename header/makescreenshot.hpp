#pragma once
#include <string>
#include <stdio.h>

struct DisplayObject;
struct WindowObject;

class ScreenShot
{
    public:
        void make_screenshot(const DisplayObject& display, const WindowObject& window, std::string savePath);
};


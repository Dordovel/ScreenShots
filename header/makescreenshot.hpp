#pragma once
#include <string>
#include <stdio.h>

struct DisplayObject;
struct WindowObject;
struct ImageObject;

class ScreenShot
{
    public:
        void make_screenshot(const ImageObject& image, std::string savePath);
};


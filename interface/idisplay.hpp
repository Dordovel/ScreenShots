#pragma once
#include <vector>

struct DisplayObject;
struct WindowObject;
struct ImageObject;

class IMainDisplay
{
    public:
        virtual WindowObject get_main_window() = 0;
        virtual DisplayObject get_main_display() = 0;
        virtual ImageObject show(const std::vector<WindowObject>& windowList) = 0;
        virtual ~IMainDisplay() = default;
};
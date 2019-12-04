#pragma once

struct DisplayObject;
struct WindowObject;

class IMainDisplay
{
    public:
        virtual WindowObject get_main_window() = 0;
        virtual DisplayObject get_main_display() = 0;
        virtual ~IMainDisplay() = default;
};
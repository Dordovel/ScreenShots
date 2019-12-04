#pragma once

#include "../interface/idisplay.hpp"
#include "../struct/object.hpp"

class MainDisplay: public IMainDisplay
{
    private:
        DisplayObject _display;
        WindowObject _window;

    public:
        WindowObject get_main_window() override;
        DisplayObject get_main_display() override;
        MainDisplay();
        ~MainDisplay() = default;
};

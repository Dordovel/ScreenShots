#pragma once

#include "../interface/idisplay.hpp"
#include "../struct/object.hpp"

class MainDisplay: public IMainDisplay
{
    private:
        DisplayObject _display;
        WindowObject _window;
        WindowObject _mainWindow;

    public:
        WindowObject get_main_window() override;
        DisplayObject get_main_display() override;
        void show(std::vector<WindowObject> windowList) override;
        MainDisplay();
        ~MainDisplay() = default;
};

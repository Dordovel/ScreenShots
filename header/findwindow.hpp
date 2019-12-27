#pragma once
#include "../interface/iwindowproperty.hpp"
#include "memory"
#include "../interface/ifindwindow.hpp"
#include "../struct/object.hpp"

class FindWindowObject: public IFindWindow
{
    private:
        WindowObject _rootWindow;
        DisplayObject _display;
        std::shared_ptr<IWindowProperty> _windowProperty;

        bool check_window_name(const WindowObject& window, std::string foundName);
        
    public:
        FindWindowObject(std::shared_ptr<IWindowProperty> windowProperty, DisplayObject display, WindowObject rootWindow);
        std::vector<WindowObject> search_window(std::string searchWindowName = "") override;
};
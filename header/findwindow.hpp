#pragma once
#include "../interface/iwindowproperty.hpp"
#include "memory"
#include "../interface/ifindwindow.hpp"
#include "../struct/object.hpp"

class FindWindow: public IFindWindow
{
    private:
        WindowObject _rootWindow;
        DisplayObject _display;
        std::shared_ptr<IWindowProperty> _windowProperty;
        std::string _propertyForGetWindowList = "_NET_CLIENT_LIST";
        std::string _propertyForGetWindowName = "_NET_WM_NAME";

        bool check_window_name(const WindowObject& window, std::string foundName);
        
    public:
        FindWindow(std::shared_ptr<IWindowProperty> windowProperty, DisplayObject display, WindowObject rootWindow);
        std::vector<WindowObject> search_window(std::string searchWindowName = "") override;
};
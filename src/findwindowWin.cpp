#include "../header/findwindow.hpp"

#if _WIN32

    #include <iostream>
    #include <string.h>
    #include "../struct/object.hpp"

    FindWindowObject::FindWindowObject(std::shared_ptr<IWindowProperty> windowProperty, 
                                DisplayObject display, 
                                WindowObject window):_rootWindow(window),
                                                        _display(display),
                                                        _windowProperty(windowProperty)
    {}

    std::vector<WindowObject> FindWindowObject::search_window(std::string searchWindowName)
    {
        std::vector<WindowObject> windowList = this->_windowProperty->get_window_list(this->_display,
                                                                            this->_rootWindow);


        if(!searchWindowName.empty() && !windowList.empty())
        {
            std::vector<WindowObject> searchList;
            for(WindowObject WindowObject : windowList)
            {
                if(this->check_window_name(WindowObject, searchWindowName))
                {
                    searchList.push_back(WindowObject);
                }
            }

            return searchList;

        }

        return windowList;

    }

    bool FindWindowObject::check_window_name(const WindowObject& window, std::string foundName)
    {
        std::string windowName = this->_windowProperty->get_window_name(this->_display,
                                                                                window);

        if(!windowName.empty())
        {
            if(windowName.find(foundName) != std::string::npos)
            {
                return true;
            }
        }
        return false;
    }

#endif
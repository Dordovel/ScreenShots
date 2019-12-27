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
    	std::vector<WindowObject> windowList;
        
        HWND* result = (HWND*)this->_windowProperty->get_window_property(this->_display,
                                                                            this->_rootWindow,
                                                                            Property::WINDOW_HANDLER);

        unsigned long count = this->_windowProperty->get_found_object_count();
        
        int iter = 0;
        for(; iter < count; ++iter)
        {
            windowList.push_back( WindowObject{ result [iter] } );
        }

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
        char* windowName = (char*)this->_windowProperty->get_window_property(this->_display,
                                                                                window,
                                                                                Property::WINDOW_NAME);

        if(windowName != NULL)
        {
            std::string temp(windowName);
            if(temp.find(foundName) == 0)
            {
                return true;
            }
        }
        return false;
    }

#endif
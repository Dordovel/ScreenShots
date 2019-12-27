#include "../header/windowproperty.hpp"

#if __linux__

    #include "../struct/object.hpp"

    unsigned long WindowProperty::get_found_object_count() noexcept
    {
        return this->_itemCount;
    }

    void* WindowProperty::get_window_property(const DisplayObject& display, const WindowObject& window, Property propertyName) noexcept
    {
        std::string property;

        if(propertyName == Property::WINDOW_HANDLER)
        {
            property = "_NET_CLIENT_LIST";
        }else if(propertyName == Property::WINDOW_NAME)
        {
            property = "_NET_WM_NAME";
        }

        Atom actual_type, filter_atom;
        int actual_format, status;
        unsigned long bytes_after;
        unsigned char* data;

        filter_atom = XInternAtom(display._display,
                                    property.c_str(),
                                    true);

        status = XGetWindowProperty(display._display,
                                    window._window,
                                    filter_atom,
                                    0,
                                    1000,
                                    False,
                                    AnyPropertyType,
                                    &actual_type,
                                    &actual_format,
                                    &this->_itemCount,
                                    &bytes_after,
                                    &data);

        if(status != 0)
        {
            printf("Error: %d", status);
        }
        return data;
    }

#endif
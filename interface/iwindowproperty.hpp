#pragma once
#include <string>

struct DisplayObject;
struct WindowObject;

class IWindowProperty
{
    public:
        virtual unsigned long get_found_object_count() = 0;
        virtual unsigned char* get_window_property(const DisplayObject& display,
                                                    const WindowObject& window,
                                                    std::string propertyName) = 0;
        virtual ~IWindowProperty() = default;
};
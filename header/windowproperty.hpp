#pragma once
#include "../interface/iwindowproperty.hpp"

class WindowProperty:public IWindowProperty
{
    private:
        unsigned long _itemCount;

    public:
        unsigned long get_found_object_count() noexcept override;
        unsigned char* get_window_property(const DisplayObject& display, const WindowObject& window, std::string propertyName) noexcept override;
        ~WindowProperty() = default;
};
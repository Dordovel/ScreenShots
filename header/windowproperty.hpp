#pragma once
#include "../interface/iwindowproperty.hpp"

class WindowProperty:public IWindowProperty
{
    private:
        unsigned long _itemCount;

        void* get_window_property(const DisplayObject& display,
                                            const WindowObject& window,
                                            Property propertyName) noexcept;
        

    public:
        unsigned long get_found_object_count() noexcept override;
        std::vector<WindowObject> get_window_list(const DisplayObject& display,
                                                    const WindowObject& window) override;

        std::string get_window_name(const DisplayObject& display,
                                                    const WindowObject& window) override;
        
        ~WindowProperty() = default;
};
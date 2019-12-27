#pragma once
#include <string>

struct DisplayObject;
struct WindowObject;

enum Property
{
	WINDOW_HANDLER,
	WINDOW_NAME
};

class IWindowProperty
{
    public:
        virtual unsigned long get_found_object_count() = 0;
        virtual void* get_window_property(const DisplayObject& display,
                                                    const WindowObject& window,
                                                    Property propertyName) = 0;
        virtual ~IWindowProperty() = default;
};
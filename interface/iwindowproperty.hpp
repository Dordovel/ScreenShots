#pragma once
#include <string>
#include <vector>

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
        virtual std::vector<WindowObject> get_window_list(const DisplayObject& display,
                                                    const WindowObject& window) = 0;

        virtual std::string get_window_name(const DisplayObject& display,
                                                    const WindowObject& window) = 0;
        virtual ~IWindowProperty() = default;
};
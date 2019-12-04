#pragma once

#if __linux__

    #include <X11/Xlib.h>

    struct DisplayObject
    {
        Display* _display;
    };

    struct WindowObject
    {
        Window _window;
    };

#endif
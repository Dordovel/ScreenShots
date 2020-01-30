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

    struct ImageObject
    {
        XImage* _image;
    };

#endif

#if _WIN32

    #include <windows.h>
    #include <vector>

    struct DisplayObject
    {
        HDC _display;
    };

    struct WindowObject
    {
        HWND _window;
    };

    struct ImageObject
    {
        HWND _image;
        HBITMAP _hBitmap;
    };

#endif
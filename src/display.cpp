#include "../header/display.hpp"

#if __linux__

    #include "X11/Xlib.h"

    MainDisplay::MainDisplay()
    {
        this->_display._display = XOpenDisplay(NULL);
        int fd_screen = XDefaultScreen(this->_display._display);
        this->_window._window = RootWindow(this->_display._display, fd_screen);
    }

    WindowObject MainDisplay::get_main_window()
    {
        return this->_window;
    }

    DisplayObject MainDisplay::get_main_display()
    {
        return this->_display;
    }

#endif
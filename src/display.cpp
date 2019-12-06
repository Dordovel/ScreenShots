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

    void MainDisplay::show()
    {
        XWindowAttributes windowAttr;
        int fd_screen = -1;
        fd_screen = DefaultScreen(this->_display._display);

        XGetWindowAttributes(this->_display._display, this->_window._window, &windowAttr);

        this->_mainWindow._window = XCreateSimpleWindow(this->_display._display, this->_window._window,
                                                    0, 0, windowAttr.width, windowAttr.height, 1, 
                                                    BlackPixel(this->_display._display, fd_screen),
                                                    WhitePixel(this->_display._display, fd_screen));

        XImage* image = XGetImage(this->_display._display, this->_window._window,0 ,0, windowAttr.width, windowAttr.height, XAllPlanes() ,ZPixmap);

        GC gc =  XDefaultGC(this->_display._display, fd_screen);

        XSelectInput(this->_display._display, this->_mainWindow._window, ExposureMask | KeyPressMask);

        XMapWindow(this->_display._display, this->_mainWindow._window);

        XEvent event;

        bool windowIsOpen = true;

        while (windowIsOpen)
        {
            XNextEvent(this->_display._display, &event);

            if(event.type == Expose)
            {
                XPutImage(this->_display._display, this->_mainWindow._window, gc, image, 0, 0, 0, 0, windowAttr.width, windowAttr.height);
            }
            
            if(event.type == KeyPress)
            {
                windowIsOpen = false;
            }
        }

        XCloseDisplay(this->_display._display);
    }

#endif
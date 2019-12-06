#include "../header/display.hpp"
#include <iostream>

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

    ImageObject MainDisplay::show(const std::vector<WindowObject>& windowList)
    {
        std::vector<XImage*> imageList;
        XImage* image;
        XWindowAttributes windowAttr;
        int windowListIter = 0;
        int fd_screen = -1;
        fd_screen = DefaultScreen(this->_display._display);

        this->_mainWindow._window = XCreateSimpleWindow(this->_display._display, this->_window._window,
                                                    0, 0, 600, 600, 1, 
                                                    BlackPixel(this->_display._display, fd_screen),
                                                    WhitePixel(this->_display._display, fd_screen));
        
        for(WindowObject object : windowList)
        {
            XGetWindowAttributes(_display._display, object._window, &windowAttr);

            imageList.push_back(
                    XGetImage(this->_display._display, object._window, 0, 0,
                                windowAttr.width, windowAttr.height, XAllPlanes(), ZPixmap)
                );
        }

        GC gc =  XDefaultGC(this->_display._display, fd_screen);

        XSelectInput(this->_display._display, this->_mainWindow._window, ExposureMask | KeyPressMask);

        XMapWindow(this->_display._display, this->_mainWindow._window);

        XEvent event;

        bool windowIsOpen = true;
        bool showImage = true;

        while (windowIsOpen)
        {
            XNextEvent(this->_display._display, &event);

            if(showImage)
            {   
                XClearWindow(this->_display._display, this->_mainWindow._window);

                image = imageList.at(windowListIter);

                XPutImage(this->_display._display, this->_mainWindow._window,
                                gc, image, 0, 0, 0, 0, image->width, image->height);

                showImage = false;
            }

            if(event.type == Expose)
            {
                showImage = true;
            }

            if(event.type == KeyPress)
            {
                if(event.xkey.keycode == 114)
                {
                    if(windowListIter > 0)
                    {
                        windowListIter--;
                    }
                    else
                    {
                        windowListIter = imageList.size() - 1;
                    }

                    showImage = true;
                }
                else if (event.xkey.keycode == 113)
                {
                    if(windowListIter < imageList.size() - 1)
                    {
                        windowListIter++;
                    }
                    else
                    {
                        windowListIter = 0;
                    }

                    showImage = true;
                }
                else if (event.xkey.keycode == 36)
                {
                    windowIsOpen = false;
                }
            }
        }

        //XCloseDisplay(this->_display._display);

        return {image};
    }

#endif
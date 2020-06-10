#include "../header/display.hpp"
#include <string.h>

#if __linux__

    #include "X11/Xlib.h"

    MainDisplay::MainDisplay(HINSTANCE hInstance, int nCmdShow):MainDisplay(){}

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
        size_t windowListIter = 0;
        size_t windowListCount = 0;
        int fd_screen = -1;
        fd_screen = DefaultScreen(this->_display._display);

        this->_mainWindow._window = XCreateSimpleWindow(this->_display._display, this->_window._window,
                                                    0, 0, 600, 600, 1, 
                                                    BlackPixel(this->_display._display, fd_screen),
                                                    WhitePixel(this->_display._display, fd_screen));
        for(WindowObject object : windowList)
        {
			XGetWindowAttributes(this->_display._display, object._window, &windowAttr);

			XImage* temp = XGetImage(this->_display._display, object._window, 0, 0,
                                windowAttr.width, windowAttr.height, AllPlanes, ZPixmap);

			if(strlen(temp->data) > 0)
			{
				imageList.push_back(temp);
			}
        }

        windowListCount = imageList.size();

        GC gc = XDefaultGC(this->_display._display, fd_screen);

        XSelectInput(this->_display._display, this->_mainWindow._window, ExposureMask | KeyPressMask);

        XMapWindow(this->_display._display, this->_mainWindow._window);

        XEvent event;

        while (true)
        {
            image = imageList.at(windowListIter);

            XPutImage(this->_display._display, this->_mainWindow._window,
                            gc, image, 0, 0, 0, 0, image->width, image->height);


            XNextEvent(this->_display._display, &event);

            if(event.type == Expose)
            {
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
                        windowListIter = windowListCount - 1;
                    }
                }
                else if (event.xkey.keycode == 113)
                {
                    if(windowListIter < windowListCount - 1)
                    {
                        windowListIter++;
                    }
                    else
                    {
                        windowListIter = 0;
                    }
                }
                else if (event.xkey.keycode == 36)
                {
                    break;
                }
            }

            XClearWindow(this->_display._display, this->_mainWindow._window);
        }

        //XCloseDisplay(this->_display._display);

        return {image};
    }

#endif

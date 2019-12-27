#pragma once

#include "../interface/idisplay.hpp"
#include "../struct/object.hpp"
#include <memory>


#if _WIN32

    #define HINSTANCE HINSTANCE

#endif

#if __linux__

    #define HINSTANCE void*

#endif

class MainDisplay: public IMainDisplay
{
    private:

        #if _WIN32

            HWND _hwnd;
            int _nCmdShow;
            static LRESULT CALLBACK WndProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

        #endif

        DisplayObject _display;
        WindowObject _window;
        WindowObject _mainWindow;

    public:

        MainDisplay();
        MainDisplay(HINSTANCE hInstance, int nCmdShow);

        WindowObject get_main_window() override;
        DisplayObject get_main_display() override;
        ImageObject show(const std::vector<WindowObject>& windowList) override;
        ~MainDisplay() = default;
};

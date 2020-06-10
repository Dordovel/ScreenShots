#include "./header/makescreenshot.hpp"
#include "./header/findwindow.hpp"
#include <iostream>
#include "./header/windowproperty.hpp"
#include "./struct/object.hpp"
#include "./header/display.hpp"


#if _WIN32

    int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
    {
        MainDisplay mainDisplay(hInstance, nCmdShow);

#endif

#if __linux__

    int main()
    {
        MainDisplay mainDisplay;

#endif

        ScreenShot screenShot;
        DisplayObject displayObject;
        WindowObject windowObject;


        displayObject = mainDisplay.get_main_display();
        windowObject = mainDisplay.get_main_window();

        std::shared_ptr<IWindowProperty> windowProperty(new WindowProperty());
        std::unique_ptr<IFindWindow> find(new FindWindowObject(windowProperty,  displayObject, windowObject));

		auto window = find->search_window();

        std::vector<WindowObject> result = window;
        result.push_back(windowObject);

        ImageObject image = mainDisplay.show(result);
        screenShot.make_screenshot(image, "screenShot.bmp");
        
        return 0;
    }

#include "./header/makescreenshot.hpp"
#include "./header/findwindow.hpp"
#include <iostream>
#include "./header/windowproperty.hpp"
#include "./struct/object.hpp"
#include "./header/display.hpp"

int main()
{
    ScreenShot screenShot;
    MainDisplay mainDisplay;
    DisplayObject displayObject;
    WindowObject windowObject;


    displayObject = mainDisplay.get_main_display();
    windowObject = mainDisplay.get_main_window();

    std::shared_ptr<IWindowProperty> windowProperty(new WindowProperty());
    std::unique_ptr<IFindWindow> find(new FindWindow(windowProperty,  displayObject, windowObject));

    std::vector<WindowObject> result = std::move(find->search_window());
    result.push_back(windowObject);

    ImageObject image = mainDisplay.show(result);
    screenShot.make_screenshot(image, "screenShot.bmp");
    
    return 0;
}
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

    std::cout<<"1: Full ScreenShot\n2: Select Window\n-> ";
    int input;
    std::cin>>input;
    if(input == 1)
    {
        screenShot.make_screenshot(displayObject, windowObject, "full_screenshot.bmp");
    }
    else if(input == 2)
    {
        std::shared_ptr<IWindowProperty> windowProperty(new WindowProperty());
        std::unique_ptr<IFindWindow> find(new FindWindow(windowProperty,  displayObject, windowObject));

        std::vector<WindowObject> result = find->search_window();

        if(!result.empty())
        {
            size_t iter = 0;
            size_t size = result.size();

            WindowObject temp;

            for(; iter < size; ++iter)
            {
                temp = result.at(iter);

                unsigned char* name = windowProperty->get_window_property(displayObject, temp, "_NET_WM_NAME");
                std::cout<<"№ "<<iter<<"    "<<name<<std::endl;
            }

            int choice;
            std::cout<<"-> ";
            std::cin>>choice;
            temp = result.at(choice);
            screenShot.make_screenshot(displayObject, temp, "screenShot" + std::to_string(choice) +".bmp");
        }else
        {
            std::cout<<"Window Not Found "<<std::endl;
        }
    }
    else
    {
        std::cout<<"OPS"<<std::endl;
    }
    
    return 0;
}
#include "../struct/object.hpp"
#include <string>
#include "../header/makescreenshot.hpp"

#if _WIN32

    void ScreenShot::make_screenshot(const ImageObject& image, std::string savePath)
    {
        HWND handle = image._image;

        
    }

#endif
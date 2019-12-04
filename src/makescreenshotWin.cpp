#if _WIN32

    #include "../header/makescreenshot.hpp"
    #include <windows.h>
    #include "./struct.hpp"

    void make_screenshot(std::string savePath)
    {
        HDC hdc;
        HBITMAP hBitMap;
        BITMAPINFOHEADER hBitMapInfo;
        int bitCount = 32;

        int windowWidth = GetSystemMetrics(SM_CXSCREEN);
        int windowHeight = GetSystemMetrics(SM_CYSCREEN);
        
        hBitMapInfo.biSize = sizeof(BITMAPINFOHEADER);
        hBitMapInfo.biWidth = windowWidth;
        hBitMapInfo.biHeight = windowHeight;
        hBitMapInfo.biPlanes = 1;
        hBitMapInfo.biBitCount = bitCount;
        hBitMapInfo.biCompression = BI_RGB;

        hdc = CreateCompatibleDC(NULL);
        hBitMap = CreateDIBSection(hdc, ())
    }

#endif
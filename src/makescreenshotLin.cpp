#if __linux__

    #include "../header/makescreenshot.hpp"
    #include <iostream>
    #include <cstring>
    #include "../struct/struct.hpp"
    #include <vector>
    #include "../struct/object.hpp"

    void ScreenShot::make_screenshot(const ImageObject& image, std::string savePath)
    {
        BITMAPFILEHEADER bitHeader;
        BITMAPINFOHEADER bitHeaderInfo;
        int bitCount = 32;
        int dwBmpSize = 0;dwBmpSize = image._image->width * 4 * image._image->height;

        memset(&bitHeader, 0, sizeof(BITMAPFILEHEADER));
        memset(&bitHeaderInfo, 0, sizeof(BITMAPINFOHEADER));
        bitHeader.bfType = 0x4D42;
        bitHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
        bitHeader.bfReserved1 = 0;
        bitHeader.bfReserved2 = 0;
        bitHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwBmpSize;
        
        bitHeaderInfo.biSize = sizeof(BITMAPINFOHEADER);
        bitHeaderInfo.biWidth = image._image->width;
        bitHeaderInfo.biHeight = image._image->height;
        bitHeaderInfo.biPlanes = 0;
        bitHeaderInfo.biBitCount = bitCount;
        bitHeaderInfo.biSizeImage = 0;
        bitHeaderInfo.biCompression = 0;
        bitHeaderInfo.biXPelsPerMeter = 0;
        bitHeaderInfo.biYPelsPerMeter = 0;
        bitHeaderInfo.biClrUsed = 0;
        bitHeaderInfo.biClrImportant = 0;

        std::vector<char> arr(dwBmpSize);

        int w = bitHeaderInfo.biWidth;
        int h = bitHeaderInfo.biHeight;
        int n1 = 0; 
        int n2 = 0;

        for(int row = 0; row < h; row++)
        {
            for(int col = 0; col < w; col++)
            {
                n1 = 4 * (col + w  * row);
                n2 = 4 * (col + w * (h - row - 1));

                arr[n2 + 0] = image._image->data[n1 + 0];
                arr[n2 + 1] = image._image->data[n1 + 1];
                arr[n2 + 2] = image._image->data[n1 + 2];
            }
        }


        FILE* file = fopen(savePath.c_str(), "wb");
        fwrite(&bitHeader, sizeof(bitHeader), 1, file);
        fwrite(&bitHeaderInfo, sizeof(bitHeaderInfo), 1, file);
        fwrite(arr.data(), dwBmpSize, 1, file);
        fclose(file);
    }

#endif
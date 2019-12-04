#pragma once 

#pragma pack(push, 1)

struct BITMAPFILEHEADER 
{
    short bfType;
    int bfSize;
    short bfReserved1;
    short bfReserved2;
    int bfOffBits;
};

struct BITMAPINFOHEADER
{
    int biSize;
    int biWidth;
    int biHeight;
    short biPlanes;
    short biBitCount;
    int biCompression;
    int biSizeImage;
    int biYPelsPerMeter;
    int biXPelsPerMeter;
    int biClrUsed;
    int biClrImportant;
};

#pragma pack(pop)
#include "../struct/object.hpp"
#include <string>
#include "../header/makescreenshot.hpp"

#if _WIN32

    void ScreenShot::make_screenshot(const ImageObject& image, std::string savePath)
    {
		if(image._image)
		{
			HBITMAP hbmScreen = image._hBitmap;
			BITMAP bmpScreen;
			HDC hdcWindow = GetWindowDC(image._image);

			GetObject(hbmScreen,sizeof(BITMAP),&bmpScreen);

			int width = bmpScreen.bmWidth;
			int height = bmpScreen.bmHeight;
		
			BITMAPFILEHEADER   bmfHeader;    
			BITMAPINFOHEADER   bi;
			
			bi.biSize = sizeof(BITMAPINFOHEADER);    
			bi.biWidth = width;    
			bi.biHeight = height;  
			bi.biPlanes = 1; 
			bi.biBitCount = 32;
			bi.biCompression = BI_RGB;
			bi.biSizeImage = 0;  
			bi.biXPelsPerMeter = 0;    
			bi.biYPelsPerMeter = 0;    
			bi.biClrUsed = 0;    
			bi.biClrImportant = 0;

			DWORD dwBmpSize = ((width * bi.biBitCount + 31) / 32) * 4 * height;

			
			HANDLE hDIB = GlobalAlloc(GHND,dwBmpSize); 
			char *lpbitmap = (char *)GlobalLock(hDIB);

			GetDIBits(hdcWindow, hbmScreen, 0,
				(UINT)height,
				lpbitmap,
				(BITMAPINFO *)&bi, DIB_RGB_COLORS);

			HANDLE hFile = CreateFile(savePath.c_str(),
				GENERIC_WRITE,
				0,
				NULL,
				CREATE_ALWAYS,
				FILE_ATTRIBUTE_NORMAL, NULL);   
			
			DWORD dwSizeofDIB = dwBmpSize + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
		
			bmfHeader.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER); 
			
			bmfHeader.bfSize = dwSizeofDIB; 
			
			bmfHeader.bfType = 0x4D42; //BM   
		
			DWORD dwBytesWritten = 0;
			WriteFile(hFile, (LPSTR)&bmfHeader, sizeof(BITMAPFILEHEADER), &dwBytesWritten, NULL);
			WriteFile(hFile, (LPSTR)&bi, sizeof(BITMAPINFOHEADER), &dwBytesWritten, NULL);
			WriteFile(hFile, (LPSTR)lpbitmap, dwBmpSize, &dwBytesWritten, NULL);
			
			GlobalUnlock(hDIB);    
			GlobalFree(hDIB);

			CloseHandle(hFile);
			DeleteObject(hbmScreen);
		}
    }

#endif
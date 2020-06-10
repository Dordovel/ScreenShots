#include "../header/display.hpp"
#include <algorithm>

#if _WIN32

	std::vector<WindowObject> windowsObjectList;
	int iter = 0;
	bool showWindowFlag = false;
	bool fillColor = false;
	ImageObject selectObject;

	void paintProgramName(HWND hwnd, std::string text)
	{
		HDC  hdc; 
		RECT rc;
		PAINTSTRUCT ps;

		std::wstring str;
		COLORREF color = RGB(255,0,0);

		hdc = BeginPaint(hwnd, &ps);

		SetRect(&rc, 0, 0 , 200, 200);

		SetTextColor(hdc, color);
		DrawTextA(hdc, text.c_str(), text.size(), &rc, DT_LEFT);

		ReleaseDC(0, hdc);
		EndPaint(hwnd, &ps);
	}
	

	void fill_window(HDC hdc)
	{
		HBRUSH brush = CreateSolidBrush(RGB(255,255,255));
		SelectObject(hdc, brush);
		Rectangle(hdc, 0, 20, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	}



	LRESULT CALLBACK MainDisplay::WndProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		HDC hdcScreen;
		HDC hdcWindow = GetWindowDC(hwnd);
		HDC hdcMemDC = CreateCompatibleDC(hdcWindow);
		HBITMAP hbmScreen = NULL;
		int sizeWindowBorderMetrics = GetSystemMetrics(SM_CYSMCAPTION) + GetSystemMetrics(SM_CYSIZEFRAME);
		RECT rcClient;

		switch(msg)
		{
			case WM_CHAR:
				switch(wParam)
				{
					case 'a':
						if(iter < windowsObjectList.size())
						{
							iter++;
							fillColor = true;
							showWindowFlag = true;
						}
						else
						{
							iter = 0;
						}
						break;
					case 'd':
						if(iter > 0)
						{
							iter--;
							fillColor = true;
							showWindowFlag = true;
						}
						else 
						{
							iter = windowsObjectList.size() - 1;
						}
						break;
				}
				break;

			case WM_KEYDOWN:
				switch(wParam)
				{
					case VK_RETURN:

						DestroyWindow(hwnd);

						HWND hWnd = windowsObjectList.at(iter)._window;

						hdcScreen = GetWindowDC(hWnd);

						if(!hdcMemDC)
						{
							MessageBoxW(hWnd, L"CreateCompatibleDC has failed",L"Failed", MB_OK);
						}
						GetClientRect(hWnd, &rcClient);

						hbmScreen = CreateCompatibleBitmap(hdcScreen,
													rcClient.right,
													rcClient.bottom + (sizeWindowBorderMetrics * 2));
							
						if(!hbmScreen)
						{
							MessageBoxW(hWnd, L"CreateCompatibleBitmap Failed",L"Failed", MB_OK);
						}

						SelectObject(hdcMemDC,hbmScreen);

						PrintWindow(hWnd, hdcMemDC, 0);

						selectObject._image = hWnd;
						selectObject._hBitmap = hbmScreen;

						DeleteObject(hdcMemDC);
						ReleaseDC(NULL,hdcScreen);
						ReleaseDC(hWnd,hdcWindow);
						break;

				}
				break;

			case WM_CREATE:
					break;

			case WM_PAINT:
					if(showWindowFlag)
					{
						if(hwnd)
						{
							if(fillColor)
							{
								fill_window(hdcWindow);
								fillColor = false;
							}

							HWND hWnd = windowsObjectList.at(iter)._window;

							hdcScreen = GetWindowDC(hWnd);

							GetClientRect(hWnd, &rcClient);

							hbmScreen = CreateCompatibleBitmap(hdcScreen,
														rcClient.right,
														rcClient.bottom + (sizeWindowBorderMetrics * 2));

							SelectObject(hdcMemDC,hbmScreen);

							PrintWindow(hWnd, hdcMemDC, 0);

							SetStretchBltMode(hdcMemDC,HALFTONE);

							if(!StretchBlt(hdcWindow,
										0,
										sizeWindowBorderMetrics, 
									rcClient.right + 20,
									rcClient.bottom + (sizeWindowBorderMetrics * 1.5) , 
									hdcMemDC,
									0,
									0,
									rcClient.right + 20,
									rcClient.bottom + (sizeWindowBorderMetrics * 1.5),
									SRCCOPY))
							{
								MessageBoxW(hWnd, L"StretchBlt has failed",L"Failed", MB_OK);
							}
							DeleteObject(hbmScreen);
							DeleteObject(hdcMemDC);
							ReleaseDC(NULL,hdcScreen);
							ReleaseDC(hWnd,hdcWindow);

						}
					}
					break;

			case WM_SETFOCUS:
					fillColor = true;
					break;

			case WM_ACTIVATE:
					showWindowFlag = fillColor = true;
					break;

			case WM_CLOSE:
				DeleteObject(hbmScreen);
				DeleteObject(hdcMemDC);
				ReleaseDC(NULL,hdcScreen);
				DestroyWindow(hwnd);
				break;

			case WM_DESTROY:
				DeleteObject(hbmScreen);
				DeleteObject(hdcMemDC);
				ReleaseDC(NULL,hdcScreen);
				PostQuitMessage(0);
				break;

			default:
				return DefWindowProc(hwnd, msg, wParam, lParam);
		} 

		return 0;
	}


	MainDisplay::MainDisplay(){}	

    MainDisplay::MainDisplay(HINSTANCE hInstance, int nCmdShow)
    {
        WNDCLASSEX wc;

		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = 0;
		wc.lpfnWndProc = MainDisplay::WndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = hInstance;
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
		wc.lpszMenuName = NULL;
		wc.lpszClassName = "Test";
		wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);


		if(!RegisterClassEx(&wc))
		{
			MessageBoxW(NULL, L"Error", L"RegisterClassEx", MB_ICONEXCLAMATION | MB_OK);
		}

		this->_mainWindow._window = CreateWindowExW(
			WS_EX_CLIENTEDGE,
			L"Test",
			L"Test",
			WS_CAPTION | WS_SYSMENU | WS_VISIBLE,
			CW_USEDEFAULT,
			CW_USEDEFAULT, 900, 500,
			NULL, NULL, hInstance, NULL);

		if(this->_mainWindow._window == NULL)
		{
			MessageBoxW(NULL, L"Error", L"CreateWindowEx", MB_ICONEXCLAMATION | MB_OK);
		}else
		{
			this->_display._display = GetDC(this->_mainWindow._window);
		}
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
		windowsObjectList = windowList;

		for (size_t a = 0; a < windowsObjectList.size(); ++a)
		{
			if(windowsObjectList.at(a)._window == GetActiveWindow())
			{
				windowsObjectList.erase(windowsObjectList.begin() + a);
			}
		}


		MSG msg;

		ShowWindow(this->_mainWindow._window, SW_SHOW); 
		UpdateWindow(this->_mainWindow._window);

		while(GetMessage(&msg, NULL, 0, 0) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
        return selectObject;
    }

#endif

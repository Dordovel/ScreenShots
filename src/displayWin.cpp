#include "../header/display.hpp"

#if _WIN32

	LRESULT CALLBACK MainDisplay::WndProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch(msg)
		{
			case WM_CHAR:
				switch(wParam)
				{
					case 'a':
						DestroyWindow(hwnd);break;
				}
				break;
			case WM_PAINT:
				break;

			case WM_CLOSE:
				DestroyWindow(hwnd);
				break;

			case WM_DESTROY:
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
			MessageBox(NULL, "Error", "RegisterClassEx", MB_ICONEXCLAMATION | MB_OK);
		}

		this->_mainWindow._window = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			"Test",
			"Test",
			WS_OVERLAPPEDWINDOW | WS_VISIBLE,
			CW_USEDEFAULT,
			CW_USEDEFAULT, 700, 340,
			NULL, NULL, hInstance, NULL);

		if(this->_mainWindow._window == NULL)
		{
			MessageBox(NULL, "Error","CreateWindowEx", MB_ICONEXCLAMATION | MB_OK);
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
    	MSG msg;

		ShowWindow(this->_mainWindow._window, this->_nCmdShow);
		UpdateWindow(this->_mainWindow._window);


		while(GetMessage(&msg, NULL, 0, 0) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
        return {};
    }

 //    void MainDisplay::paintProgramName(HWND hwnd, std::vector<WinApiTextParam> text)
	// {
	// 	HDC  hdc; 
	// 	RECT rc;
	// 	PAINTSTRUCT ps;

	// 	size_t size = text.size();

	// 	std::wstring str;
	// 	COLORREF color;

	// 	hdc = BeginPaint(hwnd, &ps);

	// 	for(int a = 0; a < size; ++a)
	// 	{
	// 		str = text.at(a).text;
	// 		str += '\n';
	// 		color = text.at(a).rgbColor;

	// 		SetRect(&rc, 0, a * 25 , 200, 200);

	// 		SetTextColor(hdc, color);
	// 		DrawTextW(hdc, str.c_str(), str.size(), &rc, DT_LEFT);
	// 	}	

	// 	ReleaseDC(0, hdc);
	// 	EndPaint(hwnd, &ps);
	// }

#endif
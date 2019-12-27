#include "../header/windowproperty.hpp"

#if _WIN32

	#include <windows.h>
	#include <vector>
	#include "../struct/object.hpp"

	BOOL CALLBACK EnumWindowsProc( HWND hwnd, LPARAM lParam )
	{
		std::vector<HWND>* params = (std::vector<HWND>*)lParam;

	    params->push_back(hwnd);
	}

	unsigned long WindowProperty::get_found_object_count() noexcept
	{
		return this->_itemCount;
	}

	void* WindowProperty::get_window_property(const DisplayObject& display,
													const WindowObject& window, 
													Property propertyName) noexcept
	{
		if(Property::WINDOW_HANDLER)
        {
        	HWND buffer[50];
			std::vector<HWND> v;
			EnumWindows(&EnumWindowsProc, (LPARAM) &v);
			this->_itemCount = v.size();

			size_t iter = 0;
			size_t count = v.size();
			
			for(; iter<count ; ++iter)
			{
				buffer[iter] = v.at(iter); 
			}

			return buffer; 
        }
        else if(propertyName == Property::WINDOW_NAME)
        {
        	const int bufferSize = 200;
        	char buffer[bufferSize];
        	GetWindowText(window._window, buffer, bufferSize);

        	return buffer;
        }
		
	}

#endif
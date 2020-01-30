#include "../header/windowproperty.hpp"

#if _WIN32

	#include <windows.h>
	#include <vector>
	#include "../struct/object.hpp"

	BOOL CALLBACK EnumWindowsProc( HWND hwnd, LPARAM lParam )
	{
		std::vector<HWND>* params = (std::vector<HWND>*)lParam;
		if(IsWindowVisible ( hwnd ))
		{
			params->push_back(hwnd);
		}

		return TRUE;
	}

	unsigned long WindowProperty::get_found_object_count() noexcept
	{
		return this->_itemCount;
	}

	void* WindowProperty::get_window_property(const DisplayObject& display,
													const WindowObject& window, 
													Property propertyName) noexcept
	{
		if(propertyName == Property::WINDOW_HANDLER)
        {
			std::vector<HWND>* v = new std::vector<HWND>();
			EnumWindows(&EnumWindowsProc, (LPARAM) v);
			this->_itemCount = v->size();

			return v;
		}
        else if(propertyName == Property::WINDOW_NAME)
		{
			const int bufferSize = 200;
			char* buffer = new char[bufferSize];
			GetWindowText(window._window, buffer, bufferSize);

			return buffer;
        }
	}


	std::vector<WindowObject> WindowProperty::get_window_list(const DisplayObject& display,
                                                    const WindowObject& window)
	{
		std::vector<WindowObject> objects;

		std::vector<HWND>* result = (std::vector<HWND>*) this->get_window_property(display,
																					window,
																					Property::WINDOW_HANDLER);

		unsigned long count = this->get_found_object_count();
        
        int iter = 0;
        for(; iter < count; ++iter)
        {
            objects.push_back( WindowObject{ result->at(iter) } );
        }
        
        delete result;

		return objects;
	}

	std::string WindowProperty::get_window_name(const DisplayObject& display,
												const WindowObject& window)
	{
		char* object = (char*)this->get_window_property(display,
                                                        window,
                                                        Property::WINDOW_NAME);

		std::string windowName(object);

		delete object;

		return windowName;
	}

#endif
#include <MyHeaders\WindowClass.h>
#include <MyHeaders\Icon.h>
#include <MyHeaders\Cursor.h>

WINPROC(BasicProc, handle, msg, wp, lp)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(handle, msg, wp, lp);
}


WindowClass::WindowClass()
{
	Registered = false;
}

const WNDCLASSEX WindowClass::GetClass() const
{
	return WinClass;
}

WindowClass::operator bool() const
{
	return Registered;
}

WindowClass::WindowClass(const TCHAR* name, const WNDPROC proc, const WCStyle style, const HCURSOR cursor, const HICON icon, const WCColor color)
{
	Registered = false;
	Register(name, proc, style, cursor, icon, color);
}

WindowClass::~WindowClass()
{
	if (Registered)
		Unregister();
}

bool WindowClass::Unregister()
{
	if (UnregisterClass(WinClass.lpszClassName, GetModuleHandle(0)) != 0)
	{
		ZeroMemory(&WinClass, sizeof(WinClass));
		Registered = false;
		return true;
	}
	return false;

}

bool WindowClass::Register(const TCHAR* name, const WNDPROC proc, const WCStyle style, const HCURSOR cursor, const HICON icon, const WCColor color)
{
	if (Registered)
		return false;
	ZeroMemory(&WinClass, sizeof(WinClass));
	WinClass.style = style;
	WinClass.cbSize = sizeof(WinClass);


	WinClass.hCursor = cursor;
	WinClass.hIcon = icon;

	WinClass.lpfnWndProc = proc;
	WinClass.lpszClassName = name;
	WinClass.hbrBackground = (HBRUSH)color.operator unsigned int();
	return Registered = (RegisterClassEx(&WinClass) != 0);
}
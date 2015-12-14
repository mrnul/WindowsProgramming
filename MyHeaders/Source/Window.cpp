#include <MyHeaders\Window.h>

Window::Window()
{
	Handle = 0;
}

Window::Window(const TCHAR *classname, const TCHAR *windowname, 
	const WStyle style, 
	const int x, const int y, 
	const int width, const int height)
{
	Handle = 0;
	Create(classname, windowname, style, x, y, width, height);
}

Window::Window(const TCHAR *classname, const TCHAR *windowname, 
	const WStyle style, 
	const int x, const int y,
	const int width, const int height, 
	const HWND parent, 
	const HMENU menuID)
{
	Handle = 0;
	Create(classname, windowname, style, x, y, width, height);
}

void Window::SetAppData(const void *data)
{
	SetWindowLongPtr(Handle, GWLP_USERDATA, (LONG)data);
}

void* Window::GetAppData()
{
	return (void*)GetWindowLongPtr(Handle, GWLP_USERDATA);
}

void Window::SetTitle(const TCHAR *title)
{
	SetWindowText(Handle, title);
}

HDC Window::getDC()
{
	return GetDC(Handle);
}

bool Window::releaseDC(HDC dc)
{
	return ReleaseDC(Handle, dc) != 0;
}

HDC Window::getWindowDC()
{
	return GetWindowDC(Handle);
}

bool Window::SetOpacity(BYTE value)
{
	return SetLayeredWindowAttributes(Handle, 0, value, LWA_ALPHA) != 0;
}


void Window::MessageLoop()
{
	while (IsWindow(Handle))
	{
		GetMessage(&msg, Handle, 0, 0);
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

bool Window::MessageAvailable()
{
	return PeekMessage(&msg, Handle, 0, 0, PM_NOREMOVE) != 0;
}

bool Window::getMessageNoWait()
{
	return PeekMessage(&msg, Handle, 0, 0, PM_REMOVE) != 0;
}

unsigned int Window::sendMessage()
{
	TranslateMessage(&msg);
	return DispatchMessage(&msg);
}

bool Window::getMessage()
{
	return GetMessage(&msg, Handle, 0, 0) > 0;
}

bool Window::Destroy()
{
	if (!Handle)
		return true;
	if (!DestroyWindow(Handle))
		return false;

	Handle = 0;
	return true;;
}

bool Window::IsVisible()
{
	return IsWindowVisible(Handle) != 0;
}


bool Window::IsEnabled()
{
	return IsWindowEnabled(Handle) != 0;
}

Window::operator HWND()
{
	if (IsWindow(Handle))
		return Handle;
	return Handle = 0;
}

void Window::getWindowRect(RECT *out)
{
	RECT rc;
	GetWindowRect(Handle, &rc);
	*out = rc;
}

void Window::getClientRect(RECT *out)
{
	RECT rc;
	POINT point;

	GetClientRect(Handle, &rc);

	ClientToScreen(Handle, &point);

	rc.top = point.y;
	rc.left = point.x;

	point.x = rc.right;
	point.y = rc.bottom;
	ClientToScreen(Handle, &point);

	rc.right = point.x;
	rc.bottom = point.y;

	*out = rc;
}

bool Window::Update()
{
	return UpdateWindow(Handle) != 0;
}

bool Window::Create(const TCHAR *classname, const TCHAR *windowname, 
	const WStyle style, 
	const int x, const int y, 
	const int width, const int height, 
	const HWND parent, 
	const HMENU menuID)
{
	RECT rect = { 0, 0, width, height };
	AdjustWindowRectEx(&rect, style, menuID != 0, 0);

	return (Handle = CreateWindowEx(0, classname, windowname, style, x, y, rect.right - rect.left, rect.bottom - rect.top, parent, menuID, GetModuleHandle(0), 0)) != 0;
}

bool Window::Create(const TCHAR *classname, const TCHAR *windowname, 
	const WStyle style, 
	const int x, const int y, 
	const int width, const int height)
{
	RECT rect = { 0, 0, width, height };
	AdjustWindowRectEx(&rect, style, false, 0);

	return (Handle = CreateWindowEx(0, classname, windowname, style, x, y, rect.right - rect.left, rect.bottom - rect.top, 0, 0, GetModuleHandle(0), 0)) != 0;
}

Window::~Window()
{
	Destroy();
}
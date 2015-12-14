#include <MyHeaders\Button.h>

Button::Button()
{
	Handle = 0;
}

Button::Button(const TCHAR *title, const DWORD ID, const HWND parent, const int x, const int y, const int width, const int height, const BStyle style, const BExStyle exstyle)
{
	Create(title, ID, parent, x, y, width, height, style, exstyle);
}

void Button::Enable(bool enable)
{
	Button_Enable(Handle, enable);
}

bool Button::Create(const TCHAR *title, const DWORD ID, const HWND parent, const int x, const int y, const int width, const int height, const BStyle style, const BExStyle exstyle)
{
	return (Handle = CreateWindowEx(exstyle, TEXT("BUTTON"), title, style.operator unsigned int() | WS_CHILD, x, y, width, height, parent, (HMENU)ID, GetModuleHandle(0), 0)) != 0;
}

LRESULT Button::SetBitmap(const HBITMAP bmp)
{
	return SendMessage(Handle, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp);
}

LRESULT Button::SetIcon(const HICON icon)
{
	return SendMessage(Handle, BM_SETIMAGE, IMAGE_ICON, (LPARAM)icon);
}

Button::operator HWND()
{
	return Handle;
}

bool Button::IsEnabled()
{
	return IsWindowEnabled(Handle) != 0;
}

bool Button::IsVisible()
{
	return IsWindowVisible(Handle) != 0;
}

bool Button::Destroy()
{
	if (!Handle)
		return true;
	if (!DestroyWindow(Handle))
		return false;

	Handle = 0;
	return true;;
}

Button::~Button()
{
	Destroy();
}
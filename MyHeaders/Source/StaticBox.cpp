#include <MyHeaders\StaticBox.h>

StaticBox::StaticBox()
{
	Handle = 0;
}

StaticBox::StaticBox(const TCHAR *title, const DWORD ID, const HWND parent, const int x, const int y, const int width, const int height, const SBStyle style, const SBExStyle exstyle)
{
	Handle = 0;
	Create(title, ID, parent, x, y, width, height, style, exstyle);
}

bool StaticBox::Create(const TCHAR *title, const DWORD ID, const HWND parent, const int x, const int y, const int width, const int height, const SBStyle style, const SBExStyle exstyle)
{
	return (Handle = CreateWindowEx(exstyle, TEXT("STATIC"), title, style.operator unsigned int() | WS_CHILD, x, y, width, height, parent, (HMENU)ID, GetModuleHandle(0), 0)) != 0;
}

int StaticBox::GetText(TCHAR *txt, const int max)
{
	return GetWindowText(Handle, txt, max);
}

bool StaticBox::SetText(const TCHAR *txt)
{
	return SetWindowText(Handle, txt) != 0;
}

int StaticBox::GetTextLength()
{
	return GetWindowTextLength(Handle);
}

bool StaticBox::IsVisible()
{
	return IsWindowVisible(Handle) != 0;
}

bool StaticBox::IsEnabled()
{
	return IsWindowEnabled(Handle) != 0;
}

StaticBox::operator HWND()
{
	return Handle;
}

LRESULT StaticBox::SetBitmap(const HBITMAP bmp)
{
	return SendMessage(Handle, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp);
}

LRESULT StaticBox::SetIcon(const HICON icon)
{
	return SendMessage(Handle, STM_SETIMAGE, IMAGE_ICON, (LPARAM)icon);
}

bool StaticBox::Destroy()
{
	if (!Handle)
		return true;
	if (!DestroyWindow(Handle))
		return false;

	Handle = 0;
	return true;;
}

StaticBox::~StaticBox()
{
	Destroy();
}

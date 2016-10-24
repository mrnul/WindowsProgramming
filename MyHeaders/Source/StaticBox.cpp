#include <MyHeaders\StaticBox.h>

int StaticBox::GetText(TCHAR *txt, const int max)
{
	return GetWindowText(ControlHandle, txt, max);
}

bool StaticBox::SetText(const TCHAR *txt)
{
	return SetWindowText(ControlHandle, txt) != 0;
}

int StaticBox::GetTextLength()
{
	return GetWindowTextLength(ControlHandle);
}

LRESULT StaticBox::SetBitmap(const HBITMAP bmp)
{
	return SendMessage(ControlHandle, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp);
}

LRESULT StaticBox::SetIcon(const HICON icon)
{
	return SendMessage(ControlHandle, STM_SETIMAGE, IMAGE_ICON, (LPARAM)icon);
}

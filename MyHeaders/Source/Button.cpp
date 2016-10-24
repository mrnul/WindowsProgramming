#include <MyHeaders\Button.h>

LRESULT Button::SetBitmap(const HBITMAP bmp)
{
	return SendMessage(ControlHandle, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp);
}

LRESULT Button::SetIcon(const HICON icon)
{
	return SendMessage(ControlHandle, BM_SETIMAGE, IMAGE_ICON, (LPARAM)icon);
}

#include <MyHeaders\EditBox.h>

EditBox::EditBox()
{
	Handle = 0;
}

EditBox::EditBox(const TCHAR *title, const DWORD ID, const HWND parent, const int x, const int y, const int width, const int height, const EBStyle style, const EBExStyle exstyle)
{
	Create(title, ID, parent, x, y, width, height, style, exstyle);
}

bool EditBox::Create(const TCHAR *title, const DWORD ID, const HWND parent, const int x, const int y, const int width, const int height, const EBStyle style, const EBExStyle exstyle)
{
	return (Handle = CreateWindowEx(exstyle, TEXT("EDIT"), title, style.operator unsigned int() | WS_CHILD, x, y, width, height, parent, (HMENU)ID, GetModuleHandle(0), 0)) != 0;
}

EditBox::operator HWND()
{
	return Handle;
}

int EditBox::GetText(TCHAR *txt, const int max)
{
	return GetWindowText(Handle, txt, max);
}

bool EditBox::SetText(const TCHAR *txt)
{
	return SetWindowText(Handle, txt) != 0;
}

void EditBox::Enable(const bool enable)
{
	Edit_Enable(Handle, enable);
}

int EditBox::GetTextLength()
{
	return GetWindowTextLength(Handle);
}

bool EditBox::IsEnabled()
{
	return IsWindowEnabled(Handle) != 0;
}

bool EditBox::IsVisible()
{
	return IsWindowVisible(Handle) != 0;
}

bool EditBox::Destroy()
{
	if (!Handle)
		return true;
	if (!DestroyWindow(Handle))
		return false;

	Handle = 0;
	return true;;
}


EditBox::~EditBox()
{
	Destroy();
}
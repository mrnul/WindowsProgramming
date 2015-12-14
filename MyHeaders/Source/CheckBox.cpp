#include <MyHeaders\CheckBox.h>

CheckBox::CheckBox()
{
	Handle = 0;
}


CheckBox::CheckBox(const TCHAR *title, const DWORD ID, const HWND parent, const int x, const int y, const int width, const int height, const CBStyle style, const DWORD exstyle)
{
	Create(title, ID, parent, x, y, width, height, style, exstyle);
}

void CheckBox::SetState(const CBState state)
{
	Button_SetCheck(Handle, state);
}

CheckBox::operator HWND()
{
	return Handle;
}

unsigned int CheckBox::GetState()
{
	return Button_GetCheck(Handle);
}

bool CheckBox::Create(const TCHAR *title, const DWORD ID, const HWND parent, const int x, const int y, const int width, const int height, const CBStyle style, const DWORD exstyle)
{
	return (Handle = CreateWindowEx(exstyle, TEXT("BUTTON"), title, style.operator unsigned int() | WS_CHILD | BS_CHECKBOX, x, y, width, height, parent, (HMENU)ID, GetModuleHandle(0), 0)) != 0;
}

bool CheckBox::IsEnabled()
{
	return IsWindowEnabled(Handle) != 0;
}

bool CheckBox::IsVisible()
{
	return IsWindowVisible(Handle) != 0;
}

bool CheckBox::Destroy()
{
	if (!Handle)
		return true;
	if (!DestroyWindow(Handle))
		return false;

	Handle = 0;
	return true;;
}

CheckBox::~CheckBox()
{
	Destroy();
}
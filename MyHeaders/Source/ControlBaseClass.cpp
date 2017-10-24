#include <MyHeaders\ControlBaseClass.h>


ControlBaseClass::ControlBaseClass()
{
	ControlID = 0;
}

ControlBaseClass::ControlBaseClass(HWND parent, const unsigned int id)
{
	Init(parent, id);
}

bool ControlBaseClass::Init(HWND parent, const unsigned int id)
{
	return (ControlHandle = GetDlgItem(parent, ControlID = id)) != 0;
}

bool ControlBaseClass::SetWLongPtr(int index, void *newValue)
{
	return SetWindowLongPtr(ControlHandle, index, (LONG_PTR)newValue) != 0;
}

LONG_PTR ControlBaseClass::GetWLongPtr(int index)
{
	return GetWindowLongPtr(ControlHandle, index);
}

void ControlBaseClass::Enable(bool enable)
{
	EnableWindow(ControlHandle, enable);
}

bool ControlBaseClass::IsEnabled()
{
	return IsWindowEnabled(ControlHandle) != 0;
}

void ControlBaseClass::Hide()
{
	ShowWindow(ControlHandle, SW_HIDE);
}

void ControlBaseClass::Show()
{
	ShowWindow(ControlHandle, SW_SHOW);
}

unsigned int ControlBaseClass::ID()
{
	return ControlID;
}

HWND ControlBaseClass::Handle()
{
	return ControlHandle;
}

HWND ControlBaseClass::Parent()
{
	return GetParent(ControlHandle);
}

bool ControlBaseClass::Destroy()
{
	if (!ControlHandle)
		return true;
	if (!DestroyWindow(ControlHandle))
		return false;

	ControlHandle = 0;
	return true;
}

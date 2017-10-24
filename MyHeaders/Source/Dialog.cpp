#include <MyHeaders\Dialog.h>

Dialog::Dialog()
{
	INITCOMMONCONTROLSEX com =
	{ sizeof(INITCOMMONCONTROLSEX),
		ICC_WIN95_CLASSES };

	InitCommonControlsEx(&com);
}

Dialog::Dialog(const unsigned int ID, DLGPROC proc, void *param, HWND parent)
{
	Create(ID, proc, param, parent);
}

bool Dialog::Create(const unsigned int ID, DLGPROC proc, void *param, HWND parent)
{
	return (Handle = CreateDialogParam(0, MAKEINTRESOURCE(ID), parent, proc, (LPARAM)param)) != 0;
}

bool Dialog::SetWLongPtr(const DIndex index, void *newValue)
{
	return SetWindowLongPtr(Handle, index, (LONG_PTR)newValue) != 0;
}

LONG_PTR Dialog::GetWLongPtr(const DIndex index)
{
	return GetWindowLongPtr(Handle, index);
}

void Dialog::MessageLoop()
{
	while (GetMessage(&msg, Handle, 0, 0)> 0)
	{
		if (!IsDialogMessage(Handle, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

bool Dialog::MessageWaiting()
{
	return PeekMessage(&msg, Handle, 0, 0, PM_NOREMOVE) != 0;
}

bool Dialog::GetAndProcessMessage()
{
	if (GetMessage(&msg, Handle, 0, 0) <= 0)
		return false;

	if (!IsDialogMessage(Handle, &msg))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return true;
}

void Dialog::Destroy()
{
	DestroyWindow(Handle);
	Handle = 0;
}

Dialog::operator HWND()
{
	if (IsWindow(Handle))
		return Handle;

	return 0;
}

Dialog::~Dialog()
{
	Destroy();
}

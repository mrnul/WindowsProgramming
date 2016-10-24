#include <MyHeaders\EditBox.h>

int EditBox::GetText(TCHAR *txt, const int max)
{
	return GetWindowText(ControlHandle, txt, max);
}

bool EditBox::SetText(const TCHAR *txt)
{
	return SetWindowText(ControlHandle, txt) != 0;
}

int EditBox::GetTextLength()
{
	return GetWindowTextLength(ControlHandle);
}

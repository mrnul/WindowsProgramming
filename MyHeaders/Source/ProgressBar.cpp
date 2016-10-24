#include <MyHeaders\ProgressBar.h>

COLORREF ProgressBar::GetBarColor()
{
	return SendMessage(ControlHandle, PBM_GETBARCOLOR, 0, 0);
}

COLORREF ProgressBar::GetBGColor()
{
	return SendMessage(ControlHandle, PBM_GETBKCOLOR, 0, 0);
}

void ProgressBar::SetBarColor(const COLORREF color)
{
	SendMessage(ControlHandle, PBM_SETBARCOLOR, 0, color);
}

void ProgressBar::SetBGColor(const COLORREF color)
{
	SendMessage(ControlHandle, PBM_SETBKCOLOR, 0, color);
}

unsigned int ProgressBar::GetStep()
{
	return SendMessage(ControlHandle, PBM_GETSTEP, 0, 0);
}

unsigned int ProgressBar::GetRange()
{
	return SendMessage(ControlHandle, PBM_GETRANGE, 0, 0);
}

unsigned int ProgressBar::GetPosition()
{
	return SendMessage(ControlHandle, PBM_GETPOS, 0, 0);
}

void ProgressBar::SetPosition(const unsigned int pos)
{
	SendMessage(ControlHandle, PBM_SETPOS, pos, 0);
}

void ProgressBar::MakeStep()
{
	SendMessage(ControlHandle, PBM_STEPIT, 0, 0);
}

void ProgressBar::SetRange(const int range)
{
	SendMessage(ControlHandle, PBM_SETRANGE, 0, MAKELPARAM(0, range));
}

void ProgressBar::SetStep(const int step)
{
	SendMessage(ControlHandle, PBM_SETSTEP, (WPARAM)step, 0);
}

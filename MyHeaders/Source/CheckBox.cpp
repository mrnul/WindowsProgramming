#include <MyHeaders\CheckBox.h>

void CheckBox::SetState(const CBState state)
{
	Button_SetCheck(ControlHandle, state);
}


unsigned int CheckBox::GetState()
{
	return Button_GetCheck(ControlHandle);
}

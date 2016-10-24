#pragma once

#define MyHeaders_EditBox

#include <MyHeaders\ControlBaseClass.h>

class EditBox : public ControlBaseClass
{
	public:
		int GetText(TCHAR *txt, const int max);
		bool SetText(const TCHAR *txt);
		int GetTextLength();
};
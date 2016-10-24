#pragma once

#define MyHeaders_StaticBox

#include <MyHeaders\ControlBaseClass.h>

class StaticBox : public ControlBaseClass
{
	public:
		int GetText(TCHAR *txt, const int max);
		bool SetText(const TCHAR *txt);
		int GetTextLength();
		LRESULT SetBitmap(const HBITMAP bmp);
		LRESULT SetIcon(const HICON icon);
};
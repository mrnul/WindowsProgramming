#pragma once

#include <MyHeaders\ControlBaseClass.h>

class Button : public ControlBaseClass
{
	public:
		LRESULT SetBitmap(HBITMAP bmp);
		LRESULT SetIcon(HICON icon);
};
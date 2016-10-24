#pragma once

#define MyHeaders_ProgressBar

#include <MyHeaders\ControlBaseClass.h>


class ProgressBar : public ControlBaseClass
{
	public:
		void SetRange(const int range);
		void SetStep(const int step);
		void SetPosition(const unsigned int pos);
		void SetBarColor(const COLORREF color);
		void SetBGColor(const COLORREF color);
		unsigned int GetPosition();
		unsigned int GetRange();
		unsigned int GetStep();
		COLORREF GetBarColor();
		COLORREF GetBGColor();
		void MakeStep();
};

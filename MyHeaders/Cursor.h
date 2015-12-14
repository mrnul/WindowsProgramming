#pragma once

#define MyHeaders_Cursor

#include <Windows.h>
#include <MyHeaders\windowdefs.h>

CREATE_NEW_DATA_TYPE(CMode);

namespace cursor
{
	namespace mode
	{
		const CMode DefaultSize(LR_DEFAULTSIZE);
		const CMode Transparent(LR_LOADTRANSPARENT);
		const CMode Monochrome(LR_MONOCHROME);
		const CMode TrueVGA(LR_VGACOLOR);
		const CMode Default(DefaultSize);
	}
	namespace OEMcursor
	{
		const HCURSOR Arrow = (HCURSOR)LoadImage(0, MAKEINTRESOURCE(32512), IMAGE_CURSOR, 0, 0, LR_SHARED);
		const HCURSOR Hand = (HCURSOR)LoadImage(0, MAKEINTRESOURCE(32649), IMAGE_CURSOR, 0, 0, LR_SHARED);
		const HCURSOR Help = (HCURSOR)LoadImage(0, MAKEINTRESOURCE(32651), IMAGE_CURSOR, 0, 0, LR_SHARED);
		const HCURSOR Default = Arrow;
	}
}

class Cursor
{
	private:
		HANDLE Handle;
	public:
		Cursor();
		Cursor(const TCHAR *path, const CMode mode = cursor::mode::Default, int desiredX = 0, int desiredY = 0);
		bool Load(const TCHAR *path, const CMode mode = cursor::mode::Default, int desiredX = 0, int desiredY = 0);
		operator HCURSOR();
		bool Destroy();
		~Cursor();
};
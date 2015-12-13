#pragma once

#define MyHeaders_Icon

#include <Windows.h>
#include <MyHeaders\windowdefs.h>

CREATE_NEW_DATA_TYPE(IMode);

namespace icon
{
	namespace mode
	{
		const IMode DefaultSize(LR_DEFAULTSIZE);
		const IMode Transparent(LR_LOADTRANSPARENT);
		const IMode Monochrome(LR_MONOCHROME);
		const IMode TrueVGA(LR_VGACOLOR);
		const IMode LoadFromFile(LR_LOADFROMFILE);
		const IMode Default(DefaultSize);
	}
	namespace OEMicon
	{
		const HICON Asterisk = (HICON)LoadImage(0, MAKEINTRESOURCE(32516), IMAGE_ICON, 0, 0, LR_SHARED);
		const HICON Error = (HICON)LoadImage(0, MAKEINTRESOURCE(32513), IMAGE_ICON, 0, 0, LR_SHARED);
		const HICON Question = (HICON)LoadImage(0, MAKEINTRESOURCE(32514), IMAGE_ICON, 0, 0, LR_SHARED);
		const HICON Shield = (HICON)LoadImage(0, MAKEINTRESOURCE(32518), IMAGE_ICON, 0, 0, LR_SHARED);
		const HICON Warning = (HICON)LoadImage(0, MAKEINTRESOURCE(32515), IMAGE_ICON, 0, 0, LR_SHARED);
		const HICON Default = (HICON)LoadImage(0, MAKEINTRESOURCE(32512), IMAGE_ICON, 0, 0, LR_SHARED);
	}
}

class Icon
{
	private:
		HANDLE Handle;
	public:
		Icon();
		Icon(const HINSTANCE hInstance, const TCHAR *path, const IMode mode = icon::mode::Default, int desiredX = 0, int desiredY = 0);
		bool Load(const HINSTANCE hInstance, const TCHAR *path, const IMode mode = icon::mode::Default, int desiredX = 0, int desiredY = 0);
		operator HICON() const;
		bool Destroy();
		~Icon();
};
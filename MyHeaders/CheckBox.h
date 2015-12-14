#pragma once

#include <Windows.h>
#include <Windowsx.h>
#include <MyHeaders\windowdefs.h>

CREATE_NEW_DATA_TYPE(CBStyle);
CREATE_NEW_DATA_TYPE(CBState);

namespace checkbox
{
	namespace exstyle
	{
		//TODO
		const unsigned int Default = 0;
	}
	namespace style
	{
		const CBStyle Visible(WS_VISIBLE);
		const CBStyle ThreeState(BS_3STATE);
		const CBStyle AutoThreeState(BS_AUTO3STATE);
		const CBStyle AutoTwoState(BS_AUTOCHECKBOX);
		const CBStyle Default(AutoTwoState | Visible);
	}
	namespace state
	{
		const CBState Check(BST_CHECKED);
		const CBState Unckeck(BST_UNCHECKED);
		const CBState Indeterminate(BST_INDETERMINATE);
	}
}


class CheckBox
{
	private:
		HWND Handle;
	public:
		CheckBox();
		CheckBox(const TCHAR *title, const DWORD ID, const HWND parent, const int x, const int y, const int width, const int height, const CBStyle style = checkbox::style::Default, const DWORD exstyle = checkbox::exstyle::Default);
		bool Create(const TCHAR *title, const DWORD ID, const HWND parent, const int x, const int y, const int width, const int height, const CBStyle style = checkbox::style::Default, const DWORD exstyle = checkbox::exstyle::Default);
		bool IsEnabled();
		bool IsVisible();
		operator HWND();
		void SetState(const CBState state = checkbox::state::Check);
		unsigned int GetState();
		bool Destroy();
		~CheckBox();
};
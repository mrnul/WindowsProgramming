#pragma once

#include <Windows.h>
#include <MyHeaders\windowdefs.h>

CREATE_NEW_DATA_TYPE(LBStyle);

namespace listbox
{
	namespace exstyle
	{
		//TODO
		const unsigned int Default = 0;
	}
	namespace style
	{
		const LBStyle Visible(WS_VISIBLE);
		const LBStyle Border1(WS_BORDER);
		const LBStyle HorizontalScrollBar(WS_HSCROLL);
		const LBStyle VerticalScrollBar(WS_VSCROLL);
		const LBStyle MultipleSelect(LBS_EXTENDEDSEL);
		const LBStyle ComboBox(LBS_COMBOBOX);
		const LBStyle ScrollBars(LBS_DISABLENOSCROLL | VerticalScrollBar | HorizontalScrollBar);
		const LBStyle Strings(LBS_HASSTRINGS);
		const LBStyle MultiColumn(LBS_MULTICOLUMN);
		const LBStyle OnOff(LBS_MULTIPLESEL);
		const LBStyle NoSel(LBS_NOSEL);
		const LBStyle Notify(LBS_NOTIFY);
		const LBStyle Sort(LBS_SORT);
		const LBStyle Standard(LBS_STANDARD);
		const LBStyle KeyBoardInput(LBS_WANTKEYBOARDINPUT);
		const LBStyle Default(Strings | Border1 | Visible);
	}
}

class ListBox
{
	private:
		HWND Handle;
	public:
		ListBox();
		ListBox(const TCHAR *title, const DWORD ID, const HWND parent, const int x, const int y, const int width, const int height, const LBStyle style = listbox::style::Default, const DWORD exstyle = listbox::exstyle::Default);
		bool Create(const TCHAR *title, const DWORD ID, const HWND parent, const int x, const int y, const int width, const int height, const LBStyle style = listbox::style::Default, const DWORD exstyle = listbox::exstyle::Default);
		int AddString(const TCHAR *str);
		bool DeleteString(const int itemIndex);
		int FindString(const TCHAR *str, const int Index = -1);
		int FindStringExact(const TCHAR *str, const int Index = -1);
		int GetItemCount();
		int GetSelectedItem();
		int GetSelectedItems(const int maxcount, int *list);
		int GetSelectedItemCount();
		bool GetString(const int itemIndex, const char *buffer);
		int GetStringLength(const int itemIndex);
		bool InsertString(const TCHAR *str, const int Index);
		void Clear();
		int SelectString(const TCHAR *str, const int from = -1);
		BOOL sendMessage(UINT msg, LPARAM lp, WPARAM wp);
		operator HWND();
		bool Destroy();
		~ListBox();
};
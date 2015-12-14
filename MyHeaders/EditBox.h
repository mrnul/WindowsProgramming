#pragma once

#define MyHeaders_EditBox

#include <Windows.h>
#include <MyHeaders\windowdefs.h>
#include <Windowsx.h>

CREATE_NEW_DATA_TYPE(EBStyle);
CREATE_NEW_DATA_TYPE(EBExStyle);

namespace editbox
{
	namespace style
	{
		const EBStyle Border1(WS_BORDER);
		const EBStyle Border2(WS_DLGFRAME);
		const EBStyle Child(WS_CHILD);
		const EBStyle HorizontalScrollBar(WS_HSCROLL);
		const EBStyle VerticalScrollBar(WS_VSCROLL);
		const EBStyle ScrollBars(HorizontalScrollBar | VerticalScrollBar);
		const EBStyle Visible(WS_VISIBLE);
		const EBStyle PopUp(WS_POPUPWINDOW);
		const EBStyle SysMenu(WS_SYSMENU);
		const EBStyle Resizable(WS_THICKFRAME);

		const EBStyle AutoVScroll(ES_AUTOVSCROLL);
		const EBStyle AutoHScroll(ES_AUTOHSCROLL);
		const EBStyle AutoScroll(ES_AUTOVSCROLL | ES_AUTOHSCROLL);
		const EBStyle LeftAlignment(ES_LEFT);
		const EBStyle RightAlignment(ES_RIGHT);
		const EBStyle CenterAlignment(ES_CENTER);
		const EBStyle MultiLine(ES_MULTILINE);
		const EBStyle LowerCase(ES_LOWERCASE);
		const EBStyle Digits(ES_NUMBER);
		const EBStyle Password(ES_PASSWORD);
		const EBStyle ReadOnly(ES_READONLY);
		const EBStyle UpperCase(ES_UPPERCASE);
		const EBStyle EnterKey(ES_WANTRETURN);

		const EBStyle Default(Border1 | Visible);
	}
	namespace exstyle
	{
		const EBExStyle DragDrop(WS_EX_ACCEPTFILES);
		const EBExStyle AppWindow(WS_EX_APPWINDOW);
		const EBExStyle ClientEdge(WS_EX_CLIENTEDGE);
		const EBExStyle QuestionMark(WS_EX_CONTEXTHELP);
		const EBExStyle DoubleBorder(WS_EX_DLGMODALFRAME);
		const EBExStyle AlphaBlend(WS_EX_LAYERED);
		const EBExStyle LeftAlign(WS_EX_LEFT);
		const EBExStyle LeftScrollBar(WS_EX_LEFTSCROLLBAR);
		const EBExStyle Overlapped(WS_EX_OVERLAPPEDWINDOW);
		const EBExStyle Palette(WS_EX_PALETTEWINDOW);
		const EBExStyle RightAlign(WS_EX_RIGHT);
		const EBExStyle RightScrollBar(WS_EX_RIGHTSCROLLBAR);
		const EBExStyle StaticEdge(WS_EX_STATICEDGE);
		const EBExStyle ToolWindow(WS_EX_TOOLWINDOW);
		const EBExStyle TopMost(WS_EX_TOPMOST);
		const EBExStyle Transparent(WS_EX_TRANSPARENT);
		const EBExStyle RaisedEdge(WS_EX_WINDOWEDGE);
		const EBExStyle Default(0);
	}
}

class EditBox
{
	private:
		HWND Handle;
	public:
		EditBox();
		EditBox(const TCHAR *title, const DWORD ID, const HWND parent, const int x, const int y, const int width, const int height, const EBStyle style = editbox::style::Default, const EBExStyle exstyle = editbox::exstyle::Default);
		bool Create(const TCHAR *title, const DWORD ID, const HWND parent, const int x, const int y, const int width, const int height, const EBStyle style = editbox::style::Default, const EBExStyle exstyle = editbox::exstyle::Default);
		int GetText(TCHAR *txt, const int max);
		bool SetText(const TCHAR *txt);
		void Enable(const bool enable);
		int GetTextLength();
		bool IsVisible();
		bool IsEnabled();
		bool Destroy();
		operator HWND();
		~EditBox();
};
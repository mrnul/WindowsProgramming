#pragma once

#define MyHeaders_StaticBox

#include <Windows.h>

#include <MyHeaders\windowdefs.h>

CREATE_NEW_DATA_TYPE(SBStyle);
CREATE_NEW_DATA_TYPE(SBExStyle);

namespace staticbox
{

	namespace exstyle
	{
		const SBExStyle DragDrop(WS_EX_ACCEPTFILES);
		const SBExStyle AppWindow(WS_EX_APPWINDOW);
		const SBExStyle ClientEdge(WS_EX_CLIENTEDGE);
		const SBExStyle QuestionMark(WS_EX_CONTEXTHELP);
		const SBExStyle DoubleBorder(WS_EX_DLGMODALFRAME);
		const SBExStyle AlphaBlend(WS_EX_LAYERED);
		const SBExStyle LeftAlign(WS_EX_LEFT);
		const SBExStyle LeftScrollBar(WS_EX_LEFTSCROLLBAR);
		const SBExStyle Overlapped(WS_EX_OVERLAPPEDWINDOW);
		const SBExStyle Palette(WS_EX_PALETTEWINDOW);
		const SBExStyle RightAlign(WS_EX_RIGHT);
		const SBExStyle RightScrollBar(WS_EX_RIGHTSCROLLBAR);
		const SBExStyle StaticEdge(WS_EX_STATICEDGE);
		const SBExStyle ToolWindow(WS_EX_TOOLWINDOW);
		const SBExStyle TopMost(WS_EX_TOPMOST);
		const SBExStyle Transparent(WS_EX_TRANSPARENT);
		const SBExStyle RaisedEdge(WS_EX_WINDOWEDGE);
		const SBExStyle Default(0);
	}
	namespace style
	{
		const SBStyle Border1(WS_BORDER);
		const SBStyle Border2(WS_DLGFRAME);
		const SBStyle Child(WS_CHILD);
		const SBStyle HorizontalScrollBar(WS_HSCROLL);
		const SBStyle VerticalScrollBar(WS_VSCROLL);
		const SBStyle ScrollBars(VerticalScrollBar | HorizontalScrollBar);
		const SBStyle Maximized(WS_MAXIMIZE);
		const SBStyle Minimized(WS_MINIMIZE);
		const SBStyle MaximizeButton(WS_MAXIMIZEBOX);
		const SBStyle MinimizeButton(WS_MINIMIZEBOX);
		const SBStyle Overlapped(WS_OVERLAPPED);
		const SBStyle OverlappedWindow(WS_OVERLAPPEDWINDOW);
		const SBStyle Visible(WS_VISIBLE);
		const SBStyle PopUp(WS_POPUPWINDOW);
		const SBStyle SysMenu(WS_SYSMENU);
		const SBStyle Resizable(WS_THICKFRAME);

		const SBStyle Bitmap(SS_BITMAP);
		const SBStyle BlackFrame(SS_BLACKFRAME);
		const SBStyle BlackRect(SS_BLACKRECT);
		const SBStyle Center(SS_CENTER);
		const SBStyle CenterImage(SS_CENTERIMAGE);
		const SBStyle EditControl(SS_EDITCONTROL);
		const SBStyle EndEllipsis(SS_ENDELLIPSIS);
		const SBStyle Frame(SS_ETCHEDFRAME);
		const SBStyle TopBottom(SS_ETCHEDHORZ);
		const SBStyle LeftRight(SS_ETCHEDVERT);
		const SBStyle GrayFrame(SS_GRAYFRAME);
		const SBStyle GrayRect(SS_GRAYRECT);
		const SBStyle Icon(SS_ICON);
		const SBStyle LeftAlign(SS_LEFT);
		const SBStyle LeftNoWrap(SS_LEFTNOWORDWRAP);
		const SBStyle Notify(SS_NOTIFY);
		const SBStyle PathEllipsis(SS_PATHELLIPSIS);
		const SBStyle RealizeControl(SS_REALSIZECONTROL);
		const SBStyle RealizeImage(SS_REALSIZEIMAGE);
		const SBStyle RightAlign(SS_RIGHT);
		const SBStyle RightJust(SS_RIGHTJUST);
		const SBStyle Simple(SS_SIMPLE);
		const SBStyle Sunken(SS_SUNKEN);
		const SBStyle WhiteFrame(SS_WHITEFRAME);
		const SBStyle WhiteRect(SS_WHITERECT);
		const SBStyle WordEllipsis(SS_WORDELLIPSIS);
		const SBStyle Default(Visible);
	}
}

class StaticBox
{
	private:
		HWND Handle;
	public:
		StaticBox();
		StaticBox(const TCHAR *title, const DWORD ID, const HWND parent, const int x, const int y,
			const int width, const int height,
			const SBStyle style = staticbox::style::Default,
			const SBExStyle exstyle = staticbox::exstyle::Default);

		bool Create(const TCHAR *title, const DWORD ID, const HWND parent, const int x, const int y,
			const int width, const int height,
			const SBStyle style = staticbox::style::Default,
			const SBExStyle exstyle = staticbox::exstyle::Default);

		int GetText(TCHAR *txt, const int max);
		bool SetText(const TCHAR *txt);
		int GetTextLength();
		bool IsVisible();
		bool IsEnabled();
		LRESULT SetBitmap(const HBITMAP bmp);
		LRESULT SetIcon(const HICON icon);
		bool Destroy();
		operator HWND();
		~StaticBox();
};
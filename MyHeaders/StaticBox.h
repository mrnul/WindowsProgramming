#pragma once

#define MyHeaders_StaticBox

#include <Windows.h>

#include <MyHeaders\windowdefs.h>

CREATE_NEW_DATA_TYPE(SBStye);
CREATE_NEW_DATA_TYPE(SBExStye);

namespace staticbox
{

	namespace exstyle
	{
		const SBExStye DragDrop(WS_EX_ACCEPTFILES);
		const SBExStye AppWindow(WS_EX_APPWINDOW);
		const SBExStye ClientEdge(WS_EX_CLIENTEDGE);
		const SBExStye QuestionMark(WS_EX_CONTEXTHELP);
		const SBExStye DoubleBorder(WS_EX_DLGMODALFRAME);
		const SBExStye AlphaBlend(WS_EX_LAYERED);
		const SBExStye LeftAlign(WS_EX_LEFT);
		const SBExStye LeftScrollBar(WS_EX_LEFTSCROLLBAR);
		const SBExStye Overlapped(WS_EX_OVERLAPPEDWINDOW);
		const SBExStye Palette(WS_EX_PALETTEWINDOW);
		const SBExStye RightAlign(WS_EX_RIGHT);
		const SBExStye RightScrollBar(WS_EX_RIGHTSCROLLBAR);
		const SBExStye StaticEdge(WS_EX_STATICEDGE);
		const SBExStye ToolWindow(WS_EX_TOOLWINDOW);
		const SBExStye TopMost(WS_EX_TOPMOST);
		const SBExStye Transparent(WS_EX_TRANSPARENT);
		const SBExStye RaisedEdge(WS_EX_WINDOWEDGE);
		const SBExStye Default(0);
	}
	namespace style
	{
		const SBStye Border1(WS_BORDER);
		const SBStye Border2(WS_DLGFRAME);
		const SBStye Child(WS_CHILD);
		const SBStye HorizontalScrollBar(WS_HSCROLL);
		const SBStye VerticalScrollBar(WS_VSCROLL);
		const SBStye ScrollBars(VerticalScrollBar | HorizontalScrollBar);
		const SBStye Maximized(WS_MAXIMIZE);
		const SBStye Minimized(WS_MINIMIZE);
		const SBStye MaximizeButton(WS_MAXIMIZEBOX);
		const SBStye MinimizeButton(WS_MINIMIZEBOX);
		const SBStye Overlapped(WS_OVERLAPPED);
		const SBStye OverlappedWindow(WS_OVERLAPPEDWINDOW);
		const SBStye Visible(WS_VISIBLE);
		const SBStye PopUp(WS_POPUPWINDOW);
		const SBStye SysMenu(WS_SYSMENU);
		const SBStye Resizable(WS_THICKFRAME);

		const SBStye Bitmap(SS_BITMAP);
		const SBStye BlackFrame(SS_BLACKFRAME);
		const SBStye BlackRect(SS_BLACKRECT);
		const SBStye Center(SS_CENTER);
		const SBStye CenterImage(SS_CENTERIMAGE);
		const SBStye EditControl(SS_EDITCONTROL);
		const SBStye EndEllipsis(SS_ENDELLIPSIS);
		const SBStye Frame(SS_ETCHEDFRAME);
		const SBStye TopBottom(SS_ETCHEDHORZ);
		const SBStye LeftRight(SS_ETCHEDVERT);
		const SBStye GrayFrame(SS_GRAYFRAME);
		const SBStye GrayRect(SS_GRAYRECT);
		const SBStye Icon(SS_ICON);
		const SBStye LeftAlign(SS_LEFT);
		const SBStye LeftNoWrap(SS_LEFTNOWORDWRAP);
		const SBStye Notify(SS_NOTIFY);
		const SBStye PathEllipsis(SS_PATHELLIPSIS);
		const SBStye RealizeControl(SS_REALSIZECONTROL);
		const SBStye RealizeImage(SS_REALSIZEIMAGE);
		const SBStye RightAlign(SS_RIGHT);
		const SBStye RightJust(SS_RIGHTJUST);
		const SBStye Simple(SS_SIMPLE);
		const SBStye Sunken(SS_SUNKEN);
		const SBStye WhiteFrame(SS_WHITEFRAME);
		const SBStye WhiteRect(SS_WHITERECT);
		const SBStye WordEllipsis(SS_WORDELLIPSIS);
		const SBStye Default(Visible);
	}
}

class StaticBox
{
	private:
		HWND Handle;
	public:
		StaticBox();
		StaticBox(const TCHAR *title, const DWORD ID, const HWND parent, const int x, const int y, const int width, const int height, const SBStye style = staticbox::style::Default, const SBExStye exstyle = staticbox::exstyle::Default);
		bool Create(const TCHAR *title, const DWORD ID, const HWND parent, const int x, const int y, const int width, const int height, const SBStye style = staticbox::style::Default, const SBExStye exstyle = staticbox::exstyle::Default);
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
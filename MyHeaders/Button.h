#pragma once

#include <MyHeaders\windowdefs.h>
#include <Windows.h>
#include <Windowsx.h>
#include <Commctrl.h>
#pragma comment(lib,"Comctl32.lib")

CREATE_NEW_DATA_TYPE(BStyle);
CREATE_NEW_DATA_TYPE(BExStyle);

namespace button
{
	namespace exstyle
	{
		const BExStyle DragDrop(WS_EX_ACCEPTFILES);
		const BExStyle AppWindow(WS_EX_APPWINDOW);
		const BExStyle ClientEdge(WS_EX_CLIENTEDGE);
		const BExStyle QuestionMark(WS_EX_CONTEXTHELP);
		const BExStyle DoubleBorder(WS_EX_DLGMODALFRAME);
		const BExStyle AlphaBlend(WS_EX_LAYERED);
		const BExStyle LeftAlign(WS_EX_LEFT);
		const BExStyle LeftScrollBar(WS_EX_LEFTSCROLLBAR);
		const BExStyle Overlapped(WS_EX_OVERLAPPEDWINDOW);
		const BExStyle Palette(WS_EX_PALETTEWINDOW);
		const BExStyle RightAlign(WS_EX_RIGHT);
		const BExStyle RightScrollBar(WS_EX_RIGHTSCROLLBAR);
		const BExStyle StaticEdge(WS_EX_STATICEDGE);
		const BExStyle ToolWindow(WS_EX_TOOLWINDOW);
		const BExStyle TopMost(WS_EX_TOPMOST);
		const BExStyle Transparent(WS_EX_TRANSPARENT);
		const BExStyle RaisedEdge(WS_EX_WINDOWEDGE);
		const BExStyle Default(0);
	}
	namespace style
	{
		const BStyle Border1(WS_BORDER);
		const BStyle Border2(WS_DLGFRAME);
		const BStyle Child(WS_CHILD);
		const BStyle HorizontalScrollBar(WS_HSCROLL);
		const BStyle VerticalScrollBar(WS_VSCROLL);
		const BStyle ScrollBars(VerticalScrollBar | HorizontalScrollBar);
		const BStyle Maximized(WS_MAXIMIZE);
		const BStyle Minimized(WS_MINIMIZE);
		const BStyle MaximizeButton(WS_MAXIMIZEBOX);
		const BStyle MinimizeButton(WS_MINIMIZEBOX);
		const BStyle Overlapped(WS_OVERLAPPED);
		const BStyle OverlappedWindow(WS_OVERLAPPEDWINDOW);
		const BStyle Visible(WS_VISIBLE);
		const BStyle PopUp(WS_POPUPWINDOW);
		const BStyle SysMenu(WS_SYSMENU);
		const BStyle Resizable(WS_THICKFRAME);
		const BStyle Bitmap(BS_BITMAP);
		const BStyle BottomText(BS_BOTTOM);
		const BStyle CenterText(BS_CENTER);
		const BStyle TopText(BS_TOP);
		const BStyle Icon(BS_ICON);
		const BStyle MultiLine(BS_MULTILINE);
		const BStyle DefPush(BS_DEFPUSHBUTTON);
		const BStyle Border(WS_BORDER);
		const BStyle DoubleFrame(WS_DLGFRAME);
		const BStyle Flat(BS_FLAT);
		const BStyle AutoRadio(BS_AUTORADIOBUTTON);
		const BStyle Radio(BS_RADIOBUTTON);
		const BStyle GroupBox(BS_GROUPBOX);
		const BStyle Group(WS_GROUP);
		const BStyle Default(Visible);
	}
}

class Button
{
	private:
		HWND Handle;
	public:
		Button();
		Button(const TCHAR *title, const DWORD ID, const HWND parent, const int x, const int y, const int width, const int height, const BStyle style = button::style::Default, const BExStyle exstyle = button::exstyle::Default);
		bool Create(const TCHAR *title, const DWORD ID, const HWND parent, const int x, const int y, const int width, const int height, const BStyle style = button::style::Default, const BExStyle exstyle = button::exstyle::Default);
		LRESULT SetBitmap(const HBITMAP bmp);
		LRESULT SetIcon(const HICON icon);
		bool IsEnabled();
		bool IsVisible();
		void Enable(bool enable = true);
		bool SetControlProc(SUBCLASSPROC proc, UINT_PTR id = 0, DWORD_PTR data = 0);
		bool RemoveControlProc(SUBCLASSPROC proc, UINT_PTR id = 0);
		operator HWND();
		bool Destroy();
		~Button();
};
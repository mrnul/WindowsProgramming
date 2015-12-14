#pragma once

#define MyHeaders_Window

#include <Windows.h>
#include <MyHeaders\windowdefs.h>
#include <MyHeaders\WindowClass.h>

#ifdef _UNICODE
#define WINMAIN(hInstance, pCmdLine, nCmdShow)  int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
#else
#define WINMAIN(hInstance, pCmdLine, nCmdShow)  int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
#endif

CREATE_NEW_DATA_TYPE(WStyle);
CREATE_NEW_DATA_TYPE(WExStyle);

namespace window
{
	namespace position
	{
		const unsigned int Default = CW_USEDEFAULT;
	}
	namespace style
	{
		const WStyle Border1(WS_BORDER);
		const WStyle Border2(WS_DLGFRAME);
		const WStyle Child(WS_CHILD);
		const WStyle HorizontalScrollBar(WS_HSCROLL);
		const WStyle VerticalScrollBar(WS_VSCROLL);
		const WStyle ScrollBars(VerticalScrollBar | HorizontalScrollBar);
		const WStyle Maximized(WS_MAXIMIZE);
		const WStyle Minimized(WS_MINIMIZE);
		const WStyle MaximizeButton(WS_MAXIMIZEBOX);
		const WStyle MinimizeButton(WS_MINIMIZEBOX);
		const WStyle Overlapped(WS_OVERLAPPED);
		const WStyle OverlappedWindow(WS_OVERLAPPEDWINDOW);
		const WStyle Visible(WS_VISIBLE);
		const WStyle PopUp(WS_POPUPWINDOW);
		const WStyle SysMenu(WS_SYSMENU);
		const WStyle Resizable(WS_THICKFRAME); 
		const WStyle Default(WS_OVERLAPPEDWINDOW | WS_VISIBLE);
	}
	namespace exstyle
	{
		const WExStyle DragDrop(WS_EX_ACCEPTFILES);
		const WExStyle AppWindow(WS_EX_APPWINDOW);
		const WExStyle ClientEdge(WS_EX_CLIENTEDGE);
		const WExStyle QuestionMark(WS_EX_CONTEXTHELP);
		const WExStyle DoubleBorder(WS_EX_DLGMODALFRAME);
		const WExStyle AlphaBlend(WS_EX_LAYERED);
		const WExStyle LeftAlign(WS_EX_LEFT);
		const WExStyle LeftScrollBar(WS_EX_LEFTSCROLLBAR);
		const WExStyle Overlapped(WS_EX_OVERLAPPEDWINDOW);
		const WExStyle Palette(WS_EX_PALETTEWINDOW);
		const WExStyle RightAlign(WS_EX_RIGHT);
		const WExStyle RightScrollBar(WS_EX_RIGHTSCROLLBAR);
		const WExStyle StaticEdge(WS_EX_STATICEDGE);
		const WExStyle ToolWindow(WS_EX_TOOLWINDOW);
		const WExStyle TopMost(WS_EX_TOPMOST);
		const WExStyle Transparent(WS_EX_TRANSPARENT);
		const WExStyle RaisedEdge(WS_EX_WINDOWEDGE);
		const WExStyle Default(0);
	}
}


class Window
{
	private:
		MSG msg;
		HWND Handle;
	public:
		Window();

		Window(const TCHAR *classname, const TCHAR *windowname, 
			const WStyle style, 
			const int x, const int y, 
			const int width, const int height, 
			const HWND parent, const HMENU menuID);

		Window(const TCHAR *classname, const TCHAR *windowname, 
			const WStyle style = window::style::Default, 
			const int x = window::position::Default, const int y = window::position::Default, 
			const int width = window::position::Default, const int height = window::position::Default);

		bool Create(const TCHAR *classname, const TCHAR *windowname,
			const WStyle style, 
			const int x, const int y, 
			const int width, const int height, 
			const HWND parent, 
			const HMENU menuID);


		bool Create(const TCHAR *classname, const TCHAR *windowname, 
			const WStyle style = window::style::Default, 
			const int x = window::position::Default, const int y = window::position::Default, 
			const int width = window::position::Default, const int height = window::position::Default);

		void getWindowRect(RECT *out);
		bool SetOpacity(BYTE value);
		void getClientRect(RECT *out);
		void SetAppData(const void *data);
		void* GetAppData();
		bool getMessage();
		unsigned int sendMessage();
		HDC getDC();
		HDC getWindowDC();
		bool releaseDC(HDC dc);
		bool getMessageNoWait();
		void SetTitle(const TCHAR *title);
		bool MessageAvailable();
		void MessageLoop();
		bool IsEnabled();
		bool IsVisible();
		bool Destroy();
		bool Update();
		operator HWND();
		~Window();
};
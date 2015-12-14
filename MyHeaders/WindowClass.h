#pragma once

#define MyHeaders_WindowClass

#include <Windows.h>
#include <MyHeaders\WindowClass.h>
#include <MyHeaders\Cursor.h>
#include <MyHeaders\Icon.h>
#include <MyHeaders\windowdefs.h>

#define WINPROC(WinProcName,HandleName,MsgName,WparamName,LparamName) LRESULT CALLBACK WinProcName(HWND HandleName,UINT MsgName,WPARAM WparamName,LPARAM LparamName)
#define WINPROCDEF(WinProcName) LRESULT CALLBACK WinProcName(HWND handle,UINT msg,WPARAM wp,LPARAM lp)

WINPROC(BasicProc, handle, msg, wp, lp);

CREATE_NEW_DATA_TYPE(WCStyle);
CREATE_NEW_DATA_TYPE(WCColor);

namespace windowclass
{
	namespace color
	{
		const WCColor ActiveBorder(COLOR_ACTIVEBORDER);
		const WCColor ActiveCaption(COLOR_ACTIVECAPTION);
		const WCColor WorkSpace(COLOR_APPWORKSPACE);
		const WCColor Background(COLOR_BACKGROUND);
		const WCColor ButtonFace(COLOR_BTNFACE);
		const WCColor ButtonShadow(COLOR_BTNSHADOW);
		const WCColor ButtonText(COLOR_BTNTEXT);
		const WCColor CaptionText(COLOR_CAPTIONTEXT);
		const WCColor GrayText(COLOR_GRAYTEXT);
		const WCColor Highlight(COLOR_HIGHLIGHT);
		const WCColor HightlightText(COLOR_HIGHLIGHTTEXT);
		const WCColor InactiveBorder(COLOR_INACTIVEBORDER);
		const WCColor InactiveCaption(COLOR_INACTIVECAPTION);
		const WCColor Menu(COLOR_MENU);
		const WCColor MenuText(COLOR_MENUTEXT);
		const WCColor ScrollBar(COLOR_SCROLLBAR);
		const WCColor Window(COLOR_WINDOW);
		const WCColor WindowFrame(COLOR_WINDOWFRAME);
		const WCColor WindowText(COLOR_WINDOWTEXT);
		const WCColor Default(Window);
	}
	namespace style
	{
		const WCStyle AlignClient(CS_BYTEALIGNCLIENT);
		const WCStyle AlignWindow(CS_BYTEALIGNWINDOW);
		const WCStyle DoubleClicks(CS_DBLCLKS);
		const WCStyle DropShadow(CS_DROPSHADOW);
		const WCStyle WidthReDraw(CS_HREDRAW);
		const WCStyle HeightReDraw(CS_VREDRAW);
		const WCStyle NoClose(CS_NOCLOSE);
		const WCStyle ReDraw(CS_VREDRAW | CS_HREDRAW);
		const WCStyle Default(ReDraw);
	}

	const WNDPROC BasicWindowProc = BasicProc;
}

class WindowClass
{
	private:
		WNDCLASSEX WinClass;
		bool Registered;
	public:
		WindowClass();
		WindowClass(const TCHAR* name, const WNDPROC proc = windowclass::BasicWindowProc,
			const WCStyle style = windowclass::style::Default, const HCURSOR cursor = cursor::OEMcursor::Default,
			const HICON icon = icon::OEMicon::Default,
			const WCColor color = windowclass::color::Default);
		
		bool Register(const TCHAR* name, const WNDPROC proc = windowclass::BasicWindowProc,
			const WCStyle style = windowclass::style::Default, const HCURSOR cursor = cursor::OEMcursor::Default,
			const HICON icon = icon::OEMicon::Default,
			const WCColor color = windowclass::color::Default);

		bool Unregister();
		const WNDCLASSEX GetClass();
		operator bool();
		~WindowClass();
};
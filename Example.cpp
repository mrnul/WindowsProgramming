#include <MyHeaders\Window.h>

WINMAIN(hin, cmd, show)
{
	WindowClass wclass("test", windowclass::BasicWindowProc, windowclass::style::Default, cursor::OEMcursor::Help,icon::OEMicon::Error);
	Window win("test", "Testing!", window::style::Default, 100, 100, 200, 200);

	win.MessageLoop();

	return 0;
}
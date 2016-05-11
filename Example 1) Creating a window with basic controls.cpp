#include <MyHeaders\Window.h>
#include <MyHeaders\Button.h>
#include <MyHeaders\EditBox.h>
#include <MyHeaders\StaticBox.h>
#include <MyHeaders\CheckBox.h>
#include <MyHeaders\ListBox.h>


WINMAIN(hin, cmd, show)
{
	WindowClass wclass("test", windowclass::BasicWindowProc, windowclass::style::Default, cursor::OEMcursor::Hand, icon::OEMicon::Question);
	Window win("test", "Testing!", window::style::SysMenu | window::style::Visible, 100, 100, 200, 400);
	
	//basic controls
	Button btn("Hey! I am a button.", 90000, win, 10, 10, 160, 30);
	EditBox eb("Hey! Edit box here.", 90001, win, 10, 50, 160, 30);
	StaticBox sb("Hey! Static box here.", 90002, win, 10, 90, 160, 30, staticbox::style::Default | staticbox::style::Border1);
	CheckBox cb("Hey! check box here.", 90003, win, 10, 130, 160, 30);
	ListBox lb("", 90004, win, 10, 170, 160, 80);
	lb.AddString("Item 1");
	lb.AddString("Item 2");
	lb.AddString("Item 3");

	//static box with an icon
	StaticBox sbIcon("", 90005, win, 10, 240, 160, 30, staticbox::style::Icon | staticbox::style::Default | staticbox::style::Border1);
	sbIcon.SetIcon(icon::OEMicon::Shield);

	
	
	//list view coming soon...
	//i lied, list views bore me to death
	
	win.MessageLoop();

	return 0;
}

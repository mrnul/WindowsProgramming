#include <MyHeaders\Dialog.h>
#include <MyHeaders\Button.h>
#include <MyHeaders\CheckBox.h>
#include <MyHeaders\ListView.h>
#include <string>
using std::wstring;
using std::to_wstring;
#include "resource.h"

struct Controls
{
	Button btn;
	CheckBox cbox;
	ListView lv;
};

DIALOGPROC(proc, handle, msg, wp, lp)
{
	//initialize objects
	if (msg == WM_INITDIALOG)
	{
		Controls *c = (Controls*)lp;

		c->btn.Init(handle, IDC_BUTTON1);
		c->cbox.Init(handle, IDC_CHECK1);
		c->lv.Init(handle, IDC_LIST1);

		c->cbox.SetState(checkbox::state::Check);
		c->lv.AddColumn(L"This is a test", 0, 200);

		return 1;
	}

	if (msg == WM_COMMAND)
	{
		if (LOWORD(wp) == IDCANCEL)
		{
			DestroyWindow(handle);
			return 1;
		}

		Controls *c = (Controls*)GetWindowLongPtr(handle, GWLP_USERDATA);

		if (LOWORD(wp) == IDC_BUTTON1)
		{
			//create a random number, convert it to wstring
			wstring str = to_wstring(rand()).c_str();

			//add it to the list view
			c->lv.InsertText((TCHAR*)str.c_str(), 0);
			return 1;
		}

		if (LOWORD(wp) == IDC_CHECK1)
		{
			c->btn.Enable(c->cbox.GetState());
			return 1;
		}
	}
	return 0;
}

WINMAIN(hin, cmd, show)
{
	Controls ctrl;

	//the address of ctrl will be passed as the LPARAM for WM_INITDIALOG
	Dialog d(IDD_DIALOG1, proc, &ctrl);

	//the address of ctrl will be available via GetWindowLongPtr
	d.SetWLongPtr(GWLP_USERDATA, (LONG_PTR)&ctrl);

	//run until user quits
	d.MessageLoop();
}
#pragma once

#include <Windows.h>
#include <CommCtrl.h>
#include <tchar.h>

#pragma comment(linker, \
  "\"/manifestdependency:type='Win32' "\
  "name='Microsoft.Windows.Common-Controls' "\
  "version='6.0.0.0' "\
  "processorArchitecture='*' "\
  "publicKeyToken='6595b64144ccf1df' "\
  "language='*'\"")

#pragma comment(lib, "ComCtl32.lib")

#define DIALOGPROC(name, handle, msg, wp ,lp) INT_PTR CALLBACK name(HWND handle, UINT msg, WPARAM wp, LPARAM lp)
#define WINMAIN(hInst, cmd, show) int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE h0, LPTSTR cmd, int show)

class Dialog
{
	private:
		HWND Handle;
		MSG msg;
	public:
		Dialog();
		Dialog(const unsigned int ID, DLGPROC proc, void *param = 0, HWND parent = 0);
		bool Create(const unsigned int ID, DLGPROC proc, void *param = 0, HWND parent = 0);
		bool SetWLongPtr(int index, void *newValue);
		LONG_PTR GetWLongPtr(int index);
		void MessageLoop();
		bool MessageWaiting();
		bool GetAndProcessMessage();
		void Destroy();
		operator HWND();
		~Dialog();
};
#pragma once

#include <Windows.h>
#include <Windowsx.h>
#include <Commctrl.h>
#pragma comment(lib,"Comctl32.lib")

class ControlBaseClass
{
	protected:
		HWND ParentHandle;
		HWND ControlHandle;
		unsigned int ControlID;
	public:
		ControlBaseClass();
		ControlBaseClass(HWND parent, const unsigned int id);
		bool Init(HWND parent, const unsigned int id);
		bool SetWLongPtr(int index, void *newValue);
		LONG_PTR GetWLongPtr(int index);
		void Enable(const bool enable = true);
		bool IsEnabled();
		void Hide();
		void Show();
		unsigned int ID();
		HWND Handle();
		HWND Parent();
		bool Destroy();
};
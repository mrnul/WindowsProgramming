#include <MyHeaders\ListBox.h>



ListBox::ListBox()
{
	Handle = 0;
}

ListBox::ListBox(const TCHAR *title, const DWORD ID, const HWND parent, const int x, const int y, const int width, const int height, const LBStyle style, const DWORD exstyle)
{
	Create(title, ID, parent, x, y, width, height, style, exstyle);
}

ListBox::operator HWND()
{
	return Handle;
}

bool ListBox::Create(const TCHAR *title, const DWORD ID, const HWND parent, const int x, const int y, const int width, const int height, const LBStyle style, const DWORD exstyle)
{
	return (Handle = CreateWindowEx(exstyle, TEXT("listbox"), title, style.operator unsigned int() | WS_CHILD | WS_VISIBLE, x, y, width, height, parent, (HMENU)ID, GetModuleHandle(0), 0)) != 0;
}

int ListBox::AddString(const TCHAR *str)
{
	return SendMessage(Handle, LB_ADDSTRING, 0, (LPARAM)str);
}

bool ListBox::DeleteString(const int itemIndex)
{
	return SendMessage(Handle, LB_DELETESTRING, (WPARAM)itemIndex, 0) != LB_ERR;
}

int ListBox::FindString(const TCHAR *str, const int Index)
{
	return SendMessage(Handle, LB_FINDSTRING, Index, (WPARAM)str);
}

int ListBox::FindStringExact(const TCHAR *str, const int Index)
{
	return SendMessage(Handle, LB_FINDSTRINGEXACT, Index, (WPARAM)str);
}

int ListBox::GetItemCount()
{
	return SendMessage(Handle, LB_GETCOUNT, 0, 0);
}

int ListBox::GetSelectedItem()
{
	return SendMessage(Handle, LB_GETCURSEL, 0, 0);
}

int ListBox::GetSelectedItems(const int maxcount, int *list)
{
	return SendMessage(Handle, LB_GETSELITEMS, maxcount, (LPARAM)list);
}

int ListBox::GetSelectedItemCount()
{
	return SendMessage(Handle, LB_GETSELCOUNT, 0, 0);
}

bool ListBox::GetString(const int itemIndex, const char *buffer)
{
	return SendMessage(Handle, LB_GETTEXT, itemIndex, (WPARAM)buffer) != LB_ERR;
}

int ListBox::GetStringLength(const int itemIndex)
{
	return SendMessage(Handle, LB_GETTEXTLEN, itemIndex, 0);
}

bool ListBox::InsertString(const TCHAR *str, const int Index)
{
	BOOL res = SendMessage(Handle, LB_INSERTSTRING, Index, (WPARAM)str);
	return (res != LB_ERR && res != LB_ERRSPACE);
}

void ListBox::Clear()
{
	SendMessage(Handle, LB_RESETCONTENT, 0, 0);
}
int ListBox::SelectString(const TCHAR *str, const int Index)
{
	return SendMessage(Handle, LB_SELECTSTRING, Index, (WPARAM)str);
}

BOOL ListBox::sendMessage(UINT msg, LPARAM lp, WPARAM wp)
{
	return SendMessage(Handle, msg, wp, lp);
}

bool ListBox::Destroy()
{
	if (!Handle)
		return true;
	if (!DestroyWindow(Handle))
		return false;

	Handle = 0;
	return true;;
}

ListBox::~ListBox()
{
	Destroy();
}

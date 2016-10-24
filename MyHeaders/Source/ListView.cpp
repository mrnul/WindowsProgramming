#include <MyHeaders\ListView.h>

bool ListView::AddColumn(TCHAR * title, const int pos, const int width)
{
	LVCOLUMN lvc = {};
	lvc.mask = LVCF_TEXT | LVCF_WIDTH;
	lvc.cx = width;
	lvc.pszText = title;
	return ListView_InsertColumn(ControlHandle, pos, &lvc) != -1;
}

bool ListView::InsertText(TCHAR * txt, const int pos)
{
	LVITEM lvI = {};
	lvI.mask = LVIF_TEXT;
	lvI.pszText = txt;
	lvI.iItem = pos;
	return ListView_InsertItem(ControlHandle, &lvI) != -1;
}

void ListView::SetItemText(TCHAR * txt, const int pos, const int column)
{
	ListView_SetItemText(ControlHandle, pos, column, txt);
}

void ListView::GetItemText(TCHAR * buffer, const int pos, const int column, const int maxChars)
{
	ListView_GetItemText(ControlHandle, pos, column, buffer, maxChars);
}

bool ListView::DeleteItem(const unsigned int pos)
{
	return ListView_DeleteItem(ControlHandle, pos) != 0;
}

bool ListView::DeleteAllItems()
{
	return ListView_DeleteAllItems(ControlHandle) != 0;
}

unsigned int ListView::GetItemCount()
{
	return ListView_GetItemCount(ControlHandle);
}

unsigned int ListView::GetSelectedItem(const int startPos)
{
	return ListView_GetNextItem(ControlHandle, startPos, LVNI_SELECTED);
}

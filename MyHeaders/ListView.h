#pragma once

#include <MyHeaders\ControlBaseClass.h>

class ListView : public ControlBaseClass
{
	public:
		bool AddColumn(TCHAR *title, const int pos, const int width);
		bool InsertText(TCHAR *txt, const int pos);
		void SetItemText(TCHAR *txt, const int pos, const int column);
		void GetItemText(TCHAR *buffer, const int pos, const int column, const int maxChars);
		bool DeleteItem(const unsigned int pos);
		bool DeleteAllItems();
		unsigned int GetItemCount();
		unsigned int GetSelectedItem(const int startPos = -1);
};
#pragma once

#include <MyHeaders\ControlBaseClass.h>
#include <MyHeaders\windowdefs.h>

CREATE_NEW_DATA_TYPE(CBState);

namespace checkbox
{
	namespace state
	{
		const CBState Check(BST_CHECKED);
		const CBState Unckeck(BST_UNCHECKED);
		const CBState Indeterminate(BST_INDETERMINATE);
	}
}


class CheckBox : public ControlBaseClass
{
	public:
		void SetState(const CBState state = checkbox::state::Check);
		unsigned int GetState();
};
#pragma once
#define MyHeaders_Heap

#include <Windows.h>

//save heap of current process for later use
namespace heap
{
	const HANDLE CurrentProcessHeap = GetProcessHeap();
}

//-------------------------simple heap functions--------------------------------------------

template<class TYPE>
TYPE* halloc(const SIZE_T elCount)
{
	return (TYPE*)HeapAlloc(heap::CurrentProcessHeap, 0, elCount*sizeof(TYPE));
}

template<class TYPE>
TYPE* hrealloc(const TYPE* pointer, const SIZE_T newElCount)
{
	return (TYPE*)HeapReAlloc(heap::CurrentProcessHeap, 0, pointer, newElCount*sizeof(TYPE));
}

template <class TYPE>
bool hfree(TYPE &pointer)
{
	if (HeapFree(heap::CurrentProcessHeap, 0, pointer))
	{
		pointer = 0;
		return true;
	}
	return false;
}

template<class TYPE>
bool AllocAndCopy(TYPE *&dest, const TYPE *source, const SIZE_T elCount)
{
	if (!(dest = halloc<TYPE>(elCount)))
		return false;
	memcpy(dest, source, elCount*sizeof(TYPE));
	return true;
}
//END----------------------simple heap functions--------------------------------------------
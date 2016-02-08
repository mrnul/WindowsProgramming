#pragma once

#define MyHeaders_Buffer

#include <Windows.h>

template<class TYPE>
class Buffer
{
	private:
		TYPE *Pointer;
		unsigned int Elements;
	public:
		Buffer();
		Buffer(const unsigned int elementsCount);
		bool Alloc(const unsigned int elementsCount);
		bool Realloc(const unsigned int elementsCount);
		bool Free();
		unsigned int GetElementsCount() const;
		unsigned int GetSizeBytes() const;
		TYPE& operator[](const int i);
		operator TYPE*() const;
		bool Lock() const;
		bool Unlock() const;
		void FillByte(const unsigned char value);
		void SetZero();
		bool AllocAndCopy(const TYPE *source, const unsigned int elementsCount);
		void Copy(const TYPE *source, const unsigned int bytes);
		TYPE* GetPointer(const unsigned int offsetElement = 0) const;
		~Buffer();
};

template<class TYPE>
Buffer<TYPE>::Buffer()
{
	Pointer = 0;
	Elements = 0;
}

template<class TYPE>
Buffer<TYPE>::Buffer(const unsigned int elementsCount)
{
	Pointer = 0;
	Alloc(elementsCount);
}

template<class TYPE>
void Buffer<TYPE>::FillByte(const unsigned char value)
{
	FillMemory(Pointer, sizeof(TYPE)*Elements, value);
}

template<class TYPE>
bool Buffer<TYPE>::AllocAndCopy(const TYPE *source, const unsigned int elements)
{
	const unsigned int size = elements*sizeof(TYPE);
	if (!Alloc(elements))
		return false;
	memcpy(Pointer, source, size);
	return true;
}

template<class TYPE>
bool Buffer<TYPE>::Alloc(const unsigned int elementsCount)
{
	return (Pointer = (TYPE*)HeapAlloc(heap::CurrentProcessHeap, HEAP_ZERO_MEMORY, (Elements = elementsCount)*sizeof(TYPE))) != 0;
}

template<class TYPE>
bool Buffer<TYPE>::Realloc(const unsigned int elementsCount)
{
	void *tmpPointer;
	if (tmpPointer = HeapReAlloc(heap::CurrentProcessHeap, 0, Pointer, elementsCount*sizeof(TYPE)))
	{
		Pointer = (TYPE*)tmpPointer;
		Elements = elementsCount;
	}
	return (tmpPointer == Pointer);
}


template<class TYPE>
bool Buffer<TYPE>::Free()
{
	if (!Pointer)
		return true;
	if (HeapFree(heap::CurrentProcessHeap, 0, Pointer))
	{
		Pointer = 0;
		Elements = 0;
		return true;
	}

	return false;

}

template<class TYPE>
unsigned int Buffer<TYPE>::GetElementsCount() const
{
	return Elements;
}

template<class TYPE>
unsigned int Buffer<TYPE>::GetSizeBytes() const
{
	return Elements*sizeof(TYPE);
}

template<class TYPE>
TYPE& Buffer<TYPE>::operator[](const int i)
{
	return Pointer[i];
}

template<class TYPE>
Buffer<TYPE>::operator TYPE*() const
{
	return Pointer;
}

template<class TYPE>
TYPE* Buffer<TYPE>::GetPointer(const unsigned int offsetElement) const
{
	return &Pointer[offsetElement];
}

template<class TYPE>
bool Buffer<TYPE>::Lock() const
{
	return HeapLock(heap::CurrentProcessHeap) != 0;
}

template<class TYPE>
bool Buffer<TYPE>::Unlock() const
{
	return HeapUnlock(heap::CurrentProcessHeap) != 0;
}

template<class TYPE>
void Buffer<TYPE>::SetZero()
{
	memset(Pointer, 0, Elements*sizeof(TYPE));
}

template<class TYPE>
void Buffer<TYPE>::Copy(const TYPE *source, const unsigned int bytes)
{
	memcpy(Pointer, source, bytes);
}

template<class TYPE>
Buffer<TYPE>::~Buffer()
{
	Free();
}
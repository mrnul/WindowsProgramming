#pragma once

#define MyHeaders_Event
#include <Windows.h>
#undef min //i can't use std::min


class Event
{
	private:
		HANDLE Handle;
	public:
		Event(const TCHAR *name = 0)
		{
			Handle = 0;
			Init(name);
		}

		bool Init(const TCHAR *name = 0)
		{
			if (Handle)
				return false;

			return (Handle = CreateEvent(0, true, false, name)) != 0;
		}

		bool IsSignaled() const
		{
			return WaitForSingleObject(Handle, 0) != WAIT_TIMEOUT;
		}

		bool Signal() const
		{
			return SetEvent(Handle) != 0;
		}

		bool Reset() const
		{
			return ResetEvent(Handle) != 0;
		}

		bool Close()
		{
			if (!Handle)
				return true;
			if (CloseHandle(Handle) == 0)
				return false;

			Handle = 0;
			return true;
		}

		bool Wait(const unsigned int ms = INFINITE) const
		{
			return WaitForSingleObject(Handle, ms) != WAIT_TIMEOUT;
		}

		HANDLE GetHandle() const
		{
			return Handle;
		}

		operator bool() const
		{
			return IsSignaled();
		}

		~Event()
		{
			Close();
		}
};
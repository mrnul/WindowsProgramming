#pragma once

#define MyHeaders_Event


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

		bool IsSignaled()
		{
			return WaitForSingleObject(Handle, 0) != WAIT_TIMEOUT;
		}

		bool Set()
		{
			return SetEvent(Handle) != 0;
		}

		bool Reset()
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

		bool Wait(const unsigned int ms = INFINITE)
		{
			return WaitForSingleObject(Handle, ms) != WAIT_TIMEOUT;
		}

		HANDLE GetHandle()
		{
			return Handle;
		}

		operator bool()
		{
			return IsSignaled();
		}

		~Event()
		{
			Close();
		}
};
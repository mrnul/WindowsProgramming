#pragma once

#define MyHeaders_File

#include <Windows.h>
#include <MyHeaders\Heap.h>
#include <tchar.h>
#include <MyHeaders\windowdefs.h>

CREATE_NEW_DATA_TYPE(FAccess);
CREATE_NEW_DATA_TYPE(FMode);
CREATE_NEW_DATA_TYPE(FFlag);
CREATE_NEW_DATA_TYPE(FShare);
CREATE_NEW_DATA_TYPE(FMethod);

namespace file
{
	namespace access
	{
		const FAccess Read(GENERIC_READ);
		const FAccess Write(GENERIC_WRITE);
		const FAccess ReadWrite(Read | Write);
	}
	namespace openmode
	{
		const FMode OpenAlways(OPEN_ALWAYS);
		const FMode OpenExisting(OPEN_EXISTING);
		const FMode CreateAlways(CREATE_ALWAYS);
		const FMode CreateNew(CREATE_NEW);
		const FMode Truncate(TRUNCATE_EXISTING);
	}
	namespace flag
	{
		const FFlag NoBuffer(FILE_FLAG_NO_BUFFERING);
		const FFlag Normal(FILE_ATTRIBUTE_NORMAL);
		const FFlag Hidden(FILE_ATTRIBUTE_HIDDEN);
		const FFlag NoCache(FILE_FLAG_WRITE_THROUGH);
		const FFlag ReadOnly(FILE_ATTRIBUTE_READONLY);
		const FFlag RndAccess(FILE_FLAG_RANDOM_ACCESS);
		const FFlag SeqAccess(FILE_FLAG_SEQUENTIAL_SCAN);
		const FFlag DelOnClose(FILE_FLAG_DELETE_ON_CLOSE);
		const FFlag Temp(FILE_ATTRIBUTE_TEMPORARY);
	}
	namespace share
	{
		const FShare Read(FILE_SHARE_READ);
		const FShare Write(FILE_SHARE_WRITE);
		const FShare DeleteRename(FILE_SHARE_DELETE);
		const FShare ReadWrite(Read | Write);
		const FShare All(ReadWrite | DeleteRename);
	}
	namespace method
	{
		const FMethod Begin(FILE_BEGIN);
		const FMethod Current(FILE_CURRENT);
		const FMethod End(FILE_END);
	}
}

CREATE_NEW_DATA_TYPE(FAttribute);

namespace enumfiles
{
	namespace attribute
	{
		const FAttribute Archive(FILE_ATTRIBUTE_ARCHIVE);
		const FAttribute Compressed(FILE_ATTRIBUTE_COMPRESSED);
		const FAttribute Device(FILE_ATTRIBUTE_DEVICE);
		const FAttribute Directory(FILE_ATTRIBUTE_DIRECTORY);
		const FAttribute Encrypted(FILE_ATTRIBUTE_ENCRYPTED);
		const FAttribute Hidden(FILE_ATTRIBUTE_HIDDEN);
		const FAttribute Normal(FILE_ATTRIBUTE_NORMAL);
		const FAttribute NotIndexed(FILE_ATTRIBUTE_NOT_CONTENT_INDEXED);
		const FAttribute Offline(FILE_ATTRIBUTE_OFFLINE);
		const FAttribute ReadOnly(FILE_ATTRIBUTE_READONLY);
		const FAttribute ReparsePoint(FILE_ATTRIBUTE_REPARSE_POINT);
		const FAttribute Sparse(FILE_ATTRIBUTE_SPARSE_FILE);
		const FAttribute System(FILE_ATTRIBUTE_SYSTEM);
		const FAttribute Temp(FILE_ATTRIBUTE_TEMPORARY);
		const FAttribute Virtual(FILE_ATTRIBUTE_VIRTUAL);
	}
}

unsigned int MakePath(const TCHAR *path);


unsigned long long int FileSize(const TCHAR *path);


unsigned long long int FileSize(const HANDLE hnd);


class EnumFiles
{
	private:
		HANDLE Handle;
		WIN32_FIND_DATA Data;
	public:
		EnumFiles() :Handle(0) {}
		bool FindFirst(const TCHAR *path) 
		{ 
			Reset();
			Handle = FindFirstFile(path, &Data);
			if (Handle == INVALID_HANDLE_VALUE)
			{
				Handle = 0;
				return false;
			}

			return true;
		}
		bool FindNext() 
		{
			bool ret = FindNextFile(Handle, &Data) != 0;
			return ret;
		}
		bool Reset() 
		{ 
			if (!Handle)
				return true;

			ZeroMemory((void*)&Data, sizeof(Data));
			if (FindClose(Handle))
			{
				Handle = 0;
				return true;
			}
			return false;
		}
		const WIN32_FIND_DATA& GetFileInfo() 
		{
			return Data;
		}
		~EnumFiles() 
		{
			Reset();
		}
};


class File
{
	private:
		HANDLE Handle;
		DWORD Lastread;
		DWORD Lastwrite;
	public:
		File();
		File(const TCHAR *fullpath, const FAccess access = file::access::ReadWrite,
			const FShare share = file::share::ReadWrite,
			const FMode openmode = file::openmode::OpenAlways,
			const FFlag = file::flag::Normal);
		bool Open(const TCHAR *fullpath, const FAccess access = file::access::ReadWrite,
			const FShare share = file::share::ReadWrite,
			const FMode openmode = file::openmode::OpenAlways,
			const FFlag = file::flag::Normal);
		bool Seek(const unsigned long long int pos, const FMethod method = file::method::Begin);
		unsigned long long int GetSize();
		unsigned long long int CurrentPos();
		unsigned int Read(void *data, const unsigned int size);
		unsigned int Write(const void *data, const unsigned int size);
		bool SetSize(const unsigned long long int bytes);
		DWORD LastRead();
		DWORD LastWrite();
		bool Close();
		bool Flush();
		operator HANDLE();
		~File();
};
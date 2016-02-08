#pragma once

#define MyHeaders_File

#include <Windows.h>
#include <MyHeaders\Heap.h>
#include <tchar.h>
#include <MyHeaders\windowdefs.h>

CREATE_NEW_DATA_TYPE(FAccess);
CREATE_NEW_DATA_TYPE(FMode);
CREATE_NEW_DATA_TYPE(FFlags);
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
	namespace flags
	{
		const FFlags NoBuffer(FILE_FLAG_NO_BUFFERING);
		const FFlags Normal(FILE_ATTRIBUTE_NORMAL);
		const FFlags Hidden(FILE_ATTRIBUTE_HIDDEN);
		const FFlags NoCache(FILE_FLAG_WRITE_THROUGH);
		const FFlags ReadOnly(FILE_ATTRIBUTE_READONLY);
		const FFlags RndAccess(FILE_FLAG_RANDOM_ACCESS);
		const FFlags SeqAccess(FILE_FLAG_SEQUENTIAL_SCAN);
		const FFlags DelOnClose(FILE_FLAG_DELETE_ON_CLOSE);
		const FFlags Temp(FILE_ATTRIBUTE_TEMPORARY);
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
		bool FindFirst(const TCHAR *path) { return (Handle = FindFirstFile(path, &Data)) != INVALID_HANDLE_VALUE; }
		bool FindNext() { return FindNextFile(Handle, &Data) != 0; }
		bool Reset() const { ZeroMemory((void*)&Data, sizeof(Data)); return FindClose(Handle) != 0; }
		const WIN32_FIND_DATA* GetFileInfo() const { return &Data; }
		~EnumFiles() { Reset(); }
};


class File
{
	private:
		HANDLE Handle;
		DWORD Lastread;
		DWORD Lastwrite;
		TCHAR *Fullpath;
	public:
		File(void);
		File(const TCHAR *fullpath, const FAccess access = file::access::ReadWrite,
			const FShare share = file::share::ReadWrite,
			const FMode openmode = file::openmode::OpenAlways,
			const FFlags = file::flags::Normal);
		bool Open(const TCHAR *fullpath, const FAccess access = file::access::ReadWrite,
			const FShare share = file::share::ReadWrite,
			const FMode openmode = file::openmode::OpenAlways,
			const FFlags = file::flags::Normal);
		bool Seek(const unsigned long long int pos, const FMethod method = file::method::Begin);
		unsigned long long int GetSize(void);
		unsigned long long int CurrentPos(void);
		unsigned int Read(void *data, const unsigned int size);
		unsigned int Write(const void *data, const unsigned int size);
		bool SetSize(const unsigned long long int bytes);
		DWORD LastRead(void);
		DWORD LastWrite(void);
		bool Close(void);
		bool Flush(void);
		operator HANDLE(void);
		const TCHAR *GetFullPath(void);
		bool Delete(void);
		~File(void);
};
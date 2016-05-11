#include <Windows.h>
#include <MyHeaders\File.h>

unsigned int MakePath(const TCHAR *path)
{
	if (_tcslen(path) > MAX_PATH - 12)
		return -1;
	TCHAR tmp[MAX_PATH - 12 + 1]; //MSDN: the directory name cannot exceed MAX_PATH minus 12 [+1 for NULL]
	_tcscpy(tmp, path);
	
	unsigned int count = 0;
	unsigned int pos = 0;
	while (tmp[pos])
	{
		if (tmp[pos] == '\\')
		{
			tmp[pos] = 0;
			if (CreateDirectory(tmp, 0))
				count++;
			tmp[pos] = '\\';
		}
		pos++;
	}
	if (CreateDirectory(tmp, 0))
		count++;
	return count;
}

unsigned long long int FileSize(const TCHAR *path)
{
	HANDLE hnd = CreateFile(path, file::access::Read, file::share::All, 0,
		file::openmode::OpenExisting, file::flag::Normal, 0);

	if (hnd == INVALID_HANDLE_VALUE)
		return -1;
		
	LARGE_INTEGER size;
	bool ok = GetFileSizeEx(hnd, &size) != 0;
	CloseHandle(hnd);

	if (ok)
		return size.QuadPart;
	return -1;
}

unsigned long long int FileSize(const HANDLE hnd)
{
	LARGE_INTEGER size;
	if (!GetFileSizeEx(hnd, &size))
		return -1;
	return size.QuadPart;
}





//-----File class implementation begins here-------

File::File()
{
	Handle = 0;
	Fullpath = 0;
	Lastread = Lastwrite = 0;
}

File::File(const TCHAR *fullpath, const FAccess access,const FShare share, const FMode openmode, const FFlag flags)
	:Handle(0), Fullpath(0), Lastread(0), Lastwrite(0)
{
	Open(fullpath, access, share, openmode, flags);
}

bool File::Open(const TCHAR *fullpath, const FAccess access, const FShare share, const FMode openmode, const FFlag flags)
{
	if ((Handle = CreateFile(fullpath, access, share, 0, openmode, flags, 0)) == INVALID_HANDLE_VALUE)
	{
		Handle = 0;
		return false;
	}

	return AllocAndCopy(Fullpath, fullpath, (_tcslen(fullpath) + 1)*sizeof(TCHAR));
}

bool File::Close()
{
	if (!Handle)
		return true;

	if (Fullpath)
		hfree(Fullpath);

	if (CloseHandle(Handle))
	{
		Handle = 0;
		return true;
	}

	return false;
}

bool File::Seek(const unsigned long long int pos, const FMethod method)
{
	LARGE_INTEGER newpos; newpos.QuadPart = pos;
	return SetFilePointerEx(Handle, newpos, 0, method) != 0;
}

unsigned long long int File::GetSize(void)
{
	LARGE_INTEGER sz;
	return (GetFileSizeEx(Handle, &sz) ? sz.QuadPart : 0);
}

unsigned long long int File::CurrentPos(void)
{
	LARGE_INTEGER zero = {};
	LARGE_INTEGER currentpos = {};
	SetFilePointerEx(Handle, zero, &currentpos, file::method::Current);
	return currentpos.QuadPart;
}

unsigned int File::Read(void *data, const unsigned int size)
{
	ReadFile(Handle, data, size, &Lastread, 0);
	return Lastread;
}

unsigned int File::Write(const void *data, const unsigned int size)
{
	WriteFile(Handle, data, size, &Lastwrite, 0);
	return Lastwrite;
}

bool File::SetSize(const unsigned long long int bytes)
{
	if (!Seek(bytes))
		return false;
	return SetEndOfFile(Handle) != 0;
}

DWORD File::LastRead(void)
{
	return Lastread;
}

DWORD File::LastWrite(void)
{
	return Lastwrite;
}


bool File::Flush(void)
{
	return FlushFileBuffers(Handle) != 0;
}

File::operator HANDLE(void)
{
	return Handle;
}

const TCHAR* File::GetFullPath(void)
{
	return Fullpath;
}

bool File::Delete(void)
{
	if (Handle)
	{
		if (!CloseHandle(Handle))
			return false;
		Handle = 0;
	}

	if (!Fullpath) // do we really need this check?
		return false;

	bool delOK = DeleteFile(Fullpath) != 0;
	hfree(Fullpath);
	return delOK;
}

File::~File(void)
{
	Close();
}
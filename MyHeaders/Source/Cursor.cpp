#include <MyHeaders\Cursor.h>

Cursor::Cursor()
{
	Handle = 0;
}

Cursor::Cursor(const TCHAR *path, const CMode mode, int desiredX, int desiredY)
{
	Handle = 0;
	Load(path, mode, desiredX, desiredY);
}

bool Cursor::Load(const TCHAR *path, const CMode mode, int desiredX, int desiredY)
{
	return (Handle = LoadImage(0, path, IMAGE_CURSOR, desiredX, desiredY, mode | CMode(LR_LOADFROMFILE))) != 0;
}

Cursor::operator HCURSOR()
{
	return (HCURSOR)Handle;
}

bool Cursor::Destroy()
{
	if (!Handle)
		return true;

	if (!DestroyCursor((HCURSOR)Handle))
		return false;

	Handle = 0;
	return true;;
}

Cursor::~Cursor()
{
	Destroy();
}
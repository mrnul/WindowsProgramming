#include <MyHeaders\Icon.h>

Icon::Icon()
{
	Handle = 0;
}

Icon::Icon(const HINSTANCE hInstance, const TCHAR *path, const IMode mode, int desiredX, int desiredY)
{
	Handle = 0;
	Load(hInstance, path, mode, desiredX, desiredY);
}

bool Icon::Load(const HINSTANCE hInstance, const TCHAR *path, const IMode mode, int desiredX, int desiredY)
{
	return (Handle = LoadImage(hInstance, path, IMAGE_ICON, desiredX, desiredY, mode | IMode(LR_LOADFROMFILE))) != 0;
}

Icon::operator HICON()
{
	return (HICON)Handle;
}

bool Icon::Destroy()
{
	if (!Handle)
		return true;
	if (!DestroyIcon((HICON)Handle))
		return false;

	Handle = 0;
	return true;;
}

Icon::~Icon()
{
	Destroy();
}
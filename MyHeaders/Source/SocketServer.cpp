#include <MyHeaders\SocketServer.h>

SocketServer::SocketServer(const int major, const int minor)
{
	Socket = 0;
	Init(major, minor);
}

bool SocketServer::Init(const int major, const int minor)
{
	WSADATA wsaData;
	Initialized = WSAStartup(MAKEWORD(major, minor), &wsaData) == 0;
	return Initialized;
}

bool SocketServer::CreateAndBind(const TCHAR *host, const TCHAR *port)
{
	ADDRINFOT hints = {};
	ADDRINFOT *res;

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if (GetAddrInfo(host, port, &hints, &res) != 0)
	{
		FreeAddrInfo(res);
		return false;
	}

	Socket = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

	if (Socket == INVALID_SOCKET)
	{
		Socket = 0;
		FreeAddrInfo(res);
		return false;
	}

	if (bind(Socket, res->ai_addr, res->ai_addrlen) == SOCKET_ERROR)
	{
		Close();
		FreeAddrInfo(res);
		return false;
	}

	FreeAddrInfo(res);
	return true;
}

bool SocketServer::Listen()
{
	if (listen(Socket, SOMAXCONN) == SOCKET_ERROR)
	{
		Close();
		return false;
	}
	return true;
}

SOCKET SocketServer::Accept()
{
	SOCKET res;
	if ((res = accept(Socket, 0, 0)) == SOCKET_ERROR)
	{
		Close();
		res = 0;
	}
	return res;
}

bool SocketServer::IsInitialized()
{
	return Initialized;
}

bool SocketServer::SetBlockingState(const bool blocking)
{
	u_long iMode = blocking ? 0 : 1;
	return ioctlsocket(Socket, FIONBIO, &iMode) == 0;
}

bool SocketServer::CheckReadability(const unsigned int secs, const unsigned int microsecs)
{
	timeval tv = { secs, microsecs };
	fd_set fd;
	FD_ZERO(&fd);
	FD_SET(Socket, &fd);
	//msdn: first parameter is ignored
	return select(0, &fd, 0, 0, &tv) > 0;
}

bool SocketServer::CheckWritability(const unsigned int secs, const unsigned int microsecs)
{
	timeval tv = { secs, microsecs };
	fd_set fd;
	FD_ZERO(&fd);
	FD_SET(Socket, &fd);
	//msdn: first parameter is ignored
	return select(0, 0, &fd, 0, &tv) > 0;
}

SocketServer::operator SOCKET()
{
	return Socket;
}

bool SocketServer::Close()
{
	if (!Socket)
		return true;

	if (closesocket(Socket) == 0)
	{
		Socket = 0;
		return true;
	}
	return false;
}

bool SocketServer::Clean()
{
	if (!Initialized)
		return true;

	if (WSACleanup() == 0)
	{
		Initialized = false;
		return true;
	}
	return false;
}

SocketServer::~SocketServer()
{
	Close();
	Clean();
}
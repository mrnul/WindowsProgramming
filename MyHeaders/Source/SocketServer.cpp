#include <MyHeaders\SocketServer.h>

SocketServer::SocketServer()
{
	Socket = 0;
	Init();
}

bool SocketServer::Init()
{
	WSADATA wsaData;
	Initialized = WSAStartup(MAKEWORD(MAJOR_WINSOCK_VER, MINOR_WINSOCK_VER), &wsaData) == 0;
	return Initialized;
}

bool SocketServer::CreateAndBind(const TCHAR *host, const TCHAR *port)
{
	ADDRINFOT hints = {};
	ADDRINFOT *res;

	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	hints.ai_protocol = IPPROTO_TCP;

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

char* SocketServer::GetLocalMachineIP()
{
	wchar_t hostname[512];
	char *buffer = 0;

	GetHostNameW(hostname, 512);

	ADDRINFOW *result;
	ADDRINFOW hints = {};

	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	if (GetAddrInfoW(hostname, 0, &hints, &result) != 0)
		return 0;

	for (ADDRINFOW *ptr = result; ptr != 0; ptr = ptr->ai_next)
	{
		SOCKADDR_IN *tmp = (SOCKADDR_IN*)ptr->ai_addr;
		buffer = inet_ntoa(tmp->sin_addr);
	}

	return buffer;
}

char* SocketServer::GetClientAddress(SOCKET client)
{
	SOCKADDR_IN addr1;
	int len1 = sizeof(addr1);
	if (getpeername(client, (SOCKADDR*)&addr1, &len1) != 0)
		return false;

	return inet_ntoa(addr1.sin_addr);
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
		res = 0;

	return res;
}

bool SocketServer::IsInitialized()
{
	return Initialized;
}

bool SocketServer::SetNonBlocking(const bool nonBlocking)
{
	u_long iMode = nonBlocking ? 1 : 0;
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

	if (WSACleanup() != 0)
		return false;

	Initialized = false;
	return true;
}

SocketServer::~SocketServer()
{
	Close();
	Clean();
}
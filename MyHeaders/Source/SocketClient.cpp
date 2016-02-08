#include <MyHeaders\SocketClient.h>

SocketClient::SocketClient()
{
	Socket = 0;
}

SocketClient::SocketClient(SOCKET con)
{
	Socket = con;
}

SocketClient::SocketClient(const unsigned int major, const unsigned int minor)
{
	Socket = 0;
	Init(major, minor);
}

bool SocketClient::WinsockInitialized()
{
	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s == INVALID_SOCKET && WSAGetLastError() == WSANOTINITIALISED)
		return false;

	closesocket(s);
	return true;
}

SocketClient::operator SOCKET()
{
	return Socket;
}

bool SocketClient::Init(const unsigned int major, const unsigned int minor)
{
	if (!WinsockInitialized())
		return WSAStartup(MAKEWORD(major, minor), &wsaData) == 0;

	return false;
}

bool SocketClient::Connect(const TCHAR *host, const TCHAR *port)
{
	ADDRINFOT *res;
	ADDRINFOT *ptr;
	ADDRINFOT hints;

	memset(&hints, 0, sizeof(hints));

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if (GetAddrInfo(host, port, &hints, &res))
	{
		Close();
		return false;
	}

	Socket = 0;

	for (ptr = res; ptr != NULL; ptr = ptr->ai_next)
	{
		Socket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

		if (Socket == INVALID_SOCKET)
		{
			Socket = 0;
			continue;
		}

		if (connect(Socket, ptr->ai_addr, ptr->ai_addrlen) == SOCKET_ERROR)
		{
			closesocket(Socket);
			Socket = 0;
			continue;
		}

		break;
	}

	FreeAddrInfo(res);

	return Socket != 0;
}

int SocketClient::Send(const void *buffer, const unsigned int len, const SCSFlag flags)
{
	int res;
	if ((res = send(Socket, (const char*)buffer, len, flags)) == SOCKET_ERROR)
	{
		Close();
		return 0;
	}

	return res;
}

int SocketClient::Recieve(void *buffer, const unsigned int len, const SCRFlag flags)
{
	int res;
	if ((res = recv(Socket, (char*)buffer, len, flags)) == SOCKET_ERROR)
	{
		Close();
		return 0;
	}

	return res;
}

bool SocketClient::SetBlockingState(const bool blocking)
{
	u_long iMode = blocking ? 1 : 0;
	return ioctlsocket(Socket, FIONBIO, &iMode) == 0;
}
bool SocketClient::CheckReadability(const unsigned int secs, const unsigned int microsecs)
{
	timeval tv = { secs, microsecs };
	fd_set fd;
	FD_ZERO(&fd);
	FD_SET(Socket, &fd);
	return  select(Socket, &fd, 0, 0, &tv) > 0;
}
bool SocketClient::CheckWritability(const unsigned int secs, const unsigned int microsecs)
{
	timeval tv = { secs, microsecs };
	fd_set fd;
	FD_ZERO(&fd);
	FD_SET(Socket, &fd);
	return  select(Socket, 0, &fd, 0, &tv) > 0;
}

bool SocketClient::ShutDownRcv()
{
	if (shutdown(Socket, SD_RECEIVE) == SOCKET_ERROR)
	{
		Close();
		return false;
	}
	return true;
}

bool SocketClient::ShutDownSnd()
{
	if (shutdown(Socket, SD_SEND) == SOCKET_ERROR)
	{
		Close();
		return false;
	}
	return true;
}

unsigned int SocketClient::GetPendingDataSize()
{
	unsigned long int size = 0;
	if (ioctlsocket(Socket, FIONREAD, &size) != 0)
		return 0;

	return size;
}

void SocketClient::Close()
{
	if (Socket)
	{
		closesocket(Socket);
		Socket = 0;
	}
}

bool SocketClient::Clean()
{
	if (WinsockInitialized())
	{
		return WSACleanup() == 0;
	}

	return false;
}

SocketClient::~SocketClient()
{
	Close();
}
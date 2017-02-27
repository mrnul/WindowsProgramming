#include <MyHeaders\SocketClient.h>

SocketClient::SocketClient()
{
	Init();
}

SocketClient::SocketClient(SOCKET con)
{
	Init(con);
}

SocketClient::operator SOCKET()
{
	return Socket;
}

bool SocketClient::Init()
{
	Socket = INVALID_SOCKET;

	WSADATA wsaData;
	Initialized = (WSAStartup(MAKEWORD(MAJOR_WINSOCK_VER, MINOR_WINSOCK_VER), &wsaData) == 0);

	return Initialized;
}

bool SocketClient::Init(SOCKET con)
{
	Socket = INVALID_SOCKET;

	WSADATA wsaData;
	Initialized = (WSAStartup(MAKEWORD(MAJOR_WINSOCK_VER, MINOR_WINSOCK_VER), &wsaData) == 0);

	if (!Initialized)
		return false;

	Socket = con;

	return SetNonBlocking(true);
}

bool SocketClient::Connect(const TCHAR *host, const TCHAR *port, const unsigned int secs, const unsigned int microsecs)
{
	ADDRINFOT *res;
	ADDRINFOT *ptr;
	ADDRINFOT hints = {};

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	if (GetAddrInfo(host, port, &hints, &res))
		return false;

	for (ptr = res; ptr != NULL; ptr = ptr->ai_next)
	{
		if ((Socket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol)) == INVALID_SOCKET)
			continue;

		if (!SetNonBlocking(true))
		{
			closesocket(Socket);
			Socket = INVALID_SOCKET;
			continue;
		}

		//if
		if (connect(Socket, ptr->ai_addr, ptr->ai_addrlen) == 0)
			break;

		//else if
		if (WSAGetLastError() == WSAEWOULDBLOCK)
		{
			if (!CheckWritability(secs, microsecs))
			{
				closesocket(Socket);
				Socket = INVALID_SOCKET;
				continue;
			}
		}

		//else
		break;
	}

	FreeAddrInfo(res);
	return Socket != 0;
}

int SocketClient::Send(const void *buffer, const int len, const SCSFlag flags)
{
	int res;
	if ((res = send(Socket, (const char*)buffer, len, flags)) == SOCKET_ERROR)
		Close();

	return res;
}

int SocketClient::Recieve(void *buffer, const int len, const SCRFlag flags)
{
	int res;
	if ((res = recv(Socket, (char*)buffer, len, flags)) == SOCKET_ERROR)
		Close();

	return res;
}

int SocketClient::RecieveNBytes(void *buffer, const int n, const unsigned int waitSeconds)
{
	int total = 0;
	while (total < n)
	{
		if (!CheckReadability(waitSeconds))
			break;

		const int tmp = recv(Socket, (char*)buffer + total, n - total, 0);
		if (tmp <= 0)
			break;

		total += tmp;
	}

	return total;
}

bool SocketClient::SetNonBlocking(const bool nonBlocking)
{
	u_long iMode = nonBlocking ? 1 : 0;
	return ioctlsocket(Socket, FIONBIO, &iMode) == 0;
}

bool SocketClient::CheckReadability(const unsigned int secs, const unsigned int microsecs)
{
	timeval tv = { secs, microsecs };
	fd_set fd;
	FD_ZERO(&fd);
	FD_SET(Socket, &fd);
	//msdn: first parameter is ignored
	return select(0, &fd, 0, 0, &tv) > 0;
}

bool SocketClient::CheckWritability(const unsigned int secs, const unsigned int microsecs)
{
	timeval tv = { secs, microsecs };
	fd_set fd;
	FD_ZERO(&fd);
	FD_SET(Socket, &fd);
	//msdn: first parameter is ignored
	return select(0, 0, &fd, 0, &tv) > 0;
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

bool SocketClient::IsInitialized()
{
	return Initialized;
}

//gracefully closed?
bool SocketClient::Close()
{
	if (Socket == INVALID_SOCKET)
		return true;

	//error checking, should i do it here?
	shutdown(Socket, SD_SEND);

	char tmp[512];
	while (recv(Socket, tmp, 512, 0) > 0);

	if (closesocket(Socket) == 0)
		Socket = INVALID_SOCKET;

	return Socket == INVALID_SOCKET;
}

bool SocketClient::Clean()
{
	if (!Initialized)
		return true;

	if (WSACleanup() != 0)
		return false;

	Initialized = false;
	return true;
}

SocketClient::~SocketClient()
{
	Close();
	Clean();
}

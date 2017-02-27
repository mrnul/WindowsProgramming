#pragma once

#define MyHeaders_SocketClient

#ifndef MyHeaders_SocketServer
#ifdef _INC_WINDOWS || _WINSOCK2API_
#error SocketServer.h  or SocketClient.h must be included first!
#endif

#endif //MyHeaders_SocketServer

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <MyHeaders\windowdefs.h>
#pragma comment(lib, "ws2_32.lib")

CREATE_NEW_DATA_TYPE(SCSFlag);
CREATE_NEW_DATA_TYPE(SCRFlag);

namespace socketclient
{
	namespace Sflag
	{
		const SCSFlag DontRoute = SCSFlag(MSG_DONTROUTE);
		const SCSFlag MsgOOB = SCSFlag(MSG_OOB);
		const SCSFlag Default = SCSFlag(0);
	}
	namespace Rflag
	{
		const SCRFlag Peek = SCRFlag(MSG_PEEK);
		const SCRFlag MsgOOB = SCRFlag(MSG_OOB);
		const SCRFlag MsgWaitAll = SCRFlag(MSG_WAITALL);
		const SCRFlag Default = SCRFlag(0);
	}
}

class SocketClient
{
	private:
		SOCKET Socket;
		bool Initialized;
	public:
		SocketClient();
		SocketClient(SOCKET con);
		bool Init();
		bool Init(SOCKET con);
		bool Connect(const TCHAR *host, const TCHAR *port, const unsigned int secs = 5, const unsigned int microsecs = 0);
		int Send(const void *buffer, const int len, const SCSFlag flags = socketclient::Sflag::Default);
		int Recieve(void *buffer, const int len, const SCRFlag flags = socketclient::Rflag::Default);
		int RecieveNBytes(void *buffer, const int n, const unsigned int waitSeconds = 5);
		bool SetNonBlocking(const bool nonBlocking = true);
		bool CheckReadability(const unsigned int secs = 0, const unsigned int microsecs = 0);
		bool CheckWritability(const unsigned int secs = 0, const unsigned int microsecs = 0);
		bool ShutDownRcv();
		bool ShutDownSnd();
		unsigned int GetPendingDataSize();
		operator SOCKET();
		bool IsInitialized();
		bool Close();
		bool Clean();
		~SocketClient();
};

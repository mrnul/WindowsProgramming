#pragma once
#define MyHeaders_SocketServer

#ifndef MyHeaders_SocketClient

#ifdef _INC_WINDOWS || _WINSOCK2API_
#error SocketServer.h  or SocketClient must be included first!
#endif

#endif //MyHeaders_SocketClient

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <MyHeaders\windowdefs.h>
#pragma comment(lib, "ws2_32.lib")

class SocketServer
{
	private:
		SOCKET Socket;
		bool Initialized;
	public:
		SocketServer();
		bool Init();
		bool CreateAndBind(const TCHAR *host, const TCHAR *port);
		char* GetLocalMachineIP(); //it just returns the last address found
		char* GetClientAddress(SOCKET client);
		bool Listen();
		SOCKET Accept();
		bool IsInitialized();
		bool SetNonBlocking(const bool nonBlocking);
		bool CheckReadability(const unsigned int secs = 0, const unsigned int microsecs = 0);
		bool CheckWritability(const unsigned int secs = 0, const unsigned int microsecs = 0);
		operator SOCKET();
		bool Close();
		bool Clean();
		~SocketServer();
};

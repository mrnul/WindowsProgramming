#pragma once
#define MyHeaders_SocketServer

#ifndef MyHeaders_SocketClient
#ifdef _INC_WINDOWS || _WINSOCK2API_
#error SocketServer.h  or SocketClient must be included first!
#endif
#endif

#ifndef  WIN32_LEAN_AND_MEAN
	#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <winsock2.h>
#include <Ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

class SocketServer
{
	private:
		SOCKET Socket;
		bool Initialized;
	public:
		SocketServer() :Socket(0), Initialized(false) {}
		SocketServer(const int major,const int minor);
		bool Init(const int major,const int minor);
		bool CreateAndBind(const TCHAR *host, const TCHAR *port);
		char* GetLocalMachineIP(); //it just returns the last address found
		void GetClientAddress(SOCKET client, char *clientAddress);
		bool Listen();
		SOCKET Accept();
		bool IsInitialized();
		bool SetBlockingState(const bool blocking);
		bool CheckReadability(const unsigned int secs, const unsigned int microsecs = 0);
		bool CheckWritability(const unsigned int secs, const unsigned int microsecs = 0);
		operator SOCKET();
		bool Close();
		bool Clean();
		~SocketServer();
};
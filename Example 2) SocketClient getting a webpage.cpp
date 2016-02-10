#include <MyHeaders\SocketClient.h>
#include <MyHeaders\Buffer.h>
#include <MyHeaders\File.h>
#include <iostream>

using std::cout;
using std::endl;
using std::cin;

#define BUFF_SIZE (1024 * 128)

int main()
{
	//initialize Winsock, version 2.2
	//we need a more decent way to do that (?)
	SocketClient socket(2, 2);

	//port 80 is for http
	if (!socket.Connect("www.stackoverflow.com", "80"))
		return -1;


	//make it non-blocking
	//no need to but just a demo
	socket.SetBlockingState(false);

	//http request, tell server we want the home page
	char *req =
		"GET / HTTP/1.1\r\n"\
		"Host: stackoverflow.com\r\n"\
		"Accept: text/html\r\n"\
		"Connection: close\r\n"\
		"\r\n\r\n";

	socket.Send(req, strlen(req));

	//page.txt will have the home page + http headers
	File out("page.txt", file::access::Write, file::share::All, file::openmode::CreateAlways);
	if (!out)
		return -2;

	//allocate 128 KB, it could be any other number, i just like this one
	Buffer<char> buffer;
	if (!buffer.Alloc(BUFF_SIZE))
		return -3;

	int totalSizeRecved = 0;
	cout << "Waiting for response..." << endl;
	//each time wait a maximum of 2 seconds
	while (socket.CheckReadability(2))
	{
		const int size = socket.Recieve(buffer, BUFF_SIZE);
		if (size <= 0)
		{
			//connection closed by the server
			if (size == 0)
				cout << "**All ok**" << endl;
			//if size < 0 then something went wrong
			else
				cout << "**Error occured**" << endl;

			break;
		}
		out.Write(buffer, size);
		totalSizeRecved += size;
		cout << "Received now:" << size << "\tTotal:" << totalSizeRecved << endl;
	}


	//no need to do that here, just a demo
	out.Flush();
	socket.Close();

	//we need a more decent way to initialize and cleanup Winsock (?)
	socket.Clean();

	cout << "\nDone" << endl;
	cin.get();
}
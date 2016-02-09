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

	//http request, tell server we want the home page
	char *req =
		"GET / HTTP/1.1\r\n"\
		"Host: stackoverflow.com\r\n"\
		"Accept: text/html\r\n"\
		"Connection: close\r\n"\
		"\r\n\r\n";

	socket.Send(req, strlen(req));

	//page.txt will have the home page
	File out("page.txt", file::access::Write, file::share::All, file::openmode::CreateAlways);
	if (!out)
		return -2;

	//allocate 128 KB, it could be any other number, i just like this one
	Buffer<char> buffer;
	if (!buffer.Alloc(BUFF_SIZE))
		return -3;

	cout << "Waiting for response..." << endl;
	//wait a maximum of 2 seconds for the response
	if (!socket.CheckReadability(2))
		return -4;
	
	int size = 0;
	int totalSizeRecved = 0;

	cout << "Getting data!" << endl;
	//we got the response in time, start recieving the data
	while ((size = socket.Recieve(buffer, BUFF_SIZE)) > 0)
	{
		out.Write(buffer, size);
		totalSizeRecved += size;
		cout << totalSizeRecved << endl;
	}

	//no need to do that here, just a demo
	out.Flush();
	socket.Close();

	//we need a more decent way to initialize and cleanup Winsock (?)
	socket.Clean();

	if (size < 0)
		cout << "**An error occured**" << endl;

	if (size == 0)
		cout << "**All ok**" << endl;

	cout << "\nDone" << endl;
	cin.get();
}
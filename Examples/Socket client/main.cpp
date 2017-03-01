#include <MyHeaders\SocketClient.h>
#include <MyHeaders\SocketServer.h>
#include <MyHeaders\File.h>
#include <MyHeaders\Buffer.h>
#include <string>
using std::string;

#define BUFFER_SZ (1024 * 1024 * 5)

int main()
{
	SocketClient client;
	client.Connect("www.stackoverflow.com", "http");

	string req =
		"GET / HTTP/1.1\r\n"
		"Host: stackoverflow.com\r\n"
		"Connection: close\r\n"
		"\r\n";

	if (!client.CheckWritability(2))
		return 0;
	
	if (client.Send(req.c_str(), req.size()) != req.size())
		return 0;

	Buffer<char> buffer;
	if (!buffer.Alloc(BUFFER_SZ))
		return 0;

	int total = 0;

	//recieve data until there are no more data to recieve
	//stop if:
	//1) response delayed more than 2 seconds
	//2) size of data recieved is greater than buffer size
	//3) error occured
	while (client.CheckReadability(2) && total < BUFFER_SZ)
	{
		const int tmp = client.Recieve(buffer + total, BUFFER_SZ - total);
		if (tmp <= 0)
			break;

		total += tmp;
	}

	if (total != 0)
	{
		File out("test.html", file::access::Write, file::share::ReadWrite, file::openmode::CreateAlways);
		out.Write(buffer, total);
	}

	
}

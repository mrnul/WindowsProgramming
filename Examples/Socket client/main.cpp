#include <MyHeaders\SocketClient.h>
#include <MyHeaders\File.h>

int main()
{
	SocketClient client(2, 2);

	if (!client.IsInitialized())
		return 0;
	
	if (!client.Connect(L"stackoverflow.com", L"80"))
		return 0;

	if (!client.SetNonBlocking())
		return 0;

	char *httpRequest =
		"GET / HTTP/1.1\r\n"
		"Host: stackoverflow.com\r\n"
		"Connection: close\r\n"
		"\r\n";

	unsigned int length = strlen(httpRequest);

	//check if we are ready to send data
	if (!client.CheckWritability(5))
		return 0;

	//send the request
	if (client.Send(httpRequest, length) != length)
		return 0;

	char buffer[1024];

	//file "response.txt" will have the http response
	File out;
	if (!out.Open(L"response.txt", file::access::Write, file::share::ReadWrite, file::openmode::CreateAlways))
		return 0;


	//wait at most 5 seconds
	while (client.CheckReadability(5))
	{
		int tmp = client.Recieve(buffer, 1024);
		if (tmp <= 0)
			break;

		out.Write(buffer, tmp);
	}
}
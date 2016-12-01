#include <MyHeaders\SocketServer.h>
#include <MyHeaders\SocketClient.h>
#include <MyHeaders\Buffer.h>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

#define BUFF_SIZE (1024 * 128)

bool SendMainPage(SocketClient &client)
{
	char *resp =
		"HTTP/1.1 200 OK\r\n"\
		"Content-Type: text/html\r\n"\
		"Connection: close\r\n"\
		"\r\n"\
		"<!DOCTYPE html>"\
		"<html>"\
		"<title>Testing server</title>"\
		"<body>"\
		"<h1>This is a heading</h1>"\
		"<p>Hello world from this server</p>"\
		"<a href=\"goodbye\">Click here to stop the server</a>"\
		"</body>"\
		"</html>";

	return client.Send(resp, strlen(resp)) > 0;
}

bool SendGoodByePage(SocketClient &client)
{
	char *resp =
		"HTTP/1.1 200 OK\r\n"\
		"Content-Type: text/html\r\n"\
		"Connection: close\r\n"\
		"\r\n"\
		"<!DOCTYPE html>"\
		"<html>"\
		"<title>Server says goodbye!</title>"\
		"<body>"\
		"<h1>I am closing</h1>"\
		"<p>Goodbye!</p>"\
		"</body>"\
		"</html>";

	return client.Send(resp, strlen(resp)) > 0;
}

int main()
{
	//initialize winsock
	SocketServer server(2, 2);

	//you can pass your local ip address as the first parameter
	//i just pass the loopback address
	if (!server.CreateAndBind("127.0.0.1", "80"))
		return -1;

	if (!server.Listen())
		return -2;

	Buffer<char> buff;
	if (!buff.Alloc(BUFF_SIZE))
		return -3;

	cout << "Open your browser and visit \"http://127.0.0.1\" OR \"localhost\"" << endl;
	cout << "Waiting for incoming connection...\n" << endl;
	while (true)
	{
		SocketClient client(server.Accept(), 2, 2);

		//get and print the http request
		const int size = client.Recieve(buff, BUFF_SIZE - 1);
		buff[size] = 0;
		cout << buff << endl;

		if (memcmp(buff, "GET / HTTP/1.1", 14) == 0)
		{
			SendMainPage(client);
		}
		else if (memcmp(buff, "GET /goodbye HTTP/1.1", 21) == 0)
		{
			SendGoodByePage(client);
			break;
		}

	}
	cout << "\n\nServer stopped" << endl;
	cin.get();
}
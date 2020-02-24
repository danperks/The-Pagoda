#define WIN32_LEAN_AND_MEAN
#define WINVER 0x0A00
#define _WIN32_WINNT 0x0A00


#include <iostream>
#include <string>
#include <WS2tcpip.h>

using namespace std;

int main()
{
	string address = "127.0.0.1";		// IP Address of the server
	int port = 54000;					// Listening port # on the server

	WSAData data;
	int wsResult = WSAStartup(MAKEWORD(2, 2), &data);
	if (wsResult != 0)
	{
		cerr << "Can't start Winsock, Err #" << wsResult << endl;
		return 0;
	}

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0); // Create socket
	if (sock == INVALID_SOCKET)
	{
		cerr << "Can't create socket, Err #" << WSAGetLastError() << endl;
		WSACleanup();
		return 0;
	}

	sockaddr_in hint; // Create (literal) hints
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, address.c_str(), &hint.sin_addr);

	// Connect to server
	int conn = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (conn == SOCKET_ERROR)
	{
		cerr << "Can't connect to server, Err #" << WSAGetLastError() << endl;
		closesocket(sock);
		WSACleanup();
		return 0;
	}

	// Main Loop
	char buffer[4096];
	string dataIn;

	do
	{
		// Prompt the user for some text
		cout << "> ";
		getline(cin, dataIn);

		if (dataIn.size() > 0)		// Make sure the user has typed in something
		{
			// Send the text
			int sendResult = send(sock, dataIn.c_str(), dataIn.size() + 1, 0);
			if (sendResult != SOCKET_ERROR)
			{
				// Wait for response
				ZeroMemory(buffer, 4096);
				int dataOut = recv(sock, buffer, 4096, 0);
				if (dataOut > 0)
				{

					cout << "SERVER> " << string(buffer, 0, dataOut) << endl;
				}
			}
		}
	
	} while (dataIn.size() > 0);

	closesocket(sock);
	WSACleanup();
}

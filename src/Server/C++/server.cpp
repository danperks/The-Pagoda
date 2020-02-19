#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

// NOTES:
// Currently works with Putty connection
// Use RAW but Telnet works
// TCP connection for when we need to build client
// Compile with -std=c++0x -lws2_32

int main()
{
	// Initialze winsock
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	int wsOk = WSAStartup(ver, &wsData);
	if (wsOk != 0)
	{
		cerr << "Can't Initialize winsock! Quitting" << endl;
		return 0;
	}
	
	// Create a socket
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET)
	{
		cerr << "Can't create a socket! Quitting" << endl;
		return 0;
	}

	// Bind the ip address and port to a socket
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;
	
	bind(listening, (sockaddr*)&hint, sizeof(hint));
	listen(listening, SOMAXCONN);

	fd_set master; // Create the FD
	FD_ZERO(&master); // Set the FD to zero
	FD_SET(listening, &master); // Add the listening socket

	// this will be changed by the \quit command (see below, bonus not in video!)
	bool running = true; 

	while (running)
	{
		fd_set copy = master; // Copy the list to maintain inactive conns - non active conns are not returned
		int socketCount = select(0, &copy, nullptr, nullptr, nullptr); // Get active conns
		for (int i = 0; i < socketCount; i++) // Loop through all the current & potential connections
		{
			SOCKET sock = copy.fd_array[i]; // Recieve data from the socket
			if (sock == listening) // Check if connection request (aka new user)
			{
				SOCKET client = accept(listening, nullptr, nullptr); // Accept a new conn
				FD_SET(client, &master); // Add new conn to FD
				string welcomeMsg = "Welcome to the Game!\r\n"; // Define welcome message
				send(client, welcomeMsg.c_str(), welcomeMsg.size() + 1, 0); // Send welcome message
			}
			else // Its an inbound message
			{
				char buf[4096]; // Allocate memory for message
				ZeroMemory(buf, 4096); // Zero the memory
				int bytesIn = recv(sock, buf, 4096, 0); // Recieve the message (in bytes)
				string clientText = string(buf, bytesIn); // Convert message to string
				if (!clientText.empty() && clientText[clientText.length()-1] == '\n') { // Removes new line from message
    				clientText.erase(clientText.length()-1);
				}
				if (bytesIn <= 0) // Checks if the response was blank - not blank unless disconnected
				{
					closesocket(sock); // Closes the socket connection
					FD_CLR(sock, &master); // Removes the socket from FD
				}
				else if (clientText == "\n" || clientText == "\r" || clientText == " " || clientText ==  ""){ 
					continue; // Ignores empty message
				}
				else {

					cout << "Client: " + sock << endl;
					cout << "Message: " + clientText << endl;
					cout << "  " << endl;

					for (int i = 0; i < master.fd_count; i++) // Sends message to all sockets 
					{
						SOCKET outSock = master.fd_array[i];
						if (outSock != listening && outSock != sock) // Bypasses listening socket
						{
							ostringstream ss;
							ss << "SOCKET #" << sock << ": " << buf << "\r\n";
							string strOut = ss.str();

							send(outSock, strOut.c_str(), strOut.size() + 1, 0);
						}
					}
				}
			}
		}
	}

	// If here, the server is shutting down

	FD_CLR(listening, &master); // Removes listening socket
	closesocket(listening); // Closes listening socket connection
	
	// Sends shutdown message, and disconnects sockets
	string msg = "Server is shutting down. Goodbye\r\n";
	while (master.fd_count > 0)
	{
		SOCKET sock = master.fd_array[0];
		send(sock, msg.c_str(), msg.size() + 1, 0);
		FD_CLR(sock, &master);
		closesocket(sock);
	}
	WSACleanup(); // Cleanup winsock
}
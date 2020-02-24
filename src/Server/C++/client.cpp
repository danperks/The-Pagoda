#define WIN32_LEAN_AND_MEAN
#define WINVER 0x0A00
#define _WIN32_WINNT 0x0A00

#include <windows.h>
#include <iostream>
#include <thread>
#include <string>
#include <WS2tcpip.h>


using namespace std;

int MessageRead(){
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	char buffer[4096];
	while (true){
	ZeroMemory(buffer, 4096);
	int dataOut = recv(sock, buffer, 4096, 0);
	if (dataOut > 0){
		cout << "SERVER> " << string(buffer, 0, dataOut) << endl;
		return 1;
		}

	}
	closesocket(sock);
	WSACleanup();
	return 0;
}


int MessageSend(){
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	string dataIn;
	while (true){	
	cout << "> ";
	getline(cin, dataIn);
	if(dataIn.size()>0){
		int sendResult = send(sock, dataIn.c_str(), dataIn.size() + 1, 0);
			if (sendResult != SOCKET_ERROR){
				// seppuku
				closesocket(sock);
				WSACleanup();	
				return 1;		
			}

	}
	

	}
	closesocket(sock);
	WSACleanup();
	return 0;
}



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
	//pthread_create (1,NULL,MessageSend, (SOCKET)sock);
	//thread MessageRead (MessageRead,sock);
	thread (MessageRead);
	thread (MessageSend);
	//Handle myHandle = CreateThread(0,0,MessageRead,0,0,0);
	//MessageSend.join();
	MessageRead.join();
	MessageSend.join();
	
	closesocket(sock);
	WSACleanup();
}





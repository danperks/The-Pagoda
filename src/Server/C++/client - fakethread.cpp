#define WIN32_LEAN_AND_MEAN
#define WINVER 0x0A00
#define _WIN32_WINNT 0x0A00


#include <iostream>
#include <string>
#include <WS2tcpip.h>
#include <conio.h>
#include <vector>
#include <ctype.h>
#include <windows.h>
#include <process.h>

using namespace std;

// TODO Need to set the socket to non blocking

int main()
{
	//string PerksClient ="C:\\Users\\hpd12\\AppData\\Local\\Programs\\Microsoft VS Code\\Code.exe";
	string address = "127.0.0.1";		// IP Address of the server
	int port = 54000;					// Listening port # on the server

	WSAData data;
	int wsResult = WSAStartup(MAKEWORD(2, 2), &data);
	if (wsResult != 0)
	{
		cerr << "An error occured - Error Code #WSA" << wsResult << endl;
		return 0;
	}

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0); // Create socket
	if (sock == INVALID_SOCKET)
	{
		cerr << "An error occured - Error Code #WSB" << WSAGetLastError() << endl;
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
	// Memory Address = &dataIn
	const char* Arguments = dataIn.data();
	const char* PerksClient = "C:\\Users\\hpd12\\AppData\\Local\\Programs\\Microsoft VS Code\\Code.exe";
	
	char* compsec = getenv("COMPSEC");
	_spawnl(_P_NOWAIT,PerksClient,dataIn.data());

	vector<string> toSend;
	string letter = "";                    
    string word = "";    
	int letterCount = 0;

	while(true)
	{
		toSend.clear();
		letter = "";                    
    	word = "";    
		letterCount = 0;

		while(true){
			if (_kbhit() ) {
				int key_code = _getch();
				string key = to_string(key_code);
				if (key == "13"){
					break;
				}
				printf("The character is %c\n", key);
				toSend.push_back(key);
			}
			else {
				int dataOut = recv(sock, buffer, 4096, 0);
				if (dataOut > 0)
				{
					printf("SERVER> " + string(buffer, 0, dataOut));
				}
			}
		}
		
		int sendResult = send(sock, dataIn.c_str(), dataIn.size() + 1, 0);
	}


	closesocket(sock);
	WSACleanup();
}

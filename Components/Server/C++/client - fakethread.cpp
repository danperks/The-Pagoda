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
	int a = 1;
        int gameID = 0;
        int userID=0;
		string InitCommand =  "{\"gameID\":\"12345\",\"type\":\"command\",\"data\":\"INIT\",\"sender\":\"server\",\"recipient\":";// just for formtting
        string LockComamnd = "{\"gameID\":"+to_string(gameID)+",\"type\":\"command\",\"data\":\"quit\",\"sender\":\"server\",\"recipient\":"+to_string(userID)+"}";
        string VoteComamnd = "{\"gameID\":"+to_string(gameID)+",\"type\":\"command\",\"data\":\"vote\",\"sender\":\"server\",\"recipient\":\"ALL\"}";
		string UnlockCommand = "{\"gameID\":"+to_string(gameID)+",\"type\":\"command\",\"data\":\"unlock\",\"sender\":\"server\",\"recipient\":\"ALL\"}";
		string KickedCommand = "{\"gameID\":"+to_string(gameID)+",\"type\":\"command\",\"data\":\"kick\",\"sender\":\"server\",\"recipient\":"+to_string(userID)+"}";
		string WinnerCommand = "{\"gameID\":"+to_string(gameID)+",\"type\":\"command\",\"data\":\"Winner\",\"sender\":\"server\",\"recipient\":"+to_string(userID)+"}";
		string WhisperCommand =  "{\"gameID\":"+to_string(gameID)+",\"type\":\"whisper\",\"data\":\"message\",\"sender\":\"server\",\"recipient\":"+to_string(userID)+"}";
	//string PerksClient ="C:\\Users\\hpd12\\AppData\\Local\\Programs\\Microsoft VS Code\\Code.exe";
	string address = "127.0.0.1";		// IP Address of the server
	int port = 54000;					// Listening port # on the server
	int clientUnlocked = true;
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
		int EstablishConnection = recv(sock,buffer,4096,0);//gets the details from the first init comand and sets them
		string initDetails = string(buffer,0,EstablishConnection);
		//cehcks  its receiving something containg a inti command - this is open for abuse but its gettting on a bit , so can be a low priority review?
			userID = stoi(initDetails.substr(initDetails.find("recipient\":")+1));
			unsigned delimit1 = initDetails.find("gameID\":")+1;
			unsigned delimit2 = initDetails.find("\",\"type");
			gameID = stoi(initDetails.substr(delimit1,delimit2-delimit1));


		while(true){
			if (_kbhit() ) {
				cout<<"Type Here"<<endl;
				cout<<"For Whisper type / whispher and recipient etc(whisper 234) else , just type message to all / command previosuly given"<<endl;
				
				string userentry;
				cin >>userentry;
				if(userentry.find("whisper")){
					string recipient = userentry.substr(userentry.find("whisper")+1);
					string userentry =  "{\"gameID\":"+to_string(gameID)+",\"type\":\"whisper\",\"data\":\""+userentry+"\",\"sender\":\"server\",\"recipient\":"+recipient+"}";
				}
				else{
					string userentry =  "{\"gameID\":"+to_string(gameID)+",\"type\":\"broadcast\",\"data\":\""+userentry+"\",\"sender\":\"server\",\"recipient\":"+"ALL"+"}"; 
				}
				
				toSend.push_back(userentry);
			}
			else {
				int dataOut = recv(sock, buffer, 4096, 0);
				if (dataOut > 0)
				{
					cout<<"SERVER> " + string(buffer, 0, dataOut)<<endl;
					 if (string(buffer,0,dataOut).find("recipient\":"+to_string(userID)) || string(buffer,0,dataOut).find("recipient\": ALL")){
						 //checks if directed at you or all , those not will jsut straight up be ignored
					 if(LockComamnd == string(buffer, 0, dataOut)){
						                                // go over this again
                                clientUnlocked == false;
								cout<<"Console Locked , Vote Recieved"<<endl;
								while(clientUnlocked == false){
									//waiting for unlock command; // cant send anything untill unlock command recieved
									int dataOut2 = recv(sock,buffer,4096,0);
									if(UnlockCommand == string(buffer,0,dataOut2)){
										clientUnlocked == true; // client then unlocked
									}
								}

                                
				}
				if(KickedCommand == string(buffer,0,dataOut)){
					cout<<"You are no longer a contestant to win the game. Thank You. Come Again."<<endl;
					cout<<"You will be forcefully disconnected. You have no choice."<<endl;
					
					break;
				}
				if(WinnerCommand == string(buffer,0,dataOut)){
					cout<<"You have played well. You are the winner. You should be ashamed. Thank You . Come Again."<<endl;
					cout<<"You will now be forcefully disconnected. You have no choice"<<endl;
					
					break;
					
				}
			}
		}
		}
		
		int sendResult = send(sock, toSend.front().c_str(), toSend.front.c_str() + 1, 0);
	}


	closesocket(sock);
	WSACleanup();
}
	}

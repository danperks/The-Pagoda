//#include "crow_all.h"
#include <string>
#include <WS2tcpip.h>
#include <conio.h>
#include <vector>
#include <ctype.h>
#include <windows.h>
#include <iostream>
#include <winsock2.h>

// include the path with crow_all.h in
// include Boost lib
// -D_WIN32_WINNT=0x0601 -std=c++11 -lws2_32 -lmswsock

#define BOOST_THREAD_USE_LIB

#define _WIN32_WINNT_WIN10                  0x0A00
#define WIN32_LEAN_AND_MEAN
#define WINVER 0x0A00
#define _WIN32_WINNT 0x0A00
using namespace std;

class Network { // For sending and recieving data
    public:
	    int a = 1;
};

class Interface { // For running the UI
    public:
        int start() {
            crow::SimpleApp app;
            
            CROW_ROUTE(app, "/")([]() {
                string text = "<b></b>Welcome to <b>The Pagoda</b>"
                    "<br><br>"
                    "Do you want to Signup or Sign In?"
                    "<br>"
                    "<button type='button' style='Margin-Right: 10px' onclick='location.href = \"signup\";'>Signup</button>"
                    "<button type='button' onclick='location.href = \"signin\";'>Signin</button>";
                return text;
                });

            CROW_ROUTE(app, "/api/signup")([](const crow::request& req) {
                cout << req.url_params;
                return "Recieved data";
                });

            CROW_ROUTE(app, "/api/signup")([](const crow::request& req) {
                cout << req.url_params;
                return "Recieved data";
                });

            CROW_ROUTE(app, "/signup")([]() {
                return "<b>The Pagoda - Signup</b><br><br>"
                    "<form action='/api/signup' onsubmit=\"alert('Attempting to sign you up...');\">"
                    "<label for='uname'>Username:</label><br>"
                    "<input type='text' id='uname' name='uname' value=''><br>"
                    "<label for='pass'>Password:</label><br>"
                    "<input type='text' id='pass' name='pass' value=''><br><br>"
                    "<input type='submit' value='Submit'>"
                    "</form>";
                });

            CROW_ROUTE(app, "/signup")([]() {
                return "<b>The Pagoda - Sign In</b><br><br>"
                    "<form action='/api/signin' onsubmit=\"alert('Attempting to sign you in...');\">"
                    "<label for='uname'>Username:</label><br>"
                    "<input type='text' id='uname' name='uname' value=''><br>"
                    "<label for='pass'>Password:</label><br>"
                    "<input type='text' id='pass' name='pass' value=''><br><br>"
                    "<input type='submit' value='Submit'>"
                    "</form>";
                });

            CROW_ROUTE(app, "/game")([]() {
                return "<b>The Pagoda - Sign In</b><br><br>"
                    "<form action='/api/login' onsubmit=\"alert('Logging you in now...');>"
                    "<label for='uname'>Username:</label><br>"
                    "<input type='text' id='uname' name='uname' value='Username'><br>"
                    "<label for='pass'>Password:</label><br>"
                    "<input type='text' id='pass' name='pass' value='Password'><br><br>"
                    "<input type='submit' value='Submit'>"
                    "</form>";
                });

            app.port(5000).multithreaded().run();
            return 0;
        }
};

class Game { // For running the game logic
    public: 
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



        void GameRun(){
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
            vector<string> toSend;
            string letter = "";                
            string word = "";
            string dataIn;
            char buffer[4096];    
	        int letterCount = 0;
            bool clientUnlocked = true;


	        while(true){
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
};


class Main {
    int init {
        Interface gui;
        Database game;
        Network net;
        return 0;
    };
    //lockout message once voting has happend , wait untill the unlcok message is broadcast
    /*
    TODO:
    - Boots the GUI
    - Logs in to server
    - Recieves gameID from server
    - Starts game:
        - Messages sent to other players go to server
        - Server relays messages to everyone else
        - After 5 mins, the server sends a command to end the round
        - Players are told to rank others
        - At some point recieve command to leave game (kicked)
        - Show user their ELO and ask if they want to play again
    OR 
    - Access leaderboard:
        - Requests json data from server
        - Parses into pretty table
    
    */

    /*
    JSON LAYOUT:

    Command (to tell a user to quit the game):
    {"gameID":"12345","type":"command","data":"quit","sender":"server","recipient":"12345"}

    Group Message:
    {"gameID":"12345","type":"message","data":"Hey guys!","sender":"789","recipient":"0"}

    Whisper:
    {"gameID":"12345","type":"whisper","data":"Let's team up!","sender":"456","recipient":"789"}
    

    Client will send the message and whisper the same as the server
    */
    
};

// Should be untouched, put code in Main class
int main() {
    Main pagoda;
    pagoda.init();
}
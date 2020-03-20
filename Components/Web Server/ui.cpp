#include "crow_all.h"
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <WS2tcpip.h>
#include <conio.h>
#include <vector>
#include <ctype.h>
#include <windows.h>

// -I the path with crow_all.h in
// -I Boost lib
// -D_WIN32_WINNT=0x0601 -std=c++11 -lws2_32 -lmswsock

using namespace std;


string generate_popup(string text, string loc)
    {
        return "<body><script type=\"text/javascript\">"
               "alert('" + text + "'); window.location.href = '" + loc + "';"
               "</script></body>";
    };


string read_html(string name)
    {
        // cout << "Printing with name " + name;
        ifstream ifs ("static/" + name);
        string s;
        getline (ifs, s, (char) ifs.eof());
        // cout << s;
        return s;
    };

vector<string> split(string toSplit, char toSplitBy)
{
    stringstream ss(toSplit);
    string item;
    vector<string> chunks;
    while (getline(ss, item, toSplitBy))
    {
       chunks.push_back(item);
    }
    return chunks;
};



class DB
{
    string name = "hi";

    public:
        int requestLogin(){
            //json = '{"gameID":"null","type":"login","data":"' + uname = ',' + pass + '","sender":"server","recipient":"12345"}'
            
            return 0;
        }


    };

class Network
{
	string address = "127.0.0.1";		// IP Address of the server
	int port = 54000;					// Listening port # on the server
    char buffer[4096];
	string dataIn;
    SOCKET sock;
    int status = 0;


    public:
        int serv_connect(){
            WSAData data;
            int wsResult = WSAStartup(MAKEWORD(2, 2), &data);
            if (wsResult != 0)
            {
                cerr << "Can't start Winsock, Err #" << wsResult << endl;
                return 1;
            }

            sock = socket(AF_INET, SOCK_STREAM, 0); // Create socket
            if (sock == INVALID_SOCKET)
            {
                cerr << "Can't create socket, Err #" << WSAGetLastError() << endl;
                WSACleanup();
                return 2;
            }

            	sockaddr_in hint; // Create (literal) hints
	            hint.sin_family = AF_INET;
	            hint.sin_port = htons(port);
	            inet_pton(AF_INET, address.c_str(), &hint.sin_addr);

                int conn = connect(sock, (sockaddr*)&hint, sizeof(hint));
                if (conn == SOCKET_ERROR)
                {
                    cerr << "Can't connect to server, Err #" << WSAGetLastError() << endl;
                    closesocket(sock);
                    WSACleanup();
                    return 3;
            
            status = 1;
            return 0;
	}
        }

        int serv_send(string data){
            int sendResult = send(sock, data.c_str(), data.size() + 1, 0);
            if (sendResult != SOCKET_ERROR){
                return 0;
            }
            return 1;
            
        }

        string serv_recieve(){
            ZeroMemory(buffer, 4096);
			int dataOut = recv(sock, buffer, 4096, 0);
            return string(buffer, 0, dataOut);
        }

        int close(){
            closesocket(sock);
	        WSACleanup();
        }

        int getstatus(){
            return status;
        }
            
    };

class BASE
{

    DB db;
    Network net;

	string address = "127.0.0.1";
	int port = 54000;

    public:


        int start()
        {
            system("http://localhost:5000");
            
            crow::SimpleApp app;

            CROW_ROUTE(app, "/")
            ([]() {
                string address = "127.0.0.1";
                int port = 54000;

                if(net.getstatus == 0){
                    cout << net.connect() << endl;
                }
                
                return read_html("loggedout.html"); 
            });

            CROW_ROUTE(app, "/api/signup").methods("POST"_method)
            ([](const crow::request &req) {
                vector<string> seglist;
                string data = req.body;
                char delim = '&';
                seglist = split(data, delim);
                
                string uname = seglist[0].substr(6);
                string pass = seglist[1].substr(5);
                string pass2 = seglist[2].substr(12);
                
                // cout << uname << endl;
                // cout << pass << endl;
                // cout << pass2 << endl;

                if(pass == pass2){
                    // send login request to server (server should log IP address)
                    // recieves yes or no for game starting
                    // server links this client to the account for rest of game
                    bool result = true;
                    if (result == true){
                        return generate_popup("You have been successfully signed up, you will now procede to matchmaking...","/waiting");
                    }
                    else{
                        return generate_popup("Your details are already in use, please try again","/signup");
                    }
                }
                else{
                    return generate_popup("Your passwords did not match, please try again", "/signup");
                };
            });

            CROW_ROUTE(app, "/signup")
            ([]() {
                return read_html("signup.html");
            });

            CROW_ROUTE(app, "/login")
            ([]() {
                return read_html("signin.html");
            });

            CROW_ROUTE(app, "/signupfailed")
            ([]() {
                return read_html("signupfailed.html");
            });

            CROW_ROUTE(app, "/loginfailed")
            ([]() {
                return read_html("loginfailed.html");
            });

            CROW_ROUTE(app, "/game")
            ([]() {
                return read_html("chat.html");
            });

            CROW_ROUTE(app, "/waiting")
            ([]() {
                return read_html("waiting.html");
            });

            CROW_ROUTE(app, "/roundcomplete")
            ([]() {
                return read_html("waiting.html");
            });

            CROW_ROUTE(app, "/howtoplay")
            ([]() {
                return read_html("waiting.html");
            });

            CROW_ROUTE(app, "/test")
            ([]() {
                return generate_popup("testing","/waiting");
            });

            // Static Files

            CROW_ROUTE(app, "/scripts/websocket.js")
            ([]() {
                return read_html("websocket.js");
            });

            app.port(5000).multithreaded().run();
        };
    };

int main()
{
    BASE base;
    base.start();
};
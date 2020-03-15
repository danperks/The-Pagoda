#include "crow_all.h"
#include <string>
#include <iostream>
#include <fstream>

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

class DB
{
    string name = "hi";

    public:
        int checkSignup(string name)
        {
            1+1;
        };


    };

class BASE
{

    string test = "";
    string loc = "";

    public:

        int start()
        {
            crow::SimpleApp app;

            CROW_ROUTE(app, "/")
            ([]() {
                return read_html("loggedout.html"); 
            });

            CROW_ROUTE(app, "/api/signup").methods("POST"_method)
            ([](const crow::request &req) {
                cout << "Args " << req.body << endl;
                cout << "Type " << typeid(req.body).name() << endl;

                string segment;
                vector<string> seglist;

                // ifstream body = req.body
                // while(getline(req.body, segment, '&'))
                // {
                //     seglist.push_back(segment);
                // };
                
                string uname = "danperks";
                string pass = "passyword";
                string pass2 = "passyword";

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
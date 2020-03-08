#include "crow_all.h"
#include <string>

// include the path with crow_all.h in
// include Boost lib
// -D_WIN32_WINNT=0x0601 -std=c++11 -lws2_32 -lmswsock

#define BOOST_THREAD_USE_LIB

#define _WIN32_WINNT_WIN10                  0x0A00

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
};


class Main {
    int init {
        Interface gui;
        Database game;
        Network net;
        return 0;
    };
    
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
#include "crow_all.h"
#include <string>

// include the path with crow_all.h in
// include Boost lib
// -D_WIN32_WINNT=0x0601 -std=c++11 -lws2_32 -lmswsock

using namespace std;

int main()
{
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([](){
        string text = "<b></b>Welcome to <b>The Pagoda</b>"
                       "<br><br>"
                       "Do you want to Signup or Sign In?"
                       "<br>"
                       "<button type='button' style='Margin-Right: 10px' onclick='location.href = \"signup\";'>Signup</button>"
                       "<button type='button' onclick='location.href = \"signin\";'>Signin</button>";
        return text;
    });

    CROW_ROUTE(app, "/api/signup")([](const crow::request& req){
        cout << req.url_params;
        return "Recieved data";
    });

    CROW_ROUTE(app, "/signup")([](){
        return "<b>The Pagoda - Signup</b><br><br>"
                "<form action='/api/signup' onsubmit=\"alert('Account Made Successfully');\">"
                    "<label for='uname'>Username:</label><br>"
                    "<input type='text' id='uname' name='uname' value='Username'><br>"
                    "<label for='pass'>Password:</label><br>"
                    "<input type='text' id='pass' name='pass' value='Password'><br><br>"
                    "<input type='submit' value='Submit'>"
                "</form>";
    });

    CROW_ROUTE(app, "/signin")([](){
        return "<b>The Pagoda - Sign In</b><br><br>"
                "<form action='/api/login' onsubmit=\"alert('Logging you in now...');>"
                    "<label for='uname'>Username:</label><br>"
                    "<input type='text' id='uname' name='uname' value='Username'><br>"
                    "<label for='pass'>Password:</label><br>"
                    "<input type='text' id='pass' name='pass' value='Password'><br><br>"
                    "<input type='submit' value='Submit'>"
                "</form>";
    });

    CROW_ROUTE(app, "/game")([](){
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
}
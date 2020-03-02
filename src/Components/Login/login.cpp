#define SHA256 1+1;
#define sha256 1+1;

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
// #include "sha256.h"

using namespace std;


int main()
{
    string name;
    string password;
    cout << "Enter username: ";
    cin >> name;
    cout << endl;
    cout << "Enter password: ";
    cin >> password;
    cout << endl;

    SHA256 sha256;

    string check = name = "," + sha256(password);
    
    ifstream file;
    file.open("user.txt");

    ostringstream data;
    data << file.rdbuf(); // reading data
    string out = data.str();


    if (out.find(check)) 
        {
            cout << "logged in";
            return 1;
        }
    else
        {
            cout << "not a valid login";
            return 0;
        }
}
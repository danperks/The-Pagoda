#include <iostream> 
#include <string>
#include <typeinfo>

#define WM_COPYDATA                     0x004A

using namespace std; 

// Needs -std=c++11

int main(int argc, char** argv) // argc = Number of arguments       argv = Array of pointers to str arguments 
{ 
    if (argc < 2){
        cout << endl << "ERROR: Too many arguments (expected 1, recieved " + to_string(argc - 1) + ")" << endl;
        cout << "USAGE: [REPLACE ME FOR PROGRAM NAME] [pointer to allocated space] [amount of allocated space]" << endl;
        return 1;
    }

    else if (argc > 2){
        cout << "ERROR: Too few arguments (expected 1, recieved " + to_string(argc - 1) + ")" << endl;
        cout << "USAGE: [REPLACE ME FOR PROGRAM NAME] [pointer to allocated space] [amount of allocated space]";
        return 1;
    }

    else if (argc = 2){ // argv[1] is empty

        cout << argv[2]

    }
  
    return 0; 
} 

// https://docs.microsoft.com/en-us/windows/win32/ipc/interprocess-communications?redirectedfrom=MSDN#using-the-clipboard-for-ipc
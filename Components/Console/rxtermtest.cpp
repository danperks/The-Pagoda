#define DEFAULT_HELPER_EXE "ConsoleLoggerHelper.exe"
#include <iostream>
#include "ConsoleLogger.cpp"

using namespace std;

    int main(int argc , char** arg) {
        CConsoleLogger CaseFileConsole;
        CConsoleLogger ChatConsole;
        CConsoleLogger TeamNotepadConsole;

        CaseFileConsole.Create("Case File");
        ChatConsole.Create("Chat Window");
        TeamNotepadConsole.Create("Team Notepad");
        string dataIn;
        cout<<"Enter Test"<<endl;
        cin>>dataIn;
        CaseFileConsole.SetAsDefaultOutput();
        cout<<dataIn<<endl;


    }
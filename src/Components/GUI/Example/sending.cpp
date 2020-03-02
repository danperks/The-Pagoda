#include <tchar.h>
#include <Windows.h>
#include <string>

using namespace std;

int main()
{
 COPYDATASTRUCT MyCDS;
 
 string MyRec = "Message Recieved";

 MyCDS.dwData = 1;          // function identifier
 MyCDS.cbData = sizeof( MyRec );  // size of data
 MyCDS.lpData = &MyRec;  


 HWND term1=FindWindow(NULL, _T("The Pagoda - Main Menu"));
 if(term1)
    SendMessage(term1,WM_COPYDATA,0,(LPARAM)"Message Recieved");
 else
    MessageBox(0,_T("notepad ain't krap!"),_T("Report"),MB_OK);

 return 0;
}
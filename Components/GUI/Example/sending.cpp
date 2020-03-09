#include <tchar.h>
#include <Windows.h>
#include <cstdio>

int main()
{
 system("pause");
 fopen("reciever.exe","r");
 HWND term1=FindWindow(NULL, _T("The Pagoda - Window"));
 if(term1)
    SendMessage(term1,WM_SETTEXT,0,(LPARAM)"This is data");
 else
    MessageBox(0,_T("notepad ain't krap!"),_T("Report"),MB_OK);

 return 0;
}
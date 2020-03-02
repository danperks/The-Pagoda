#include <tchar.h>
#include <Windows.h>
#include <string>

//set title as The Pagoda - Window

int main(){
    HWND foreground = GetActiveWindow();
    SendMessage(foreground,WM_SETTEXT,0,(LPARAM)_T("The Pagoda - Window"));
    LPWSTR window_title;
    GetWindowText(foreground,window_title,256);
}
#include <stdio.h> // I/O buffer
#include <winsock2.h>
#include <iostream> // For cout
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#define _WIN32_WINNT 0x501 // needs -lws2_32 in g++ compile statement
#define DEFAULT_PORT "27015"

int main (){// based of ms example
    WSADATA wsaData;
    struct addrinfo * result = NULL, *ptr = NULL, protocol;
    int ourSocket;
    int WSAResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (ourSocket != 0) {
        printf("Socket failed");
        return 1;
    }
    protocol.ai_family = AF_INET;
    protocol.ai_socktype = SOCK_STREAM;
    protocol.ai_protocol = IPPROTO_TCP;
    protocol.ai_flags = AI_PASSIVE;

    WSAResult = getaddrinfo(NULL, DEFAULT_PORT, &protocol, &result);
    if(WSAResult !=0){
        printf("Failure to get adress info");
        WSACleanup();
        return 1;

    }
    for (ptr = result;ptr != NULL;ptr = ptr -> ai_next){
        ourSocket = socket(ptr -> ai_family,ptr -> ai_socktype,ptr ->ai_protocol);
        if (ourSocket == INVALID_SOCKET){
            printf("Socket failed");
            WSACleanup();
            return 1;
        }
       WSAResult = connect( ourSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
       if (WSAResult == SOCKET_ERROR){
           printf("Socket failed");
           WSACleanup();
           return 1;
       }
       break; // connection acheived
    }
    freeaddrinfo(result);
    
    while(true):
        string message = cin<<"Enter To Send"<<endl;
        WSAResult = send(ourSocket,message,(int)strlen(message),0);
        if(WSAResult == SOCKET_ERROR){
            printf("Message Send Fail");
            closesocket(ourSocket);
            WSACleanup()
        }

    



}
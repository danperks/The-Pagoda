#define _WIN32_WINNT 0x501 
#define WIN32_LEAN_AND_MEAN
#include <stdio.h> // I/O buffer
#include <winsock2.h>
#include <iostream> // For cout
#include <ws2tcpip.h>
#include <stdlib.h>
#include <windows.h>

// needs -lws2_32 in g++ compile statement
#define DEFAULT_PORT "27015"
int main(int argc, char **argv) {
    // based of ms example
    std::cout<<"it ran"<<std::endl;
    WSADATA wsaData;
    struct addrinfo * result = NULL, *ptr = NULL, protocol;
    SOCKET ourSocket;
    int WSAResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (WSAResult != 0) {
        printf("Socket failed");
        return 1;
    }
    protocol.ai_family = AF_UNSPEC;
    protocol.ai_socktype = SOCK_STREAM;
    protocol.ai_protocol = IPPROTO_TCP;
    protocol.ai_flags = AI_PASSIVE;
    char recievedMessage[512];
    WSAResult = getaddrinfo(argv[1], DEFAULT_PORT, &protocol, &result);
    
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
    
    while(true){
        std::cout<<"Enter To Send"<<std::endl;
        char message[10];
        std::cin>>message;
        WSAResult = send(ourSocket,message,(int)strlen(message),0);
        if(WSAResult == SOCKET_ERROR){
            printf("Message Send Fail");
            closesocket(ourSocket);
            WSACleanup();
            return 1;
        }
        printf("Message Sent");
        break;
        // build check to break out once user doesnt want to send no more messsages
    }
    WSAResult = shutdown(ourSocket,SD_SEND);
    do{
        WSAResult = recv(ourSocket, recievedMessage,512,0);
        if (WSAResult > 0){
            printf("Bytes received: %d\n",WSAResult);
        }
    }
    while(WSAResult>0);

    closesocket(ourSocket);
    WSACleanup();
}

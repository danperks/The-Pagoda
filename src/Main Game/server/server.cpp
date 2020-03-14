#include "json.hpp"
#include <stdlib.h>
#include <iostream>
#include <WS2tcpip.h>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdio>
#include <ctime>

// include the path with crow_all.h in
// include Boost lib
// -D_WIN32_WINNT=0x0601 -std=c++11 -lws2_32 -lmswsock

#define BOOST_THREAD_USE_LIB
#define _WIN32_WINNT_WIN10                  0x0A00

using namespace std;

class Network {
	int sendAll(gameId, data, sender){
        1+1;
    };
    int sendOne(gameID, data, sender, reciever){
        1+1;
    };
};

class Data {// this hosuld have entrie static methods as far as i can tell but as it isnt done ill leave it be
    
    public int CreateGame(){//function to return gameID;
        return 12345;//should be a game id - going ot assume 12345 at present
    }
    int doJson(gameId,command,data,sender,reciever){
        if (command = "quit"){
            void exit(1);
        }
        if (command = "message"){
            ProcMessage();
        }
        if (command = "whisper"){
            ProcWhisper();
        }
        
    };

	int parseJsonIn(dataIn){
        jsonIn = StrToJson(dataIn); // converts string to json obj
        string gameId = jsonIn["gameID"];  // gets data and saves to var
        string command = jsonIn["command"];
        string data = jsonIn["data"];
        string sender = jsonIn["sender"];
        string reciever = jsonIn["reciever"];
        doJson(gameId,command,data,sender,reciever); // passes all the data to dojson fun
        };

    json toJson(const char* jsonString){
        json jsonObj;
        std::stringstream(jsonString) >> jsonObj;
        return jsonObj;
    };

    int ProcMessage(gameID, data, sender){
        sendAll();
    }

    int ProcWhisper(gameID, data, sender, reciever){
        sendOne();
    }

};


class Main {
    SOCKET client ;
    int gameID;
    vector<int> ConnectedClients;
    
    public int start() {
        1+1;
        Data data;
        gameID = data.CreateGame();
        ServerStart();
        return 1;

    }
    int ServerStart()
        {
            // Initialze winsock
            WSADATA wsData;
            WORD ver = MAKEWORD(2, 2);

            int wsOk = WSAStartup(ver, &wsData);
            if (wsOk != 0)
            {
                cerr << "Can't Initialize winsock! Quitting" << endl;
                return 0;
            }
            
            // Create a socket
            SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
            if (listening == INVALID_SOCKET)
            {
                cerr << "Can't create a socket! Quitting" << endl;
                return 0;
            }

            // Bind the ip address and port to a socket
            sockaddr_in hint;
            hint.sin_family = AF_INET;
            hint.sin_port = htons(54000);
            hint.sin_addr.S_un.S_addr = INADDR_ANY;
            
            bind(listening, (sockaddr*)&hint, sizeof(hint));
            listen(listening, SOMAXCONN);

            fd_set master; // Create the FD
            FD_ZERO(&master); // Set the FD to zero
            FD_SET(listening, &master); // Add the listening socket

            // this will be changed by the \quit command (see below, bonus not in video!)
            bool running = true;
            int RoundNumber = 1; 
            clock_t  RoundStartTime = time(0);
            clock_t RoundEndTime = RoundStartTime + (5*60);// oculd do this with a while loop timer but idk this makes mroe sense now? ADDS 5 Minute
            bool isTimeToVote = false;//will somehow need to update list of active connections in the game once one has been kicked
            int AmountOfVotesRemaining = 0;
            vector<int> UserToKick ; // stores the user id of the perosn to kick
            while (running)
            {
                if (RoundEndTime < time(0)){//check if time has elapsed - would like to test this function in isolation tbf but meh half of this is placeholder it can wait, itll fail in favour anyway if it doesnt work
                    isTimeToVote=true;
                    AmountOfVotesRemaining = master.fd_count;

                }
                if(AmountOfVotesRemaining == 0){
                    MessageSend("Unlock Message");// this can be a json command , but placeholder boilerplate atm , stops people spamming multiple votes if their client jsut simply discards the message on transmission.
                }
                fd_set copy = master; // Copy the list to maintain inactive conns - non active conns are not returned
                int socketCount = select(0, &copy, nullptr, nullptr, nullptr); // Get active conns
                for (int i = 0; i < socketCount; i++) // Loop through all the current & potential connections
                {
                    if(isTimeToVote){
                        Voting(master,RoundNumber);// passing and overwriting / retunring the master fd , dont like it but i think itll get around the server not knwoing whos been kicked?
                        
                    }
                    SOCKET sock = copy.fd_array[i]; // Recieve data from the socket
                    if (sock == listening) // Check if connection request (aka new user) // for hd viva
                    {
                        if(master.fd_count <=9){
                            client = accept(listening, nullptr, nullptr); // Accept a new conn
                            FD_SET(client, &master); // Add new conn to FD
                            string welcomeMsg = "Welcome to the Game!\r\n"; // Define welcome message
                            send(client, welcomeMsg.c_str(), welcomeMsg.size() + 1, 0);//send welecom messsage
                        }
                        else{
                            client = accept(listening,nullptr,nullptr);
                            string MaximumGameMessage = "Quit Message";
                             // send json quit command here;
                            send(client,MaximumGameMessage.c_str(),MaximumGameMessage.size()+1,0);
                            FD_CLR(client,&master);
                            continue;//client rejected
                        } // Send welcome message
                    }
                    else // Its an inbound message
                    {   
                        char buf[4096]; // Allocate memory for message
                        ZeroMemory(buf, 4096); // Zero the memory
                        int bytesIn = recv(sock, buf, 4096, 0); // Recieve the message (in bytes)
                        string clientText = string(buf, bytesIn); // Convert message to string
                        if (!clientText.empty() && clientText[clientText.length()-1] == '\n') { // Removes new line from message
                            clientText.erase(clientText.length()-1);
                        }
                        if (bytesIn <= 0) // Checks if the response was blank - not blank unless disconnected
                        {
                            closesocket(sock); // Closes the socket connection
                            FD_CLR(sock, &master); // Removes the socket from FD
                        }
                        else if (clientText == "\n" || clientText == "\r" || clientText == " " || clientText ==  ""){ 
                            continue; // Ignores empty message
                        }
                        else {

                            cout << "Client: " + sock << endl;
                            cout << "Message: " + clientText << endl;
                            cout << "  " << endl;
                            if(isTimeToVote){//votes remain anonymous so not sent back round in ring ot all
                                    RoundEndTime = RoundEndTime+(5*60); // if the one above works this will , if it doesnt it can be looked at another time and jsut serve as pseudo
                                    AmountOfVotesRemaining = AmountOfVotesRemaining -1;
                                    MessageSend("Vote Has Been Received - Amount Left - " + AmountOfVotesRemaining);// have this act as a lockout message asweell
                                    UserToKick.push_back(stoi(clientText));// seesm to be one that ignores letters
                                    if (AmountOfVotesRemaining ==0){
                                        ReturnPlayers(RoundNumber,master,UserToKick);//not sure if this should be wiht an &
                                        if(RoundNumber == 4){
                                            FD_CLR(listening, &master); // Removes listening socket
                                            closesocket(listening);
                                            string msg = "Winner Decalred - Server shutting Down\r\n";
                                            while (master.fd_count > 0){
                                                SOCKET sock = master.fd_array[0];
                                                send(sock, msg.c_str(), msg.size() + 1, 0);
                                                FD_CLR(sock, &master);
                                                closesocket(sock);
                                                }
                                            WSACleanup(); //end game


                                        }

                                            
                                        //calculate most common elelemtns
                                        //kick those where neccessary
                                        //give the thing to a function that takes round number and the fd set 
                                        //overwrite the fd set
                                        // Boradcasts amount of votes recieved
                            }
                            for (int i = 0; i < master.fd_count; i++) // Sends message to all sockets 
                            {
                                SOCKET outSock = master.fd_array[i];
                                if (outSock != listening && outSock != sock) // Bypasses listening socket
                                {
                                    ostringstream ss;
                                    ss << "SOCKET #" << sock << ": " << buf << "\r\n";
                                    string strOut = ss.str();

                                    send(outSock, strOut.c_str(), strOut.size() + 1, 0);
                                }
                            }
                            
                        }
                    }

                }
            }

            // If here, the server is shutting down

            FD_CLR(listening, &master); // Removes listening socket
            closesocket(listening); // Closes listening socket connection
            
            // Sends shutdown message, and disconnects sockets
            string msg = "Server is shutting down. Goodbye\r\n";
            while (master.fd_count > 0)
            {
                SOCKET sock = master.fd_array[0];
                send(sock, msg.c_str(), msg.size() + 1, 0);
                FD_CLR(sock, &master);
                closesocket(sock);
            }
            WSACleanup(); // Cleanup winsock
        }
        }
        
        fd_set ReturnPlayers(int RoundNumber,fd_set fdMaster,vector<int> VotesTaken){
            //calculates most common votes and kicks them
            //not sure if should be passing in fdmaster as a &fdmaster
            int MostCommonItem = 0;
            int MostCommonNumber =0;       
            int SecondMostCommon =0;
            int SecondMostNumber=0;     
            for(int i =0;i<=VotesTaken.size;++i){//Selects item to count for - simple mechanism to get the most common votes
                int CurrentItem =VotesTaken.at(i);
                int CurrentNumber=0;
                for(int j =0;j<VotesTaken.size;i++){//iterates through
                    if(VotesTaken.at(j) == CurrentItem){
                        CurrentNumber = CurrentNumber +1;
                        if(CurrentNumber>MostCommonNumber){//else no need to swap the first
                            SecondMostCommon = MostCommonItem;
                            SecondMostNumber = MostCommonNumber;
                            MostCommonItem = CurrentItem;
                            MostCommonNumber = CurrentNumber;
                        }
                        else if (CurrentNumber > SecondMostNumber){
                            SecondMostCommon = CurrentItem;
                            SecondMostNumber = CurrentNumber;
                        }
                        
                    }
                }
            }//now time to remove the users;
            if(RoundNumber == 1 || RoundNumber ==2 ){
                FD_CLR(MostCommonItem,&fdMaster) ;
                FD_CLR(SecondMostCommon,&fdMaster) ;
                //2 person kicked
                return fdMaster;
            }
            else if(RoundNumber == 3){//1 kicked
                FD_CLR(MostCommonItem,&fdMaster) ;
                return fdMaster;

            }
            else if (RoundNumber ==4 ){
                //vote for winner
                MessageSend("Winner is "+ MostCommonItem);//sort these placeholders out;
                return fdMaster;
            }

        }
        

        void Voting(fd_set FDClients,int RoundNumber){
            int CurrentAmountOfPlayers = FDClients.fd_count;
            if(RoundNumber == 1 || RoundNumber ==2){
                //2 person kicked
                MessageSend("SERVER SEND TO ALL PLEASE 2 Will be kicked");//fill in correct json here
            }
            else if(RoundNumber ==3){
                MessageSend("SERVER SEND TO ALL PLEASE VOTE 1 will be kicked");
            }
            else{
                MessageSend("SERVER SEND TO ALL PLEASE VOTE FOR THE WINNER");//vote for your winner;
            }
            //take current amoutn of players
            //take votes to vote off each player
            //count votes for each player
            //players wiht msot votes are sent messages with json command informing them theyve been voted out

        }

        int MessageSend(string MessageToSend){
             send(client, MessageToSend.c_str(), MessageToSend.size() + 1, 0);//send welecom messsage
        }


        /*
        TODO:
        - Boot the server
        - Accept first 10 connections 
        - Create a gameID (in database)
        - Pass the gameID to the clients
        - Link the clients to their userID (recieve them from client as joining message?)
        - Start the game - threaded:
            - 4 rounds, 5 mins per round:
                - round 1 - 2 people kicked (8 remain)
                - round 2 - 2 people kicked (6 remain)
                - round 3 - 1 person kicked (5 remain)
                - round 4 - vote for winner at end
            - One minute voting between rounds
            - Clients should give each other number, for use in voting
            - In the last round, the majority voted person wins
            - All clients are told to leave
            - The GameID is deleted
            - ELOs on db are updated


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
    Main server;
    server.start();
}
#include <iostream>
#include <sqlite3.h>
#include <string>
#include "picosha2.h"

using namespace std;

// win a game + n(points)
// send points to database
// order database for matchmaking
// put database into a lifo queue 
// create games with 10 players    

// check if player is matchmaking
// add them to the same game id
// when game is done delete game id
// add scores to database 

// teams of 10
// games played  = g
// 1st place = 100 + e^()
// max = 1375
// win = elo + (50-games_won) = 50

// for nth place >= 5 = elo + (5*(10-n))-game_won 5th = 25
// for nth place < 5 = elo - (5*(6-n))

int elo(){

    int first_place_elo;
    int second_place_elo;
    int third_place_elo;
    int fourth_place_elo;
    int fith_place_elo;
    int six_place_elo;
    int seven_place_elo;
    int eight_place_elo;
    int nine_place_elo;
    int ten_place_elo;

    sqlite3* DB;
    char* errormessage;
    string id;

    

    int exit = sqlite3_open("thepagoda.db", &DB);

    string sql = "SELECT "


    if (user = ten_place){
        string sql = "UPDATE users set elo = "
    }
}



int main()
{   
    sqlite3* DB;
    int exit = 0;
    exit = sqlite3_open("thepagoda.db", &DB);
    
    if (exit) {
        cout << "Error opening the database" << endl;
        return (-1);
    }
    else
    {
        cout << "Database has been opened" << endl;
    sqlite3_close(DB);
    return (0);
    }
    
}

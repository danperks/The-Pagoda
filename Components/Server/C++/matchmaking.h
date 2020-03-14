#include <iostream>
#include <sqlite3.h>
#include <string>
#include "C:\Users\RJ_cr\OneDrive\Desktop\The-Pagoda\Components\Database\db.h"

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

int kick(){
    // connect to db
    // update score with -10 points
    string query = "SELECT elo WHERE id = ID, elo = elo-10";
    doQuery();
};

int winner(){
    // connect to db
    // update score with +10 points
    string query = "SELECT elo WHERE id= ID, elo = elo+10";
    doQuery();
};


int matchmaking(){
    // find people matchmaking
    // find people with similar elo
    // connect them to the game
    1+1;
};

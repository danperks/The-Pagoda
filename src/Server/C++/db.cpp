#include <iostream>
#include <pqxx/pqxx>

using namespace std;
using namespace pqxx;

int main(){
    const connection C = connect();
}

connection connect() {
    connection C("dbname = thepagoda user=postgres password = Mumdad45 \
        hostaddr = localhost port = 5432");
    cout << "Database has been opened:" << C.dbname() << endl;
}


int insertplayers(connection C) {
    char playerid;
    int playertype;
    char playeraddr;
    int gametoken;

    cout << "playerid" << endl;
    cin >> playerid;
    cout << "playertype" << endl;
    cin >> playertype;
    cout << "playeraddr" << endl;
    cin >> playeraddr;
    cout << "gametoken" << endl;
    cin >> gametoken;


    string sql = "INSERT INTO players (playerid, playertype, playeraddr, gametoken) " \
          "VALUES (playerid, playertype, playeraddr, gametoken)";
    work W(C);

    W.exec(sql);
    W.commit();
    cout << "Player information has been added successfully" << endl;
    C.disconnect();
    }

int insertplayergroups(connection C) {
    char playergroup;
    char playerid;

    cout << "playerid" << endl;
    cin >> playerid;
    cout << playergroup << endl;
    cin >> playergroup;

    string sql = "INSERT INTO playergroups (playergroup, playerid)" \
          "VALUES (playergroup, playerid)";
    work W(C);

    W.exec(sql);
    W.commit();
    cout << "Player information has been added successfully" << endl;
}

int insertmessages(int argc, char* argv[]) {
    int messagetoken;
    int gametoken;
    int playergroup;
    int playerid;
    char time;
    char message;

    cout << "messagetoken" << endl;
    cin >> messagetoken;
    cout << "gametoken" << endl;
    cin >> gametoken;
    cout << "playergroup" << endl;
    cin >> playergroup;
    cout << "playerid" << endl;
    cin >> playerid;
    cout << "time" << endl;
    cin >> time;
    cout << "message" << endl;
    cin >> message;

}
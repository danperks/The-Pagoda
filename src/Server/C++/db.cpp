#include <iostream>
#include <pqxx/pqxx>

using namespace std;
using namespace pqxx;

int main(){
    connect()
}

int connect(int argc, char* argv[]) {
    try {
        connection C("dbname = thepagoda user=postgres password = Mumdad45 \
        hostaddr = localhost port = 5432");
        if (C.is_open()){
            cout << "Database has been opened:" << C.dbname() << endl;
        } else{
            cout << "Database can't be opened" << endl;
            return 1;
        }
    } catch (const std::exception &e) {
        cerr << e.what() << std::endl;
        return 1;
    }
}


int insertplayers(int argc, char* argv[]) {
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


    sql = "INSERT INTO players (playerid, playertype, playeraddr, gametoken) " \
          "VALUES (playerid, playertype, playeraddr, gametoken); "
    work W(C);

    W.exec(sql);
    W.commit();
    cout << "Player information has been added successfully" << endl;
    C.disconnect();
    }

int insertplayergroups(int argc, char* argv[]) {
    char playergroup;
    char playerid;

    cout << "playerid" << endl;
    cin >> playerid;
    cout << playergroup << endl;
    cin >> playergroup;

    sql = "INSERT INTO playergroups (playergroup, playerid)" \
          "VALUES (playergroup, playerid);"
    work W(C);

    W.exec(sql);
    W.commit();
    cout << "Player information has been added successfully" << endl;
    C.disconnect();
    }
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
#include <iostream>
#include <sqlite3.h>
#include <string>
#include "picosha2.h"



using namespace std;

int create_db(){
    sqlite3* DB;
    string sql = "CREATE TABLE users("
                "id INT PRIMARY KEY NOT NULL, "
                "name TEXT NOT NULL,"
                "username TEXT NOT NULL,"
                "passhash TEXT NOT NULL,"
                "timecreate DATETIME NOT NULL)";
    int exit = 0;
    exit = sqlite3_open("thepagoda.db", &DB);
    char* errormessage;
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &errormessage);

    if (exit != SQLITE_OK) {
        cout << "Couldn't create table";
        sqlite3_free(errormessage);
    }
    else
    {
        cout << "Table created";
    sqlite3_close(DB);
    return (0);
    }
                
}


int user_create(){
    sqlite3* DB;
    char* errormessage;
    int exit = sqlite3_open("thepagoda.db", &DB);
    string query = "SELECT * FROM users;";

     sqlite3_exec(DB, query.c_str(), NULL, NULL, NULL);
    
    string id;
    string name;
    string username;
    string passprehash;
    string time;

    cout << "id";
    cin >> id;
    cout << "name";
    cin >> name;
    cout << "username";
    cin >> username;
    cout << "password";
    cin >> passprehash;
    cout << "time";
    cin >> time;

    vector<unsigned char> temphash(picosha2::k_digest_size);
    picosha2::hash256(passprehash.begin(), passprehash.end(), temphash.begin(), temphash.end());
    string passhash = picosha2::bytes_to_hex_string(temphash.begin(), temphash.end());


    string sql("INSERT INTO users VALUES('"+ id +"', '"+ name +"', '"+ username +"', '"+ passhash +"', '"+ time +"');");


    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &errormessage);
    if (exit != SQLITE_OK) {
        cout << "Could not insert";
        cout << errormessage;
        sqlite3_free(errormessage);
    }
    else
    {
        cout << "Insert completed";
    }
    
} 

int user_delete(){

    sqlite3* DB;
    char* errormessage;
    string id;

    int exit = sqlite3_open("thepagoda.db", &DB);
    string query = "SELECT * FROM users;";

    sqlite3_exec(DB, query.c_str(), NULL, NULL, NULL);

    cout << "Which user would you like to delete? ";
    cin >> id;

    string sql("DELETE FROM users WHERE id = "+ id +";");

    cout << sql;

    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &errormessage);
    if (exit != SQLITE_OK) {
        cout << "Could not delete";
        sqlite3_free(errormessage);
    }
    else
    {
        cout << "User Deleted";    
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
    user_create();
    sqlite3_close(DB);
    return (0);
    }
    
}

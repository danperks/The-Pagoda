#include <iostream>
#include <string>
#include "picosha2.h"
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

using namespace std;


const string server = "private-db-mysql-lon1-94725-do-user-7232253-0.a.db.ondigitalocean.com";
const string username = "doadmin";
const string password = "vjaoa4grnxedx1jf";

int connectionDB(){
    Driver *driver;
    Connection *con;
    Statement &stmt;
    PreparedStatement *pstmt;

    try{
        driver = get_driver_instance();
        con = driver->connect(server, username, password);
    }

    catch (SQLException e){
        cout << "Cant connect to server." << e.what();
        system("pause");
        exit(1);
    }

};

int createDB(){
    connectionDB();
    stmt = con->createStatement();
    stmt->execute("CREATE TABLE users (id INT PRIMARY KEY, name VARCHAR(60), elo INT, games_won INT, username VARCHAR(60), passhash VARCHAR(60));");
    cout << "Created table" << endl;
    delete stmt;

};

int instertDB(){
    connectionDB();

    string id;
    string name;
    string username;
    string passprehash;

    cout << "id";
    cin >> id;
    cout << "name";
    cin >> name;
    cout << "username";
    cin >> username;
    cout << "password";
    cin >> passprehash;

    vector<unsigned char> temphash(picosha2::k_digest_size);
    picosha2::hash256(passprehash.begin(), passprehash.end(), temphash.begin(), temphash.end());
    string passhash = picosha2::bytes_to_hex_string(temphash.begin(), temphash.end());

    stmt = con->createStatement();
    stmt->execute("INSERT INTO users('"+ id +"', '"+ name +"', 1000 , 0, '"+ username +"', '"+ passhash +"');");

};

int removeUser(){
    connectionDB();

    cout << "Which user would you like to delete? ";
    cin >> id;

    stmt = con->createStatement();
    stmt->execute("DELETE FROM users WHERE id = "+ id +";");

    cout << "User is now deleted";

}


int main(){
    1+1;
};
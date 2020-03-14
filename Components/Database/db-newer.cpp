#include <stdlib.h>
#include <iostream>

#include "D:\Files\Cloud\OneDrive - Coventry University\University\1 - Level 4 - 19 to 20\4007CEM - CS Project\Project 1 - Text Based Game\The-Pagoda\Components\Database\mySQL\include\jdbc\mysql_connection.h"
#include "D:\Files\Cloud\OneDrive - Coventry University\University\1 - Level 4 - 19 to 20\4007CEM - CS Project\Project 1 - Text Based Game\The-Pagoda\Components\Database\mySQL\include\jdbc\cppconn\driver.h"
#include "D:\Files\Cloud\OneDrive - Coventry University\University\1 - Level 4 - 19 to 20\4007CEM - CS Project\Project 1 - Text Based Game\The-Pagoda\Components\Database\mySQL\include\jdbc\cppconn\exception.h"
#include "D:\Files\Cloud\OneDrive - Coventry University\University\1 - Level 4 - 19 to 20\4007CEM - CS Project\Project 1 - Text Based Game\The-Pagoda\Components\Database\mySQL\include\jdbc\cppconn\resultset.h"
#include "D:\Files\Cloud\OneDrive - Coventry University\University\1 - Level 4 - 19 to 20\4007CEM - CS Project\Project 1 - Text Based Game\The-Pagoda\Components\Database\mySQL\include\jdbc\cppconn\prepared_statement.h"
using namespace std;

//for demonstration only. never save your password in the code! Naughty Naughty
const string server = "private-db-mysql-lon1-94725-do-user-7232253-0.a.db.ondigitalocean.com";
const string username = "doadmin";
const string password = "vjaoa4grnxedx1jf";

int main()
{
	sql::Driver *driver;
	sql::Connection *con;
	sql::PreparedStatement *pstmt;
	sql::ResultSet *result;

	try
	{
		driver = get_driver_instance();
		//for demonstration only. never save password in the code!
		con = driver->connect(server, username, password);
	}
	catch (sql::SQLException e)
	{
		cout << "Could not connect to server. Error message: " << e.what() << endl;
		system("pause");
		exit(1);
	}

	con->setSchema("defaultdb");

	//select  
	pstmt = con->prepareStatement("SELECT * FROM inventory;");
	result = pstmt->executeQuery();

	while (result->next())
		printf("Reading from table=(%d, %s, %d)\n", result->getInt(1), result->getString(2).c_str(), result->getInt(3));

	delete result;
	delete pstmt;
	delete con;
	system("pause");
	return 0;
}
#include <cassert>
#include <iostream>

#include <tao/pq.hpp>

int main()
{
  // Open connection
  const auto conn = tao::pq::connection::create( "dbname=template1" );

  // Execute SQL statement
  conn->execute( "DROP TABLE IF EXISTS taopq_example" );
  conn->execute( "CREATE TABLE taopq_example ( a INTEGER PRIMARY KEY, b INTEGER, c TEXT NOT NULL )" );

  // Prepare statement
  conn->prepare( "my_stmt", "INSERT INTO taopq_example VALUES ( $1, $2, $3 )" );

  {
    // Begin transaction
    const auto tr = conn->transaction();

    // Execute statement with parameters
    tr->execute( "INSERT INTO taopq_example VALUES ( $1, $2, $3 )", 1, 42, "foo" );

    // Execute previously prepared statement with parameters (recommended)
    tr->execute( "my_stmt", 2, tao::pq::null, "Hello, world!" );

    // Commit transaction
    tr->commit();
  }

  // insert/update/delete statements return an object that contains the number of rows affected
  {
    const auto res = conn->execute( "insert", 3, 3, "drei" );
    assert( res.rows_affected() == 1 );
  }

  // Queries return object with result set
  const auto res = conn->execute( "SELECT * FROM taopq_example" );
  assert( res.size() == 3 );

  // Conveniently convert result into C++ container
  const auto v = res.vector< std::tuple< int, std::optional< int >, std::string > >();
}
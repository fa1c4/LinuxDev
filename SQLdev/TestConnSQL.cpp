#include <stdlib.h>
#include <iostream>
#include <mysql_connection.h>
#include <mysql_driver.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace sql;

int main() {
    std::cout << "testing for connection of mysql database\n";
    try {
        // connecting to mySql
        sql::Driver* mDriver;
        sql::Connection* mConn;
        sql::Statement* mStmt;
        sql::ResultSet* mRes;

        mDriver = get_driver_instance();
        mConn = mDriver->connect("tcp://127.0.0.1", "fa1c4", " ");
        mConn->setSchema("test");
        mStmt = mConn->createStatement();
        mRes = mStmt->executeQuery("Select 'Hello World' AS _message");

        while (mRes->next()) {
            std::cout << mRes->getString("_message") << std::endl;
        }

        delete mRes;
        delete mStmt;
        delete mConn;
    } catch (sql::SQLException &e) {
        std::cout << "Failed Connect to mySql database" << std::endl;
        std::cout << "Error: " << e.what() << std::endl;
        std::cout << "Error Code: " << e.getErrorCode() << std::endl;
    }
}
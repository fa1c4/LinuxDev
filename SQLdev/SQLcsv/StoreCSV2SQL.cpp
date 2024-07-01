#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <mysql_connection.h>
#include <mysql_driver.h>
// mysql_driver.h has sql namespace
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>


// trim space of string
void trim(std::string &s) {
    if (!s.empty()) {
        s.erase(0, s.find_first_not_of(" "));
        s.erase(s.find_last_not_of(" ") + 1);
    }
}

// define table values here
// for registrator member struct: (name, powerlevel, powertype, gender)
sql::SQLString csvSplit(std::string& inStr) {
    std::stringstream mStream(inStr);
    sql::SQLString mSQL;
    std::string mStr;
    mSQL = "";
    mSQL.append("INSERT INTO members(name,powerlevel,powertype,gender,create_date) VALUES (");

    int i = 0;
    while (i < 4) {
        ++i;
        mStr.clear();
        // getline(mStream, mStr, ',');
        getline(mStream, mStr, '|');
        // trim space for mStr
        trim(mStr);
        mSQL.append("'" + mStr + "',");
    }

    mSQL.append("now());");
    std::cout << mSQL.c_str() << std::endl; // debug for mSQL command

    return mSQL;
}

int main(int argc, char* argv[]) {
    std::string line;
    std::vector<sql::SQLString> mVec;
    std::ifstream mFile(argv[1]);

    if (mFile.is_open()) {
        while (getline(mFile, line)) {
            // split line read from file and build insert statement, then save to mVec
            mVec.push_back(csvSplit(line));
        }
        mFile.close();
    } else {
        std::cout << "can not open file" << std::endl;
        return -1;
    }

    try {
        std::cout << "C++ Store CSV Connect to mySql" << std::endl;
        sql::Driver* mDriver;
        sql::Connection* mConn;
        sql::Statement* mStmt;

        mDriver = get_driver_instance();
        mConn = mDriver->connect("tcp://127.0.0.1", "fa1c4", " ");
        mConn->setSchema("members");
        mStmt = mConn->createStatement();
        
        for (auto it = mVec.begin(); it != mVec.end(); ++it) {
            mStmt->execute(*it);
        }

        delete mStmt;
        delete mConn;
    } catch (sql::SQLException &e) {
        std::cout << "Filed Connect to mySql database" << std::endl;
        std::cout << "Error: " << e.what() << std::endl;
        std::cout << "Error Code: " << e.getErrorCode() << std::endl;
    }

    std::cout << "END store CSV file to mySql database" << std::endl;
    return 0;
}
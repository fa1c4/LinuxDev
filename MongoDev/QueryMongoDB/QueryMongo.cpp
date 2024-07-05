#include <iostream>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/client_session.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>


int main(int argc, char* argv[]) {
    // create instance for mongodb connection
    mongocxx::instance inst{};
    mongocxx::uri mURI("mongodb://localhost:27017"); 
    // mongodb default port is 27017
    bsoncxx::builder::stream::document mDoc;

    try {
        // connecting to mongo database
        mongocxx::client conn(mURI);
        mongocxx::database mDB = conn["mongotest"]; // database name differs from coders
        mongocxx::collection mColl = mDB["members"]; // collections name differs from coders
        // mongocxx::cursor mCor = mColl.find({});
        // get data by gender
        mDoc << "gender" << argv[1]; // notice that there is no ' ' in "gender" string 
        mongocxx::cursor mCor = mColl.find(mDoc.view());

        // print all item in collection as json file format
        // for (auto&& doc : mCor) {
        //     std::cout << bsoncxx::to_json(doc) << std::endl;
        // }
        // print as std::string
        for (auto&& doc : mCor) {
            bsoncxx::document::element mName = doc["name"];
            bsoncxx::document::element mGender = doc["gender"];
            bsoncxx::document::element mPowertype = doc["powertype"];
            bsoncxx::document::element mPowerlevel = doc["powerlevel"];
            std::string strName = std::string(mName.get_string().value);
            std::string strGender = std::string(mGender.get_string().value);
            std::string strPowertype = std::string(mPowertype.get_string().value);
            std::string strPowerlevel = std::string(mPowerlevel.get_string().value);
            std::cout << "member: " << strName << std::endl;
            std::cout << "gender: " << strGender << std::endl;
            std::cout << "power type: " << strPowertype << std::endl;
            std::cout << "power level: " << strPowerlevel << std::endl << std::endl;
        }
    } catch (const std::exception& xcp) {
        std::cout << "connection failed: " << xcp.what() << std::endl;
        return EXIT_FAILURE;
    }

    return 0;
}

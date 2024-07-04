#include <iostream>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/client_session.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>


int main() {
    // create instance for mongodb connection
    mongocxx::instance inst{};
    mongocxx::uri mURI("mongodb://localhost:27017"); 
    // mongodb default port is 27017

    try {
        // connecting to mongo database
        mongocxx::client conn(mURI);
        mongocxx::database mDB = conn["mongotest"]; // database name differs from coders
        mongocxx::collection mColl = mDB["members"]; // collections name differs from coders
        mongocxx::cursor mCor = mColl.find({});

        // print all item in collection as json file format
        for (auto&& doc : mCor) {
            std::cout << bsoncxx::to_json(doc) << std::endl;
        }
    } catch (const std::exception& xcp) {
        std::cout << "connection failed: " << xcp.what() << std::endl;
        return EXIT_FAILURE;
    }

    return 0;
}
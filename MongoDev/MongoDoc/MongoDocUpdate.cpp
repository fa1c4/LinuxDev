#include <iostream>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/client_session.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_array;
using bsoncxx::builder::basic::make_document; 


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

        {
            mColl.update_one(
                make_document(kvp("name", "baili3")), // search parameter
                make_document(kvp("$set", make_document(kvp("gender", "female")))) // update the value
            );

            mCor = mColl.find({});
            std::cout << std::endl;
            for (auto&& doc : mCor) {
                std::cout << bsoncxx::to_json(doc) << std::endl;
            }
        }
    } catch (const std::exception& xcp) {
        std::cout << "connection failed: " << xcp.what() << std::endl;
        return EXIT_FAILURE;
    }

    return 0;
}

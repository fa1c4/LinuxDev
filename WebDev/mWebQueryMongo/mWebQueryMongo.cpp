#include <memory>
#include <string>
#include <cstdlib>
#include <sstream>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/basic/kvp.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/client_session.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>

#include <restbed>


using namespace std;
using namespace restbed;
using bsoncxx::builder::stream::document;


void testQueryMongo() {
    mongocxx::uri mURI("mongodb://localhost:27017"); 
    // mongodb default port is 27017
    bsoncxx::builder::stream::document mDoc;

    try {
        // connecting to mongo database
        mongocxx::client conn(mURI);
        mongocxx::database mDB = conn["mongotest"]; // database name differs from coders
        mongocxx::collection mColl = mDB["members"]; // collections name differs from coders
        
        // get data by gender
        mDoc << "gender" << "male";
        mongocxx::cursor mCor = mColl.find(mDoc.view());

        // print all item in collection as json file format
        for (auto&& doc : mCor) {
            std::cout << bsoncxx::to_json(doc) << std::endl;
        }

    } catch (const std::exception& xcp) {
        std::cout << "connection failed: " << xcp.what() << std::endl;
        return;
    }
}

std::stringstream queryMongoDB(const bsoncxx::builder::basic::document &inDoc) {
// std::stringstream queryMongoDB(const bsoncxx::builder::stream::document &inDoc) {
    stringstream mStream;
    mStream.clear();

    mongocxx::uri mURI("mongodb://localhost:27017"); 
    // mongodb default port is 27017
    // mongocxx::client conn{mURI};

    try {
        // connecting to mongo database
        mongocxx::client conn(mURI);
        mongocxx::database mDB = conn["mongotest"]; // database name differs from coders
        mongocxx::collection mColl = mDB["members"]; // collections name differs from coders

        // std::cout << "debug checkpoint 1\n";        
        mongocxx::cursor mCor = mColl.find(inDoc.view());
        // std::cout << "debug checkpoint 2\n";
        for (auto&& doc: mCor) { // bugs here
            // std::cout << bsoncxx::to_json(doc) << std::endl;
            // std::cout << "debug checkpoint 3\n";
            mStream << bsoncxx::to_json(doc) << "\r\n";
        }

    } catch(const std::exception& xcp) {
        std::cout << "mColl find error with " << xcp.what() << std::endl;
        mStream << "mColl find error with " << xcp.what() << std::endl;
        return mStream;
    }

    return mStream;
}

void get_method_handler(const shared_ptr<Session> session) {
    const auto request = session->get_request();
    string response_body;
    stringstream mStream;
    mStream.clear();

    string paramLevel = request->get_query_parameter("powerlevel");
    string paramGender = request->get_query_parameter("gender");
    string paramName = request->get_query_parameter("name");

    bsoncxx::builder::basic::document mDoc;
    // bsoncxx::builder::stream::document mDoc;
    if (paramName.length() > 0) {
        mDoc.append(bsoncxx::builder::basic::kvp("name", paramName));
        // mDoc << "name" << paramName;
    }
    if (paramGender.length() > 0) {
        mDoc.append(bsoncxx::builder::basic::kvp("gender", paramGender));
        // mDoc << "gender" << paramGender;
    }
    if (paramLevel.length() > 0) {
        mDoc.append(bsoncxx::builder::basic::kvp("powerlevel", paramLevel));
        // mDoc << "powerlevel" << paramLevel;
    }

    try {
        mStream = queryMongoDB(mDoc);
    } catch (const std::exception& xpc) {
        mStream << "no results in mongo database for\n" << "name: " << paramName << "\n";
        mStream << "gender: " << paramGender << "\n";
        mStream << "powerlevel: " << paramLevel << "\n";
    }
    
    // testQueryMongo();

    response_body = mStream.str();
    session->close(OK, response_body, {{"Content-Length", std::to_string(response_body.length())}, {"Content-Type", "application/json"}});
}

void service_ready_handler(Service&) {
    // shared_ptr<mongocxx::instance> inst = make_shared<mongocxx::instance>();
    // big bug here, instance has no use at all
    cout << "The service port 1234 /members is up and running." << std::endl;
}


int main(int argc, char *argv[])
{
    shared_ptr<restbed::Resource> mResource = make_shared<restbed::Resource>();
    mResource->set_path("/members");
    mResource->set_method_handler("GET", get_method_handler);

    shared_ptr<restbed::Settings> mSettings = make_shared<restbed::Settings>();
    mSettings->set_port(1234);
    mSettings->set_default_header("Connection", "close");

    shared_ptr<restbed::Service> mService = make_shared<restbed::Service>();
    mService->publish(mResource);
    mService->set_ready_handler(service_ready_handler);
    mService->start(mSettings);

    return EXIT_SUCCESS;
}

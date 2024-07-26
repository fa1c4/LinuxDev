#include <iostream>
#include <memory>
#include <string>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <restbed>

#include <nlohmann/json.hpp>

#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/basic/kvp.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/client_session.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>

using namespace restbed;


void function_get_method(const std::shared_ptr<Session> session) {
    std::string response_body;
    std::string line;
    std::stringstream mStream;

    const auto request = session->get_request();
    std::string paramName = request->get_query_parameter("name");
    std::string paramGender = request->get_query_parameter("gender");

    mStream << "{\r\n";
    mStream << "    Name: " << paramName << std::endl;
    mStream << "    Gender: " << paramGender << std::endl;
    mStream << "}\r\n";

    response_body = mStream.str();
    session->close(OK, response_body, {{"Content-Length", std::to_string(response_body.length())}, {"Content-Type", "application/json"}});
}

void insertIntoMongoDB(const bsoncxx::builder::basic::document& inDoc) {
    mongocxx::uri mURI("mongodb://localhost:27017");
    mongocxx::client conn{mURI};
    mongocxx::collection Coll = conn["mongotest"]["members"];
    try {
        std::string inDocContents = bsoncxx::to_json(inDoc.view());
        std::cout << inDocContents << std::endl;

        Coll.insert_one(inDoc.view());
        std::cout << "insert inDoc successfully" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

/*
void parseBodyToBsonDoc(const std::string& inStr) {
    bsoncxx::builder::basic::document mBsonDoc;
    // trim string
    std::string mStr = inStr;
    mStr.erase(0, mStr.find_first_not_of(" \t\n\r\v"));
    mStr.erase(mStr.find_last_not_of(" \t\n\r\v") + 1);

    QJsonDocument mDoc = QJsonDocument::fromJson(mStr.c_str());
    QJsonObject mObj = mDoc.object();
    if (mObj.isEmpty()) {
        std::cout << "JSON data empty or conversion not success" << std::endl;
    } else {
        for (auto it = mObj.begin(); it != mObj.end(); ++it) {
            std::string mKey = std::string(it.key().toUtf8());
            std::string mValue;
            if (it->isArray()) {
                // build BSON Array
                QJsonArray mArr = it->toArray();
                mValue = "[ ";
                for (auto iter = mArr.begin(); iter != mArr.end(); ++iter) {
                    mValue += std::string(iter->toString().toUtf8());
                    mValue += ",";
                }
                mValue.erase(mValue.find_last_not_of(','));
                mValue += " ]";
            } else {
                mValue = std::string(it.value().toString().toUtf8());
            }
            mBsonDoc.append(bsoncxx::builder::basic::kvp(mKey, mValue));
        }
        insertIntoMongoDB(mBsonDoc);
    }
}
*/

void parseBodyToBsonDoc(const std::string& inStr) {
    bsoncxx::builder::basic::document mBsonDoc;

    // Trim the input string
    std::string mStr = inStr;
    mStr.erase(0, mStr.find_first_not_of(" \t\n\r\v"));
    mStr.erase(mStr.find_last_not_of(" \t\n\r\v") + 1);

    try {
        // Parse the JSON string into a JSON object
        nlohmann::json mObj = nlohmann::json::parse(mStr);

        // Iterate over the JSON object and build the BSON document
        for (auto it = mObj.begin(); it != mObj.end(); ++it) {
            std::string mKey = it.key();
            std::string mValue;

            if (it->is_array()) {
                mValue = "[ ";
                for (const auto& element : it.value()) {
                    mValue += element.get<std::string>();
                    mValue += ", ";
                }
                if (!it.value().empty()) {
                    mValue.pop_back(); // Remove the trailing comma
                    mValue.pop_back(); // Remove the trailing space
                }
                mValue += " ]";
            } else if (it->is_string()) {
                mValue = it.value();
            } else {
                mValue = it.value().dump(); // Dump non-string types to string
            }

            mBsonDoc.append(bsoncxx::builder::basic::kvp(mKey, mValue));
        }
        insertIntoMongoDB(mBsonDoc);

    } catch (const nlohmann::json::parse_error& e) {
        std::cout << "JSON parse error: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void function_post_method(const std::shared_ptr<Session> session) {
    const auto request = session->get_request();
    int content_length = 0;
    request->get_header("Content-Length", content_length, 0);

    session->fetch(content_length,
                    [](const std::shared_ptr<Session> session, const Bytes &body){
                        std::string bodyStr = std::string(body.begin(), body.end());
                        std::string response_body = "Body-Length is: " + std::to_string(bodyStr.length());
                        parseBodyToBsonDoc(bodyStr);
                        session->close(OK, bodyStr, {{"Content-Length", std::to_string(bodyStr.length())}});
                    }); 
}

void function_service_ready(Service&) {
    std::cout << "REST Service of /members port 1234 is ready" << std::endl;
}

int main(int argc, char* argv[]) {
    // Set Resource
    auto resource = std::make_shared<Resource>();
    resource->set_path("/members");
    resource->set_method_handler("GET", function_get_method);
    resource->set_method_handler("POST", function_post_method);

    // Set Setting
    auto settings = std::make_shared<Settings>();
    // settings->set_bind_address("127.0.0.1");
    settings->set_port(1234);
    settings->set_default_header("Connection", "close");

    // Set and Initialize Service
    auto service = std::make_shared<Service>();
    service->publish(resource);
    service->set_ready_handler(function_service_ready);
    service->start(settings);

    return EXIT_SUCCESS;
}

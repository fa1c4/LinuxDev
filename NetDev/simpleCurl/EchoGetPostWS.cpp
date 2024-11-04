#include "EchoGetPostWS.h"

using namespace std;
using namespace restbed;


int ws_port;
std::string ws_path;

void post_method_handler(const shared_ptr<Session> session) {
    const auto request = session->get_request();
    int content_length = 0;
    request->get_header("Content-Length", content_length, 0);
    std::cout << "HTTP POST Request received content_length: " << content_length << std::endl;
    session->fetch(content_length, [](const shared_ptr<Session> session, const Bytes &body){
        const auto request = session->get_request();
        int content_length = 0;
        request->get_header("Content-Length", content_length, 0);
        
        std::stringstream mStream;
        mStream << "{\r\n";
        mStream << "    'WS port': '" << ws_port << "',\r\n    'WS path': '" << ws_path << "',\r\n";
        mStream << "    'http_request': 'POST',\r\n";
        mStream << "    'Content-Length': '" << content_length << "',\r\n";
        mStream << "    " << std::string(body.begin(), body.end()) << "\r\n}";
        std::cout << std::string(body.begin(), body.end()) << std::endl;

        std::string bodyStr = mStream.str();
        std::string response_body = "Body-Length is: " + std::to_string(bodyStr.length());
        session->close(OK, bodyStr, {{"Content-Length", std::to_string(bodyStr.length())}});
    });
}

void get_method_handler(const shared_ptr<Session> session) {
    const auto request = session->get_request();
    int content_length = 0;
    request->get_header("Content-Length", content_length, 0);
    std::cout << "HTTP Get Request received content-length: " << content_length << std::endl;

    std::string response_body;
    std::stringstream mStream;
    std::string paramName = request->get_query_parameter("Name");
    std::string paramGender = request->get_query_parameter("Gender");

    mStream << "{\r\n";
    mStream << "    'WS port': '" << ws_port << "',\r\n    'WS path': '" << ws_path << "',\r\n";
    mStream << "    'http_request': 'GET',\r\n  'Content-Length': '" << content_length << "',\r\n";
    if (paramName.length() > 0) {
        mStream << "    'Name': '" << paramName;
        std::cout << "{ Name: " << paramName;
    }
    if (paramGender.length() > 0) {
        if (paramName.length() > 0) {
            std::cout << ", ";
            mStream << "',\r\n";
        }
        std::cout << "Gender: " << paramGender << " }" << std::endl;
        mStream << "    'Gender': '" << paramGender;
    }
    mStream << "'\r\n}";

    response_body = mStream.str();
    session->close(OK, response_body, {{"Content-Length", ::to_string(response_body.length())}, {"Content-Type", "application/json"}});
}

void put_method_handler(const shared_ptr<Session> session) {
    std::string response_body;
    std::stringstream mStream;
    int content_length = 0;
    const auto request = session->get_request();
    request->get_header("Content-Length", content_length, 0);
    std::cout << "HTTP PUT Request received Content_Length: " << content_length << std::endl;

    mStream << "{\r\n";
    mStream << "    'WS port': " << ws_port << "',\r\n WS path: '" << ws_path << "',\r\n";
    mStream << "    'http_request': 'PUT',\r\n  'Content_Length': '" << content_length << "'}\r\n";
    response_body = mStream.str();
    session->close(OK, response_body, {{"Content-Length", ::to_string(response_body.length())}, {"Content-Type", "application/json"}});
}

void service_ready_handler(Service&) {
    std::cout << "The service port " << ws_port << " " << ws_path << " is up and running." << std::endl;
}


int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " <port> <WS path>" << std::endl;
        std::cout << "Example: " << argv[0] << " 1234 ./mEchoWS" << std::endl;
        return EXIT_FAILURE;
    }

    ws_port = atoi(argv[1]);
    ws_path = std::string(argv[2]);

    std::shared_ptr<restbed::Resource> mResource = make_shared<restbed::Resource>();
    mResource->set_path(ws_path);
    mResource->set_method_handler("GET", get_method_handler);
    mResource->set_method_handler("POST", post_method_handler);
    mResource->set_method_handler("PUT", put_method_handler);

    std::shared_ptr<restbed::Settings> mSettings = make_shared<restbed::Settings>();
    mSettings->set_port(ws_port);
    mSettings->set_default_header("Connection", "close");

    std::shared_ptr<restbed::Service> mService = make_shared<restbed::Service>();
    mService->publish(mResource);
    mService->set_ready_handler(service_ready_handler);
    mService->start(mSettings);

    return EXIT_SUCCESS;
}

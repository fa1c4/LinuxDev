#include <iostream>
#include <memory>
#include <string>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <restbed>

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

void function_post_method(const std::shared_ptr<Session> session) {
    const auto request = session->get_request();
    int content_length = 0;
    request->get_header("Content-Length", content_length, 0);

    session->fetch(content_length,
                    [](const std::shared_ptr<Session> session, const Bytes &body){
                        std::string bodyStr = std::string(body.begin(), body.end());
                        std::string response_body = "Body-Length is: " + std::to_string(bodyStr.length());
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

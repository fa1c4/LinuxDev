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

    std::ifstream mFile("./members.json");
    if (mFile.is_open()) {
        while (getline(mFile, line)) {
            mStream << line << "\r\n";
        }
        mFile.close();
    } else {
        std::cout << "open json file failed" << std::endl;
    }

    response_body = mStream.str();
    session->close(OK, response_body, {{"Content-Length", std::to_string(response_body.length())}, {"Content-Type", "application/json"}});
}

void function_service_ready(Service&) {
    std::cout << "REST Service of /members port 1234 is ready" << std::endl;
}

int main(int argc, char* argv[]) {
    // Set Resource
    auto resource = std::make_shared<Resource>();
    resource->set_path("/members");
    resource->set_method_handler("GET", function_get_method);

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
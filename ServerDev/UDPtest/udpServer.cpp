#include "udpServer.hpp"
#include <cstdlib>
#include <iostream>
#include <boost/asio.hpp>
#include <stdio.h>
#include <string.h>

// using boost::asio::ip::udp;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: udp server <port>" << std::endl;
        return -1;
    }

    // step1: instantiate io_service
    // step2: make a customerized server
    // step3: start io_service
    try {
        boost::asio::io_service mio_service;
        mUdpServer mServer(mio_service, std::atoi(argv[1]));
        mio_service.run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}   

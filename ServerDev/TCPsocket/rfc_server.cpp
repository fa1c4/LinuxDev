#include <iostream>
#include <string.h>
#include <ctime>
#include <string>
#include <fstream>
#include <boost/asio.hpp>

using namespace std;
using boost::asio::ip::tcp;


std::string func_daytime_string() {
    time_t now = time(0);
    return ctime(&now);
}


int main(int argc, char* argv[]) {
    char FileName[128];
    memset(FileName, '\0', sizeof(FileName));

    try {
        if (argc != 3) {
            std::cerr << "Usage: " << argv[0] << " <port> " << " <FileName> " << std::endl;
            return -1;
        }
        memcpy(FileName, argv[2], strlen(argv[2]));

        boost::asio::io_context io_context;
        tcp::endpoint endpoint(tcp::v4(), std::atoi(argv[1]));
        tcp::acceptor acceptor(io_context, endpoint);
        std::string line;

        while (true) {
            tcp::iostream stream;
            boost::system::error_code ec;
            acceptor.accept(stream.socket(), ec);

            if (!ec) {
                ofstream mFile(FileName);
                if (mFile.is_open()) {
                    while (true) {
                        std::getline(stream, line);
                        if (stream.basic_iostream::eof()) break;
                        mFile << line << std::endl;
                    }
                    mFile.flush();
                    mFile.close();
                    std::cout << "Receiving completed and written to " << FileName << std::endl;
                }
            }
        }
    } catch (exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

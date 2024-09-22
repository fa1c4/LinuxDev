#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/asio.hpp>

using namespace std;
using boost::asio::ip::tcp;

std::string func_daytime_string() {
    time_t now = time(0);
    return ctime(&now);
}


int main(int argc, char* argv[]) {
    try {
        if (argc != 3) {
            std::cerr << "Usage: " << argv[0] << " <host:port> <File Name>" << std::endl;
            return -1;
        }

        std::vector<std::string> sVec;
        split(sVec, argv[1], boost::is_any_of(":"));
        std::string line;

        tcp::iostream s(sVec[0], sVec[1]);
        if (!s) {
            std::cout << "Unable to connect to: " << argv[1] << std::endl;
            std::cout << s.error().message() << std::endl;
            return -2;
        }

        ifstream mFile(argv[2]);
        if (mFile.is_open()) {
            while (std::getline(mFile, line)) {
                s << line << std::endl;
            }            
        }
        mFile.close();
        s.close();
    } catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    return 0;
}

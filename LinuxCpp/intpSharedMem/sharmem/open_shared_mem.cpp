#include <boost/interprocess/managed_shared_memory.hpp>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <stdio.h>

using namespace boost::interprocess;


int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " handle" << std::endl;
        return -1;
    }

    char buffer[1024];
    char opt[32];
    memset(buffer, '\0', sizeof(buffer));
    memset(opt, '\0', sizeof(opt));

    managed_shared_memory segment(open_only, "mSharedMemory");
    managed_shared_memory::handle_t handle = 0;

    // obtain handle value
    std::stringstream ss;
    ss << argv[1];
    ss >> handle;

    // get buffer local address from handle
    void *msg = segment.get_address_from_handle(handle);
    while (true) {
        std::cout << "Select Option (write | read | exit): ";
        std::cin.getline(opt, sizeof(opt));

        if (!strcmp(opt, "write")) {
            std::cout << "Shared Memory: ";
            memset(buffer, '\0', sizeof(buffer));
            std::cin.getline(buffer, sizeof(buffer));
            memset(msg, '\0', 1024);
            memcpy((char*)msg, buffer, strlen(buffer));
        } else if (!strcmp(opt, "read")) {
            std::cout << "Shared Memory: ";
            std::cout << (char*)msg << std::endl;
        } else { // exit
            break;
        }
    }

    std::cout << "exiting from open shared memory" << std::endl;
    return 0;
}

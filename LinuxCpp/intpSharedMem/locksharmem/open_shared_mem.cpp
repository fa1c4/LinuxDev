#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include "shared_memory_object.hpp"

using namespace boost::interprocess;


int main(int argc, char* argv[]) {
    char buffer[1024];
    char opt[32];
    memset(buffer, '\0', sizeof(buffer));
    memset(opt, '\0', sizeof(opt));

    std::cout << "Waiting for data region unlocking ..." << std::endl;

    shared_memory_object shm(open_only, "mSharedMemory", read_write);
    mapped_region region(shm, read_write);
    void *addr = region.get_address();
    shared_memory_message* data = static_cast<shared_memory_message*>(addr);
    scoped_lock<interprocess_mutex> lock(data->mutex);

    while (true) {
        std::cout << "Select Option (lock | unlock | write | read | exit): ";
        memset(opt, '\0', sizeof(opt));
        std::cin.getline(opt, sizeof(opt));

        if (!strcmp(opt, "lock")) {
            if (!lock.owns()) lock.lock();
        } else if (!strcmp(opt, "unlock") && lock.owns()) {
            lock.unlock();
        } else if (!strcmp(opt, "write")) {
            if (lock.owns()) {
                std::cout << "Shared Memory: ";
                memset(buffer, '\0', sizeof(buffer));
                std::cin.getline(buffer, sizeof(buffer));
                memset(data->items, '\0', 1024);
                memcpy(data->items, buffer, strlen(buffer));
            }
        } else if (!strcmp(opt, "read")) {
            std::cout << "Shared Memory: ";
            std::cout << data->items << std::endl;
        } else { // exit
            // create_shared_mem should start first and exit first
            lock.unlock();
            break;
        }
    }

    std::cout << "exiting from open shared memory" << std::endl;
    return 0;
}

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include "shared_memory_object.hpp"

using namespace boost::interprocess;


int main(int argc, char* argv[]) {
    char buffer[1024];
    char opt[32];
    memset(buffer, '\0', sizeof(buffer));
    memset(opt, '\0', sizeof(opt));

    struct shm_remove {
        shm_remove() {shared_memory_object::remove("mSharedMemory");}
        ~shm_remove() {shared_memory_object::remove("mSharedMemory");}
    } remover;

    shared_memory_object shm(create_only, "mSharedMemory", read_write);
    shm.truncate(sizeof(shared_memory_message));
    mapped_region region(shm, read_write);
    void *addr = region.get_address();

    shared_memory_message* data = new (addr) shared_memory_message;
    scoped_lock<interprocess_mutex> lock(data->mutex);

    if (lock.owns()) {
        char Initstr[] = "Initial Create Message";
        memcpy(data->items, Initstr, strlen(Initstr));
        lock.unlock();
    }

    while (true) {
        std::cout << "Select Option (lock | unlock | write | read | exit): ";
        memset(opt, '\0', sizeof(opt));
        std::cin.getline(opt, sizeof(opt));
        if (!strcmp(opt, "lock")) {
            if (!lock.owns()) lock.lock();
        } else if (!strcmp(opt, "unlock")) {
            if (lock.owns()) lock.unlock();
        } else if (!strcmp(opt, "write")) {
            if (lock.owns()) {
                std::cout << "Shared Memory: ";
                memset(buffer, '\0', sizeof(buffer));
                std::cin.getline(buffer, sizeof(buffer));
                memset(data->items, '\0', 1024);
                memcpy(data->items, buffer, strlen(buffer));
            } else {
                std::cout << "Other process locked shared_memory_object" << std::endl;
            }
        } else if (!strcmp(opt, "read")) {
            std::cout << "Shared Memory: " << data->items << std::endl;
        } else {
            break;
        }
    }

    std::cout << "exiting from create shared memory" << std::endl;
    return 0;
}

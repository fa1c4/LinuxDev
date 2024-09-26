#include <boost/interprocess/managed_shared_memory.hpp>
#include <cstdlib>
#include <sstream>
#include <iostream>

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

    managed_shared_memory segment(create_only, "mSharedMemory", 65536);
    managed_shared_memory::size_type free_memory_before = segment.get_free_memory();
    void *shptr = segment.allocate(1024);
    managed_shared_memory::size_type free_memory_after = segment.get_free_memory();
    std::cout << "Free Memory Before: " << free_memory_before << std::endl;
    std::cout << "Free Memory After: " << free_memory_after << std::endl;
    std::cout << "Free Memory Diff: " << free_memory_before - free_memory_after << std::endl;

    managed_shared_memory::handle_t handle = segment.get_handle_from_address(shptr);
    std::cout << "Shared Memory handle: " << handle << std::endl;

    while (true) {
        std::cout << "Select Option (write | read | exit): ";
        memset(opt, '\0', sizeof(opt));
        std::cin.getline(opt, sizeof(opt));
        if (!strcmp(opt, "write")) {
            std::cout << "Shared Memory: ";
            memset(buffer, '\0', sizeof(buffer));
            std::cin.getline(buffer, sizeof(buffer));
            memset(shptr, '\0', 1024);
            memcpy((char*)shptr, buffer, strlen(buffer));
        } else if (!strcmp(opt, "read")) {
            std::cout << "Shared Memory: " << (char*)shptr << std::endl;
        } else {
            break;
        }
    }

    std::cout << "exiting from create shared memory" << std::endl;
    return 0;
}

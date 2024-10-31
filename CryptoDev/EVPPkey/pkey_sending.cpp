#include "evp_class.h"
#include <boost/interprocess/managed_shared_memory.hpp>
#include <cstdlib>
#include <sstream>

using namespace boost::interprocess;


int main(int argc, char* argv[]) {
    LibOpenSSL::Message textMsg;
    LibOpenSSL::Message byteMsg;
    EVP_PKEY* m_pkey = nullptr;
    int shared_mem_len = sizeof(LibOpenSSL::Message);

    if (argc != 2) {
        fprintf(stdout, "Usage: %s <key_file>\n", argv[0]);
        fprintf(stdout, "Example: %s public_key.pem\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    struct shm_remove {
        shm_remove() {shared_memory_object::remove("mSharedMemory");}
        ~shm_remove() {shared_memory_object::remove("mSharedMemory");}
    } remover;

    managed_shared_memory segment(create_only, "mSharedMemory", 65536);
    void* shptr = segment.allocate(shared_mem_len);
    managed_shared_memory::handle_t handle = segment.get_handle_from_address(shptr);
    std::cout << "Shared Memory handle: " << handle << std::endl;
    LibOpenSSL::mEVP_Key keyObj;
    m_pkey = keyObj.load_key("public", argv[1]);
    if (m_pkey == nullptr) {
        std::cout << "Load Key File Error " << std::endl;
        exit(EXIT_FAILURE);
    }

    while (true) {
        std::cout << "Input Message: ";
        memset(textMsg.msg_body, 0, MAX_BUFFER_SIZE);
        std::cin.getline((char*)textMsg.msg_body, MAX_BUFFER_SIZE);

        if (memcmp(textMsg.msg_body, "exit", sizeof("exit")) == 0) {
            break;
        }

        textMsg.msg_len = strlen((char*)textMsg.msg_body);

        if (textMsg.msg_len > 0) {
            memset(byteMsg.msg_body, 0, MAX_BUFFER_SIZE);
            memset(shptr, 0, shared_mem_len);
            byteMsg.msg_len = keyObj.pkey_encrypt(textMsg.msg_body, byteMsg.msg_body);
            if (byteMsg.msg_len > 0) {
                keyObj.print_hash(byteMsg.msg_body, byteMsg.msg_len);
                memcpy((char*)shptr, &byteMsg, shared_mem_len);
            }
        }
    }

    return 0;
}

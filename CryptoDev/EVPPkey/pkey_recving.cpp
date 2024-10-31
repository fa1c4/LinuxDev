#include "evp_class.h"
#include <boost/interprocess/managed_shared_memory.hpp>
#include <iostream>
#include <stdio.h>

using namespace boost::interprocess;


int main(int argc, char* argv[]) {
    char opt[32];
    memset(opt, 0, sizeof(opt));

    if (argc != 3) {
        fprintf(stdout, "Usage: %s <handle> <key_file>\n", argv[0]);
        fprintf(stdout, "Example: %s 233\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    managed_shared_memory segment(open_only, "mSharedMemory");
    managed_shared_memory::handle_t handle = 0;

    std::stringstream s;
    s << argv[1];
    s >> handle;

    void* msg = segment.get_address_from_handle(handle);
    LibOpenSSL::mEVP_Key keyObj;
    EVP_PKEY* m_pkey = keyObj.load_key("private", argv[2]);
    if (m_pkey == nullptr) {
        std::cout << "Load Key File Error " << std::endl;
        exit(EXIT_FAILURE);
    }

    while (true) {
        memset(opt, 0, sizeof(opt));
        std::cout << "Select Option (read | exit): ";
        std::cin.getline(opt, sizeof(opt));

        if (!strcmp(opt, "read")) {
            LibOpenSSL::Message textMsg;
            LibOpenSSL::Message byteMsg;
            memcpy(&byteMsg, msg, sizeof(LibOpenSSL::Message));
            if (byteMsg.msg_len > 0) {
                keyObj.print_hash(byteMsg.msg_body, byteMsg.msg_len);
                textMsg.msg_len = keyObj.pkey_decrypt(textMsg.msg_body, byteMsg.msg_body, byteMsg.msg_len);
                std::cout << "Message Received: ";
                std::cout << textMsg.msg_body << " (" << textMsg.msg_len << ")" << std::endl;
            }
        } else if (!strcmp(opt, "exit")) {
            break;
        }
    }

    segment.deallocate(msg);
    return 0;
}

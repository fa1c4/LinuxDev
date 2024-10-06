#ifndef EVP_CLASS_H
#define EVP_CLASS_H

#include <iostream>
#include <iomanip>
#include <string>
#include <memory>
#include <string.h>
#include <sstream>
#include <openssl/ssl.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/err.h>

#define MAX_BUFFER_SIZE 1024


namespace LibOpenSSL {
    class AES_CBC_256 {
    public:
        AES_CBC_256();
        int encrypt(unsigned char* plaintext, unsigned char* ciphertext);
        int decrypt(unsigned char* plaintext, unsigned char* ciphertext, int ciphertext_len);
        void print_ciphertext(unsigned char* ciphertext, int ciphertext_len);

        ~AES_CBC_256();
    private:
        unsigned char* key;
        unsigned char* iv;
    };
};

#endif // EVP_CLASS_H

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
#include <openssl/x509.h>
#include <openssl/rsa.h>
#include <openssl/dsa.h>

#define MAX_BUFFER_SIZE 512

namespace LibOpenSSL {
    struct Message {
        size_t msg_len;
        unsigned char msg_body[MAX_BUFFER_SIZE];
        Message() {
            msg_len = 0;
            memset(msg_body, 0, MAX_BUFFER_SIZE);
        }
    };

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

    class mEVP_Key {
    public:
        mEVP_Key();

        EVP_PKEY* generate_rsa_key(unsigned int key_bits);
        EVP_PKEY* load_key(std::string key_file_type, std::string key_file);

        EVP_PKEY* get_pkey() { return pkey; }
        int get_pkey_size() { return EVP_PKEY_size(pkey); }
        int get_pkey_bits() { return EVP_PKEY_bits(pkey); }

        std::string get_keytype();
        void display_key(bool is_private=true);
        void write_key(std::string key_file, bool is_private=true);

        void print_hash(unsigned char* value, size_t length);

        int pkey_encrypt(unsigned char* pInText, unsigned char* pOutBytes);
        int pkey_decrypt(unsigned char* pOutText, unsigned char* pInBytes, size_t inBytes_len);

        ~mEVP_Key();
    
    private:
        EVP_PKEY* pkey;
    };
};

#endif // EVP_CLASS_H

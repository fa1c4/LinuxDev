#include "evp_class.h"

using namespace LibOpenSSL;


AES_CBC_256::AES_CBC_256() {
    key = (unsigned char*)"12345678901234567890123456789012"; // 256 bits key (32 bytes
    iv = (unsigned char*)"1234567890123456"; // 128 bits key (16 bytes
}

int AES_CBC_256::encrypt(unsigned char* plaintext, unsigned char* ciphertext) {
    int len;
    int plaintext_len = strlen((char*)plaintext);
    int ciphertext_len;
    int rc;

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    rc = EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);
    if (rc != ERR_LIB_NONE) {
        std::cout << "encrypt: EVP_DecryptInit_ex() error" << std::endl;
        return -1;
    }

    // padding before encryption
    // EVP_CIPHER_CTX_set_padding(ctx, 1);

    rc = EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len);
    if (rc != ERR_LIB_NONE) {
        std::cout << "encrypt: EVP_EncryptUpdate() error" << std::endl;
        return -2;
    }
    ciphertext_len = len;

    rc = EVP_EncryptFinal_ex(ctx, ciphertext, &len);
    if (rc != ERR_LIB_NONE) {
        std::cout << "encrypt: EVP_EncryptFinal_ex() error" << std::endl;
        return -3;
    }
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);
    return ciphertext_len;
}

int AES_CBC_256::decrypt(unsigned char* plaintext, unsigned char* ciphertext, int ciphertext_len) {
    int len, plaintext_len, rc;
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    
    rc = EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);
    if (rc != ERR_LIB_NONE) {
        std::cout << "decrypt: EVP_DecryptInit_ex() error" << std::endl;
        return -4;
    }

    // padding before decryption
    EVP_CIPHER_CTX_set_padding(ctx, 0);

    rc = EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len);
    if (rc != ERR_LIB_NONE) {
        std::cout << "decrypt: EVP_DecryptUpdate() error" << std::endl;
        return -5;
    }
    plaintext_len = len;

    rc = EVP_DecryptFinal_ex(ctx, plaintext, &len);
    if (rc != ERR_LIB_NONE) {
        std::cout << "decrypt: EVP_DecryptFinal_ex() error -> " << rc << std::endl;
        return -6;
    }
    plaintext_len += len;

    EVP_CIPHER_CTX_free(ctx);
    return plaintext_len;
}

void AES_CBC_256::print_ciphertext(unsigned char* ciphertext, int ciphertext_len) {
    printf("Ciphertext is:\n");
    BIO_dump_fp(stdout, (const char*)ciphertext, ciphertext_len);
}

AES_CBC_256::~AES_CBC_256() {}

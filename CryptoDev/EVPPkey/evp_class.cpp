#include "evp_class.h"

using namespace LibOpenSSL;

AES_CBC_256::AES_CBC_256() {
    key = (unsigned char*)"12345678901234567890123456789012"; // 32 bytes
    iv = (unsigned char*)"1234567890123456"; // 16 bytes
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

    rc = EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len);
    if (rc != ERR_LIB_NONE) {
        std::cout << "encrypt: EVP_EncryptUpdate() error" << std::endl;
        return -1;
    }
    ciphertext_len = len;

    rc = EVP_EncryptFinal_ex(ctx, ciphertext + len, &len);
    if (rc != ERR_LIB_NONE) {
        std::cout << "encrypt: EVP_EncryptFinal_ex() error" << std::endl;
        return -1;
    }
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);
    return ciphertext_len;
}

int AES_CBC_256::decrypt(unsigned char* plaintext, unsigned char* ciphertext, int ciphertext_len) {
    int len;
    int plaintext_len;
    int rc;

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    rc = EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);
    if (rc != ERR_LIB_NONE) {
        std::cout << "decrypt: EVP_DecryptInit_ex() error" << std::endl;
        return -1;
    }

    rc = EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len);
    if (rc != ERR_LIB_NONE) {
        std::cout << "decrypt: EVP_DecryptUpdate() error" << std::endl;
        return -1;
    }
    plaintext_len = len;

    rc = EVP_DecryptFinal_ex(ctx, plaintext + len, &len);
    if (rc != ERR_LIB_NONE) {
        std::cout << "decrypt: EVP_DecryptFinal_ex() error" << std::endl;
        return -1;
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

mEVP_Key::mEVP_Key(): pkey(nullptr) {}

EVP_PKEY* mEVP_Key::generate_rsa_key(unsigned int key_bits) {
    EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, NULL);
    EVP_PKEY_keygen_init(ctx);
    EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, key_bits);
    EVP_PKEY_keygen(ctx, &pkey);
    EVP_PKEY_CTX_free(ctx);

    return pkey;
}

EVP_PKEY* mEVP_Key::load_key(std::string key_file_type, std::string key_file) {
    BIO* bio_key = NULL;
    bio_key = BIO_new_file(key_file.c_str(), "r");

    if (key_file_type == "public") {
        pkey = PEM_read_bio_PUBKEY(bio_key, NULL, NULL, NULL);
    }

    if (key_file_type == "private") {
        pkey = PEM_read_bio_PrivateKey(bio_key, NULL, NULL, NULL);
    }

    if (pkey == nullptr) {
        std::cout << "Error: failed to load key from" << key_file << std::endl;
    }

    BIO_free(bio_key);

    return pkey;
}

std::string mEVP_Key::get_keytype() {
    std::string key_type_str;
    int type_id;

    type_id = EVP_PKEY_base_id(pkey);
    switch(EVP_PKEY_type(type_id)) {
        case EVP_PKEY_RSA:
            key_type_str = "EVP_PKEY_RSA";
            break;
        case EVP_PKEY_DSA:
            key_type_str = "EVP_PKEY_DSA";
            break;
        case EVP_PKEY_EC:
            key_type_str = "EVP_PKEY_EC";
            break;
        case EVP_PKEY_HMAC:
            key_type_str = "EVP_PKEY_HMAC";
            break;
        default:
            key_type_str = "EVP_PKEY_NONE";
            break;
    }

    return key_type_str;
}

void mEVP_Key::display_key(bool is_private) {
    BIO* bio_out = BIO_new_fp(stdout, BIO_NOCLOSE);
    if (is_private) EVP_PKEY_print_private(bio_out, pkey, 0, NULL);
    else EVP_PKEY_print_public(bio_out, pkey, 0, NULL);
    BIO_free(bio_out);
}

void mEVP_Key::print_hash(unsigned char* value, size_t length) {
    printf("Hash Value: (%d)", (int)length);
    for (size_t i = 0; i < length; ++i) {
        printf("%02x:", value[i]);
    }
    printf("\n");
}

void mEVP_Key::write_key(std::string key_file, bool is_private) {
    BIO* bio_out = BIO_new_file(key_file.c_str(), "w");
    if (is_private) PEM_write_bio_PrivateKey(bio_out, pkey, NULL, NULL, 0, 0, NULL);
    else PEM_write_bio_PUBKEY(bio_out, pkey);
    BIO_free(bio_out);
}

mEVP_Key::~mEVP_Key() {
    if (pkey != nullptr) 
        EVP_PKEY_free(pkey);
}

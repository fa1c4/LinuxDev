#include <iostream>
#include <stdio.h>
#include <string.h>

#include <openssl/bio.h>
#include <openssl/evp.h>


int main(int argc, char* argv[]) {
    EVP_MD_CTX* mdctx;
    const EVP_MD* md;
    int inByte = 0;
    BIO* bio_in = NULL;
    BIO* bio_hash = NULL;

    unsigned char md_value[EVP_MAX_MD_SIZE];
    unsigned char plaintext[EVP_MAX_MD_SIZE];
    unsigned char hash_buffer[EVP_MAX_MD_SIZE];
    unsigned int md_len;

    memset(md_value, 0, EVP_MAX_MD_SIZE);
    memset(plaintext, 0, EVP_MAX_MD_SIZE);
    memset(hash_buffer, 0, EVP_MAX_MD_SIZE);

    if (argc != 4) {
        printf("Usage: %s <algorithm> <InFile> <OutHashFile>\n", argv[0]);
        printf("Example: %s SHA256 test.txt test_hash.dat\n", argv[0]);
        printf("Supported Digest Algorithm:\n");
        printf("    SHA, SHA1, SHA224, SHA256, SHA384, SHA512\n");
        printf("    MD2, MD4, MDC2, MD5\n");
        exit(1);
    }

    bio_in = BIO_new_file(argv[2], "r");
    bio_hash = BIO_new_file(argv[3], "rb");

    md = EVP_get_digestbyname(argv[1]);
    if (md == NULL) {
        printf("Unknown message digest %s\n", argv[1]);
        exit(1);
    }

    mdctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(mdctx, md, NULL);

    while ((inByte = BIO_read(bio_in, plaintext, EVP_MAX_MD_SIZE)) > 0) {
        EVP_DigestUpdate(mdctx, plaintext, inByte);
    }

    EVP_DigestFinal_ex(mdctx, md_value, &md_len);
    EVP_MD_CTX_free(mdctx);

    inByte = BIO_read(bio_hash, hash_buffer, EVP_MAX_MD_SIZE);
    if (inByte > 0 && inByte == (int)md_len && memcmp(md_value, hash_buffer, md_len) == 0) {
        std::cout << "Verify OK" << std::endl;
    } else {
        std::cout << "Verify Fail" << std::endl;
    }

    BIO_free(bio_in);
    BIO_free(bio_hash);

    exit(0);
}

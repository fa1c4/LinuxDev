#include <iostream>
#include <stdio.h>
#include <string.h>

#include <openssl/bio.h>
#include <openssl/evp.h>


int main(int argc, char* argv[]) {
    EVP_MD_CTX* mdctx;
    const EVP_MD* md;

    unsigned char md_value[EVP_MAX_MD_SIZE];
    unsigned char plaintext[EVP_MAX_MD_SIZE];
    unsigned int md_len;

    memset(md_value, 0, EVP_MAX_MD_SIZE);
    memset(plaintext, 0, EVP_MAX_MD_SIZE);

    if (argc != 3) {
        printf("Usage: %s <algorithm> <message>\n", argv[0]);
        printf("Example: %s SHA256 \"test string\"\n", argv[0]);
        printf("Supported Digest Algorithm:\n");
        printf("    SHA, SHA1, SHA224, SHA256, SHA384, SHA512\n");
        printf("    MD2, MD4, MDC2, MD5\n");
        exit(1);
    }

    md = EVP_get_digestbyname(argv[1]);
    if (md == NULL) {
        printf("Unknown message digest %s\n", argv[1]);
        exit(1);
    }

    int text_len = strlen(argv[2]);
    memcpy(plaintext, argv[2], strlen(argv[2]));

    mdctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(mdctx, md, NULL);
    EVP_DigestUpdate(mdctx, plaintext, text_len);
    EVP_DigestFinal_ex(mdctx, md_value, &md_len);
    EVP_MD_CTX_free(mdctx);

    BIO_dump_fp(stdout, (const char*)md_value, md_len);
    std::cout << "length of " << argv[1] << " is: " << md_len << " Bytes\n";
    exit(0);
}

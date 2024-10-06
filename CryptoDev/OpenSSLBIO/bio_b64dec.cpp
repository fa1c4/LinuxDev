// openssl enc -d -base64 -in test_b64enc.txt -out test_openssl_b64dec.txt

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <openssl/ssl.h>
#include <openssl/bio.h>

#define MAX_BUFFER_SIZE 1024


int main(int argc, char* argv[]) {
    BIO* bio_out = NULL;
    BIO* bio_in = NULL;
    BIO* bio_b64 = NULL;
    int inBytes = 0, outBytes = 0;
    char buffer[MAX_BUFFER_SIZE];
    memset(buffer, 0, MAX_BUFFER_SIZE);

    if (argc != 3) {
        std::cout << "Usage: bio_b64_dec.elf <encoded-file> <decoded-file>" << std::endl;
        return -1;
    }

    bio_in = BIO_new_file(argv[1], "rb");
    bio_out = BIO_new_file(argv[2], "w");
    bio_b64 = BIO_new(BIO_f_base64());
    BIO_push(bio_b64, bio_in);

    while ((inBytes = BIO_read(bio_b64, buffer, MAX_BUFFER_SIZE)) > 0) {
        outBytes = BIO_write(bio_out, buffer, inBytes);
        if (inBytes != outBytes) {
            std::cout << "In Bytes: " << inBytes << " Out Bytes: " << outBytes << std::endl;
            break;
        }
    }

    BIO_free(bio_out);
    BIO_free_all(bio_b64);
    return 0;    
}

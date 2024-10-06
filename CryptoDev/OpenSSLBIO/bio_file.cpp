#include <iostream>
#include <string.h>
#include <stdio.h>
#include <openssl/ssl.h>
#include <openssl/bio.h>

#define MAX_BUFFER_SIZE 1024


int main(int argc, char* argv[]) {
    BIO* bio_out = NULL;
    BIO* bio_in = NULL;
    int inBytes = 0, outBytes = 0;
    char buffer[MAX_BUFFER_SIZE];
    memset(buffer, 0, MAX_BUFFER_SIZE);

    if (argc != 3) {
        std::cout << "Usage: bio_file.elf <file-read> <file_write>" << std::endl;
        return -1;
    }

    bio_in = BIO_new_file(argv[1], "r");
    bio_out = BIO_new_file(argv[2], "w");
    while ((inBytes = BIO_read(bio_in, buffer, MAX_BUFFER_SIZE)) > 0) {
        outBytes = BIO_write(bio_out, buffer, inBytes);
        if (inBytes != outBytes) {
            std::cout << "In Bytes: " << inBytes << " Out Bytes: " << outBytes << std::endl;
            break;
        }
    }

    return 0;
}

#include "evp_class.h"


int main(int argc, char* argv[]) {
    EVP_PKEY* mPKey = NULL;
    unsigned int mKeyBits;

    if (argc != 4) {
        fprintf(stdout, "Usage: %s <bits> <private key_file> <public key_file>\n", argv[0]);
        fprintf(stdout, "Example: %s 2048 rsa_private_key.pem rsa_public_key.pem\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    mKeyBits = (unsigned int)atoi(argv[1]);
    LibOpenSSL::mEVP_Key keyObj;
    mPKey = keyObj.generate_rsa_key(mKeyBits);
    if (mPKey == NULL) {
        std::cout << "generate RSA Key error" << std::endl;
        exit(EXIT_FAILURE);
    }

    keyObj.write_key(argv[2], true); // private_key
    keyObj.write_key(argv[3], false); // public_key

    return 0;
}

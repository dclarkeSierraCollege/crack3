#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
#include "md5.h"

void md5String(const char *input, char *output) {
    unsigned char digest[EVP_MAX_MD_SIZE];
    unsigned int length;
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(ctx, EVP_md5(), NULL);
    EVP_DigestUpdate(ctx, input, strlen(input));
    EVP_DigestFinal_ex(ctx, digest, &length);
    EVP_MD_CTX_free(ctx);

    for (unsigned int i = 0; i < length; i++) {
        sprintf(output + (i * 2), "%02x", digest[i]);
    }
}

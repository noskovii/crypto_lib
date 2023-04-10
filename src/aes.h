#ifndef _AES_H_
#define _AES_H_

#include <openssl/aes.h>
#include <openssl/evp.h>

#include "base64.h"

#define CALC_SIZE(LENGTH) (LENGTH / 16 + 1) * 16

char* aes_encrypt(char*, unsigned char*);
char* aes_decrypt(char*, unsigned char*);

#endif /* _AES_H_ */

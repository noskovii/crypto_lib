#ifndef _CRYPTO_H_
#define _CRYPTO_H_

#include "aes.h"

/* Максимальный размер ключа - 256 бит */
#define PASSWD_LENGTH 32
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

char* result_value;

int get_key_from_file(const char*, unsigned char*, size_t);

char* encrypt(char*);
char* decrypt(char*);

char* encrypt_with_passwd(char*, unsigned char*);
char* decrypt_with_passwd(char*, unsigned char*);

void free_result_value();

#endif /* _CRYPTO_H_ */

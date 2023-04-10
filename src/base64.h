#ifndef _BASE64_H_
#define _BASE64_H_

#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#define PAD_SYMB '='

char* build_decoding_table();

char* base64_encode(const unsigned char*, size_t, size_t*);
unsigned char* base64_decode(const char*, size_t, size_t*);

#endif /* _BASE64_H_ */

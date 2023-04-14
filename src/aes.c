#include "aes.h"


char* aes_encrypt(char* text, unsigned char* passwd)
{
    unsigned char iv[AES_BLOCK_SIZE];
    memset(iv, 0x00, AES_BLOCK_SIZE);

    int enc_text_size = CALC_SIZE(strlen(text));

    char* encrypted_text = (char*)calloc(sizeof(char), enc_text_size);

    AES_KEY enc_key;
    AES_set_encrypt_key(passwd, 256, &enc_key);

    AES_cbc_encrypt(text, encrypted_text, enc_text_size, &enc_key, iv, AES_ENCRYPT);

    size_t size;
    char* encoded_text = base64_encode(encrypted_text, enc_text_size, &size);
    encoded_text[size - 1] = '\0';

    free(encrypted_text);

    return encoded_text;
}

char* aes_decrypt(char* text, unsigned char* passwd)
{
    unsigned char iv[AES_BLOCK_SIZE];
    memset(iv, 0x00, AES_BLOCK_SIZE);

    unsigned char* decoded_text;
    size_t size;
    decoded_text = base64_decode(text, strlen(text), &size);

    if (!decoded_text) return NULL;

    char* decrypted_text = (char*)calloc(sizeof(char), size);

    AES_KEY dec_key;
    AES_set_decrypt_key(passwd, 256, &dec_key);

    AES_cbc_encrypt(decoded_text, decrypted_text, strlen(decoded_text), &dec_key, iv, AES_DECRYPT);

    free(decoded_text);

    return decrypted_text;
}

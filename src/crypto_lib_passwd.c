#include "crypto_lib_passwd.h"

const char* MASTER_PASSWD_PATH = "/etc/master_passwd";


int get_key_from_file(const char* passwd_path, unsigned char* key_buf, size_t buf_size)
{
  FILE* file = fopen(passwd_path, "r");

  if (file) {
    size_t size = fread(key_buf, sizeof(char), buf_size, file);

    if (!size) return 1;

    if (size != buf_size && feof(file) && key_buf[size - 1] == '\n') {
      key_buf[size - 1] = 0;
    }

    fclose(file);
    return 0;
  }

  return 1;
}

char* encrypt(char* text)
{
  unsigned char key[PASSWD_LENGTH] = {};

  if (get_key_from_file(MASTER_PASSWD_PATH, key, sizeof(key))) {
    result_value = strdup(text);
    return result_value;
  }

  result_value = aes_encrypt(text, key);
  return result_value;
}

char* decrypt(char* text)
{
  unsigned char key[PASSWD_LENGTH] = {};

  if (get_key_from_file(MASTER_PASSWD_PATH, key, sizeof(key))) {
    result_value = strdup(text);
    return result_value;
  }

  result_value = aes_decrypt(text, key);
  return result_value;
}

char* encrypt_with_passwd(char* text, unsigned char* passwd)
{
  unsigned char key[PASSWD_LENGTH] = {};
  memcpy(key, passwd, MIN(PASSWD_LENGTH, strlen((char*)passwd)));

  result_value = aes_encrypt(text, key);
  return result_value;
}

char* decrypt_with_passwd(char* text, unsigned char* passwd)
{
  unsigned char key[PASSWD_LENGTH] = {};
  memcpy(key, passwd, MIN(PASSWD_LENGTH, strlen((char*)passwd)));

  result_value = aes_decrypt(text, key);
  return result_value;
}

void free_result_value()
{
  if (result_value) free(result_value);
}

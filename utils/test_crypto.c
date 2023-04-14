#include "../src/crypto_lib_passwd.h"


int main()
{
    int i;
    int num = 1000;
    char* txt = "1234567890";

    for (i = 0; i < num; i++) {
        printf("txt = %s\n", txt);

        char* enc_txt = encrypt(txt);
        printf("enc = %s\n", enc_txt);

        char* dec_txt = decrypt(enc_txt);
        printf("dec = %s\n\n", dec_txt);

        if(strcmp(dec_txt, txt)) {
            printf("NOT EQUAL!\n");
            return 1;
        }
    }

    for (i = 0; i < num; i++) {
        char* passwd = "qwerty";
        printf("txt = %s\n", txt);

        char* enc_txt = encrypt_with_passwd(txt, passwd);
        printf("enc = %s\n", enc_txt);

        char* dec_txt = decrypt_with_passwd(enc_txt, passwd);
        printf("dec = %s\n\n", dec_txt);

        if(strcmp(dec_txt, txt)) {
            printf("NOT EQUAL!\n");
            return 1;
        }
    }

    return 0;
}

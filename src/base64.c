#include "base64.h"


static char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                                'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                'w', 'x', 'y', 'z', '0', '1', '2', '3',
                                '4', '5', '6', '7', '8', '9', '+', '/'};

static int mod_table[] = {0, 2, 1};

char* build_decoding_table()
{
    char* decoding_table = (char*)calloc(sizeof(char), 256);

    int i;
    for (i = 0; i < 64; i++) {
        decoding_table[(unsigned char)encoding_table[i]] = i;
    }

    return decoding_table;
}

char* base64_encode(const unsigned char* data,
                    size_t input_length,
                    size_t* output_length)
{
    *output_length = 4 * ((input_length + 2) / 3) + 1;

    char* encoded_data = (char*)calloc(sizeof(char), *output_length);

    if (encoded_data == NULL) return NULL;

    int i, j;
    for (i = 0, j = 0; i < input_length;) {
        uint32_t octet_a = i < input_length ? (unsigned char)data[i++] : 0;
        uint32_t octet_b = i < input_length ? (unsigned char)data[i++] : 0;
        uint32_t octet_c = i < input_length ? (unsigned char)data[i++] : 0;

        uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

        encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
    }

    for (i = 0; i < mod_table[input_length % 3]; i++) {
        encoded_data[*output_length - 1 - i] = PAD_SYMB;
    }

    return encoded_data;
}

unsigned char* base64_decode(const char* data,
                             size_t input_length,
                             size_t* output_length)
{
    char* decoding_table = build_decoding_table();

    if (input_length % 4 != 0) return NULL;

    *output_length = input_length / 4 * 3;

    if (data[input_length - 1] == PAD_SYMB) (*output_length)--;
    if (data[input_length - 2] == PAD_SYMB) (*output_length)--;

    unsigned char* decoded_data = (unsigned char*)calloc(sizeof(unsigned char), *output_length);

    if (decoded_data == NULL) return NULL;

    int i, j;
    for (i = 0, j = 0; i < input_length;) {
        uint32_t sextet_a = data[i] == PAD_SYMB ? 0 & i++ : decoding_table[data[i++]];
        uint32_t sextet_b = data[i] == PAD_SYMB ? 0 & i++ : decoding_table[data[i++]];
        uint32_t sextet_c = data[i] == PAD_SYMB ? 0 & i++ : decoding_table[data[i++]];
        uint32_t sextet_d = data[i] == PAD_SYMB ? 0 & i++ : decoding_table[data[i++]];

        uint32_t triple = (sextet_a << 3 * 6)
                          + (sextet_b << 2 * 6)
                          + (sextet_c << 1 * 6)
                          + (sextet_d << 0 * 6);

        if (j < *output_length) decoded_data[j++] = (triple >> 2 * 8) & 0xFF;
        if (j < *output_length) decoded_data[j++] = (triple >> 1 * 8) & 0xFF;
        if (j < *output_length) decoded_data[j++] = (triple >> 0 * 8) & 0xFF;
    }

    free(decoding_table);

    return decoded_data;
}

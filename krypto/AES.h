#ifndef AES_H
#define AES_H

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define AES_MAX_TEXTLENGTH 10000

//~ void AES_get_key_and_text(char *input_key, char *input_text, int encrypt);
char *AES_encrypt(const char *input_key, const char *input_text, const int N, char *cipher);
char *AES_decrypt(const char *input_key, const char *input_text, const int N, char *klartext);
int AES_test();

#endif // AES_H

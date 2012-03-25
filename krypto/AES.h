#ifndef AES_H
#define AES_H

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//static void makeColumn(int state[4][4], char inv);

void AES_get_key_and_text(char *input_key, char *input_text, int encrypt);
char *AES_encrypt(char *input_key, char *input_text, char *cipher);
char *AES_decrypt(char *input_key, char *input_text, char *klartext);
void AES_test();

#endif // AES_H

#ifndef AES_H
#define AES_H

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//static void makeColumn(int state[4][4], char inv);

//void AES_encrypt();
//void AES_decrypt();
void AES_encrypt(char *input_key, char *input_text);
void AES_encrypt_start(char *input_key, char *input_text);
//~ void AES_decrypt(std::string input_key, std::string input_text);

#endif // AES_H

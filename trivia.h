#ifndef TRIVIA_H
#define TRIVIA_H

#include "main.h"

//4.13
int aufsummieren(int n);
//4.17
void summe_g_ug(int n, int *sum_g, int *sum_ug);
//5.3
void schreibe_zeichen(char c,int n);
//5.4
double wurzel4(int k);
//5.8
int f(int x,int a,int b,int c);
//6.2
float invers(float zahl);
//6.8
void d2b(short v,int n);
int zyklischer_shift(short a,int n);
//6.9
int spiegel(short a);
//6.12
int max4(int x,int y,int z,int w);
int max2(int x,int y);
int min2(int x,int y);
//6.17
short datum_packer(int tag,int monat,int jahr);
void datum_entpacker(short gepackt, int *tag, int *monat, int *jahr);
//7.15
int ist_palindrom(char *string, size_t laenge);


#endif //TRIVIA_H

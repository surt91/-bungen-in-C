#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "main.h"

//4.13
int aufsummieren(int n);
//4.17
void summe_g_ug(int n, int *sum_g, int *sum_ug);
//5.2
int power(int x,int n);
//5.3
void schreibe_zeichen(char c,int n);
//5.4
double wurzel4(int k);
//5.8
int f(int x,int a,int b,int c);
//5.12
int fibonacci(int n);
int ist_prim(int test);
//5.14
void primfaktoren(int zahl);
//5.18
void muenzwurf(int wuerfe, int *kopf, int *zahl);
//5.19
int monteCarloGeburtstagsProblem(int k);
//6.2
float invers(float zahl);
//6.8
void d2b(short v,int n);
int zyklischer_shift(short a,int n);
//6.9
int spiegel(short a);
//6.12
int max(int x,int y,int z,int w);
//6.16
int roulette();
int roulette_gewinn_faktor(int k,int kugel);
//6.17
short datum_packer(int tag,int monat,int jahr);
void datum_entpacker(short gepackt, int *tag, int *monat, int *jahr);
//6.23
struct card
    {
        enum farbe {herz = 1, pik, karo, kreuz} f;
        enum wert {ass = 1, zwei, drei, vier, funf, sechs, sieben, acht, neun, zehn, bube, dame, konig} w;
    };
struct card *karten_geber(struct card *hand);
void karten_zeiger(struct card *hand);
//6.24
int is_fullhouse(struct card *hand);
int is_flush(struct card *hand);
int is_street(struct card *hand);
struct card *karten_sortierer(struct card *hand);
//int comp_cards(int *p, int *q);

#endif //FUNCTIONS_H

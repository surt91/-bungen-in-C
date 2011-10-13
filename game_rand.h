#ifndef GAME_RAND_H
#define GAME_RAND_H

#include "main.h"

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
int is_straight(struct card *hand);
struct card *karten_sortierer(struct card *hand); //auch 7.11
//5.18
void muenzwurf(int wuerfe, int *kopf, int *zahl);
//5.19
int monteCarloGeburtstagsProblem(int k);
//7.12
double pi(int versuche);
double pi_benchmark();

#endif //GAME_RAND_H

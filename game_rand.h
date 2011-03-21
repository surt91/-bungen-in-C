#ifndef GAME_RAND_H
#define GAME_RAND_H

#include "main.h"

#define GERADE 37
#define UNGERADE 38
#define ROT 39
#define SCHWARZ 40
#define NIEDRIG 41
#define HOCH 42
#define RHSS "roulette_highscore_save.dat"
#define NUMHS 10

//6.16
int roulette_menu(int *liste, int runde, int besitz);
int roulette_gewinn(int *liste, int kugel);
void roulette_setzen(int *besitz, int *liste, int k);
int roulette_drehen(int *liste, int *besitz);
int roulette_save(int runde, int geld, int max_geld, char *filename);
int roulette_load(int *runde, int *geld, int *max_geld, char *filename);
void roulette_zeige_highscore(int max_geld, int max_runde);
int roulette_load_highscore();
void roulette_save_highscore(int max_geld, int max_runde, char *name);
void roulette_highscore_sort();
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

#endif //GAME_RAND_H

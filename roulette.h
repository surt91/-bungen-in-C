#ifndef ROULETTE_H
#define ROULETTE_H

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
void roulette_start();
int roulette_menu(int *liste, int runde, int besitz);
int roulette_gewinn(int *liste, int kugel);
void roulette_setzen(int *besitz, int *liste, int k);
int roulette_drehen(int *liste, int *besitz);
int roulette_save(int runde, int geld, int max_geld, char *filename);
int roulette_load(int *runde, int *geld, int *max_geld, char *filename);
void roulette_zeige_highscore(int max_geld, int max_runde);
int roulette_load_highscore();
int roulette_save_highscore(int max_geld, int max_runde, char *name);
void roulette_highscore_sort();

#endif //ROULETTE_H

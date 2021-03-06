#ifndef ROULETTE_H
#define ROULETTE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <ncurses.h>
#include <locale.h>

#include "highscore.h"

#define GERADE 37
#define UNGERADE 38
#define ROT 39
#define SCHWARZ 40
#define NIEDRIG 41
#define HOCH 42
#define ROULETTE_HIGHSCORE_FILENAME "roulette_highscore_save.dat"
#define ROULETTE_RIGHT 25

//6.16
void roulette_start();
char roulette_menu(int *liste, int runde, int besitz);
int roulette_gewinn(int *liste, int kugel);
void roulette_setzen(int *besitz, int *liste, int k);
int roulette_drehen(int *liste, int *besitz);
int roulette_save(int runde, int geld, int max_geld, char *filename);
int roulette_load(int *runde, int *geld, int *max_geld, char *filename);

#endif //ROULETTE_H

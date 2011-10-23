#ifndef POKER_H
#define POKER_H

#include <stdio.h>

#include "karten.h"
#include "blackjack.h"
#include "../highscore.h"

#define POKER_HIGHSCORE_FILENAME "poker_highscore_save.dat"

void poker_start();

int is_pair(struct deck *hand);
int is_fullhouse(struct deck *hand);
int is_flush(struct deck *hand);
int is_straight(struct deck *hand);
int is_straight_flush(struct deck *hand);
int is_royal_flush(struct deck *hand);
int poker_gewinn(struct deck *hand, int einsatz);

void poker_monte_carlo(int anzahl, int leute, int **ergebnis);
void poker_monte_carlo_darstellen(int *u, int spieler);

#endif //POKER_H

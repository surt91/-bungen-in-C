#ifndef POKER_H
#define POKER_H

#include <stdio.h>

#include "karten.h"

int is_fullhouse(struct deck *hand);
int is_flush(struct deck *hand);
int is_straight(struct deck *hand);
int is_straight_flush(struct deck *hand);
int is_royal_flush(struct deck *hand);

void poker_monte_carlo(int anzahl, int leute, int **ergebnis);
void poker_monte_carlo_darstellen(int *u);

#endif //POKER_H

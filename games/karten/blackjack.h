#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <stdio.h>
#include <stdlib.h>

#include <ncurses.h>
#include <locale.h>

#include "karten.h"

#define BJ_TOP 5
#define BJ_RIGHT 15

int bj_summiere_augen(struct deck *hand);
//~ int bj_summiere_augen();

void bj_test();

#endif //BLACKJACK_H

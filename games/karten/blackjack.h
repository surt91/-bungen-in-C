#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <stdio.h>
#include <stdlib.h>

#include <ncurses.h>
#include <locale.h>

#include "../highscore.h"
#include "karten.h"

#define BJ_TOP 8
#define BJ_BOT 17
#define BJ_RIGHT 15
#define BLACKJACK_HIGHSCORE_FILENAME "blackjack_highscore_save.dat"

#define BJ_HIT 1
#define BJ_START 1
#define BJ_BLACKJACK 3
#define BJ_STAY 2
#define BJ_BUST 0
#define BJ_BANK_BUST 4
#define BJ_WIN 5
#define BJ_LOST 6
#define BJ_REMIS 7

int bj_summiere_augen(struct deck *hand);
void bj_zeige_hande(struct deck *spieler, struct deck *bank);
int bj_gewinn(int status, int einsatz);

void blackjack_start();

#endif //BLACKJACK_H

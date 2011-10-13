#ifndef KARTEN_H
#define KARTEN_H

#include "main.h"

struct card
{
    enum farbe {herz = 1, pik, karo, kreuz} f;
    enum wert {ass = 1, zwei, drei, vier, funf, sechs, sieben, acht, neun, zehn, bube, dame, konig} w;
};

struct deck
{
    struct card karte;
    struct deck *next;
};

void karten_zeiger(struct card *hand);

void karten_init_deck(struct deck *stapel);
void karten_delete_card_from_deck(struct deck **stapel);

void karten_test();

#endif //KARTEN_H

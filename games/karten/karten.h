#ifndef KARTEN_H
#define KARTEN_H

#include <stdio.h>
#include <stdlib.h>

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

void karten_zeiger(struct card hand);

void karten_init_deck(struct deck *stapel, int anz);
void karten_gebe_karte(struct deck **stapel, struct deck **hand);
struct card karten_pop(struct deck **stapel);
void karten_show(struct deck *stapel);
void karten_vertausche_zwei_karten(struct deck **stapel, int eins, int zwei);
struct card *karten_sortierer(struct card *hand);

//~ void karten_test();

#endif //KARTEN_H

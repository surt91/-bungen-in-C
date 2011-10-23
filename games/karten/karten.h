#ifndef KARTEN_H
#define KARTEN_H

#include <stdio.h>
#include <stdlib.h>

#include <ncurses.h>
#include <locale.h>

struct card
{
    enum farbe {herz = 0, pik, karo, kreuz} f;
    enum wert {zwei = 0, drei, vier, funf, sechs, sieben, acht, neun, zehn, bube, dame, konig, ass} w;
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
//~ struct card *karten_sortierer(struct card *hand);
int karten_counter(struct deck *stapel);
void karten_sortierer(struct deck **hand);
void karten_delete_stapel(struct deck **stapel);

struct card karten_get_card_by_index(struct deck *stapel, int idx);

//~ void karten_test();

#endif //KARTEN_H

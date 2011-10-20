#ifndef POKER_H
#define POKER_H

#include <stdio.h>

#include "karten.h"

int is_fullhouse(struct card *hand);
int is_flush(struct card *hand);
int is_straight(struct card *hand);

#endif //POKER_H

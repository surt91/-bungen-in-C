#ifndef SNAKE_H
#define SNAKE_H

#include "main.h"
//~ #include <time.h>

struct snake_map
{
    int x,y;
    int length;
    int *schlange;
    int kopf[2];
    int futter[2];
};

void snake();
int snake_dead_or_eating(snake_map map);
#endif //SNAKE_H

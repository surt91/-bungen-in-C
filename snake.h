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
void snake_draw(struct snake_map map);
int snake_set_status(int x, int y, struct snake_map map, char state);
int snake_get_status(int x, int y, struct snake_map map);
void snake_random_pos(int *pos, struct snake_map map);
struct snake_map snake_koerper(struct snake_map map);
int snake_dead_or_eating(struct snake_map map);
#endif //SNAKE_H

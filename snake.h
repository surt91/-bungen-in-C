#ifndef SNAKE_H
#define SNAKE_H

#include "main.h"
#include <unistd.h>
#include <termios.h>
//~ #include <time.h>

#define LEVEL1 1000000
#define LEVEL2 700000
#define LEVEL3 500000
#define LEVEL4 100000
#define LEVEL5 50000
#define LEVEL6 20000
#define LEVEL7 10000
#define LEVEL8 5000
#define LEVEL9 1000

struct snake_map
{
    int x,y;
    int length;
    int *schlange;
    int kopf[2];
    int futter[2];
};

void snake(int schwierigkeit, int torus);
void snake_draw(struct snake_map map);
int snake_set_status(int x, int y, struct snake_map map, char state);
int snake_get_status(int x, int y, struct snake_map map);
void snake_random_pos(int *pos, struct snake_map map);
struct snake_map snake_koerper(struct snake_map map);
int snake_dead_or_eating(struct snake_map map);
int snake_rand(struct snake_map map);
void snake_verloren(int punkte);

int getch();
int kbhit();
#endif //SNAKE_H

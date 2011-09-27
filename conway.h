#ifndef CONWAY_H
#define CONWAY_H

#include "main.h"
#include <cairo/cairo.h>

struct conway_map
{
    short *status;
    int x;
    int y;
};

struct conway_pos
{
    int x;
    int y;
};

void conway_gleiter();
void conway_random();
void conway_HWSS();
int conway_draw(struct conway_map map, int gen);
int conway_paint(struct conway_map map, int gen);
int conway_update_status(struct conway_map map, struct conway_pos pos);
void conway_main(struct conway_map map);
int conway_dead_or_alive(int counter, int state);

//~ static const conway_map conway_glider;
//~ conway_glider.x = conway_glider.y = 10;
//~ conway_glider.status = (short *) calloc(matrix_out.zeilen * matrix_out.spalten, sizeof(short));


#endif //CONWAY_H

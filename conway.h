#ifndef CONWAY_H
#define CONWAY_H

#include "main.h"
#include <cairo/cairo.h>

struct conway_map
{
    char *status;
    int x;
    int y;
    int gen;
};

void conway_gleiter();
void conway_random();
void conway_HWSS();
void conway_pulsator();
void conway_stabil();
int conway_draw(struct conway_map map, int gen);
int conway_paint(struct conway_map map, int gen);
char conway_update_status(int x, int y, struct conway_map map);
void conway_main(struct conway_map map);
char conway_dead_or_alive(int counter, int state);
int conway_set_status(int x, int y, struct conway_map map, char state);
int conway_get_status(int x, int y, struct conway_map map);
struct conway_map conway_init_map(struct conway_map map);

#endif //CONWAY_H

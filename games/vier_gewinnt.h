#ifndef VIER_GEWINNT_H
#define VIER_GEWINNT_H

#include <stdio.h>
#include <stdlib.h>

#include <ncurses.h>

#define VG_LEER  0
#define VG_KREIS 1
#define VG_KREUZ 2

#define VG_X 7
#define VG_Y 6

struct vg_feld
{
    int status[VG_X][VG_Y];
    int runde;
};

void vier_gewinnt_start();
void vg_draw(struct vg_feld *map);
int vg_steuern(struct vg_feld *map, char sym);
void vg_setzen(struct vg_feld *map, int x, int spieler);
int vg_prufe_gewinn(struct vg_feld *map);
int vg_vier(struct vg_feld *map, int x, int y);

#endif //VIER_GEWINNT_H

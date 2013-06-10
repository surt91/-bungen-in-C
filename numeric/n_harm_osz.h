#ifndef N_HARM_OSZ_H
#define N_HARM_OSZ_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cairo/cairo.h>

typedef struct n_body_zustand
{
    double *x;
    double *y;
    double *z;
    double *vx;
    double *vy;
    double *vz;
    int N;
    int t;
} r_type;

void n_harm_osz_main();

#endif //N_HARM_OSZ_H

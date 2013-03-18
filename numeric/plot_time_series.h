#ifndef PLOT_TIME_SERIES_H
#define PLOT_TIME_SERIES_H

#include <stdlib.h>
#include <stdio.h>
#include <cairo/cairo.h>
#include "runge_kutta.h"

void rk4a_paint(double *zt_seq, int dim, int freq);
double * rk4a_interpolate(double *zt_seq, int dim, int freq);

int plot_time_series_paint_frame(double *x, double *y, double t, int n, int x_max, int y_max);

#endif //PLOT_TIME_SERIES_H

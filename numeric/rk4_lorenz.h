#ifndef RK4_LORENZ_H
#define RK4_LORENZ_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../error.h"
#include "plot_time_series.h"
#include "runge_kutta.h"

void rk_lorenz_func(double *r, double t, int dim, double *out);
void runge_kutta_lorenz();
void runge_kutta_lorenz_adaptiv();
void runge_kutta_lorenz_ensemble_adaptiv();

double runge_kutta_benchmark(double tau, double T);

#endif //RK4_LORENZ_H

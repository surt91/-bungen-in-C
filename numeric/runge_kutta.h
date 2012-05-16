#ifndef RUNGE_KUTTA_H
#define RUNGE_KUTTA_H

#include <stdio.h>
#include <stdlib.h>

double * rk4_step(double *z, double t, double tau, double * (*dgl)(), int dim);
double * H(double *z, double t, int dim);

double * rk_lorenz_func(double *r, double t, int dim);
double * rk_test_func(double *r, double t, int dim);

void runge_kutta_lorenz();
void runge_kutta_test();
double runge_kutta_benchmark(double tau, double T);

#endif //RUNGE_KUTTA_H

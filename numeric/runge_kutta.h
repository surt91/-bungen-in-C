#ifndef RUNGE_KUTTA_H
#define RUNGE_KUTTA_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../error.h"

double * rk4_step(double *z, double t, double tau, double * (*dgl)(), int dim);
double * H(double *z, double t, int dim);

double rk4_get_new_tau(double *z, double t, double tau, double * (*dgl)(), int dim, double r_desired);
double * rk4_adaptiv(double *z0, double tau, double * (*dgl)(), double T, int dim, double r_desired);

void rk4_print(double *z_seq, int dim, int T, double tau);
void rk4a_print(double *z_t_seq, int dim);

double * rk_lorenz_func(double *r, double t, int dim);
double * rk_test_func(double *r, double t, int dim);

void runge_kutta_lorenz();
void runge_kutta_test();
void runge_kutta_adaptiv_test();
double runge_kutta_benchmark(double tau, double T);

#endif //RUNGE_KUTTA_H

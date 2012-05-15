#ifndef RUNGE_KUTTA_H
#define RUNGE_KUTTA_H

#include <stdio.h>
#include <stdlib.h>

struct vektor
    {
        double *z;
        int len;
    };

double * rk4_step(double *z, double t, double tau, int dim);
double * H(double *z, double t, int dim);

void runge_kutta_test();

#endif //RUNGE_KUTTA_H

#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <time.h>

#include "../numeric/mat.h"
#include "../zufall/random.h"
#include "../prim/prim.h"
#include "../games/karten/poker.h"
#include "../numeric/runge_kutta.h"

void benchmark_start();
int benchmark_save(double ma, double pi, double pr, double po, double dg);

double matrix_benchmark();
double prim_benchmark(unsigned *laenge);
double pi_benchmark(double *v);
double poker_benchmark(int **u);
double dgl_benchmark(double *z);

#endif //BENCHMARK_H

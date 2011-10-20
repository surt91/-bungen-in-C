#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <time.h>

#include "../lina/mat.h"
#include "../zufall/random.h"
#include "../prim/prim.h"

void benchmark_start();
int benchmark_save(double ma, double pi, double pr);

double matrix_benchmark();
double prim_benchmark(unsigned *laenge);
double pi_benchmark();

#endif //BENCHMARK_H

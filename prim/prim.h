#ifndef PRIM_H
#define PRIM_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//5.2
int power(int x,int n);
//5.12
int fibonacci(int n);
int *fibonacci_array(int n, int *fibo_array);
int ist_prim(int test);
void prim_ermitteln(unsigned long max);
void primzahl(unsigned max, short *a);
unsigned *prim_array_bereinigen(short *alt_array, unsigned alt_array_laenge, unsigned *neu_array_laenge);
unsigned prim_max(unsigned *prim_liste, unsigned letzte);
void prim_ausgabe(unsigned *prim_liste, unsigned anzahl_prim);
int ist_prim_array(int test);
//5.14
void primfaktoren(int zahl);

#endif //PRIM_H

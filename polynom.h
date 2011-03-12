#ifndef POLYNOM_H
#define POLYNOM_H

#include "main.h"

//7.8
int *polynom_eingabe(int *polynom, int *grad);
void polynom_anzeige(int *polynom, int grad);
long long polynom_naiv(int *polynom, int x, int grad);
long long polynom_horner(int *polynom, int x, int grad);
//7.9
int *polynom_addierer(int *ergebnis_poly, int *poly1, int *poly2, int *grad_ergebnis, int grad1, int grad2);
//7.10
int *polynom_multiplizierer(int *ergebnis_poly, int *poly1, int *poly2, int *grad_ergebnis, int grad1, int grad2);
int *polynom_ableiter(int *poly_out, int *poly_in, int *grad_out, int grad_in);


#endif //POLYNOM_H

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "main.h"

//4.13
int aufsummieren(int n);
//4.17
void summe_g_ug(int n, int *sum_g, int *sum_ug);
//5.2
int power(int x,int n);
//5.3
void schreibe_zeichen(char c,int n);
//5.4
double wurzel4(int k);
//5.8
int f(int x,int a,int b,int c);
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
//5.18
void muenzwurf(int wuerfe, int *kopf, int *zahl);
//5.19
int monteCarloGeburtstagsProblem(int k);
//6.2
float invers(float zahl);
//6.8
void d2b(short v,int n);
int zyklischer_shift(short a,int n);
//6.9
int spiegel(short a);
//6.12
int max4(int x,int y,int z,int w);
int max2(int x,int y);
int min2(int x,int y);
//6.16
int roulette();
int roulette_gewinn_faktor(int k,int kugel);
//6.17
short datum_packer(int tag,int monat,int jahr);
void datum_entpacker(short gepackt, int *tag, int *monat, int *jahr);
//6.23
struct card
    {
        enum farbe {herz = 1, pik, karo, kreuz} f;
        enum wert {ass = 1, zwei, drei, vier, funf, sechs, sieben, acht, neun, zehn, bube, dame, konig} w;
    };
struct card *karten_geber(struct card *hand);
void karten_zeiger(struct card *hand);
//6.24
int is_fullhouse(struct card *hand);
int is_flush(struct card *hand);
int is_straight(struct card *hand);
struct card *karten_sortierer(struct card *hand); //auch 7.11
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
//7.15
int ist_palindrom(char *string, size_t laenge);
//7.16
struct mat
	{
		double *matrix;
		int zeilen;
		int spalten;
	};
struct mat matrix_eingabe(struct mat matrix_out);
void matrix_anzeige(struct mat matrix_in);
struct mat matrix_transponieren(struct mat matrix_in);
struct mat matrix_addieren(struct mat matrix1, struct mat matrix2);
struct mat matrix_skalaprodukt(struct mat matrix_in, double faktor);
struct mat matrix_matrixprodukt(struct mat matrix1, struct mat matrix2);
struct mat matrix_z_S(struct mat matrix_in, int k, double faktor);
struct mat matrix_z_Q(struct mat matrix_in, int k, int l, double faktor);
struct mat matrix_z_P(struct mat matrix_in, int k, int l);
struct mat matrix_rref(struct mat matrix_in);
//~ double matrix_det(struct mat matrix_in);

#endif //FUNCTIONS_H

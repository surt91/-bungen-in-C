#ifndef MAT_H
#define MAT_H

#include "main.h"

#define FLOATNULL 0.000004

struct mat
	{
		double *matrix;
		int zeilen;
		int spalten;
	};
struct mat matrix_eingabe(struct mat matrix_out);
struct mat matrix_e(int n);
struct mat matrix_rand(int n, int m, int p, int g, int z);
struct mat matrix_auslesen(struct mat matrix_out, char *filename);
void matrix_anzeige(struct mat matrix_in);
void matrix_ianzeige(struct mat matrix_in);
int matrix_schreiben(struct mat matrix_in, char *filename);
int matrix_save(struct mat matrix_out);
struct mat matrix_transponieren(struct mat matrix_in);
struct mat matrix_addieren(struct mat matrix1, struct mat matrix2);
struct mat matrix_skalaprodukt(struct mat matrix_in, double faktor);
struct mat matrix_matrixprodukt(struct mat matrix1, struct mat matrix2);
struct mat matrix_z_S(struct mat matrix_in, int k, double faktor);
struct mat matrix_z_Q(struct mat matrix_in, int k, int l, double faktor);
struct mat matrix_z_P(struct mat matrix_in, int k, int l);
struct mat matrix_gnf(struct mat matrix_in);
struct mat matrix_dgf(struct mat matrix_out);
struct mat matrix_invertieren(struct mat matrix_in);
double matrix_det(struct mat matrix_in);
struct mat matrix_streichen(struct mat matrix_in, int i, int j);
struct mat matrix_adjunkte(struct mat matrix_in);
struct mat matrix_invertieren_adjunkte(struct mat matrix_in);
double matrix_benchmark();

#endif //MAT_H

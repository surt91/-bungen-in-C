#include "mat_aufruf.h"

void aufg_MAT_1()
{
	struct mat matrix_in, matrix_out;
	matrix_in.zeilen = matrix_in.spalten = 0;
	printf("Eine Matrix Transponieren.\n");
	printf("Wie lautet die Matrix?\n");
	matrix_in = matrix_eingabe(matrix_in);
	printf("Deine Matrix:\n");
	matrix_anzeige(matrix_in);
	matrix_out = matrix_transponieren(matrix_in);
	printf("Die %d x %d transponierte Matrix lautet:\n", matrix_out.zeilen, matrix_out.spalten);
	matrix_anzeige(matrix_out);
	matrix_save(matrix_out);
	return;
}
void aufg_MAT_2()
{
	struct mat matrix1, matrix2, matrix_out;
	matrix1.zeilen = matrix1.spalten =  matrix2.zeilen = matrix2.spalten = 0;
	printf("Zwei Matrizen addieren.\n");
	printf("Wie lautet die erste Matrix?\n");
	matrix1 = matrix_eingabe(matrix1);
	printf("Die erste Matrix:\n");
	matrix_anzeige(matrix1);
	matrix2.zeilen=matrix1.zeilen;
	matrix2.spalten=matrix1.spalten;
	printf("Wie lautet die zweite %d x %d Matrix?\n", matrix2.zeilen, matrix2.spalten);
	matrix2 = matrix_eingabe(matrix2);
	printf("Die zweite Matrix:\n");
	matrix_anzeige(matrix2);

	matrix_out = matrix_addieren(matrix1, matrix2);
	printf("Die %d x %d Matrix lautet:\n", matrix_out.zeilen, matrix_out.spalten);
	matrix_anzeige(matrix_out);
	matrix_save(matrix_out);
	return;
}
void aufg_MAT_3()
{
	double faktor;
	struct mat matrix_in, matrix_out;
	matrix_in.zeilen = matrix_in.spalten = 0;
	printf("Eine Matrix mit einem Skalar multiplizieren.\n");
	printf("Wie lautet die Matrix?\n");
	matrix_in = matrix_eingabe(matrix_in);
	printf("Die Matrix:\n");
	matrix_anzeige(matrix_in);
	printf("Wie lautet der Skalar?\n");
	scanf("%lf",&faktor);

	matrix_out = matrix_skalaprodukt(matrix_in, faktor);
	printf("Die %d x %d Matrix lautet:\n", matrix_out.zeilen, matrix_out.spalten);
	matrix_anzeige(matrix_out);
	matrix_save(matrix_out);
	return;
}
void aufg_MAT_4()
{
	struct mat matrix1, matrix2, matrix_out;
	matrix1.zeilen = matrix1.spalten =  matrix2.zeilen = matrix2.spalten = 0;
	printf("Eine Matrix mit einer Matrix multiplizieren.\n");
	printf("Wie lautet die erste Matrix?\n");
	matrix1 = matrix_eingabe(matrix1);
	printf("Die erste Matrix:\n");
	matrix_anzeige(matrix1);
	printf("Wie lautet die zweite Matrix?\n");
	matrix2 = matrix_eingabe(matrix2);
	printf("Die zweite Matrix:\n");
	matrix_anzeige(matrix2);

	if(matrix1.spalten != matrix2.zeilen)
	{
		printf("Die Dimension der Spalten der ersten Matrix stimmt nicht mit der Dimension der Zeilen der zweiten Matrix überein.\n");
		return;
	}

	matrix_out = matrix_matrixprodukt(matrix1, matrix2);

	printf("Die %d x %d Matrix lautet:\n", matrix_out.zeilen, matrix_out.spalten);
	matrix_anzeige(matrix_out);
	matrix_save(matrix_out);
	return;
}
void aufg_MAT_5()
{
	int k;
	double faktor;
	struct mat matrix_in, matrix_out;
	matrix_in.zeilen = matrix_in.spalten = 0;
	printf("Elementare Zeilenumformung: Eine Zeile mit einem Skalar multiplizieren.\n");
	printf("Wie lautet die Matrix?\n");
	matrix_in = matrix_eingabe(matrix_in);
	printf("Die Matrix:\n");
	matrix_anzeige(matrix_in);
	printf("Welche Zeile soll mit dem Skalar multipliziert werden?\n");
	scanf("%d",&k);
	printf("Wie lautet der Skalar?\n");
	scanf("%lf",&faktor);

	matrix_out = matrix_z_S(matrix_in, k-1, faktor);
	printf("Die %d x %d Matrix lautet:\n", matrix_out.zeilen, matrix_out.spalten);
	matrix_anzeige(matrix_out);
	matrix_save(matrix_out);
	return;
}
void aufg_MAT_6()
{
	int k, l;
	double faktor;
	struct mat matrix_in, matrix_out;
	matrix_in.zeilen = matrix_in.spalten = 0;
	printf("Elementare Zeilenumformung: Eine Zeile k mit dem mu-fachen einer anderen Zeile l addieren.\n");
	printf("Wie lautet die Matrix?\n");
	matrix_in = matrix_eingabe(matrix_in);
	printf("Die Matrix:\n");
	matrix_anzeige(matrix_in);
	printf("Welche Zeile soll verändert werden??\n");
	scanf("%d",&k);
	printf("Welche Zeile soll darauf addiert werden?\n");
	scanf("%d",&l);
	printf("Mit welchem mu soll die addierte Zeile vorher multipliziert werden??\n");
	scanf("%lf",&faktor);

	matrix_out = matrix_z_Q(matrix_in, k-1, l-1, faktor);
	printf("Die %d x %d Matrix lautet:\n", matrix_out.zeilen, matrix_out.spalten);
	matrix_anzeige(matrix_out);
	matrix_save(matrix_out);
	return;
}
void aufg_MAT_7()
{
	int k, l;
	struct mat matrix_in, matrix_out;
	matrix_in.zeilen = matrix_in.spalten = 0;
	printf("Elementare Zeilenumformung: Eine Zeile k mit der Zeile l vertauschen.\n");
	printf("Wie lautet die Matrix?\n");
	matrix_in = matrix_eingabe(matrix_in);
	printf("Die Matrix:\n");
	matrix_anzeige(matrix_in);
	printf("erste Zeile k, die vertauscht werden soll?\n");
	scanf("%d",&k);
	printf("zweite Zeile l, die vertauscht werden soll?\n");
	scanf("%d",&l);

	matrix_out = matrix_z_P(matrix_in, k-1, l-1);
	printf("Die %d x %d Matrix lautet:\n", matrix_out.zeilen, matrix_out.spalten);
	matrix_anzeige(matrix_out);
	matrix_save(matrix_out);
	return;
}
void aufg_MAT_8()
{
	struct mat matrix_in, matrix_out;
	matrix_in.zeilen = matrix_in.spalten = 0;
	printf("Welche Matrix soll in Gaußsche Normalform gebracht werden?.\n");
	printf("Wie lautet die Matrix?\n");
	matrix_in = matrix_eingabe(matrix_in);
	printf("Die Matrix:\n");
	matrix_anzeige(matrix_in);

	matrix_out = matrix_gnf(matrix_in);
	printf("Die %d x %d Matrix lautet:\n", matrix_out.zeilen, matrix_out.spalten);
	matrix_anzeige(matrix_out);
	matrix_save(matrix_out);
	return;
}
void aufg_MAT_9()
{
	struct mat matrix_in, matrix_out;
	matrix_in.zeilen = matrix_in.spalten = 0;
	printf("Welche Matrix soll auf Diagonalform gebracht werden?.\n");
	printf("Wie lautet die Matrix?\n");
	matrix_in = matrix_eingabe(matrix_in);
	printf("Die Matrix:\n");
	matrix_anzeige(matrix_in);
	matrix_out = matrix_dgf(matrix_in);
	printf("Die %d x %d Matrix lautet:\n", matrix_out.zeilen, matrix_out.spalten);
	matrix_anzeige(matrix_out);
	matrix_save(matrix_out);
	return;
}
void aufg_MAT_10()
{
	struct mat matrix_in;
	matrix_in.zeilen = matrix_in.spalten = 0;
	printf("Für welche Matrix soll die Determinante berechnet werden?.\n");
	printf("Wie lautet die Matrix?\n");
	matrix_in = matrix_eingabe(matrix_in);
	printf("Die Matrix:\n");
	matrix_anzeige(matrix_in);
	printf("Die Determinante ist: %lg \n", matrix_det(matrix_in));
	return;
}
void aufg_MAT_11()
{
	struct mat matrix_in, matrix_out;
	matrix_in.zeilen = matrix_in.spalten = 0;
	printf("Zu welche Matrix soll die Adjunkte gefunden werden?\n");
	printf("Wie lautet die Matrix?\n");
	matrix_in = matrix_eingabe(matrix_in);
	printf("Die Matrix:\n");
	matrix_anzeige(matrix_in);
	matrix_out = matrix_adjunkte(matrix_in);
	printf("Die %d x %d Matrix lautet:\n", matrix_out.zeilen, matrix_out.spalten);
	matrix_anzeige(matrix_out);
	matrix_save(matrix_out);
	return;
}
void aufg_MAT_12()
{
	struct mat matrix_in, matrix_out;
	matrix_in.zeilen = matrix_in.spalten = 0;
	printf("Welche Matrix soll auf Diagonalform gebracht werden?.\n");
	printf("Wie lautet die Matrix?\n");
	matrix_in = matrix_eingabe(matrix_in);
	printf("Die Matrix:\n");
	matrix_anzeige(matrix_in);
	matrix_out = matrix_invertieren(matrix_in);
	if (matrix_out.zeilen != 0)
	{
		printf("Die invertierte %d x %d Matrix lautet:\n", matrix_out.zeilen, matrix_out.spalten);
		matrix_anzeige(matrix_out);
		matrix_save(matrix_out);
	}
	return;
}
void aufg_MAT_13()
{
	struct mat matrix_in, matrix_out;
	matrix_in.zeilen = matrix_in.spalten = 0;
	printf("Zu welcher Matrix soll die Inverse mit der Adjunkten ermittelt werden?\n");
	printf("Wie lautet die Matrix?\n");
	matrix_in = matrix_eingabe(matrix_in);
	printf("Die Matrix:\n");
	matrix_anzeige(matrix_in);
	matrix_out = matrix_invertieren_adjunkte(matrix_in);
	printf("Die %d x %d Matrix lautet:\n", matrix_out.zeilen, matrix_out.spalten);
	matrix_anzeige(matrix_out);
	matrix_save(matrix_out);
	return;
}
void aufg_MAT_14()
{
	struct mat matrix_out;
	int n, m, p=0, g=10, z=0, s;
	printf("Erzeugung einer zufälligen Matrix\n");
	printf("Wie groß soll die Matrix sein?\n");
	printf("Zeilen?\n");
	scanf("%d",&n);
	printf("Spalten?\n");
	scanf("%d",&m);
	printf("Optional:\n");
	printf("Nur ganze Zahlen?\n");
	scanf("%d",&z);
	printf("Nur positive Zahlen?\n");
	scanf("%d",&p);
	printf("Größter Betrag?\n");
	scanf("%d",&g);
	matrix_out = matrix_rand(n, m, p, z, g);
	printf("Die %d x %d Matrix lautet:\n", matrix_out.zeilen, matrix_out.spalten);
	if (z)
		matrix_ianzeige(matrix_out);
	else
		matrix_anzeige(matrix_out);
	matrix_save(matrix_out);
	return;
}
void aufg_MAT_15()
{
	struct mat matrix_out;
	int begin, end;
	int i;
	printf("Benchmark des Systems durch das Lösen von 100 zufälligen 100x100 Matrizen. (Diagonalform)\n");
	begin = clock();
	for(i=0;i<100;i++) matrix_dgf(matrix_rand(100,100,0,0,100));
	end = clock();
	printf("Time: %4.2f s\n",(double)(end-begin)/1000000);
	return;
}

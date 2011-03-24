#include "mat.h"

void alloc_fail()
{
	printf("Allozieren des Speichers Fehlgeschlagen!\nIrgendwas läuft schief :/");
}
// Nimmt Eingaben zur Erstellung einer Matrix
struct mat matrix_eingabe(struct mat matrix_out)
{
	int i, j;
	if(matrix_out.zeilen == 0 || matrix_out.spalten == 0)
	{
		printf("Anzahl Zeilen der Matrix?\n");
		scanf("%d",&matrix_out.zeilen);
		printf("Anzahl Spalten der Matrix?\n");
		scanf("%d",&matrix_out.spalten);
	}
	// Matrix aus Datei lesen
	if(matrix_out.zeilen < 0 || matrix_out.spalten < 0)
	{
		char *filename;
		printf("Matrix aus Datei lesen!\n");
		printf("Aus welcher Datei soll eine Matrix gelesen werden?\n");
		scanf("%s",&filename);
		matrix_out = matrix_auslesen(matrix_out,filename);
	}
	// Oder Matrix per Hand eingeben
	else
	{
		// erstellt ein Array variabler Länge
		matrix_out.matrix = (double *) calloc(matrix_out.zeilen * matrix_out.spalten, sizeof(double));
		printf("Zeilen und Spalten beginnen bei Null und Enden bei #Zeilen-1 bzw. #Spalten-1\n");
		for(i=0;i< matrix_out.zeilen ;i++)
			for(j=0;j< matrix_out.spalten ;j++)
			{
				printf("%d-te Zeile, %d-te Spalte\n", i+1, j+1);
				scanf("%lf", &matrix_out.matrix[i * matrix_out.spalten + j]);
			}
	}
	return (matrix_out);
}
struct mat matrix_auslesen(struct mat matrix_in, char *filename)
{
	int i,j;
	FILE *datei;
	double tmp = 3;
	struct mat matrix_out;
	printf("Matrix wird aus %s gelesen!\n", filename);
	datei = fopen (filename, "r");
	if (datei == NULL)
	{
		printf("Fehler beim Öffnen der Datei!\n");
		return;
	}

	fscanf(datei, "%dx%d", &matrix_out.zeilen, &matrix_out.spalten);

	matrix_out.matrix = (double *) calloc(matrix_out.zeilen * matrix_out.spalten, sizeof(double));
	if(matrix_out.matrix == NULL) alloc_fail();

	for(i=0;i<matrix_out.zeilen;i++)
		for(j=0;j<matrix_out.spalten;j++)
			fscanf(datei, "%lf", &matrix_out.matrix[j* matrix_out.zeilen+i]);

	fclose (datei);
	return (matrix_out);
}
// Erzeugt eine n x n Einheitsmatrix
struct mat matrix_e(int n)
{
	int i, j;
	struct mat matrix_out;
	matrix_out.zeilen = matrix_out.spalten = n;
	matrix_out.matrix = (double *) calloc(n * n, sizeof(double));
	if(matrix_out.matrix == NULL) alloc_fail();

	for(i=0;i<matrix_out.zeilen;i++)
		for(j=0;j<matrix_out.spalten;j++)
		{
			if(i==j)
				matrix_out.matrix[j* matrix_out.zeilen+i] = 1;
			else
				matrix_out.matrix[j* matrix_out.zeilen+i] = 0;
		}
	return matrix_out;
}
// Erzeugt eine n x m zufallsmatrix
// p=1: nur positive Werte, g obere Grenze des Betrags der Werte,
// z=1 nur ganze Zahlen
struct mat matrix_rand(int n, int m, int p, int z, int g)
{
	int i, j;
	int vz=1;
	struct mat matrix_out;
	matrix_out.zeilen  = n;
	matrix_out.spalten = m;
	matrix_out.matrix = (double *) calloc(n * m, sizeof(double));
	if(matrix_out.matrix == NULL) alloc_fail();

	for(i=0;i<matrix_out.zeilen;i++)
		for(j=0;j<matrix_out.spalten;j++)
		{
			if(!p)
			{
				vz = rand()%2;
				if(vz == 0)
					vz = -1;
			}
			if(z)
				matrix_out.matrix[j* matrix_out.zeilen+i] = (rand() % (g+1)) * vz;
			else
				matrix_out.matrix[j* matrix_out.zeilen+i] = ((double)rand() / RAND_MAX ) * g * vz;
		}
	return matrix_out;
}

void matrix_anzeige(struct mat matrix_in)
{
	int i, j;
	double tmp;

	for(i=0;i<matrix_in.zeilen;i++)
	{
		printf(" ");
		for(j=0;j<matrix_in.spalten;j++)
		{
			tmp = matrix_in.matrix[i* matrix_in.spalten+j];
			if(tmp < FLOATNULL && tmp > -FLOATNULL)
				printf(" % #5d     ", 0);
			else
				if((tmp - (int)tmp) < FLOATNULL && (tmp -(int)tmp) > -FLOATNULL)
					printf(" % #5d     ", (int)tmp);
				else
					printf(" % #9.3f ", tmp);
		}
		printf("\n");
	}
}
void matrix_ianzeige(struct mat matrix_in)
{
	int i, j;
	double tmp;
	for(i=0;i<matrix_in.zeilen;i++)
	{
		printf(" ");
		for(j=0;j<matrix_in.spalten;j++)
		{
			printf(" % #5d ", (int)matrix_in.matrix[i* matrix_in.spalten+j]);
		}
		printf("\n");
	}
}
int matrix_schreiben(struct mat matrix_in, char *filename)
{
	int i,j;
	FILE *datei;
	datei = fopen (filename, "w");
	if (datei == NULL)
	{
		printf("Fehler beim Öffnen der Datei!\n");
		return 1;
	}
	fprintf (datei, "%dx%d ", matrix_in.zeilen, matrix_in.spalten);
	for(i=0;i<matrix_in.zeilen;i++)
		for(j=0;j<matrix_in.spalten;j++)
			fprintf (datei, "%lf ", matrix_in.matrix[j* matrix_in.zeilen+i]);
	fprintf (datei, "\n");
	fclose (datei);
	printf("Matrix erfolgreich nach %s geschrieben\n", filename);
	return 0;
}
int matrix_save(struct mat matrix_out)
{
	char c;
	char filename[80];
	printf("Soll die Matrix gespeichert werden? (y/n) ");
	scanf("%c",&c);
	scanf("%c",&c);
	if(c=='y'||c=='Y'||c=='1')
	{
		printf("Unter welchem Namen?\n");
		scanf("%s",filename);
		//~ matrix_schreiben(matrix_out,filename);
		return matrix_schreiben(matrix_out,filename);
	}
	return 0;
}

struct mat matrix_transponieren(struct mat matrix_in)
{
	int i, j;
	struct mat matrix_out;
	matrix_out.zeilen = matrix_in.spalten;
	matrix_out.spalten = matrix_in.zeilen;
	matrix_out.matrix = (double *) calloc(matrix_out.zeilen * matrix_out.spalten, sizeof(double));
	if(matrix_out.matrix == NULL) alloc_fail();

	for(i=0;i<matrix_in.zeilen;i++)
		for(j=0;j<matrix_in.spalten;j++)
			matrix_out.matrix[j* matrix_out.spalten+i] = matrix_in.matrix[i* matrix_in.spalten+j];

	free(matrix_in.matrix);
	return matrix_out;
}
struct mat matrix_addieren(struct mat matrix1, struct mat matrix2)
{
	int i, j;
	struct mat matrix_out;
	matrix_out.zeilen = matrix1.zeilen;
	matrix_out.spalten = matrix1.spalten;
	matrix_out.matrix = (double *) calloc(matrix_out.zeilen * matrix_out.spalten, sizeof(double));
	if(matrix_out.matrix == NULL) alloc_fail();

	for(i=0;i<matrix_out.zeilen;i++)
		for(j=0;j<matrix_out.spalten;j++)
			matrix_out.matrix[i* matrix_out.spalten+j] = matrix1.matrix[i* matrix1.spalten+j]+matrix2.matrix[i* matrix2.spalten+j];

	free(matrix1.matrix);
	free(matrix2.matrix);
	return matrix_out;
}
struct mat matrix_skalaprodukt(struct mat matrix_out, double faktor)
{
	int i, j;
	for(i=0;i<matrix_out.zeilen;i++)
		for(j=0;j<matrix_out.spalten;j++)
			matrix_out.matrix[i* matrix_out.spalten+j] = matrix_out.matrix[i* matrix_out.spalten+j]*faktor;

	return matrix_out;
}
struct mat matrix_matrixprodukt(struct mat matrix1, struct mat matrix2)
{
	int i, j, k;
	struct mat matrix_out;
	if(matrix1.spalten != matrix2.zeilen)
	{
		printf("Die Dimension der Spalten der ersten Matrix stimmt nicht mit der Dimension der Zeilen der zweiten Matrix überein.\n");
		return;
	}
	matrix_out.zeilen = matrix1.zeilen;
	matrix_out.spalten = matrix2.spalten;
	matrix_out.matrix = (double *) calloc(matrix_out.zeilen * matrix_out.spalten, sizeof(double));
	if(matrix_out.matrix == NULL) alloc_fail();

	for(i=0;i<matrix_out.zeilen;i++)
		for(j=0;j<matrix_out.spalten;j++)
			for(k=0;k<matrix1.spalten;k++)
				matrix_out.matrix[i*matrix_out.spalten+j] += matrix2.matrix[k*matrix2.spalten+j]*matrix1.matrix[i*matrix1.spalten+k];

	free(matrix1.matrix);
	free(matrix2.matrix);
	return matrix_out;
}
//Multiplikation der k-ten Zeile mit einem Skalar
struct mat matrix_z_S(struct mat matrix_out, int k, double faktor)
{
	int j;
	for(j=0;j<matrix_out.spalten;j++)
		matrix_out.matrix[k* matrix_out.spalten+j] = matrix_out.matrix[k* matrix_out.spalten+j]*faktor;

	return matrix_out;
}
//Addition des mu-fachen der l-ten zeile zur k-ten Zeile
struct mat matrix_z_Q(struct mat matrix_out, int k, int l, double faktor)
{
	int j;
	if(k!=l)
		for(j=0;j<matrix_out.spalten;j++)
			matrix_out.matrix[k* matrix_out.spalten+j] += matrix_out.matrix[l* matrix_out.spalten+j]*faktor;

	return matrix_out;
}
//Vertauschen der k-ten und l-ten Zeile
struct mat matrix_z_P(struct mat matrix_in, int k, int l)
{
	int i, j;
	struct mat matrix_out;
	matrix_out.zeilen = matrix_in.zeilen;
	matrix_out.spalten = matrix_in.spalten;
	matrix_out.matrix = (double *) calloc(matrix_out.zeilen * matrix_out.spalten, sizeof(double));
	if(matrix_out.matrix == NULL) alloc_fail();

	for(i=0;i<matrix_out.zeilen;i++)
		for(j=0;j<matrix_out.spalten;j++)
			matrix_out.matrix[i* matrix_out.spalten+j] = matrix_in.matrix[i* matrix_in.spalten+j];

	for(j=0;j<matrix_in.spalten;j++)
	{
		matrix_out.matrix[k* matrix_out.spalten+j] = matrix_in.matrix[l* matrix_in.spalten+j];
		matrix_out.matrix[l* matrix_out.spalten+j] = matrix_in.matrix[k* matrix_in.spalten+j];
	}

	//~ free(matrix_in.matrix);
	return matrix_out;
}
// ref / Gaußsche Normalform / Dreiecksform
struct mat matrix_gnf(struct mat matrix_out)
{
	int i, p, q, k;
	double tmp;

	for(q=0;q<matrix_out.zeilen;q++)
	{
		for(p=q+1;p<matrix_out.zeilen;p++)
		{
			tmp = matrix_out.matrix[q * matrix_out.spalten + q];
			if(tmp<FLOATNULL && tmp>-FLOATNULL)
			{
				for(i=q;i<matrix_out.zeilen;i++)
				{
					tmp=matrix_out.matrix[i * matrix_out.spalten + q];
					if(tmp>FLOATNULL || tmp<-FLOATNULL)
					{
						matrix_out = matrix_z_P(matrix_out,i,q);
						break;
					}
				}
			}
			else
				matrix_out = matrix_z_Q(matrix_out, p, q, -1 * matrix_out.matrix[p * matrix_out.spalten + q]/tmp);
		}
		for(k=q;k<matrix_out.spalten;k++)
		{
			tmp=matrix_out.matrix[q * matrix_out.spalten + k];
			if(tmp>FLOATNULL || tmp<-FLOATNULL)
			{
				matrix_out = matrix_z_S(matrix_out,q,1/tmp);
				break;
			}
		}
	}
	return matrix_out;
}
// Diagonalform
struct mat matrix_dgf(struct mat matrix_out)
{
	// Auch das rechte obere Dreieck mit Nullen füllen (reduzierte Gaußsche Normalform / Diagonalform)
	int i, j, p;
	double tmp;

	matrix_out = matrix_gnf(matrix_out);
	for(i=matrix_out.zeilen;i>=0;i--)
		for(j=0;j<matrix_out.spalten;j++)
		{
			tmp=matrix_out.matrix[i* matrix_out.spalten+j];
			if(tmp>1+FLOATNULL || tmp<1-FLOATNULL) //Element ungleich 1, sprich: kein Pivotelement (durch gnf sichergestellt)
				continue;
			else
				for(p=0;p<i;p++)
					matrix_out=matrix_z_Q(matrix_out, p, i, -matrix_out.matrix[p* matrix_out.spalten+j]);
		}
	return matrix_out;
}
// invertieren
struct mat matrix_invertieren(struct mat matrix_in)
{
	// An die zu invertierende Matrix (muss quadratisch und linear unabhängig sein) wird die Einheitsmatrix drangehängt. Die große Matrix wird danach auf Diagonalform gebracht. Die ehemalige einheitsmatrix wird wieder abgeschnitten. Fertig ist die invertierte.
	int i, j;
	double det;
	struct mat einheit;
	einheit=matrix_e(matrix_in.zeilen);
	struct mat tmp, matrix_out, tmp2;
	tmp2.spalten = matrix_in.spalten;
	tmp2.zeilen = matrix_in.zeilen;
	tmp2.matrix = (double *) calloc(tmp2.zeilen * tmp2.spalten, sizeof(double));
	if(tmp2.matrix == NULL) alloc_fail();

	for(i=0;i<tmp2.zeilen;i++)
		for(j=0;j<tmp2.spalten;j++)
			tmp2.matrix[i* tmp2.spalten+j] = matrix_in.matrix[i* matrix_in.spalten+j];

	det = matrix_det(tmp2);

	//~ if(det < -FLOATNULL || det > FLOATNULL) // Wenn Determinante != 0
	if(det != 0) // Wenn Determinante != 0
	{
		tmp.spalten = matrix_in.spalten*2;
		tmp.zeilen = matrix_in.zeilen;
		tmp.matrix = (double *) calloc(tmp.zeilen * tmp.spalten, sizeof(double));
		if(tmp.matrix == NULL) alloc_fail();

		matrix_out.spalten = matrix_in.spalten;
		matrix_out.zeilen = matrix_in.zeilen;
		matrix_out.matrix = (double *) calloc(matrix_out.zeilen * matrix_out.spalten, sizeof(double));
		if(matrix_out.matrix == NULL) alloc_fail();

		for(i=0;i<matrix_in.zeilen;i++)
			for(j=0;j<matrix_in.spalten;j++)
				tmp.matrix[i* tmp.spalten+j] = matrix_in.matrix[i* matrix_in.spalten+j];

		for(i=0;i<matrix_in.zeilen;i++)
			for(j=0;j<matrix_in.spalten;j++)
				tmp.matrix[i* tmp.spalten+j+matrix_in.spalten] = einheit.matrix[i* einheit.spalten+j];
		tmp = matrix_dgf(tmp);;
		for(i=0;i<matrix_in.zeilen;i++)
			for(j=0;j<matrix_in.spalten;j++)
				matrix_out.matrix[i* matrix_in.spalten +j] = tmp.matrix[i* tmp.spalten + (j+matrix_in.spalten)];

		free(matrix_in.matrix);
		free(tmp.matrix);
		return matrix_out;
	}
	else
	{
		printf("Die Matrix ist nicht invertierbar.\n");
		matrix_out.zeilen = matrix_out.spalten = 0;
		return matrix_out;
	}
}
// Determinante
double matrix_det(struct mat matrix_out)
{
	int i, p, q;
	double det=1, tmp;

	if(matrix_out.zeilen != matrix_out.spalten)
		return 0;

	for(q=0;q<matrix_out.zeilen;q++)
	{
		for(p=q+1;p<matrix_out.zeilen;p++)
		{
			tmp = matrix_out.matrix[q * matrix_out.spalten + q];
			if(tmp<FLOATNULL && tmp>-FLOATNULL)
			{
				for(i=q;i<matrix_out.zeilen;i++)
				{
					tmp=matrix_out.matrix[i * matrix_out.spalten + q];
					if(tmp>FLOATNULL || tmp<-FLOATNULL)
					{
						matrix_out = matrix_z_P(matrix_out,i,q);
						det *= -1;
						break;
					}
				}
			}
			else
			{
				matrix_out = matrix_z_Q(matrix_out, p, q, -1 * matrix_out.matrix[p * matrix_out.spalten + q]/tmp);
			}
		}
		tmp=matrix_out.matrix[q * matrix_out.spalten + q];
		if(tmp>FLOATNULL || tmp<-FLOATNULL)
		{
			matrix_out = matrix_z_S(matrix_out,q,1/tmp);
			det *= tmp;
		} else { tmp = 0; }
	}

	for(i=0;i<matrix_out.spalten;i++)
		det *= matrix_out.matrix[i* matrix_out.spalten+i];

	free(matrix_out.matrix);
	return det;
}
// Zeile/Spalte streichen
struct mat matrix_streichen(struct mat matrix_in, int i, int j)
{
	int p, q, n, m;
	struct mat tmp;

	tmp.spalten = matrix_in.spalten - 1;
	tmp.zeilen = matrix_in.zeilen - 1;
	tmp.matrix = (double *) calloc(tmp.zeilen * tmp.spalten, sizeof(double));
	if(tmp.matrix == NULL) alloc_fail();

	for(m=0,q=0;q<matrix_in.zeilen;q++,m++)
	{
		if(q==j)
		{
			m--;
			continue;
		}
		for(n=0,p=0;p<matrix_in.spalten;p++,n++)
			{
				if(p==i)
				{
					n--;
					continue;
				}
				tmp.matrix[m* tmp.spalten+n] = matrix_in.matrix[q* matrix_in.spalten+p];
			}
	}
	return(tmp);
}
// Adjunkte Matrix finden
struct mat matrix_adjunkte(struct mat matrix_in)
{
	int i, j;
	double det=0;
	struct mat tmp, matrix_out;
	matrix_out.spalten = matrix_in.spalten;
	matrix_out.zeilen = matrix_in.zeilen;
	matrix_out.matrix = (double *) calloc(matrix_out.zeilen * matrix_out.spalten, sizeof(double));
	if(matrix_out.matrix == NULL) alloc_fail();

	if(matrix_out.zeilen != matrix_out.spalten)
		return;

	for(i=0;i<matrix_in.zeilen;i++)
		for(j=0;j<matrix_in.spalten;j++)
		{
			det = matrix_det(matrix_streichen(matrix_in,i,j));
			if(i%2==1)
				det*=-1;
			if(j%2==1)
				det*=-1;
			matrix_out.matrix[i* matrix_in.spalten+j]=det;
		}
	return matrix_out;
}
// invertieren mit Adjunkter
struct mat matrix_invertieren_adjunkte(struct mat matrix_in)
{
	double det;
	struct mat tmp;
	tmp.spalten = matrix_in.spalten;
	tmp.zeilen = matrix_in.zeilen;
	tmp.matrix = (double *) calloc(tmp.zeilen * tmp.spalten, sizeof(double));
	if(tmp.matrix == NULL) alloc_fail();

	tmp=matrix_adjunkte(matrix_in);
	det=matrix_det(matrix_in);
	if(det > -FLOATNULL && det < FLOATNULL) // Wenn Determinante == 0
		return;
	det=1/det;

	return(matrix_skalaprodukt(tmp,det));
}
double matrix_benchmark()
{
	int begin, end;
	int i;
	struct mat rand;
	rand = matrix_rand(200,200,0,0,200);

	begin = clock();
	for(i=0;i<200;i++)
		matrix_dgf(rand);
		//~ matrix_dgf(matrix_rand(100,100,0,0,100));
	end = clock();

	free(rand.matrix);
	return ((double)(end-begin)/1000000);
}

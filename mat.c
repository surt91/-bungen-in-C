#include "mat.h"

// Nimmt Eingaben zur Erstellung einer Matrix
struct mat matrix_eingabe(struct mat matrix_out)
{
	int i, j;
	if(matrix_out.zeilen == 0 || matrix_out.spalten == 0){
		printf("Anzahl Zeilen der Matrix?\n");
		scanf("%d",&matrix_out.zeilen);
		printf("Anzahl Spalten der Matrix?\n");
		scanf("%d",&matrix_out.spalten);
	}
	// erstellt ein Array variabler Länge
	matrix_out.matrix = (double *) calloc(matrix_out.zeilen * matrix_out.spalten, sizeof(double));
	printf("Zeilen und Spalten beginnen bei Null und Enden bei #Zeilen-1 bzw. #Spalten-1\n");
	for(i=0;i< matrix_out.zeilen ;i++)
		for(j=0;j< matrix_out.spalten ;j++)
		{
			printf("%d-te Zeile, %d-te Spalte\n", i+1, j+1);
			scanf("%lf", &matrix_out.matrix[i * matrix_out.spalten + j]);
		}
	return (matrix_out);
}
// Erzeugt eine n x n Einheitsmatrix
struct mat matrix_e(int n)
{
	int i, j;
	struct mat matrix_out;
	matrix_out.zeilen = matrix_out.spalten = n;
	matrix_out.matrix = (double *) calloc(n * n, sizeof(double));
	for(i=0;i<matrix_out.zeilen;i++)
		for(j=0;j<matrix_out.spalten;j++)
		{
			if(i==j)
				matrix_out.matrix[j* matrix_out.spalten+i] = 1;
			else
				matrix_out.matrix[j* matrix_out.spalten+i] = 0;
		}
	return matrix_out;
}

//~ struct mat matrix_auslesen(struct mat matrix_out)
//~ {
	//~ FILE *fp;
	//~ FILE *fopen(char *, char *);
	//~ char c, zahl[20];
	//~ int i;
	//~ fp = fopen(name, mode);
	//~ while(c != 'Q')
		//~ while(c != '\n')
		//~ {
			//~ i=0;
			//~ n=0;
			//~ while(c != ',')
			//~ {
				//~ c = getc(fp);
				//~ zahl[i]=c;
				//~ i++;
			//~ }
			//~ (const char) *zahl;
			//~ matrix[n] = atoi(*zahl);
			//~ n++;
		//~ }
//~
	//~ fclose(fp);
	//~ int i, j;
	//~ if(matrix_out.zeilen == 0 || matrix_out.spalten == 0){
		//~ printf("Anzahl Zeilen der Matrix?\n");
		//~ scanf("%d",&matrix_out.zeilen);
		//~ printf("Anzahl Spalten der Matrix?\n");
		//~ scanf("%d",&matrix_out.spalten);
	//~ }
	//~ // erstellt ein Array variabler Länge
	//~ matrix_out.matrix = (int *) calloc(matrix_out.zeilen * matrix_out.spalten, sizeof(int));
	//~ printf("Zeilen und Spalten beginnen bei Null und Enden bei #Zeilen-1 bzw. #Spalten-1\n");
	//~ for(i=0;i< matrix_out.zeilen ;i++)
		//~ for(j=0;j< matrix_out.spalten ;j++)
		//~ {
			//~ printf("%d-te Zeile, %d-te Spalte\n", i, j);
			//~ scanf("%d", &matrix_out.matrix[i * matrix_out.spalten + j]);
		//~ }
	//~ return (matrix_out);
//~ }
void matrix_anzeige(struct mat matrix_in)
{
	int i, j;
	for(i=0;i<matrix_in.zeilen;i++)
	{
		printf(" ");
		for(j=0;j<matrix_in.spalten;j++)
		{
			printf(" % #5.3f ", matrix_in.matrix[i* matrix_in.spalten+j]);
		}
		printf("\n");
	}
}
//~ void matrix_schreiben(struct mat matrix_in)
//~ {
	//~ int i, j;
	//~ for(i=0;i<matrix_in.zeilen;i++)
	//~ {
		//~ printf("| ");
		//~ for(j=0;j<matrix_in.spalten;j++)
		//~ {
			//~ printf("%d ", matrix_in.matrix[i* matrix_in.spalten+j]);
		//~ }
		//~ printf("|\n");
	//~ }
//~ }
struct mat matrix_transponieren(struct mat matrix_in)
{
	int i, j;
	struct mat matrix_out;
	matrix_out.zeilen = matrix_in.spalten;
	matrix_out.spalten = matrix_in.zeilen;
	matrix_out.matrix = (double *) calloc(matrix_out.zeilen * matrix_out.spalten, sizeof(double));
	for(i=0;i<matrix_in.zeilen;i++)
		for(j=0;j<matrix_in.spalten;j++)
			matrix_out.matrix[j* matrix_out.spalten+i] = matrix_in.matrix[i* matrix_in.spalten+j];

	return matrix_out;
}
struct mat matrix_addieren(struct mat matrix1, struct mat matrix2)
{
	int i, j;
	struct mat matrix_out;
	matrix_out.zeilen = matrix1.zeilen;
	matrix_out.spalten = matrix1.spalten;
	matrix_out.matrix = (double *) calloc(matrix_out.zeilen * matrix_out.spalten, sizeof(double));
	for(i=0;i<matrix_out.zeilen;i++)
		for(j=0;j<matrix_out.spalten;j++)
			matrix_out.matrix[i* matrix_out.spalten+j] = matrix1.matrix[i* matrix1.spalten+j]+matrix2.matrix[i* matrix2.spalten+j];

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
	for(i=0;i<matrix_out.zeilen;i++)
		for(j=0;j<matrix_out.spalten;j++)
			for(k=0;k<matrix1.spalten;k++)
				matrix_out.matrix[i*matrix_out.spalten+j] += matrix2.matrix[k*matrix2.spalten+j]*matrix1.matrix[i*matrix1.spalten+k];

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
	for(i=0;i<matrix_out.zeilen;i++)
		for(j=0;j<matrix_out.spalten;j++)
			matrix_out.matrix[i* matrix_out.spalten+j] = matrix_in.matrix[i* matrix_in.spalten+j];

	for(j=0;j<matrix_in.spalten;j++)
	{
		matrix_out.matrix[k* matrix_out.spalten+j] = matrix_in.matrix[l* matrix_in.spalten+j];
		matrix_out.matrix[l* matrix_out.spalten+j] = matrix_in.matrix[k* matrix_in.spalten+j];
	}

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
	for(i=0;i<tmp2.zeilen;i++)
		for(j=0;j<tmp2.spalten;j++)
			tmp2.matrix[i* tmp2.spalten+j] = matrix_in.matrix[i* matrix_in.spalten+j];

	det = matrix_det(tmp2);

	if(det < -FLOATNULL || det > FLOATNULL) // Wenn Determinante != 0
	{
		tmp.spalten = matrix_in.spalten*2;
		tmp.zeilen = matrix_in.zeilen;
		tmp.matrix = (double *) calloc(tmp.zeilen * tmp.spalten, sizeof(double));
		matrix_out.spalten = matrix_in.spalten;
		matrix_out.zeilen = matrix_in.zeilen;
		matrix_out.matrix = (double *) calloc(matrix_out.zeilen * matrix_out.spalten, sizeof(double));

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
		return matrix_out;
	}
	else
	{
		printf("Die Matrix ist nicht invertierbar.\n");
		return;
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

	tmp=matrix_adjunkte(matrix_in);
	det=matrix_det(matrix_in);
	if(det > -FLOATNULL && det < FLOATNULL) // Wenn Determinante == 0
		return;
	det=1/det;

	return(matrix_skalaprodukt(tmp,det));
}

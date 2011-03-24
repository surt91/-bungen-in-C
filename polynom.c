#include "polynom.h"

// Nimmt Eingaben zur Erstellung eines Polynoms entgegen
int *polynom_eingabe(int *polynom, int *grad)
{
	int i;
	printf("Welchen Grad soll das Polynom haben?\n");
	scanf("%d",grad);
	// erstellt ein Array variabler Länge
	polynom = (int *) calloc(*grad, sizeof(int));
	for(i=*grad;i>=0;i--)
	{
		printf("a%d (%d. Koeffizient (vor x^%d))?\n", i, *grad-i+1, i);
		scanf("%d", &polynom[i]);
	}
	printf("Dein Polynom:\n");
	polynom_anzeige(polynom, *grad);
	return (polynom);
}
void polynom_anzeige(int *polynom, int grad)
{
	int i;
	printf("f(x)= ");
	for(i=grad;i>0;i--)
	{
		printf("%dx^%d + ", polynom[i], i);
	}
	printf("%d\n\n",polynom[i]);
}
// Errechnet ein Polynom n-ten Grades
long long polynom_naiv(int *polynom, int x, int grad)
{
	int i;
	long long ergebnis=0;
	for(i=grad;i>=0;i--)
	{
		ergebnis += (power(x, grad-i)*polynom[i]);
	}
	return (ergebnis);
}
// Errechnet ein Polynom n-ten Grades nach dem Horner Schema
long long polynom_horner(int *polynom, int x, int grad)
{
	int i;
	long long ergebnis=0;
	//a0 + x(a1 + x(a2 + x(....(a_grad-1 + x(a_grad))...)))
	//letzte Klammer (-> a_grad)
	ergebnis = polynom[grad];
	for(i=grad-1;i>=0;i--)
	{
		ergebnis *= x;
		ergebnis += polynom[i];
	}
	return (ergebnis);
}

// addiert zwei Polynome
int *polynom_addierer(int *ergebnis_poly, int *poly1, int *poly2, int *grad_ergebnis, int grad1, int grad2)
{
	int i, grad_max, grad_min;
	if(grad1==grad2)
	{
		grad_min = grad_max = grad1;
	}
	else
	{
		grad_max = max2(grad1, grad2);
		grad_min = min2(grad1, grad2);
	}
	*grad_ergebnis=grad_max;
	ergebnis_poly = (int *) calloc(*grad_ergebnis, sizeof(int));
	for(i=0;i<=grad_min;i++)
	{
		ergebnis_poly[i]=poly1[i]+poly2[i];
	}
	if(grad1==grad2)
		;
	else if (grad1>grad2)
		for(;i<=grad_max;i++)
			ergebnis_poly[i]=poly1[i];
	else if (grad1<grad2)
		for(;i<=grad_max;i++)
			ergebnis_poly[i]=poly2[i];
	else
		return 0;
	return (ergebnis_poly);
}

// multipliziert zwei Polynome
int *polynom_multiplizierer(int *ergebnis_poly, int *poly1, int *poly2, int *grad_ergebnis, int grad1, int grad2)
{
	int i, j;
	*grad_ergebnis = grad1 + grad2; //Potenzgesetzte ftw!
	ergebnis_poly = (int *) calloc(*grad_ergebnis, sizeof(int));
	for(i=0;i<=grad1;i++)
		for(j=0;j<=grad2;j++)
			ergebnis_poly[i+j] += poly1[i] * poly2[j];
	return (ergebnis_poly);
}

// differenziert ein Polynom
int *polynom_ableiter(int *poly_out, int *poly_in, int *grad_out, int grad_in)
{
	int i;
	*grad_out = grad_in - 1;
	poly_out = (int *) calloc(*grad_out, sizeof(int));
	for(i=0;i<=*grad_out;i++)
		poly_out[i]=(poly_in[i+1]*(i+1));
	return (poly_out);
}

// gibt ein zufälliges Polynom aus
int* polynom_random(int *polynom, int grad)
{
	int i;
	polynom = (int *) calloc(grad, sizeof(int));
	for(i=grad;i>=0;i--)
		polynom[i] = rand() % 100;
	return (polynom);
}

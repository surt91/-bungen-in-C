#include "polynom_aufruf.h"

void aufg_POLY_1()
{
	int *polynom=0, grad, x, fvonx;
	polynom=polynom_eingabe(polynom, &grad);
	printf("Welchen Wert soll x haben?\n");
	scanf("%d", &x);
	//fvonx=polynom_naiv(polynom, x, grad);
	fvonx=polynom_horner(polynom, x, grad);
	printf("\nf(%d) = %d\n", x, fvonx);
	return;
}

void aufg_POLY_2()
{
	int *erstes_polynom, *zweites_polynom, *ergebnis_polynom, grad_eins, grad_zwei, grad_ergebnis;
	printf("Zwei Polynome addieren.\n");
	printf("Wie lautet das erste Polynom?\n");
	erstes_polynom = polynom_eingabe(erstes_polynom, &grad_eins);
	printf("Wie lautet das zweite Polynom?\n");
	zweites_polynom = polynom_eingabe(zweites_polynom, &grad_zwei);
	printf("Polynom eins: %d. Grad\nPolynom zwei: %d. Grad\n", grad_eins, grad_zwei);
	ergebnis_polynom = polynom_addierer(ergebnis_polynom, erstes_polynom, zweites_polynom, &grad_ergebnis, grad_eins, grad_zwei);
	printf("Das addierte Polynom(%d. Grad):\n", grad_ergebnis);
	polynom_anzeige(ergebnis_polynom, grad_ergebnis);
	return;
}

void aufg_POLY_3()
{
	int *erstes_polynom, *zweites_polynom, *ergebnis_polynom, grad_eins, grad_zwei, grad_ergebnis;
	printf("Zwei Polynome multiplizieren.\n");
	printf("Wie lautet das erste Polynom?\n");
	erstes_polynom = polynom_eingabe(erstes_polynom, &grad_eins);
	printf("Wie lautet das zweite Polynom?\n");
	zweites_polynom = polynom_eingabe(zweites_polynom, &grad_zwei);
	printf("Polynom eins: %d. Grad\nPolynom zwei: %d. Grad\n", grad_eins, grad_zwei);
	ergebnis_polynom = polynom_multiplizierer(ergebnis_polynom, erstes_polynom, zweites_polynom, &grad_ergebnis, grad_eins, grad_zwei);
	printf("Das multiplizierte Polynom (%d. Grad):\n", grad_ergebnis);
	polynom_anzeige(ergebnis_polynom, grad_ergebnis);
	return;
}

void aufg_POLY_4()
{
	int *polynom_in, *polynom_out, grad_in, grad_out;
	printf("Ein Polynom ableiten.\n");
	printf("Wie lautet das Polynom?\n");
	polynom_in = polynom_eingabe(polynom_in, &grad_in);
	polynom_out = polynom_ableiter(polynom_out, polynom_in, &grad_out, grad_in);
	printf("Das differenzierte Polynom (%d. Grad):\n", grad_out);
	polynom_anzeige(polynom_out, grad_out);
	return;
}

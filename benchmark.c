#include "benchmark.h"

void benchmark_start()
{
    unsigned w;
    double ma, pi, pr, v;
    char yn;
    printf("Benchmark des Systems durch das Lösen von 200 zufälligen 200x200 Matrizen. (Diagonalform)\n");
    ma = matrix_benchmark();
    printf("Time: %4.2f s\n", ma);
    printf("Benchmark des Systems durch das Zählen der Treffer bei 100.000.000 Darts auf eine Dartscheibe (und dabei angenäherter Wert von PI)\n");
    pi = pi_benchmark(&v);
    printf("Time: %4.2f s (pi=%f)\n", pi, v);
    printf("Benchmark des Systems durch das Ermitteln aller Primzahlen < 100.000.000\n");
    pr = prim_benchmark(&w);
    printf("Time: %4.2f s (%d Stück)\n", pr, w);

    printf("save? (y,n)");
    scanf("%c", &yn);
    if( yn == 'y' || yn == 'Y' || yn == '1')
        benchmark_save(ma,pi,pr);
    return;
}

int benchmark_save(double ma, double pi, double pr)
{
	char* filename = "bench.stat";
	FILE *datei;
	datei = fopen (filename, "w");
	if (datei == NULL)
	{
		printf("Fehler beim Öffnen der Datei!\n");
		return 1;
	}
	fprintf (datei, "%f,%f,%f\n", ma, pi, pr);
	fclose (datei);
	printf("Benchmark Ergebnisse erfolgreich nach %s geschrieben\n", filename);
	return 0;
}

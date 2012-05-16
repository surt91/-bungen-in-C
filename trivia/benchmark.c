#include "benchmark.h"

void benchmark_start()
{
    unsigned w;
    int *u;
    double ma, pi, pr, v, po, dg, z;
    char yn;

    printf("Benchmark des Systems durch das Lösen von 200 zufälligen 200x200 Matrizen. (Diagonalform)\n");
    ma = matrix_benchmark();
    printf("Time: %4.2f s\n\n", ma);

    printf("Benchmark des Systems durch das Zählen der Treffer bei 100.000.000 Darts auf eine Dartscheibe (und dabei angenäherter Wert von PI)\n");
    pi = pi_benchmark(&v);
    printf("Time: %4.2f s (pi=%f)\n\n", pi, v);

    printf("Benchmark des Systems durch das Ermitteln aller Primzahlen < 100.000.000\n");
    pr = prim_benchmark(&w);
    printf("Time: %4.2f s (%d Stück)\n\n", pr, w);

    printf("Benchmark des Systems durch das Verteilen und auswerten von je 250.000 Pokerhände an 8 Spieler (10.000.000 verteilte Karten) \n");
    po = poker_benchmark(&u);
    poker_monte_carlo_darstellen(u, 8);
    printf("Time: %4.2f s \n\n", po);

    printf("Benchmark des Systems durch das Lösen eines Lorenz Modells mit einem Runge-Kutta 4ten Grades. T=3000s, tau=0.0005s\n");
    dg = dgl_benchmark(&z);
    printf("Time: %4.2f s (letztes z: %g)\n\n", dg, z);

    printf("save? (y,n)");
    scanf("%c", &yn);
    if( yn == 'y' || yn == 'Y' || yn == '1')
        benchmark_save(ma,pi,pr,po,dg);
    return;
}

int benchmark_save(double ma, double pi, double pr, double po, double dg)
{
    char* filename = "bench.stat";
    FILE *datei;
    datei = fopen (filename, "w");
    if (datei == NULL)
    {
        printf("Fehler beim Öffnen der Datei!\n");
        return 1;
    }
    fprintf (datei, "%f,%f,%f,%f,%f\n", ma, pi, pr, po, dg);
    fclose (datei);
    printf("Benchmark Ergebnisse erfolgreich nach %s geschrieben\n", filename);
    return 0;
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
    end = clock();

    free(rand.matrix);
    return ((double)(end-begin)/CLOCKS_PER_SEC);
}

double prim_benchmark(unsigned *w)
{
    int begin,end;
    short *array=0;
    int max = 100000000;
    array = (short *) calloc(max, sizeof(short));
    begin = clock();
    primzahl(max, array);
    prim_array_bereinigen(array, max, w);
    end = clock();
    free(array);

    return((double)(end-begin)/CLOCKS_PER_SEC);
}

double pi_benchmark(double *v)
{
    int begin,end;
    begin = clock();
    *v=pi(100000000);
    end = clock();
    return((double)(end-begin)/CLOCKS_PER_SEC);
}

double poker_benchmark(int **u)
{
    int begin,end;
    begin = clock();
    poker_monte_carlo(250000, 8, u);
    end = clock();
    return((double)(end-begin)/CLOCKS_PER_SEC);
}

double dgl_benchmark(double *z)
{
    int begin,end;
    begin = clock();
    *z = runge_kutta_benchmark(0.0005, 3000);
    end = clock();
    return((double)(end-begin)/CLOCKS_PER_SEC);
}

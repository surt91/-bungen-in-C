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
    return ((double)(end-begin)/CLOCKS_PER_SEC);
}

double prim_benchmark(unsigned *w)
{
    int begin,end;

    //~ unsigned  *prim_liste;
    short *array=0;
    int max = 100000000;
    array = (short *) calloc(max, sizeof(short));
//    printf("test");
    begin = clock();
    primzahl(max, array);
    //~ prim_liste = prim_array_bereinigen(array, max, w);
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

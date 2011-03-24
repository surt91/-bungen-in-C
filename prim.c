#include "prim.h"

// Funktion zur Zerlegung einer Zahl in ihre Primfaktoren
void primfaktoren(zahl)
{
    int i;
    printf("1 ");
    for(i=2;i<=zahl;)
    {
        if(zahl%i==0)
        {
            printf("x %d ", i);
            zahl /= i;
        }
        else
        {
            i++;
        }
    }
    printf("\n");
    return;
}

// Funktion für die n-te Potenz
int power(int x,int n)
{
    int i;
    long long y=x;
    if(n==0)
		return 1;
	if(n==1)
		return x;
	if(n<=0)
		return -1;
    for(i=2;i<=n; i++)
    {
        y=x*y;
    }
    return y;
}

// Funktion zur Berechnung der n-ten Fibonacci-Zahl
int fibonacci(n)
{
    int i, j = 1, k=0,tmp=0;
    if(n<1)
        return -1;
    if(n==1)
        return 0;
    if(n==2)
        return 1;
    if(n==3)
        return 1;
    for(i=3;i<=n;i++)
    {
        k=j;
        j=k+tmp;
        tmp=k;
    }
    return j;
}
// Funktion zur Berechnung der ersten n Fibonacci-Zahlen (als Array, das >= n sein muss)
int *fibonacci_array(int n, int *fibo_array)
{
    int i;
    if(n<1)
        return 0;
    fibo_array[0]=0;
    fibo_array[1]=0;
    fibo_array[2]=1;
    for(i=3;i<=n;i++)
    {
		fibo_array[i]=fibo_array[i-2]+fibo_array[i-1];
    }
    return fibo_array;
}

// Funktion die testet, ob eine Primzahl vorliegt
int ist_prim(test)
{
    int grenze = sqrt(test), i;
    for(i=2;i<=grenze;i++)
    {
        if(test%i==0 || test == 1)
        {
            return 0;
        }
    }
    return 1;
}
// Funktionsgruppe, die schneller große Primzahlen errechnet
void prim_ermitteln(unsigned long max)
{
    unsigned laenge=0, *prim_liste;
    short *array=0;
    if(max==0)
    {
        printf("Bis zu Welcher Zahl, sollen Primzahlen gesucht werden?\n");
        scanf("%lu", &max);
        printf("\n\n");
    }
    array = (short *) calloc(max, sizeof(short));
    primzahl(max, array);
    prim_liste = prim_array_bereinigen(array, max, &laenge);
    prim_ausgabe(prim_liste, laenge);
    free(array);
}
// Primzahlenermittlung mit Array
void primzahl(unsigned max, short *a)
{
    unsigned pot,wurzpot, i, n;
    short *c;
    pot=sqrt(max);
    wurzpot=sqrt(pot);
    c = (short *) calloc(pot, sizeof(short));

    a[0]=1; a[1]=1;
    c[0]=1; c[1]=1;

    for(i=2;i<=wurzpot;i++)
        for(n=i+1;n<=pot;n++)
            if(n%i==0)
                if(c[n]!=1)
                    c[n]=1;

    for(n=2;n<=pot;n++)
        if(c[n]==0)
            for(i=n+n;i<=max;i=i+n)
                if(a[i]!=1)
                    a[i]=1;
    free(c);
    return;
}
unsigned *prim_array_bereinigen(short *alt_array, unsigned alt_array_laenge, unsigned *neu_array_laenge)
{
    unsigned i, n=0, *neu_array;

    for(i=0; i<=alt_array_laenge; i++){
        if(alt_array[i]!=1){
            n++;
        }
    }

    *neu_array_laenge=n;
    neu_array = (unsigned *) calloc(*neu_array_laenge, sizeof(unsigned));
    n=0;
    for(i=0; i<=alt_array_laenge; i++){
        if(alt_array[i]!=1){
            neu_array[n]=i;
            n++;
        }
    }
    return neu_array;
}
unsigned prim_max(unsigned *prim_liste, unsigned letzte)
{
    return (prim_liste[letzte-1]);
}
void prim_ausgabe(unsigned *prim_liste, unsigned anzahl_prim)
{
    unsigned i;
    short tmp=0;

    for(i=0; i<anzahl_prim; i++){
        printf("%10u ",prim_liste[i]);
        tmp++;
        if(tmp%5==0)
            printf("\n");
    }
    printf("\n#%d\n", anzahl_prim);
    return;
}
int ist_prim_array(test)
{
	short *array=0;
	unsigned *prim_liste, laenge;
	if(test<=1)
		return 0;
	array = (short *) calloc(test, sizeof(short));
	primzahl(test, array);
	prim_liste = prim_array_bereinigen(array, test, &laenge);
	free(array);
	if(prim_max(prim_liste, laenge) == test)
		return 1;
	else
		return 0;
}

double prim_benchmark()
{
	int begin,end;
	double v;

	unsigned laenge=0, *prim_liste;
    short *array=0;
    int max = 100000000;
    array = (short *) calloc(max, sizeof(short));
    begin = clock();
    primzahl(max, array);
    prim_liste = prim_array_bereinigen(array, max, &laenge);
    end = clock();
    free(array);

	return((double)(end-begin)/1000000);
}

#include "prim_aufruf.h"

void aufg_PRIM_3()
{
    int n, x;
    printf("Basis?\n");
    scanf("%d", &x);
    printf("Potenz?\n");
    scanf("%d", &n);
    printf("Ergebnis: %d", power(x,n));
    return;
}

void aufg_PRIM_1()
{
    int k;
    printf("Welche Zahl soll in ihre Primfaktoren zerlegt werden?\n");
    scanf("%d",&k);
    primfaktoren(k);
    return;
}

void aufg_PRIM_2()
{
    int k;
    printf("Bis zu welcher Zahl sollen Primzahlen gesucht werden?\n");
    scanf("%d",&k);
    prim_ermitteln(k);
    return;
}

void aufg_PRIM_4()
{
    int k,q, *array;
    printf("Die wievielte Fibonacci Zahl soll überprüft werden?\n");
    scanf("%d",&k);
    array = (int *) calloc(k+1, sizeof(int));
    array=fibonacci_array(k, array);
    q=array[k];
    if(q<0)
    {
		printf("Bitte gebe eine ganze Zahl größer gleich 1 an.\n");
		return;
	}
    if(ist_prim_array(q))
    {
        printf("Die %d. Fibonacci Zahl %d ist eine Primzahl\n", k, q);
    }
    else
    {
        printf("Die %d. Fibonacci Zahl %d ist keine Primzahl\n", k, q);
    }
    return;
}

void aufg_PRIM_5()
{
    int n,i,fibo=0,k=0;
    printf("Wieviele Fibonacci-Primzahlen sollen ausgegeben werden?\n");
    scanf("%d", &n);
    for(i=3;k<n;i++)
    {
        fibo=fibonacci(i);
        if(ist_prim(fibo) && fibo > 1)
        {
            printf("%d, ", fibo);
            k++;
        }
    }
    printf("sind die ersten %d Fibonacci Zahlen, die auch Primzahlen sind\n",k);
}
void aufg_PRIM_6()
{   int n,i, *fibo_array=0, prim_max;
    short *prim_array;
    printf("Wieviele Fibonacci-Primzahlen sollen ausgegeben werden?\n");
    scanf("%d", &n);
    fibo_array = (int *) calloc(n+1, sizeof(int));
    fibonacci_array(n, fibo_array);
    prim_max=fibo_array[n];
    prim_array = (short *) calloc(prim_max, sizeof(short));
    primzahl(prim_max, prim_array);
    for(i=1;i<=n;i++)
    {
		if(!prim_array[fibo_array[i]])
			printf("%d, ", fibo_array[i]);
	}
	free(prim_array);
	free(fibo_array);
    printf("sind die Primzahlen unter den ersten %d Fibonacci Zahlen\n",n);
}


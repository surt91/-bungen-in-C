#include "fft.h"

#define PI 3.141592

double complex *dft(double complex *x, int N)
{
    int k, n;
    double complex *X;
    X = (double complex *) calloc(N, sizeof(double complex));
    if(X == NULL) alloc_fail();

    for(k=0;k<N;k++)
        for(n=0;n<N;n++)
            X[k] += x[n]*cexp(-2*PI*_Complex_I*n*k/N);

    return X;
}

void dft_test()
{
    int N,i;
    double complex *x;

    N = 4;
    x = (double complex *) calloc(N, sizeof(double complex));
    if(x == NULL) alloc_fail();

    for(i=0;i<N;i++)
        x[i] = i+1;

    x = dft(x,N);
    for(i=0;i<N;i++)
        printf("%.2f + %.2f i\n",creal(x[i]), cimag(x[i]));

    free(x);
    return;
}

int reverse(int x, int N)
{
    int n, y = 0;
    for(n = 0; n < N; n++)
    {
        y <<= 1;
        y |= x & 1;
        x >>= 1;
    }
    return(y);
}

#include "fft.h"

#define PI 3.141592654

double complex *fft(double complex *x, int N)
{
    unsigned int n,i,m,l,r, stufen, elemente;
    double complex *W, tmp, w;
    // N muss zweier Potenz sein: N = 2^M
    int M = ceil(log2(N));
    printf("M: %d\n",M);
    N = exp2(M);
    printf("N: %d\n",N);
    // Rest bis zweierpotenz mit 0 auffüllen
    //~ xTmp = (double complex *) realloc(x, N * sizeof(double complex));
    //~ if (xTmp != NULL) x=xTmp;
    //~ else alloc_fail();
    //~ free(xTmp);
    // Bit reverse Ordnen (zb. N=4: 0 2 1 3)
    for(n=0;n<N/2;n++)
    {
        m = reverse(n,M);
        tmp = x[n];
        x[n] = x[m];
        x[m] = tmp;
    }

    // Koeffizienten W^n, n = 0..N-1, berechnen
    // W = e^-2*pi*i/N
    W = (double complex *) calloc(N, sizeof(double complex));
    if(W == NULL) alloc_fail();
    for(n=0;n<N;n++)
        W[n] = cexp(-2*PI*_Complex_I*n/N);

    // Butterfly Schritte
    for(i=0;i<M;i++)
    {
        // Anzahl der Butterflies
        stufen = exp2(M-i-1);
        for(n=0;n<stufen;n++)
        {
            // Element des Abschnitts
            elemente = exp2(i);
            for(m=0;m<elemente;m++)
            {
                w = W[stufen*m];

                l = exp2(i+1)*n+m;
                r = l + exp2(i);
                printf("l: %d, r: %d\n", l, r);
                printf("x[%d] = %f + %f i\n",l,creal(x[l]), cimag(x[l]));
                printf("x[%d] = %f + %f i\n",r,creal(x[r]), cimag(x[r]));
                tmp  = x[l] + w * x[r];
                x[r] = x[l] - w * x[r];
                x[l] = tmp;

                printf("i: %d\n",i);
                printf("n: %d\n",n);
                printf("m: %d\n",m);
                printf("W^%d  = %f + %f i\n",stufen*m, creal(w), cimag(w));
                printf("x[%d] = %f + %f i\n",l,creal(x[l]), cimag(x[l]));
                printf("x[%d] = %f + %f i\n",r,creal(x[r]), cimag(x[r]));
                printf("\n");
            }
            printf("--------------\n");
        }
        printf("================\n");
    }
    free(W);
    return x;
}

double complex *dft(double complex *x, int N)
{
    int k, n;
    double complex *X, W;
    X = (double complex *) calloc(N, sizeof(double complex));
    if(X == NULL) alloc_fail();

    W = cexp(-2*PI*_Complex_I/N);

    for(k=0;k<N;k++)
        for(n=0;n<N;n++)
            X[k] += x[n]*cpow(W,n*k);

    return X;
}

void dft_test()
{
    int N,i;
    double complex *x;

    N = 16;
    x = (double complex *) calloc(N, sizeof(double complex));
    if(x == NULL) alloc_fail();

    for(i=0;i<N;i++)
        x[i] = i*3+1;

    x = dft(x,N);
    for(i=0;i<N;i++)
        printf("%.2f + %.2f i\n",creal(x[i]), cimag(x[i]));

    free(x);
    return;
}

void fft_test()
{
    int N,i;
    double complex *x;

    N = 16;
    x = (double complex *) calloc(N, sizeof(double complex));
    if(x == NULL) alloc_fail();

    for(i=0;i<N;i++)
        x[i] = i*3+1;

    x = fft(x,N);
    for(i=0;i<N;i++)
        printf("%.2f + %.2f i\n",creal(x[i]), cimag(x[i]));

    //~ free(x);
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

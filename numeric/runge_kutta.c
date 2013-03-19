#include "runge_kutta.h"

double * rk4(double *z0, double tau, void (*dgl)(),double T,int dim)
{
    double *zout, *z_seq, t;
    int j, n, N;

    N = T/tau;

    z_seq = (double *) calloc(dim * N, sizeof(double));
    if(z_seq == NULL) alloc_fail();
    zout = (double *) calloc(dim, sizeof(double));
    if(zout == NULL) alloc_fail();

    for(j=0;j<dim;j++)
        z_seq[j * N + 0] = z0[j];

    for(n=1;n<N;n++)
    {
        t=n*tau;
        for(j=0;j<dim;j++)
            zout[j] = z_seq[j * N + n-1];

        rk4_step(zout,t,tau,dgl,dim);

        for(j=0;j<dim;j++)
            z_seq[j * N + n] = zout[j];
    }
    free(zout);
    return z_seq;
}

double * rk4a(double *z0, double tau, void (*dgl)(),
                                    double T, int dim, double r_desired)
{
    double *zout, *zt_seq, t=0, *tmp;
    int j, n=0, N=1000;

    zt_seq = (double *) calloc((dim+1) * N, sizeof(double));
    if(zt_seq == NULL) alloc_fail();
    zout = (double *) calloc(dim, sizeof(double));
    if(zout == NULL) alloc_fail();

    for(j=0;j<dim;j++)
        zt_seq[0 * (dim+1) + j] = z0[j];
    zt_seq[0 * (dim+1) + dim] = 0;

    while(t<T)
    {
        n++;
        if(n>N-2)
        {
            N+=1000;
            tmp = (double*) realloc(zt_seq, (dim+1)*N* sizeof(double));
            if (tmp != NULL) zt_seq=tmp;
            else alloc_fail();
            free(tmp);
        }
        for(j=0;j<dim;j++)
            zout[j] = zt_seq[(n-1) * (dim+1) + j];

        tau = rk4_get_new_tau(zout, t, tau, dgl, dim, r_desired);
        t += tau;

        rk4_step(zout,t,tau,dgl,dim);

        zt_seq[n * (dim+1) + dim] = t;
        for(j=0;j<dim;j++)
            zt_seq[n * (dim+1) + j] = zout[j];
    }
    free(zout);

    zt_seq[(n +1)* (dim+1) + dim] = 0;

    tmp = (double*) realloc (zt_seq, (dim+1) * (n+2) * sizeof(double));
    if (tmp != NULL) zt_seq=tmp;
    else alloc_fail();
    free(tmp);

    return zt_seq;
}

void rk4_step(double *z, double t, double tau, void (*dgl)(),
                                                                int dim)
{
    int i;
    double *ztmp, *Hs[4];

    for(i=0;i<4;i++)
    {
        Hs[i] = (double *) calloc(dim, sizeof(double));
        if(Hs[i] == NULL) alloc_fail();
    }
    ztmp = (double *) calloc(dim, sizeof(double));
    if(ztmp == NULL) alloc_fail();

    dgl(z, t, dim, Hs[0]);
    for(i=0;i<dim;i++)
        ztmp[i] = z[i]+tau/2*Hs[0][i];
    dgl(ztmp, t+tau/2, dim, Hs[1]);
    for(i=0;i<dim;i++)
        ztmp[i] = z[i]+tau/2*Hs[1][i];
    dgl(ztmp, t+tau/2, dim, Hs[2]);
    for(i=0;i<dim;i++)
        ztmp[i] = z[i]+tau  *Hs[2][i];
    dgl(ztmp, t+tau, dim, Hs[3]);

    for(i=0;i<dim;i++)
        z[i] = z[i]+ tau/6*(Hs[0][i]+2*Hs[1][i]+2*Hs[2][i]+Hs[3][i]);

    for(i=0;i<4;i++)
        free(Hs[i]);
    free(ztmp);
}

double rk4_get_new_tau(double *z, double t, double tau,
                           void (*dgl)(), int dim, double r_desired)
{
    int i;
    double S = 0.9, tau_neu, r, tmp1, tmp2;
    double *z1, *z2;
    z1    = (double *) calloc(dim, sizeof(double));
    if(z1 == NULL) alloc_fail();
    z2    = (double *) calloc(dim, sizeof(double));
    if(z2 == NULL) alloc_fail();

    for(i=0;i<dim;i++)
    {
        z1[i]=z[i];
        z2[i]=z[i];
    }

    rk4_step(z1,t,tau,dgl,dim);
    rk4_step(z2,t,tau/2,dgl,dim);
    rk4_step(z2,t,tau/2,dgl,dim);

    tmp1 = 0; tmp2 = 0;
    for(i=0;i<dim;i++)
    {
        //Norm^2 von z2-z1
        tmp1 += (z2[i]-z1[i])*(z2[i]-z1[i]);
        //Norm^2 von (z1+z2)/2
        tmp2 += (z1[i]+z2[i])*(z1[i]+z2[i])/4;
    }
    free(z1); free(z2);
    r = sqrt(tmp1)/sqrt(tmp2);

    tau_neu = tau * pow((r_desired/r),1/5.);
    tau_neu = S*tau_neu;
    if(tau_neu < tau/4)
        tau_neu = tau/4;
    if(tau_neu > 4*tau)
        tau_neu = 4*tau;

    return tau_neu;
}

void rk_test_func(double *r, double t, int dim, double *out)
{
    int i;

    for(i=0;i<dim;i++)
        out[i] = 2*t;
}

void runge_kutta_test()
{
    double z0[]={0,0}, tau = 0.01, T = 2, *z_seq;
    int dim=1;

    z_seq = rk4(z0, tau, rk_test_func, T, dim);
    rk4_print(z_seq, dim, T, tau);
    free(z_seq);
}

void runge_kutta_adaptiv_test()
{
    double z0[]={0,0}, tau = 0.01, T = 2, *zt_seq;
    int dim=1;

    zt_seq = rk4a(z0, tau, rk_test_func, T, dim, 0.0002);
    rk4a_print(zt_seq, dim);
    free(zt_seq);
}

void rk4_print(double *z_seq, int dim, int T, double tau)
{
    int i, j, N;
    N = T/tau;
    for(i=0;i<N;i++)
    {
        printf("%g   ",i*tau);
        for(j=0;j<dim;j++)
            printf("%g   ",z_seq[j * N + i]);
        printf("\n");
    }
}

void rk4a_print(double *zt_seq, int dim)
{
    int n=0, j;
    do
    {
        printf("%g   ",zt_seq[n * (dim +1) + dim]);
        for(j=0;j<dim;j++)
            printf("%g   ",zt_seq[n * (dim +1) + j]);
        printf("\n");
        n++;
    } while(zt_seq[n * (dim +1) + dim] != 0);
}

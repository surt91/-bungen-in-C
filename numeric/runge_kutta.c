#include "runge_kutta.h"

double * rk4(double *z0, double tau, double T, int dim)
{
    double *zout, *z_seq, *t_seq, t;
    int j, n, N;

    N = T/tau;

    z_seq = (double *) calloc(dim * N, sizeof(double));
    //~ if(z_seq == NULL) alloc_fail();
    t_seq = (double *) calloc(N, sizeof(double));
    //~ if(t_seq == NULL) alloc_fail();
    zout = (double *) calloc(dim, sizeof(double));
    //~ if(zout == NULL) alloc_fail();

    for(j=0;j<dim;j++)
        z_seq[j * N + 0] = z0[j];

    for(n=1;n<N;n++)
    {
        t=n*tau;
        for(j=0;j<dim;j++)
            zout[j] = z_seq[j * N + n-1];

        zout = rk4_step(zout,t,tau, dim);

        for(j=0;j<dim;j++)
            z_seq[j * N + n] = zout[j];
        t_seq[n] = t;
    }
    return z_seq;
}

double * rk4_step(double *z, double t, double tau, int dim)
{
    int i;
    double *ztmp, *H1, *H2, *H3, *H4, *zout;

    H1 = (double *) calloc(dim, sizeof(double));
    //~ if(H1 == NULL) alloc_fail();
    H2 = (double *) calloc(dim, sizeof(double));
    //~ if(H2 == NULL) alloc_fail();
    H3 = (double *) calloc(dim, sizeof(double));
    //~ if(H3 == NULL) alloc_fail();
    H4 = (double *) calloc(dim, sizeof(double));
    //~ if(H4 == NULL) alloc_fail();
    ztmp = (double *) calloc(dim, sizeof(double));
    //~ if(ztmp == NULL) alloc_fail();
    zout = (double *) calloc(dim, sizeof(double));
    //~ if(zout == NULL) alloc_fail();

    H1=H(z, t, dim);
    for(i=0;i<dim;i++)
        ztmp[i] = z[i]+tau/2*H1[i];
    H2=H(ztmp, t+tau/2, dim);
    for(i=0;i<dim;i++)
        ztmp[i] = z[i]+tau/2*H2[i];
    H3=H(ztmp, t+tau/2, dim);
    for(i=0;i<dim;i++)
        ztmp[i] = z[i]+tau  *H3[i];
    H4=H(ztmp, t+tau, dim);

    for(i=0;i<dim;i++)
        zout[i] = z[i] + tau/6*(H1[i]+2*H2[i]+2*H3[i]+H4[i]);

    return zout;
}

double * H(double *r, double t, int dim)
{
    // t^2
    //~ int i;
    //~ for(i=0;i<dim;i++)
        //~ *out[i] = 2*t;

    // Lorenz Modell
    double sigma, r_param, b;
    double x, y, z, *out;
    out = (double *) calloc(dim, sizeof(double));
    //~ if(out == NULL) alloc_fail();
    sigma   = 10;
    r_param = 28;
    b       = 8/3;

    x=r[0]; y=r[1]; z=r[2];

    out[0] = sigma*(y-x);
    out[1] = r_param*x - y - x*z;
    out[2] = x*y - b*z;

    return out;
}

void runge_kutta_test()
{
    double z0[]={1,1,20}, tau = 0.01, T = 2, *z_seq;
    int dim=3, j, i, N;

    N = T/tau;

    z_seq = rk4(z0, tau, T, dim);
    for(i=0;i<N;i++)
    {
        for(j=0;j<dim;j++)
            printf("%g   ",z_seq[j * N + i]);
        printf("\n");
    }
}

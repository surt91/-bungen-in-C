#include "runge_kutta.h"

double * rk4(double *z0, double tau, double * (*dgl)(), double T, int dim)
{
    double *zout, *z_seq, t;
    //~ double *t_seq;
    int j, n, N;

    N = T/tau;

    z_seq = (double *) calloc(dim * N, sizeof(double));
    //~ if(z_seq == NULL) alloc_fail();
    //~ t_seq = (double *) calloc(N, sizeof(double));
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

        zout = rk4_step(zout,t,tau,dgl,dim);

        for(j=0;j<dim;j++)
            z_seq[j * N + n] = zout[j];
        //~ t_seq[n] = t;
    }
    //~ free(zout);
    return z_seq;
}

double * rk4_adaptiv(double *z0, double tau, double * (*dgl)(), double T, int dim, double r_desired)
{
    double *zout, *z_t_seq, t=0;
    int j, n=0, N=1000;

    z_t_seq = (double *) calloc((dim+1) * N, sizeof(double));
    //~ if(z_seq == NULL) alloc_fail();
    //~ t_seq = (double *) calloc(N, sizeof(double));
    //~ if(t_seq == NULL) alloc_fail();
    zout = (double *) calloc(dim, sizeof(double));
    //~ if(zout == NULL) alloc_fail();

    for(j=0;j<dim;j++)
        z_t_seq[0 * (dim+1) + j] = z0[j];
    z_t_seq[0 * (dim+1) + dim] = 0;

    while(t<T)
    {
        n++;
        if(n>N-2)
        {
            N+=1000;
            z_t_seq = (double*) realloc (z_t_seq, (dim+1) * N * sizeof(double));
        }
        for(j=0;j<dim;j++)
            zout[j] = z_t_seq[(n-1) * (dim+1) + j];

        tau = rk4_get_new_tau(zout, t, tau, dgl, dim, r_desired);
        t += tau;

        zout = rk4_step(zout,t,tau,dgl,dim);

        z_t_seq[n * (dim+1) + dim] = t;
        for(j=0;j<dim;j++)
            z_t_seq[n * (dim+1) + j] = zout[j];
    }
    //~ free(zout);

    z_t_seq[(n +1)* (dim+1) + dim] = 0;
    return z_t_seq;
}

double * rk4_step(double *z, double t, double tau, double * (*dgl)(), int dim)
{
    int i;
    double *ztmp, *Hs[4];

    for(i=0;i<4;i++)
    {
        Hs[i] = (double *) calloc(dim, sizeof(double));
        //~ if(Hs[i] == NULL) alloc_fail();
    }
    ztmp = (double *) calloc(dim, sizeof(double));
    //~ if(ztmp == NULL) alloc_fail();

    Hs[0]=dgl(z, t, dim);
    for(i=0;i<dim;i++)
        ztmp[i] = z[i]+tau/2*Hs[0][i];
    Hs[1]=dgl(ztmp, t+tau/2, dim);
    for(i=0;i<dim;i++)
        ztmp[i] = z[i]+tau/2*Hs[1][i];
    Hs[2]=dgl(ztmp, t+tau/2, dim);
    for(i=0;i<dim;i++)
        ztmp[i] = z[i]+tau  *Hs[2][i];
    Hs[3]=dgl(ztmp, t+tau, dim);

    for(i=0;i<dim;i++)
        ztmp[i] = z[i] + tau/6*(Hs[0][i]+2*Hs[1][i]+2*Hs[2][i]+Hs[3][i]);

    //~ for(i=0;i<4;i++)
        //~ free(Hs[i]);
    return ztmp;
}

double rk4_get_new_tau(double *z, double t, double tau, double * (*dgl)(), int dim, double r_desired)
{
    int i;
    double S = 0.9, tau_neu, r, tmp1, tmp2;
    double *z1, *z2, *z_tmp;
    z_tmp = (double *) calloc(dim, sizeof(double));
    z1    = (double *) calloc(dim, sizeof(double));
    z2    = (double *) calloc(dim, sizeof(double));

    z1 = rk4_step(z,t,tau,dgl,dim);
    z_tmp = rk4_step(z,t,tau/2,dgl,dim);
    z2 = rk4_step(z_tmp,t,tau/2,dgl,dim);

    tmp1 = 0; tmp2 = 0;
    for(i=0;i<dim;i++)
    {
        //Norm^2 von z2-z1
        tmp1 += (z2[i]-z1[i])*(z2[i]-z1[i]);
        //Norm^2 von (z1+z2)/2
        tmp2 += (z1[i]+z2[i])*(z1[i]+z2[i])/4;
    }
    r = sqrt(tmp1)/sqrt(tmp2);

    tau_neu = tau * pow((r_desired/r),1/5.);
    tau_neu = S*tau_neu;
    if(tau_neu < tau/4)
        tau_neu = tau/4;
    if(tau_neu > 4*tau)
        tau_neu = 4*tau;

    return tau_neu;
}

double * rk_test_func(double *r, double t, int dim)
{
    // t^2
    int i;
    double *out;
    out = (double *) calloc(dim, sizeof(double));
    //~ if(out == NULL) alloc_fail();

    for(i=0;i<dim;i++)
        out[i] = 2*t;

    return out;
}

double * rk_lorenz_func(double *r, double t, int dim)
{
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
    double z0[]={0,0}, tau = 0.01, T = 2, *z_seq;
    int dim=1;

    z_seq = rk4(z0, tau, rk_test_func, T, dim);
    rk4_print(z_seq, dim, T, tau);
}

void runge_kutta_adaptiv_test()
{
    double z0[]={0,0}, tau = 0.01, T = 2, *z_seq;
    int dim=1;

    z_seq = rk4_adaptiv(z0, tau, rk_test_func, T, dim, 0.0002);
    rk4a_print(z_seq, dim);
}

void rk4a_print(double *z_t_seq, int dim)
{
    int n=0, j;
    do
    {
        printf("%g   ",z_t_seq[n * (dim +1) + dim]);
        for(j=0;j<dim;j++)
            printf("%g   ",z_t_seq[n * (dim +1) + j]);
        printf("\n");
        n++;
    } while(z_t_seq[n * (dim +1) + dim] != 0);
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

void runge_kutta_lorenz()
{
    double z0[]={1,1,20}, tau = 0.001, T = 40, *z_seq;
    int dim=3;

    z_seq = rk4(z0, tau, rk_lorenz_func, T, dim);
    rk4_print(z_seq, dim, T, tau);
}

double runge_kutta_benchmark(double tau, double T)
{
    double z0[]={1,1,20}, *z_seq;
    int dim=3, N;

    N = T/tau;

    z_seq = rk4(z0, tau, rk_lorenz_func, T, dim);
    return z_seq[2 * N + N - 1];
}

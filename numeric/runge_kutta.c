#include "runge_kutta.h"

double * rk4(double *z0, double tau, double * (*dgl)(),double T,int dim)
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

        zout = rk4_step(zout,t,tau,dgl,dim);

        for(j=0;j<dim;j++)
            z_seq[j * N + n] = zout[j];
    }
    free(zout);
    return z_seq;
}

double * rk4a(double *z0, double tau, double * (*dgl)(),
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
        }
        for(j=0;j<dim;j++)
            zout[j] = zt_seq[(n-1) * (dim+1) + j];

        tau = rk4_get_new_tau(zout, t, tau, dgl, dim, r_desired);
        t += tau;

        zout = rk4_step(zout,t,tau,dgl,dim);

        zt_seq[n * (dim+1) + dim] = t;
        for(j=0;j<dim;j++)
            zt_seq[n * (dim+1) + j] = zout[j];
    }
    free(zout);

    zt_seq[(n +1)* (dim+1) + dim] = 0;

    tmp = (double*) realloc (zt_seq, (dim+1) * (n+2) * sizeof(double));
    if (tmp != NULL) zt_seq=tmp;
    else alloc_fail();

    return zt_seq;
}

double * rk4_step(double *z, double t, double tau, double *  (*dgl)(),
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
        ztmp[i] = z[i]+ tau/6*(Hs[0][i]+2*Hs[1][i]+2*Hs[2][i]+Hs[3][i]);

    for(i=0;i<4;i++)
        free(Hs[i]);
    return ztmp;
}

double rk4_get_new_tau(double *z, double t, double tau,
                           double * (*dgl)(), int dim, double r_desired)
{
    int i;
    double S = 0.9, tau_neu, r, tmp1, tmp2;
    double *z1, *z2;
    z1    = (double *) calloc(dim, sizeof(double));
    if(z1 == NULL) alloc_fail();
    z2    = (double *) calloc(dim, sizeof(double));
    if(z2 == NULL) alloc_fail();

    z1 = rk4_step(z,t,tau,dgl,dim);
    z2 = rk4_step(z,t,tau/2,dgl,dim);
    z2 = rk4_step(z2,t,tau/2,dgl,dim);

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

double * rk_test_func(double *r, double t, int dim)
{
    int i;
    double *out;
    out = (double *) calloc(dim, sizeof(double));
    if(out == NULL) alloc_fail();

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
    if(out == NULL) alloc_fail();
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
    double z0[]={0,0}, tau = 0.01, T = 2, *zt_seq;
    int dim=1;

    zt_seq = rk4a(z0, tau, rk_test_func, T, dim, 0.0002);
    rk4a_print(zt_seq, dim);
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


double * rk4a_interpolate(double *zt_seq, int dim, int freq)
{
    double T, t1=0, t2=0, t_start, *tmp, *tmp2, *z1, *z2, *zt_out;
    int n = 0, m=0, j, N = 1000;

    z1 = (double *) calloc(dim, sizeof(double));
    if(z1 == NULL) alloc_fail();
    z2 = (double *) calloc(dim, sizeof(double));
    if(z2 == NULL) alloc_fail();
    tmp = (double *) calloc(dim, sizeof(double));
    if(tmp == NULL) alloc_fail();

    zt_out = (double *) calloc((dim+1) * N, sizeof(double));
    if(zt_out == NULL) alloc_fail();

    t_start = zt_seq[0 + dim];

    T = 1/freq;
    do
    {
        n++;
        if(t1 > m*T && t2-t_start > T/2)
        {
            for(j=0;j<dim;j++)
                zt_out[m * (dim+1) + j] = tmp[j]/(t2-t_start);
            zt_out[m * (dim+1) + dim] = m*T;
            m++;

            t_start = zt_seq[n * (dim+1) + dim];

            if(m>N-2)
            {
                N+=1000;
                tmp2 = (double*) realloc(zt_out, (dim+1)*N* sizeof(double));
                if (tmp != NULL) zt_out=tmp2;
                else alloc_fail();
            }
        }
        t2 = t1;
        t1 = zt_seq[n * (dim+1) + dim];
        for(j=0;j<dim;j++)
        {
            z2[j] = z1[j];
            z1[j] = zt_seq[n * (dim+1) + j];

            tmp[j] = (z1[j] + z2[j]) / 2 * (t2-t1);
        }
    } while(zt_seq[n * (dim +1) + dim] != 0);
    free(z1); free(z2); free(tmp);
    return zt_out;
}

void runge_kutta_lorenz()
{
    double z0[]={1,1,20}, tau = 0.001, T = 40, *z_seq;
    int dim=3;

    z_seq = rk4(z0, tau, rk_lorenz_func, T, dim);
    rk4_print(z_seq, dim, T, tau);
}

void runge_kutta_lorenz_adaptiv()
{
    double z0[]={1,1,20}, tau = 0.001, T = 40, r_desired = 1e-6, *zt_seq;
    int dim=3;

    zt_seq = rk4a(z0, tau, rk_lorenz_func, T, dim, r_desired);
    rk4a_print(zt_seq, dim);
}

double runge_kutta_benchmark(double tau, double T)
{
    double z0[]={1,1,20}, *z_seq;
    int dim=3, N;

    N = T/tau;

    z_seq = rk4(z0, tau, rk_lorenz_func, T, dim);
    return z_seq[2 * N + N - 1];
}

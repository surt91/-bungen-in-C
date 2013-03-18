#include "rk4_lorenz.h"

void rk_lorenz_func(double *r, double t, int dim, double *out)
{
    // Lorenz Modell
    double sigma, r_param, b;
    double x, y, z;
    sigma   = 10;
    r_param = 28;
    b       = 8/3;

    x=r[0]; y=r[1]; z=r[2];

    out[0] = sigma*(y-x);
    out[1] = r_param*x - y - x*z;
    out[2] = x*y - b*z;
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
    double z0[]={1,1,20}, tau = 0.001, T = 40, r_desired = 1e-10, *zt_seq;
    int dim=3;

    zt_seq = rk4a(z0, tau, rk_lorenz_func, T, dim, r_desired);
    //~ rk4a_print(zt_seq, dim);
    rk4a_paint(zt_seq, dim, 100);
}

void runge_kutta_lorenz_ensemble_adaptiv()
{
    #define NUM 250
    double tau = 0.001, T = 5*60/4, r_desired = 1e-10;
    double z0[NUM][3], r, p[3] = {1,1,20};
    double *(zt_seq[NUM]), *(zt_out[NUM]);
    int dim=3, freq = 100,i;

    int n=0;
    double x[NUM], y[NUM], t;

    for(i=0;i<NUM;i++)
    {
        r = rand() / (double)RAND_MAX * 0.5 - 0.5;
        z0[i][0] = p[0] + r; z0[i][1] = p[1] + r; z0[i][2] = p[2];
        zt_seq[i] = rk4a(z0[i], tau, rk_lorenz_func, T, dim, r_desired);
        zt_out[i] = rk4a_interpolate(zt_seq[i], dim, freq);
        free(zt_seq[i]);
    }
    do
    {
        n++;
        for(i=0;i<NUM;i++)
        {
            x[i] = zt_out[i][n * (dim +1) + 0];
            y[i] = zt_out[i][n * (dim +1) + 1];
        }
        t=zt_out[0][n * (dim +1) + dim];
        // paint frame
        plot_time_series_paint_frame(x, y, t, NUM, 52, 52);
    } while(t != 0);
}

double runge_kutta_benchmark(double tau, double T)
{
    double z0[]={1,1,20}, *z_seq;
    int dim=3, N;

    N = T/tau;

    z_seq = rk4(z0, tau, rk_lorenz_func, T, dim);
    return z_seq[2 * N + N - 1];
}

#include "n_harm_osz.h"

#define CAIRO_XSCALE 16
#define CAIRO_YSCALE 9
#define CAIRO_SCALE 120
#define SCALE 10
#define VMAX 50.0

#define VMIN(X) ((X) < (1) ? (X) : (1))

void n_harm_osz_step(r_type *r, double dt, double k)
{
    int i, n, N;
    double x, y, z;
    double dx, dy, dz, dr, c;

    N = r->N;
    for(n=0;n<N;n++)
    {
        x = r->x[n];
        y = r->y[n];
        z = r->z[n];
        for(i=0;i<N;i++)
        {
            if(i==n)
                continue;
            dx = r->x[i] - x;
            dy = r->y[i] - y;
            dz = r->z[i] - z;

            dr = sqrt(dx*dx + dy*dy + dz*dz);

            // F = - k r
            c = k * dr * dt;

            r->vx[n] += dx * c;
            r->vy[n] += dy * c;
            r->vz[n] += dz * c;
        }
    }

    for(n=0;n<N;n++)
    {
        r->x[n] += r->vx[n] * dt;
        r->y[n] += r->vy[n] * dt;
        r->z[n] += r->vz[n] * dt;
    }
    r->t++;
}

void n_harm_osz_print_cairo(r_type r, int t)
{
    int i;
    cairo_surface_t *surface;
    cairo_t *cr;
    char filename[40];

    sprintf(filename, "n_harm_osz/n_harm_osz_%04d.png", t);

    surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, CAIRO_XSCALE*CAIRO_SCALE, CAIRO_YSCALE*CAIRO_SCALE);
    cr = cairo_create (surface);

    /* weißer Hintergrund */
    cairo_set_source_rgb (cr, 1, 1, 1);
    cairo_paint (cr);

    /* Drawing code goes here */
    for(i=0; i < r.N ; i++)
    {
        cairo_set_source_rgb (cr, VMIN(fabs(r.vx[i]/VMAX)), VMIN(fabs(r.vy[i]/VMAX)), VMIN(fabs(r.vz[i]/VMAX)));
        cairo_rectangle (cr, (int) (r.x[i]*CAIRO_SCALE*0.8+0.1*CAIRO_XSCALE*CAIRO_SCALE), (int) (r.y[i]*CAIRO_SCALE*0.8+0.1*CAIRO_YSCALE*CAIRO_SCALE), 1*SCALE, 1*SCALE);
        cairo_fill (cr);
    }

    /* Write output and clean up */
    cairo_surface_write_to_png (surface, filename);
    cairo_destroy (cr);
    cairo_surface_destroy (surface);
}

void n_harm_osz_main()
{
    int N = 100, n, T = 10000, i;
    r_type r;

    r.t = 0;
    r.N = N;
    r.x = (double *) malloc(N * sizeof(double));
    r.y = (double *) malloc(N * sizeof(double));
    r.z = (double *) malloc(N * sizeof(double));
    r.vx = (double *) malloc(N * sizeof(double));
    r.vy = (double *) malloc(N * sizeof(double));
    r.vz = (double *) malloc(N * sizeof(double));

    for(n=0;n<N;n++)
    {
        //initialisiere Startpunkte
        r.x[n] = rand()/ ((double) RAND_MAX) * CAIRO_XSCALE;
        r.y[n] = rand()/ ((double) RAND_MAX) * CAIRO_YSCALE;
        r.z[n] = 0;
        //initialisiere Startgeschwindigkeiten
        r.vx[n] = 0;
        r.vy[n] = 0;
        r.vz[n] = 0;
    }

    for(n=0;n<T;n++)
    {
        for(i=0;i<50;i++)
            n_harm_osz_step(&r, 0.001/50, 1);
        n_harm_osz_print_cairo(r, n);
        if(n%100 == 0)
            printf("% 5d/% 5d\n", n, T);
    }
}

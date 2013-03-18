#include "plot_time_series.h"
#define CAIRO_SCALE 12

void rk4a_paint(double *zt_seq, int dim, int freq)
{
    int n=0;
    double *zt_out;

    zt_out = rk4a_interpolate(zt_seq, dim, freq);
    rk4a_print(zt_out, dim);
    do
    {
        n++;
        // paint frame
        plot_time_series_paint_frame(&zt_out[n * (dim +1) + 0], &zt_out[n * (dim +1) + 1], zt_out[n * (dim +1) + dim], 1, 50, 50);
    } while(zt_out[n * (dim +1) + dim] != 0);
}

double * rk4a_interpolate(double *zt_seq, int dim, int freq)
{
    double T, *tmp2, *zt_out;
    int n = 0, m=0, j=0, N = 1000;

    zt_out = (double *) calloc((dim+1) * N, sizeof(double));
    if(zt_out == NULL) alloc_fail();

    T = 1./freq;
    do
    {
        n++;
        if(zt_seq[n * (dim+1) + dim] > ((double)m)*T)
        {
            for(j=0;j<dim;j++)
                zt_out[m * (dim+1) + j] = zt_seq[n * (dim+1) + j];
            zt_out[m * (dim+1) + dim] = ((double)m)*T;
            m++;

            if(m>N-2)
            {
                N+=1000;
                tmp2 = (double*) realloc(zt_out, (dim+1)*N* sizeof(double));
                if (tmp2 != NULL) zt_out=tmp2;
                else alloc_fail();
            }
        }
    } while(zt_seq[n * (dim +1) + dim] != 0);
    zt_out = (double*) realloc(zt_out, (dim+1)*(m+2)* sizeof(double));
    return zt_out;
}

int plot_time_series_paint_frame(double * x, double * y, double t, int n, int x_max, int y_max)
{
    int i;
    cairo_surface_t *surface;
    cairo_t *cr;
    char filename[40];

    sprintf(filename, "rk4/rk4_%05.0f.png", t*100);

    surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, CAIRO_SCALE*x_max, CAIRO_SCALE*y_max);
    cr = cairo_create (surface);
    cairo_scale (cr, CAIRO_SCALE, CAIRO_SCALE);

    /* weißer Hintergrund */
    cairo_set_source_rgb (cr, 1, 1, 1);
    cairo_paint (cr);

    /* Drawing code goes here */
    cairo_set_source_rgb (cr, 0, 0, 0);
    for(i=0;i<n;i++)
    {
        cairo_rectangle (cr, x[i]+x_max/2, y[i]+y_max/2, 1, 1);
        //~ cairo_rectangle (cr, x[i]+x_max/2, y[i], 1, 1);
    }
    cairo_fill (cr);

    /* Write output and clean up */
    cairo_surface_write_to_png (surface, filename);
    cairo_destroy (cr);
    cairo_surface_destroy (surface);

    return 0;
}

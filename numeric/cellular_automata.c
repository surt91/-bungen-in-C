#include "cellular_automata.h"
#define CAIRO_SCALE 1

// returns 0, if every entry is 0, else 1
int ca_get_next_status(uint8_t *status, int x, uint8_t rule)
{
    int i;
    int all_zero = 1;
    uint8_t *tmp_status;
    uint8_t l,c,r;
    uint8_t pack;

    int periodic_boundary = 1;

    tmp_status = (uint8_t *) calloc(x, sizeof(uint8_t));

    for(i=0;i<x;i++)
    {
        if(status[i])
        {
            all_zero = 0;
            break;
        }
    }
    if(all_zero)
        return 0;

    for(i=0;i<x;i++)
    {
        if(i-1 >= 0)
            l = status[i-1];
        else
        {
            if(periodic_boundary)
                l = status[x-1];
            else
                l = 0;
        }
        c = status[i];
        if(i+1 < x)
            r = status[i+1];
        else
        {
            if(periodic_boundary)
                r = status[0];
            else
                r = 0;
        }

        // pack bytes
        pack = ((l & 1) << 2) | ((c & 1) << 1) | (r & 1);
        // 0 <= pack <= 7

        switch(pack)
        {
            case 0b000:
                if(rule & 1<<0)
                    tmp_status[i] = 1;
                break;
            case 0b001:
                if(rule & 1<<1)
                    tmp_status[i] = 1;
                break;
            case 0b010:
                if(rule & 1<<2)
                    tmp_status[i] = 1;
                break;
            case 0b011:
                if(rule & 1<<3)
                    tmp_status[i] = 1;
                break;
            case 0b100:
                if(rule & 1<<4)
                    tmp_status[i] = 1;
                break;
            case 0b101:
                if(rule & 1<<5)
                    tmp_status[i] = 1;
                break;
            case 0b110:
                if(rule & 1<<6)
                    tmp_status[i] = 1;

                break;
            case 0b111:
                if(rule & 1<<7)
                    tmp_status[i] = 1;
                break;
        }
    }

    memcpy(status, tmp_status, x);

    free(tmp_status);

    return 1;
}

void ca_print_on_stdout(uint8_t *out, int x, int y)
{
    int i, j;

    for(j=0;j<y;j++)
    {
        for(i=0;i<x;i++)
            if(out[i+x*j])
                printf("*");
            else
                printf(" ");
        printf("\n");
    }
}

int ca_paint(uint8_t *out, int x, int y, char *filename)
{
    int i, j;
    cairo_surface_t *surface;
    cairo_t *cr;

    surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, CAIRO_SCALE*x, CAIRO_SCALE*y);
    cr = cairo_create (surface);
    cairo_scale (cr, CAIRO_SCALE, CAIRO_SCALE);

    /* weißer Hintergrund */
    cairo_set_source_rgb (cr, 1, 1, 1);
    //~ cairo_set_source_rgb (cr, 0, 0, 0);
    cairo_paint (cr);

    /* Drawing code goes here */
    //~ cairo_set_source_rgb (cr, 0, 0, 0);
    cairo_set_source_rgb (cr, 0, 1, 0);
    for(j=0; j < y; j++)
        for(i=0; i < x ; i++)
            if(out[i+x*j])
                cairo_rectangle (cr, i, j, 1, 1);
    cairo_fill (cr);

    /* Write output and clean up */
    cairo_surface_write_to_png (surface, filename);
    cairo_destroy (cr);
    cairo_surface_destroy (surface);

    return 0;
}

void ca_init_status_random(uint8_t *status, int x)
{
    int i;
    for(i=0;i<x;i++)
    {
        status[i] = !(rand()%100);
    }
}

void ca_init_status_seed(uint8_t *status, int x)
{
    int i;
    for(i=0;i<x;i++)
    {
        status[i] = 0;
    }
    status[x/2] = 1;
}

void ca_main(uint8_t rule, int x, int y, uint8_t *out, int random_seed)
{
    int i;

    uint8_t *status;

    status = (uint8_t *) malloc(x * sizeof(uint8_t));

    if(random_seed)
        ca_init_status_random(status, x);
    else
        ca_init_status_seed(status, x);

    for(i=0;i<y;i++)
    {
        memcpy(out+i*x, status, x);
        ca_get_next_status(status, x, rule);
    }

    free(status);
}

void ca_every_rule()
{
    uint8_t *out;

    int x = 2001;
    int y = 1000;

    uint8_t rule;
    char filename[40];

    int i;
    int random;

    out = (uint8_t *) calloc( x * y, sizeof(uint8_t));

    for(random=0;random<=1;random++)
        for(i=0;i<256;i++)
        {
            rule = i;
            if(random)
                sprintf(filename, "wolfram/wolfram_random_seed_rule_%03d.png", rule);
            else
                sprintf(filename, "wolfram/wolfram_rule_%03d.png", rule);

            ca_main(rule, x, y, out, random);

            ca_paint(out, x, y, filename);
        }

    free(out);
}

void ca_cli()
{
    uint8_t *out;

    int x = 81;
    int y = 40;

    uint8_t rule;
    int tmp;

    printf("Rule? ");
    scanf("%d", &tmp);

    if(tmp>255)
        return;
    else
        rule = (uint8_t) tmp;

    out = (uint8_t *) calloc( x * y, sizeof(uint8_t));

    ca_main(rule, x, y, out, 0);

    ca_print_on_stdout(out, x, y);

    free(out);
}

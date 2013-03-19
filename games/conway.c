/***
 *  Conways Game of Live
 *
 *  27.09.2011
 *  Hendrik Schawe <hendrik.schawe@gmail.com>
 ***/

#include "conway.h"
#define CAIRO_SCALE 15

void conway_gleiter()
{
    struct conway_map map;
    map.gen=32;
    map.x = map.y = 10;
    map = conway_init_map(map);
    conway_set_status(0, 2, map, 1);
    conway_set_status(1, 2, map, 1);
    conway_set_status(2, 2, map, 1);
    conway_set_status(2, 1, map, 1);
    conway_set_status(1, 0, map, 1);
    conway_main(map);
    free(map.status);
    return;
}

void conway_random()
{
    int i, j, state;
    struct conway_map map;
    map.gen=300;
    map.x = map.y = 100;
    map = conway_init_map(map);
    for(i=0; i < map.x ; i++)
            for(j=0; j < map.y; j++)
            {
                state = (rand()%100 < 31 ? 1 : 0);
                conway_set_status(i, j, map, state);
            }
    conway_main(map);
    free(map.status);
    return;
}

void conway_pulsator()
{
    struct conway_map map;
    map.gen=15;
    map.x = 20;
    map.y = 20;
    map = conway_init_map(map);
    conway_set_status( 6,  8, map, 1);
    conway_set_status( 7,  8, map, 1);
    conway_set_status( 8,  8, map, 1);
    conway_set_status( 9,  8, map, 1);
    conway_set_status(10,  8, map, 1);
    conway_set_status(11,  8, map, 1);
    conway_set_status(12,  8, map, 1);
    conway_set_status(13,  8, map, 1);
    conway_set_status( 6, 10, map, 1);
    conway_set_status( 7, 10, map, 1);
    conway_set_status( 8, 10, map, 1);
    conway_set_status( 9, 10, map, 1);
    conway_set_status(10, 10, map, 1);
    conway_set_status(11, 10, map, 1);
    conway_set_status(12, 10, map, 1);
    conway_set_status(13, 10, map, 1);
    conway_set_status( 6,  9, map, 1);
    conway_set_status( 8,  9, map, 1);
    conway_set_status( 9,  9, map, 1);
    conway_set_status(10,  9, map, 1);
    conway_set_status(11,  9, map, 1);
    conway_set_status(13,  9, map, 1);
    conway_main(map);
    free(map.status);
    return;
}

void conway_HWSS()
{
    struct conway_map map;
    map.gen=200;
    map.x = 100;
    map.y = 10;
    map = conway_init_map(map);
    conway_set_status(1, 3, map, 1);
    conway_set_status(2, 3, map, 1);
    conway_set_status(3, 3, map, 1);
    conway_set_status(4, 3, map, 1);
    conway_set_status(5, 3, map, 1);
    conway_set_status(6, 3, map, 1);
    conway_set_status(0, 4, map, 1);
    conway_set_status(0, 6, map, 1);
    conway_set_status(2, 7, map, 1);
    conway_set_status(3, 7, map, 1);
    conway_set_status(3, 7, map, 1);
    conway_set_status(5, 6, map, 1);
    conway_set_status(6, 5, map, 1);
    conway_set_status(6, 4, map, 1);
    conway_main(map);
    free(map.status);
    return;
}

void conway_stabil()
{
    struct conway_map map;
    map.gen=19;
    map.x = 19;
    map.y = 19;
    map = conway_init_map(map);
    conway_set_status( 8, 11, map, 1);
    conway_set_status( 9, 11, map, 1);
    conway_set_status(10, 11, map, 1);
    conway_set_status( 9,  9, map, 1);
    conway_set_status(10,  9, map, 1);
    conway_set_status( 9,  8, map, 1);
    conway_set_status(10,  8, map, 1);
    conway_set_status( 9,  7, map, 1);
    conway_set_status(10,  7, map, 1);
    conway_main(map);
    free(map.status);
    return;
}

int conway_set_status(int x, int y, struct conway_map map, char state)
{
    map.status[y * map.x + x] = state;
    return 0;
}
int conway_get_status(int x, int y, struct conway_map map)
{
    return map.status[y * map.x + x];
}

struct conway_map conway_init_map(struct conway_map map)
{
    map.status = (char *) calloc(map.x * map.y, sizeof(char));
    return map;
}

void conway_main(struct conway_map map)
{
    int i, j, n=0, m;
    struct conway_map tmp;
    tmp.x = map.x;
    tmp.y = map.y;
    tmp = conway_init_map(tmp);

    for(n=0;n<map.gen;n++)
    {
        conway_draw(map, n+1);
        conway_paint(map, n+1);
        for(i=0; i < map.x ; i++)
            for(j=0; j < map.y; j++)
                conway_set_status(i, j, tmp, conway_update_status(i, j, map));
        for(m=0; m<tmp.y*tmp.x;m++)
            map.status[m] = tmp.status[m];
    }
    free(tmp.status);
    return;
}

int conway_draw(struct conway_map map, int gen)
{
    int i,j;
    printf("\nGeneration %03d\n", gen);
    for(i=0; i < map.x; i++)
        printf("-");
    printf("--\n");
    for(j=0; j < map.y ; j++)
    {
        printf("|");
        for(i=0; i < map.x; i++)
        {
            if(conway_get_status(i, j, map))
                printf("o");
            else
                printf(" ");
        }
        printf("|\n");
    }
    printf("--");
    for(i=0; i < map.x; i++)
        printf("-");
    printf("\n");

    return 0;
}

int conway_paint(struct conway_map map, int gen)
{
    int i, j;
    cairo_surface_t *surface;
    cairo_t *cr;
    char filename[40];

    sprintf(filename, "conway/conwayGoL_%03d.png", gen);

    surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, CAIRO_SCALE*map.x, CAIRO_SCALE*map.y);
    cr = cairo_create (surface);
    cairo_scale (cr, CAIRO_SCALE, CAIRO_SCALE);

    /* weißer Hintergrund */
    cairo_set_source_rgb (cr, 1, 1, 1);
    cairo_paint (cr);

    /* Drawing code goes here */
    cairo_set_source_rgb (cr, 0, 0, 0);
    for(i=0; i < map.x ; i++)
        for(j=0; j < map.y; j++)
            if(conway_get_status(i, j, map))
                cairo_rectangle (cr, i, j, 1, 1);
    cairo_fill (cr);

    /* Write output and clean up */
    cairo_surface_write_to_png (surface, filename);
    cairo_destroy (cr);
    cairo_surface_destroy (surface);

    return 0;
}

char conway_update_status(int x, int y, struct conway_map map)
{
    int counter = 0, i, j, state;
    state = conway_get_status(x, y, map);
    for(i = x-1; i <= x+1 ; i++)
        for(j = y-1; j <= y+1; j++)
            if(j >= 0 && j < map.y && i >= 0 && i < map.x)
                if(i!=x || j!=y)
                    if(conway_get_status(i, j, map))
                        counter++;
    return conway_dead_or_alive(counter, state);
}

char conway_dead_or_alive(int counter, int state)
{
    if(counter==3 || (state == 1 && counter == 2))
        return 1;
    return 0;
}

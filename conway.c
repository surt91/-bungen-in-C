#include "conway.h"

//~ #define GENERATIONEN 32
#define CAIRO_SCALE 15
// Conways Game of Live

void conway_gleiter()
{
    struct conway_map map;
    map.gen=32;
    map.x = map.y = 10;
    map.status = (char *) calloc(map.x * map.y, sizeof(char));
    conway_set_status(0, 2, map, 1);
    conway_set_status(1, 2, map, 1);
    conway_set_status(2, 2, map, 1);
    conway_set_status(2, 1, map, 1);
    conway_set_status(1, 0, map, 1);
    conway_main(map);
    return;
}

void conway_random()
{
    return;
}

void conway_pulsator()
{
    return;
}

void conway_HWSS()
{
    struct conway_map map;
    map.gen=200;
    map.x = 100;
    map.y = 10;
    map.status = (char *) calloc(map.x * map.y, sizeof(char));
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
    return;
}

int conway_set_status(int x, int y, struct conway_map map, char state)
{
    map.status[y * map.x + x] = state;
    return 1;
}
int conway_get_status(int x, int y, struct conway_map map)
{
    return map.status[y * map.x + x];
}

void conway_main(struct conway_map map)
{
    int i, j, n=0, m;
    struct conway_map tmp;
    tmp.x = map.x;
    tmp.y = map.y;
    tmp.status = (char *) calloc(tmp.x * tmp.y, sizeof(char));

    for(n=0;n<map.gen;n++)
    {
        conway_draw(map, n+1);
        conway_paint(map, n+1);
        for(i=0; i < map.x ; i++)
            for(j=0; j < map.y; j++)
                conway_set_status(i, j, tmp, conway_update_status(i, j, map));
                //~ tmp.status[i* tmp.x+j] = conway_update_status(i, j, map);
        for(m=0; m<tmp.y*tmp.x;m++)
            map.status[m] = tmp.status[m];
    }
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

#include "conway.h"

#define GENERATIONEN 10
// Conways Game of Live

void conway_test()
{
    struct conway_map conway_glider;
    conway_glider.x = conway_glider.y = 10;
    conway_glider.status = (short *) calloc(conway_glider.x * conway_glider.y, sizeof(short));
    conway_glider.status[7*10+9] = 1;
    conway_glider.status[7*10+8] = 1;
    conway_glider.status[7*10+7] = 1;
    conway_glider.status[8*10+7] = 1;
    conway_glider.status[9*10+8] = 1;
    conway_main(conway_glider);
    return;
}

void conway_main(struct conway_map map)
{
    int i, j, n,m;
    struct conway_pos now;
    struct conway_map tmp;
    tmp.x = map.x;
    tmp.y = map.y;
    tmp.status = (short *) calloc(tmp.x * tmp.y, sizeof(short));

    for(n=0;n<GENERATIONEN;n++)
    {
        conway_draw(map, n+1);
        for(i=0; i < map.x ; i++){
            for(j=0; j < map.y; j++)
            {
                now.x = i;
                now.y = j;
                tmp.status[i* tmp.x+j] = conway_update_status(map,now);
            }
        }
        for(m=0; m<tmp.y*tmp.x;m++)
            map.status[m] = tmp.status[m];
    }
    return;
}

void conway_draw(struct conway_map map, int gen)
{
    int i,j;
    printf("\nGeneration %03d\n", gen);
    for(j=0; j < map.y; j++)
        printf("-");
    printf("--\n");
    for(i=0; i < map.x ; i++)
    {
        printf("|");
        for(j=0; j < map.y; j++)
        {
            if(map.status[i* map.x+j])
                printf("o");
            else
                printf(" ");
        }
        printf("|\n");
    }
    printf("--");
    for(j=0; j < map.y; j++)
        printf("-");
    printf("\n");
}

int conway_update_status(struct conway_map map, struct conway_pos pos)
{
    int counter = 0, i, j, state;
    state = map.status[pos.x * map.x + pos.y];
    for(i = pos.x-1; i <= pos.x+1 ; i++)
    {
        for(j = pos.y-1; j <= pos.y+1; j++)
        {
            if(j > 0 && j < map.y && i > 0 && i < map.x){
                if(i!=pos.x || j!=pos.y){
                    if(map.status[i * map.x + j]){
                        counter++;
                    }}
                    }
        }
    }
    return conway_dead_or_alive(counter, state);
}

int conway_dead_or_alive(int counter, int state)
{
    if(counter==3 || (state == 1 && counter == 2))
        return 1;
    return 0;
}

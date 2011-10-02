/***
 *  Snake
 *
 *  02.10.2011
 *  Hendrik Schawe <hendrik.schawe@gmail.com>
 ***/

#include "snake.h"

void snake()
{
    struct snake_map map;
    //~ srand( (unsigned) time(NULL) ) ;

    map.x = map.y = 15;
    map.length = 3;
    map.schlange = (int *) calloc(map.x * map.y, sizeof(int));

    map.kopf = snake_random_pos(map.kopf, map);
    map.futter = snake_random_pos(map.futter, map);
    //~ map.schlange[map.kopf[1] * map.x + map.kopf[0]] = 1;

    // Hauptspielschleife
    while(1)
    {
        switch (snake_dead_or_eating(map))
        {
            case 2:
                printf ("Leider verloren");
                return;
            case 1:
                map.length++;
            case 0:
        }

        map = snake_koerper(map);
        map.schlange[map.kopf[1] * map.x + map.kopf[0]] = 1;
        snake_draw();
    }
}

void snake_draw(struct snake_map map)
{
    int i,j;
    for(i=0; i < map.x; i++)
        printf("-");
    printf("--\n");
    for(j=0; j < map.y; j++)
    {
        printf("|");
        for(i=0; i < map.x; i++)
        {
            if(snake_get_status(i, j, map))
                printf("o");
            else if(map.kopf[i] && map.kopf[j])
                printf("O");
            else if(map.futter[i] && map.futter[j])
                printf("X");
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

int snake_set_status(int *pos, struct snake_map map, char state)
{
    map.schlange[pos[1] * map.x + pos[0]] = state;
    return 0;
}
int snake_get_status(int *pos, struct snake_map map)
{
    return map.schlange[pos[1] * map.x + pos[0]];
}

int *snake_random_pos(int *pos, struct snake_map map;)
{
    do
    {
        cordX = rand()%map.x;
        cordY = rand()%map.y;
    } while (map.schlange[cordY * map.x + cordX])
    return pos[crodX,cordY];
}

int snake_dead_or_eating(struct snake_map map)
{
    int i;
    // 0: leeres Feld
    // 1: Essen
    // 2: tot
    if(map.kopf[0] == map.futter[0] && map.kopf[1] == map.futter[1])
        return 1;
    else if (map.schlange[map.kopf[1] * map.x + map.kopf[0]])
        return 2;
    return 0;
}

struct snake_map snake_koerper(struct snake_map map)
{
    int i;
    for(i=0;i<map.x*map.y;i++)
        if(map.schlange[i])
            map.schlange[i]++;
    return map;
}

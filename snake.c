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
    int runde = 0, status = 1;
    //~ srand( (unsigned) time(NULL) ) ;

    map.x = map.y = 15;
    map.length = 3;
    map.schlange = (int *) calloc(map.x * map.y, sizeof(int));

    snake_random_pos(map.kopf, map);
    snake_random_pos(map.futter, map);
    //~ map.schlange[map.kopf[1] * map.x + map.kopf[0]] = 1;

    map.kopf[0]=1;
    map.futter[0]=1;

    // Hauptspielschleife
    while(status)
    {
        snake_draw(map);
        map.kopf[0]++;
        status = snake_rand(map);
        switch (snake_dead_or_eating(map))
        {
            case 1:
                map.length++;
                printf ("Mampf\n");
                break;
            case 0:
                break;
            case 2:
                status = 0;
                printf("In den Schwanz gebissen.\nVerloren");
                break;
        }
        printf("Runde:  %03d\nPunkte: %03d\n%d\n",runde++, map.length, status);
        map = snake_koerper(map);
        map.schlange[map.kopf[1] * map.x + map.kopf[0]] = 1;

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
            if(map.kopf[0] == i && map.kopf[1] == j)
                printf("O");
            else if(snake_get_status(i, j, map))
                printf("o");
            else if(map.futter[0] == i && map.futter[1] == j)
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

    return;
}

int snake_set_status(int x, int y, struct snake_map map, char state)
{
    map.schlange[y * map.x + x] = state;
    return 0;
}
int snake_get_status(int x, int y, struct snake_map map)
{
    return map.schlange[y * map.x + x];
}

void snake_random_pos(int *pos, struct snake_map map)
{
    int cordX, cordY;
    do
    {
        cordX = rand()%map.x;
        cordY = rand()%map.y;
    } while (map.schlange[cordY * map.x + cordX]);
    pos[0]=cordX;
    pos[1]=cordY;
    return;
}

int snake_rand(struct snake_map map)
{
    if(map.kopf[0] >= map.x || map.kopf[1] >= map.y)
    {
        printf("Gegen die Wand gelaufen.\nVerloren");
        return 0;
    }
    return 1;
}

int snake_dead_or_eating(struct snake_map map)
{
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
    {
        if(map.schlange[i])
            map.schlange[i]++;
        if(map.schlange[i] > map.length)
            map.schlange[i] = 0;
    }
    return map;
}

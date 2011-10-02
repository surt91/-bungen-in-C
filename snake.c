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
    int runde=0;
    //~ srand( (unsigned) time(NULL) ) ;

    map.x = map.y = 15;
    map.length = 3;
    map.schlange = (int *) calloc(map.x * map.y, sizeof(int));

    snake_random_pos(map.kopf, map);
    snake_random_pos(map.futter, map);
    //~ map.schlange[map.kopf[1] * map.x + map.kopf[0]] = 1;

    // Hauptspielschleife
    while(1)
    {
        printf("Runde %03d\n",runde++);
        switch (snake_dead_or_eating(map))
        {
            case 2:
                printf ("Leider verloren\n");
                return;
            case 1:
                map.length++;
            case 0:
                break;
        }

        map = snake_koerper(map);
        map.schlange[map.kopf[1] * map.x + map.kopf[0]] = 1;
        snake_draw(map);
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
        if(map.schlange[i])
            map.schlange[i]++;
    return map;
}

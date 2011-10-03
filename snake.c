/***
 *  Snake
 *
 *  02.10.2011
 *
 *  License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>.
 *  This is free software: you are free to change and redistribute it."
 *  There is NO WARRANTY, to the extent permitted by law.
 *
 *  Hendrik Schawe <hendrik.schawe@gmail.com>
 *
 ***/

#include "snake.h"

static const char *titel = "\
     ____  _   _    _    _  _______ \n\
    / ___|| \\ | |  / \\  | |/ / ____|\n\
    \\___ \\|  \\| | / _ \\ | ' /|  _|  \n\
     ___) | |\\  |/ ___ \\| . \\| |___ \n\
    |____/|_| \\_/_/   \\_\\_|\\_\\_____|\n\
                                     \n";
static const char *verloren ="\
__     __        _                      _ \n\
\\ \\   / /__ _ __| | ___  _ __ ___ _ __ | |\n\
 \\ \\ / / _ \\ '__| |/ _ \\| '__/ _ \\ '_ \\| |\n\
  \\ V /  __/ |  | | (_) | | |  __/ | | |_|\n\
   \\_/ \\___|_|  |_|\\___/|_|  \\___|_| |_(_)\n\
                                          \n";

void snake_menu()
{
    int exit = 0, m, level = 3, torus = 0;
    char k;

    while(!exit)
    {
        m=0;
        printf("%s\n", titel);
        printf("Spiele Snake:  1\n");
        printf("Einstellungen: 2\n");
        printf("Beende Snake:  3\n");
        scanf("%d", &m);
        switch(m)
        {
            case 2:
                printf("Schwierigkeitsgrad zwischen 1 und 9 [3]\n");
                getchar();
                k = getchar();
                level = k-48;
                if(level < 1 || level >9)
                    level = 3;
                printf("Spiele auf Level %d\n", level);

                printf("Torusförmiges Spielfeld y/n [n]\n");
                getchar();
                k = getchar();
                torus = k == 'y' ? 1 : 0;
                if(torus)
                    printf("Spiele auf Torusförmigem Spielfeld\n");
                else
                    printf("Spiele auf begrenztem Spielfeld\n");

                break;
            case 1:
                snake(level, torus);
                break;
            case 3:
                return;
                break;
        }
    }
}

void snake(int schwierigkeit, int torus)
{
    struct snake_map map;
    int status = 1;
    static const int stufen[9] =
    {LEVEL1, LEVEL2, LEVEL3, LEVEL4, LEVEL5, LEVEL6, LEVEL7, LEVEL8, LEVEL9};
    map.level = stufen[schwierigkeit];
    map.richtung = 's';
    map.runde = 0;
    //~ srand( (unsigned) time(NULL) ) ;

    map.x = 30;
    map.y = 15;
    map.length = 3;
    map.schlange = (int *) calloc(map.x * map.y, sizeof(int));

    snake_random_pos(map.kopf, map);
    snake_random_pos(map.futter, map);

    map.kopf[0]=1;
    map.futter[0]=1;

    // Hauptspielschleife
    while(status)
    {
        map.punkte = (map.length - 3) * schwierigkeit;
        map.runde++;
        snake_draw(map);
        map = snake_steuerung(map);

        if(torus)
            map = snake_torus(map);
        else
            status = snake_rand(map);
        switch (snake_dead_or_eating(map))
        {
            case 1:
                map.length++;
                printf ("Mampf\n");
                snake_random_pos(map.futter, map);
                break;
            case 0:
                break;
            case 2:
                status = 0;
                printf("In den Schwanz gebissen.\n");

                break;
        }
        map = snake_koerper(map);
        map.schlange[map.kopf[1] * map.x + map.kopf[0]] = 1;
    }
    snake_verloren(map.punkte);
}

void snake_draw(struct snake_map map)
{
    int i,j;
    printf("\nRunde:  % 5d\nLänge:  % 5d\nPunkte: % 5d\n", map.runde, map.length, map.punkte);
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

struct snake_map snake_steuerung(struct snake_map map)
{
    int tmp = 0;
    usleep(map.level);
    // Input Funktion
    do
    {
        if(kbhit())
            map.richtung = getch();
        else
            map.richtung = map.richtung_alt;
        switch (map.richtung)
        {
            case 'w':
                if (map.richtung_alt == 's')
                    tmp = 1;
                else
                {
                    map.kopf[1]--;
                    tmp = 0;
                }
                break;
            case 'a':
                if (map.richtung_alt == 'd')
                    tmp = 1;
                else
                {
                    map.kopf[0]--;
                    tmp = 0;
                }
                break;
            case 's':
                if (map.richtung_alt == 'w')
                    tmp = 1;
                else
                {
                    map.kopf[1]++;
                    tmp = 0;
                }
                break;
            case 'd':
                if (map.richtung_alt == 'a')
                    tmp = 1;
                else
                {
                    map.kopf[0]++;
                    tmp = 0;
                }
                break;
            default:
                tmp = 1;
                break;
        }
    } while(tmp);
    map.richtung_alt = map.richtung;
    return map;
}

void snake_verloren(int punkte)
{
    printf("%s\n", verloren);
    printf("Du hast -= %d =- Punkte erzielt\n", punkte);
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
    if(map.kopf[0] >= map.x || map.kopf[1] >= map.y || map.kopf[0] < 0 || map.kopf[1] < 0)
    {
        printf("Gegen die Wand gelaufen.\n");
        return 0;
    }
    return 1;
}

struct snake_map snake_torus(struct snake_map map)
{
    if(map.kopf[0] >= map.x)
        map.kopf[0] = 0;
    if(map.kopf[1] >= map.y)
        map.kopf[1] = 0;
    if(map.kopf[0] < 0)
        map.kopf[0] = map.x-1;
    if(map.kopf[1] < 0)
        map.kopf[1] = map.y-1;
    return map;
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

int getch()
{
    static int ch = -1, fd = 0;
    struct termios neu, alt;
    fd = fileno(stdin);
    tcgetattr(fd, &alt);
    neu = alt;
    neu.c_lflag &= ~(ICANON|ECHO);
    tcsetattr(fd, TCSANOW, &neu);
    ch = getchar();
    tcsetattr(fd, TCSANOW, &alt);
    return ch;
}

int kbhit()
{
        struct termios term, oterm;
        int fd = 0;
        int c = 0;
        tcgetattr(fd, &oterm);
        memcpy(&term, &oterm, sizeof(term));
        term.c_lflag = term.c_lflag & (!ICANON);
        term.c_cc[VMIN] = 0;
        term.c_cc[VTIME] = 1;
        tcsetattr(fd, TCSANOW, &term);
        c = getchar();
        tcsetattr(fd, TCSANOW, &oterm);
        if (c != -1)
        ungetc(c, stdin);
        return ((c != -1) ? 1 : 0);
}

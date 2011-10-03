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
static const char *verloren = "\
__     __        _                      _ \n\
\\ \\   / /__ _ __| | ___  _ __ ___ _ __ | |\n\
 \\ \\ / / _ \\ '__| |/ _ \\| '__/ _ \\ '_ \\| |\n\
  \\ V /  __/ |  | | (_) | | |  __/ | | |_|\n\
   \\_/ \\___|_|  |_|\\___/|_|  \\___|_| |_(_)\n\
                                          \n";
static const char *highscore = "\
 _   _ _       _                                 \n\
| | | (_) __ _| |__  ___  ___ ___  _ __ ___  ___ \n\
| |_| | |/ _` | '_ \\/ __|/ __/ _ \\| '__/ _ \\/ __|\n\
|  _  | | (_| | | | \\__ \\ (_| (_) | | |  __/\\__ \\\n\
|_| |_|_|\\__, |_| |_|___/\\___\\___/|_|  \\___||___/\n\
         |___/                                   \n";

static const char snake_themes[3][4] = {{'+','0','X',}, {'o','O','X'}, {'*','X','@'}};

void snake_menu()
{
    int exit = 0, m, level = 3, torus = 0, theme = 0, i;
    char k;
    snake_load_config(&level, &torus, &theme);
    snake_highscore_init();
    while(!exit)
    {
        m=0;
        printf("%s\n", titel);
        printf("Spiele Snake:  1\n");
        printf("Einstellungen: 2\n");
        printf("Highscore:     3\n");
        printf("Beende Snake:  4\n");
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

                printf("Torusförmiges Spielfeld y/n [y]\n");
                getchar();
                k = getchar();
                torus = k == 'n' ? 0 : 1;
                if(torus)
                    printf("Spiele auf Torusförmigem Spielfeld\n");
                else
                    printf("Spiele auf begrenztem Spielfeld\n");

                printf("Wähle Theme [1]\n");
                for(i = 0;i<3;i++)
                    printf("%d: %s\n", i+1, snake_themes[i]);
                getchar();
                k = getchar();
                theme = k-48;
                if(theme < 1 || theme >3)
                    theme = 1;
                printf("%d", theme);
                theme--;

                snake_save_config(level, torus, theme);
                break;

            case 1:
                snake(level, torus, theme);
                break;
            case 3:
                snake_load_highscore();
                break;
            case 4:
                return;
                break;
        }
    }
}

void snake(int schwierigkeit, int torus, int theme)
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
        snake_draw(map, theme);
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
    snake_show_highscore(map.punkte, schwierigkeit);
}

void snake_draw(struct snake_map map, int theme)
{
    int i,j;
    printf("\nRunde:  % 5d\nLänge:  % 5d\nPunkte: % 5d\n",\
                                    map.runde, map.length, map.punkte);
    for(i=0; i < map.x; i++)
        printf("-");
    printf("--\n");
    for(j=0; j < map.y; j++)
    {
        printf("|");
        for(i=0; i < map.x; i++)
        {
            if(map.kopf[0] == i && map.kopf[1] == j)
                putchar(snake_themes[theme][1]);
            else if(snake_get_status(i, j, map))
                putchar(snake_themes[theme][0]);
            else if(map.futter[0] == i && map.futter[1] == j)
                putchar(snake_themes[theme][2]);
            else
                putchar(' ');
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
    if(map.kopf[0] >= map.x || map.kopf[1] >= map.y\
                || map.kopf[0] < 0 || map.kopf[1] < 0)
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

int snake_load_config(int *level, int *torus, int *theme)
{
    FILE *datei;
    printf("Lade letzte Einstellungen:\n");
    datei = fopen (SNAKE_CONFIG_FILENAME, "r");
    if (datei == NULL)
    {
        printf("Fehler beim Öffnen der Datei!\n");
        return 1;
    }
    fscanf (datei, "%d;%d;%d\n", level, torus, theme);
    fclose (datei);
    printf("Einstellungen erfolgreich geladen!\n\n");
    printf("Spiele auf Level %d\n", *level);
    if(*torus)
        printf("Spiele auf Torusförmigem Spielfeld\n");
    else
        printf("Spiele auf begrenztem Spielfeld\n");

    printf("Du benutzt Theme \"%s\"", snake_themes[*theme]);
    printf("\n");

    return 0;
}

int snake_save_config(int level, int torus, int theme)
{
    FILE *datei;
    char *filename = SNAKE_CONFIG_FILENAME;

    datei = fopen (filename, "w");
    if (datei == NULL)
    {
        printf("Fehler beim Öffnen der Datei!\n");
        return 1;
    }

    fprintf (datei, "%d;%d;%d", level, torus, theme);
    fclose (datei);
    printf("Einstellungen gespeichert in ./%s\n", SNAKE_CONFIG_FILENAME);
    return 0;
}

int snake_show_highscore(int punkte, int level)
{
    char name[80];

    printf("\nHighscore:\n\n");
    printf("% 5d \t\t\t auf Level %d\n", punkte, level);
    if(punkte > snake_load_highscore())
    {
        printf("Das ist ein neuer Highscore!\n");
        printf("Trage deinen Namen ein:\n");
        scanf("%s",name);
        snake_save_highscore(punkte, level, name);
    }
    return 0;
}

int snake_load_highscore()
{
    FILE *datei;
    int i, punkte, level, day, month, year, hour, min, tmp=0;
    char *filename = SNAKE_HIGHSCORE_FILENAME;
    char name[80];
    datei = fopen (filename, "r");
    if (datei == NULL)
    {
        printf("Fehler beim Öffnen der Datei!\n");
        return 1;
    }
    printf("%s\n", highscore);
    printf("\tName\t\tPunkte\t\tLevel\t\t     Datum\t  Uhr\n");
    for(i=0;i<SNAKE_NUMHS;i++)
    {
        fscanf (datei, "%d;%d;%d-%d-%dT%d:%d;%s\n", &punkte, &level,\
                                &year, &month, &day, &hour, &min, name);
        printf("\t%s", name);
        printf("\t\t% 6d",punkte);
        printf("\t\t    %d",level);
        printf("\t\t%02d.%02d.%04d",day,month,year);
        printf("\t%02d:%02d",hour,min);
        printf("\n");
    }
    fclose (datei);
    printf("\n");
    tmp = punkte;
    return tmp;
}

int snake_save_highscore(int punkte, int level, char *name)
{
    FILE *datei;
    char *filename = SNAKE_HIGHSCORE_FILENAME;

    struct tm *ts;
    time_t t;

    datei = fopen (filename, "a");
    if (datei == NULL)
    {
        printf("Fehler beim Öffnen der Datei!\n");
        return 1;
    }

    t = time(NULL);
    ts = localtime(&t);

    fprintf (datei, "%d;%d;%d-%d-%dT%d:%d;%s\n", punkte, level,\
    ts->tm_year+1900, ts->tm_mon+1, ts->tm_mday, ts->tm_hour, ts->tm_min,\
    name);
    fclose (datei);
    snake_highscore_sort();
    printf("Highscore gespeichert!\n");
    return 0;
}

void snake_highscore_sort()
{
    FILE *datei;
    int i, j, data[SNAKE_NUMHS+1], itmp, index[SNAKE_NUMHS+1];
    char *filename = SNAKE_HIGHSCORE_FILENAME;
    char rest[SNAKE_NUMHS+1][100];
    for(i=0;i<SNAKE_NUMHS+1;i++)
        index[i] = i;
    datei = fopen (filename, "r");
    if (datei == NULL)
    {
        printf("Fehler beim Öffnen der Datei!\n");
        return;
    }
    for(i=0;i<SNAKE_NUMHS+1;i++)
        fscanf (datei, "%d;%s\n", &data[i], rest[i]);
    fclose (datei);
    for(i=0;i<SNAKE_NUMHS+1;i++)
        for(j=SNAKE_NUMHS;i<j;j--)
            if(data[index[j-1]]<data[index[j]])
            {
                itmp = index[j-1];
                index[j-1] = index[j];
                index[j] = itmp;
            }

    datei = fopen (filename, "w");
    for(i=0;i<SNAKE_NUMHS;i++)
        fprintf(datei, "%d;%s\n", data[index[i]], rest[index[i]]);
    fclose (datei);
    return;
}

void snake_highscore_init()
{
    FILE *datei;
    int i, tmp;
    char *filename = SNAKE_HIGHSCORE_FILENAME;
    datei = fopen (filename, "r");
    if (datei != NULL)
    {
        tmp = fgetc(datei);
        fclose(datei);
    }
    else
    {
        tmp = EOF;
    }
    if (tmp == EOF)
    {
        datei = fopen (filename, "w");
        for (i = 0; i<10; i++)
            fprintf(datei,"0;0;2011-10-3T15:31;Abe\n");
        fclose(datei);
    }
    return;
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

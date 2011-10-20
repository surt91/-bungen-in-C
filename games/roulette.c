#include "roulette.h"

void roulette_start()
{
    int x, besitz, runde, i, k;
    int max_geld;
    int max_runde;
    int liste[42];

    setlocale(LC_ALL,"");
    initscr();
    raw();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    for(i=0;i<=42;i++)
        liste[i] = 0;
    k=-1;
    runde=1;
    besitz=100;
    max_geld = besitz;
    max_runde = runde;
    while(1)
    {
        max_runde = runde;
        if(max_geld < besitz)
            max_geld = besitz;
        x = roulette_menu(liste, runde, besitz);

        switch(x)
        {
            case '0':
            case 'd':
            case 'D':
                if(roulette_drehen(liste, &besitz))
                {
                    hs_show_highscore(max_geld, "Geld", max_runde, "Runde", ROULETTE_HIGHSCORE_FILENAME);
                    endwin();
                    return;
                }
                runde++;
                break;
            case '1':
            case 'g':
            case 'G':
                roulette_setzen(&besitz, liste, GERADE);
                break;
            case '2':
            case 'u':
            case 'U':
                roulette_setzen(&besitz, liste, UNGERADE);
                break;
            case '3':
            case 'r':
            case 'R':
                roulette_setzen(&besitz, liste, ROT);
                break;
            case '4':
            case 'b':
            case 'B':
                roulette_setzen(&besitz, liste, SCHWARZ);
                break;
            case '5':
            case 'n':
            case 'N':
                roulette_setzen(&besitz, liste, NIEDRIG);
                break;
            case '6':
            case 'o':
            case 'O':
                roulette_setzen(&besitz, liste, HOCH);
                break;
            case '7':
            case 'z':
            case 'Z':
                printw("Auf welche Zahl zwischen 0 und 36 setzt du?\n");
                refresh();
                while(1)
                {
                    echo();
                    scanw("%d",&k);
                    noecho();
                    if(k<0 || k>36)
                    {
                        printw("Wähle eine Zahl zwischen 0 und 36.\n");
                    }
                    else
                    {
                        printw("Du setzt auf die %d!\n",k);
                        break;
                    }
                    refresh();
                }
                roulette_setzen(&besitz, liste, k);
                break;
            case 'q':
            case 'Q':
                hs_show_highscore(max_geld, "Geld", max_runde, "Runde", ROULETTE_HIGHSCORE_FILENAME);
                endwin();
                return;
            case 'h':
            case 'H':
                hs_load_highscore(ROULETTE_HIGHSCORE_FILENAME);
                break;
            case 's':
            case 'S':
                roulette_save(runde, besitz, max_geld, "roulette_save.dat");
                break;
            case 'l':
            case 'L':
                roulette_load(&runde, &besitz, &max_geld, "roulette_save.dat");
                break;
            default:
                printw("unzulässig, bitte wähle erneut");
                break;
        }
        refresh();
        //~ getch();
    }
}

char roulette_menu(int *liste, int runde, int besitz)
{
    int i, y=0;
    char tmp;
    mvprintw(y++,0,"Roulette");
    mvprintw(++y,0,"Runde:       % 5d",runde);
    mvprintw(++y,0,"Konto:       % 5d€",besitz);
    y++;
    mvprintw(++y,0,"0: Dreh das Rad");
    mvprintw(++y,0,"1: Gerade    % 5d€",liste[GERADE]);
    mvprintw(++y,0,"2: Ungerade  % 5d€",liste[UNGERADE]);
    mvprintw(++y,0,"3: Rot       % 5d€",liste[ROT]);
    mvprintw(++y,0,"4: Schwarz   % 5d€",liste[SCHWARZ]);
    mvprintw(++y,0,"5: niedrig   % 5d€",liste[NIEDRIG]);
    mvprintw(++y,0,"6: hoch      % 5d€",liste[HOCH]);

    for(i=0,tmp=0;i<=36;i++)
        tmp += liste[i];
    mvprintw(++y,0,"7: Zahl      % 5d€  ",tmp);
    for(i=0;i<=36;i++)
        if(liste[i])
            printw(", %d: %d€ ",i, liste[i]);
    mvprintw(++y,0,"Q: zum Beenden");
    mvprintw(++y,0,"H: zu den Highscores");
    mvprintw(++y,0,"S: zum Speichern");
    mvprintw(++y,0,"L: zum Laden");

    refresh();
    tmp = getch();
    return tmp;
}
// berechnet wie Groß der Gewinn-Faktor ist
int roulette_gewinn(int *liste, int kugel)
{
    int i, gewinn = 0, y=2, x=ROULETTE_RIGHT;
    if(kugel)
    {
        if(kugel%2==0)
            liste[GERADE] *= 2;
        else
            liste[GERADE]  = 0;
        if(liste[GERADE])
            mvprintw(y++,x,"Gerade  : Dein Einsatz verdoppelt sich auf %d!", liste[GERADE]);
        // Ungerade
        if(kugel%2==1)
            liste[UNGERADE] *= 2;
        else
            liste[UNGERADE]  = 0;
        if(liste[UNGERADE])
            mvprintw(y++,x,"Ungerade: Dein Einsatz verdoppelt sich auf %d!", liste[UNGERADE]);
        // Rot
        if((kugel+kugel%10)%2==0)
            liste[ROT] *= 2;
        else
            liste[ROT]  = 0;
        if(liste[ROT])
            mvprintw(y++,x,"Rot     : Dein Einsatz verdoppelt sich auf %d!", liste[ROT]);
        // Schwarz
        if((kugel+kugel%10)%2==1)
            liste[SCHWARZ] *= 2;
        else
            liste[SCHWARZ]  = 0;
        if(liste[SCHWARZ])
            mvprintw(y++,x,"Schwarz : Dein Einsatz verdoppelt sich auf %d!\n", liste[SCHWARZ]);
        // <=18
        if(kugel <= 18)
            liste[NIEDRIG] *= 2;
        else
            liste[NIEDRIG]  = 0;
        if(liste[NIEDRIG])
            mvprintw(y++,x,"Niedrig : Dein Einsatz verdoppelt sich auf %d!", liste[NIEDRIG]);
        // > 18
        if(kugel > 18)
            liste[HOCH] *= 2;
        else
            liste[HOCH]  = 0;
        if(liste[HOCH])
            mvprintw(y++,x,"Hoch    : Dein Einsatz verdoppelt sich auf %d!", liste[HOCH]);
    }
    else
        for(i=1;i<=42;i++)
            liste[i]=0;
    // Zahl
    liste[kugel] *= 36;
    if(liste[kugel])
        mvprintw(y++,x,"Treffer : Dein Einsatz ver-36-facht sich!");

    for(i=0;i<=36;i++)
        if(i!=kugel)
            liste[i]=0;

    for(i=0;i<=42;i++)
    {
        gewinn += liste[i];
        liste[i] = 0;
    }
    refresh();
    return gewinn;
}
void roulette_setzen(int *besitz, int *liste, int k)
{
    int x,y;
    getyx(stdscr, y, x);
    mvprintw(y+2, 0, "Du hast %d€", *besitz);
    mvprintw(y+3, 0, "Wieviel setzt du? ");
    refresh();
    echo();
    scanw("%d", &liste[k]);
    noecho();
    erase();
    *besitz-=liste[k];
    return;
}
int roulette_drehen(int *liste, int *besitz)
{
    int kugel, gewinn, einsatz=0, i, x ,y;
    kugel = rand()%37;
    mvprintw(2,ROULETTE_RIGHT,"Die Kugel ist auf %d liegen geblieben!", kugel);

    for(i=0;i<=42;i++)
        einsatz += liste[i];

    gewinn=roulette_gewinn(liste, kugel);
    *besitz+=gewinn;
    getyx(stdscr, y, x);
    y++;
    if(gewinn-einsatz > 0)
    {
        mvprintw(++y, ROULETTE_RIGHT, "Du hast Gewonnen!");
        mvprintw(++y, ROULETTE_RIGHT, "Du hast %d€ gesetzt und %d€ gewonnen.", einsatz, gewinn);
        mvprintw(++y, ROULETTE_RIGHT, "Du hast jetzt %d€", *besitz);
        return 0;
    }
    else if(gewinn-einsatz <= 0 && *besitz > 0)
    {
        mvprintw(++y, ROULETTE_RIGHT, "Leider verloren!");
        mvprintw(++y, ROULETTE_RIGHT, "Du hast %d€ gesetzt und %d€ gewonnen.", einsatz, gewinn);
        mvprintw(++y, ROULETTE_RIGHT, "Du hast jetzt %d€", *besitz);
        return 0;
    }
    else
    {
        mvprintw(++y, ROULETTE_RIGHT, "Du bist leider Pleite und wirst aus dem Kasino geworfen!");
        return 1;
    }
    refresh();
}
// schreibt einen Roulette Spielstand in eine Datei
int roulette_save(int runde, int geld, int max_geld, char *filename)
{
    FILE *datei;
    datei = fopen (filename, "w");
    if (datei == NULL)
    {
        printf("Fehler beim Öffnen der Datei!\n");
        return 1;
    }
    fprintf (datei, "%d;%d;%d\n", runde, geld, max_geld);
    fclose (datei);
    printf("Spielstand erfolgreich gespeichert!\n");
    return 0;
}
int roulette_load(int *runde, int *geld, int *max_geld, char *filename)
{
    FILE *datei;
    datei = fopen (filename, "r");
    if (datei == NULL)
    {
        printf("Fehler beim Öffnen der Datei!\n");
        return 1;
    }
    fscanf (datei, "%d;%d;%d\n", runde, geld, max_geld);
    fclose (datei);
    printf("\nSpielstand erfolgreich geladen!\n\n");
    printf("Dein Geld:\t%5d €\n",*geld);
    printf("Runde    :\t%5d\n",*runde);
    printf("\n\n");
    return 0;
}

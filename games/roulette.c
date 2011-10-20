#include "roulette.h"

void roulette_start()
{
    int x, besitz, runde, i, k;
    int max_geld;
    int max_runde;
    int liste[42];
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
            case 0:
                if(roulette_drehen(liste, &besitz))
                {
                    roulette_zeige_highscore(max_geld, max_runde);
                    return;
                }
                runde++;
                break;
            case 1:
                roulette_setzen(&besitz, liste, GERADE);
                break;
            case 2:
                roulette_setzen(&besitz, liste, UNGERADE);
                break;
            case 3:
                roulette_setzen(&besitz, liste, ROT);
                break;
            case 4:
                roulette_setzen(&besitz, liste, SCHWARZ);
                break;
            case 5:
                roulette_setzen(&besitz, liste, NIEDRIG);
                break;
            case 6:
                roulette_setzen(&besitz, liste, HOCH);
                break;
            case 7:
                printf("Auf welche Zahl zwischen 0 und 36 setzt du?\n");
                while(1)
                {
                    scanf("%d",&k);
                    if(k<0 || k>36)
                    {
                        printf("Wähle eine Zahl zwischen 0 und 36.\n");
                    }
                    else
                    {
                        printf("Du setzt auf die %d!\n",k);
                        break;
                    }
                }
                roulette_setzen(&besitz, liste, k);
                break;
            case 666:
                roulette_zeige_highscore(max_geld, max_runde);
                return;
            case 888:
                roulette_load_highscore();
                break;
            case 1337:
                roulette_save(runde, besitz, max_geld, "roulette_save.dat");
                break;
            case 1338:
                roulette_load(&runde, &besitz, &max_geld, "roulette_save.dat");
                break;
            default:
                printf("unzulässig, bitte wähle erneut");
                break;
        }
    }
}

int roulette_menu(int *liste, int runde, int besitz)
{
    int i, tmp;
    printf("\n\nRoulette\n\n");
    printf("\t\tRunde: \t %5d\n",runde);
    printf("\t\tKonto: \t %5d€\n\n",besitz);
    printf("Worauf setzt du?\n\n");
    printf("0: Dreh das Rad\n");
    printf("1: Gerade   \t\t %d€\n",liste[GERADE]);
    printf("2: Ungerade \t\t %d€\n",liste[UNGERADE]);
    printf("3: Rot      \t\t %d€\n",liste[ROT]);
    printf("4: Schwarz  \t\t %d€\n",liste[SCHWARZ]);
    printf("5: niedrig  \t\t %d€\n",liste[NIEDRIG]);
    printf("6: hoch     \t\t %d€\n",liste[HOCH]);

    for(i=0,tmp=0;i<=36;i++)
        tmp += liste[i];
    printf("7: Zahl     \t\t %d€  ",tmp);
    for(i=0;i<=36;i++)
        if(liste[i])
            printf(", %d: %d€ ",i, liste[i]);
    printf("\n");

    printf("666: zum Beenden\n");
    printf("888: zu den Highscores\n");
    printf("1337: zum Speichern\n");
    printf("1338: zum Laden\n\n");

    scanf("%d", &tmp);
    return tmp;
}
// berechnet wie Groß der Gewinn-Faktor ist
int roulette_gewinn(int *liste, int kugel)
{
    int i, gewinn = 0;
    if(kugel)
    {
        if(kugel%2==0)
            liste[GERADE] *= 2;
        else
            liste[GERADE]  = 0;
        if(liste[GERADE])
            printf("Gerade  : Dein Einsatz verdoppelt sich auf %d!\n", liste[GERADE]);
        // Ungerade
        if(kugel%2==1)
            liste[UNGERADE] *= 2;
        else
            liste[UNGERADE]  = 0;
        if(liste[UNGERADE])
            printf("Ungerade: Dein Einsatz verdoppelt sich auf %d!\n", liste[UNGERADE]);
        // Rot
        if((kugel+kugel%10)%2==0)
            liste[ROT] *= 2;
        else
            liste[ROT]  = 0;
        if(liste[ROT])
            printf("Rot     : Dein Einsatz verdoppelt sich auf %d!\n", liste[ROT]);
        // Schwarz
        if((kugel+kugel%10)%2==1)
            liste[SCHWARZ] *= 2;
        else
            liste[SCHWARZ]  = 0;
        if(liste[SCHWARZ])
            printf("Schwarz : Dein Einsatz verdoppelt sich auf %d!\n", liste[SCHWARZ]);
        // <=18
        if(kugel <= 18)
            liste[NIEDRIG] *= 2;
        else
            liste[NIEDRIG]  = 0;
        if(liste[NIEDRIG])
            printf("Niedrig : Dein Einsatz verdoppelt sich auf %d!\n", liste[NIEDRIG]);
        // > 18
        if(kugel > 18)
            liste[HOCH] *= 2;
        else
            liste[HOCH]  = 0;
        if(liste[HOCH])
            printf("Hoch    : Dein Einsatz verdoppelt sich auf %d!\n", liste[HOCH]);
    }
    else
        for(i=1;i<=42;i++)
            liste[i]=0;
    // Zahl
    liste[kugel] *= 36;
    if(liste[kugel])
        printf("Treffer : Dein Einsatz ver-36-facht sich!\n");

    for(i=0;i<=36;i++)
        if(i!=kugel)
            liste[i]=0;

    for(i=0;i<=42;i++)
    {
        gewinn += liste[i];
        liste[i] = 0;
    }
    return gewinn;
}
void roulette_setzen(int *besitz, int *liste, int k)
{
    printf("Du hast %d€\nWieviel setzt du?\n", *besitz);
    scanf("%d", &liste[k]);
    *besitz-=liste[k];
    return;
}
int roulette_drehen(int *liste, int *besitz)
{
    int kugel, gewinn, einsatz=0, i;
    kugel = rand()%37;
    printf("Die Kugel ist auf %d liegen geblieben!\n", kugel);

    for(i=0;i<=42;i++)
        einsatz += liste[i];

    gewinn=roulette_gewinn(liste, kugel);
    *besitz+=gewinn;
    if(gewinn-einsatz > 0)
    {
        printf("Du hast Gewonnen!\nDu hast %d€ gesetzt und %d€ gewonnen.\nDu hast jetzt %d€\n\n",einsatz, gewinn, *besitz);
        return 0;
    }
    else if(gewinn-einsatz <= 0 && *besitz > 0)
    {
        printf("Leider verloren!\nDu hast %d€ gesetzt und %d€ gewonnen\nDu hast noch %d€\n\n",einsatz, gewinn, *besitz);
        return 0;
    }
    else
    {
        printf("Du bist leider Pleite und wirst aus dem Kasino geworfen!\n\n");
        return 1;
    }
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
void roulette_zeige_highscore(int max_geld, int max_runde)
{
    char name[80];

    printf("\nHighscore:\n\n");
    printf("Geld  :\t%5d €\n",max_geld);
    printf("Runde :\t%5d\n",max_runde);
    printf("\n");
    if(max_geld > roulette_load_highscore())
    {
        printf("Das ist ein neuer Highscore!\n");
        printf("Trage deinen Namen ein:\n");
        scanf("%s",name);
        roulette_save_highscore(max_geld,max_runde,name);
    }
}
int roulette_load_highscore()
{
    FILE *datei;
    int i, hs_geld, hs_runde,day, month, year, hour, min, tmp=0;
    char *filename = RHSS;
    char name[80];
    datei = fopen (filename, "r");
    if (datei == NULL)
    {
        printf("Fehler beim Öffnen der Datei!\n");
        return 1;
    }
    printf("\tAll Time Highscores\n");
    printf("\tNAME   \t\t  GELD\t\tRUNDE\t\tDATUM\n");
    for(i=0;i<NUMHS;i++)
    {
        fscanf (datei, "%d;%d;%d;%d;%d;%d;%d;%s\n", &hs_geld, &hs_runde, &day, &month, &year, &hour, &min, name);
        printf("\t%s", name);
        printf("\t\t%5d€",hs_geld);
        printf("\t\t%5d",hs_runde);
        printf("\t\t%02d.%02d.%04d",day,month,year);
        printf("\t%02d:%02d",hour,min);
        printf("\n");
    }
    fclose (datei);
    printf("\n");
    tmp = hs_geld;
    return tmp;
}

int roulette_save_highscore(int max_geld, int max_runde, char *name)
{
    FILE *datei;
    char *filename = RHSS;

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

    fprintf (datei, "%d;%d;%d;%d;%d;%d;%d;%s\n", max_geld, max_runde, ts->tm_mday, ts->tm_mon+1, ts->tm_year+1900, ts->tm_hour, ts->tm_min, name);
    fclose (datei);
    roulette_highscore_sort();
    printf("Highscore gespeichert!\n");
    return 0;
}

void roulette_highscore_sort()
{
    FILE *datei;
    int i, j, data[NUMHS+1], itmp, index[NUMHS+1];
    char *filename = RHSS;
    char rest[NUMHS+1][100];
    for(i=0;i<NUMHS+1;i++)
        index[i] = i;
    datei = fopen (filename, "r");
    if (datei == NULL)
    {
        printf("Fehler beim Öffnen der Datei!\n");
        return;
    }
    for(i=0;i<NUMHS+1;i++)
        fscanf (datei, "%d;%s\n", &data[i], rest[i]);
    fclose (datei);
    for(i=0;i<NUMHS+1;i++)
        for(j=NUMHS;i<j;j--)
            if(data[index[j-1]]<data[index[j]])
            {
                itmp = index[j-1];
                index[j-1] = index[j];
                index[j] = itmp;
            }

    datei = fopen (filename, "w");
    for(i=0;i<NUMHS;i++)
        fprintf(datei, "%d;%s\n", data[index[i]], rest[index[i]]);
    fclose (datei);
    return;
}

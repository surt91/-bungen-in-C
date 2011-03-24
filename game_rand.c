#include "game_rand.h"

int roulette_menu(int *liste, int runde, int besitz)
{
	int i, tmp;
	printf("\n\nRoulette\n\n");
	printf("\t\tRunde: \t %5d\n",runde);
	printf("\t\tKonto: \t %5d€\n\n",besitz);
	printf("Worauf setzt du?\n\n",runde);
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
	int i,j;
	FILE *datei;
	datei = fopen (filename, "w");
	if (datei == NULL)
	{
		printf("Fehler beim Öffnen der Datei!\n");
		return 1;
	}
	fprintf (datei, "%d;%d;%d\n", runde, geld, max_geld);
	fclose (datei);
	printf("Spielstand erfolgreich gespeichert!\n", filename);
	return 0;
}
int roulette_load(int *runde, int *geld, int *max_geld, char *filename)
{
	int i,j;
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
	int tmp;

	printf("\nHighscore:\n\n");
	printf("Geld  :\t%5d €\n",max_geld);
	printf("Runde :\t%5d\n",max_runde);
	printf("\n");
	if(max_geld > roulette_load_highscore())
	{
		printf("Das ist ein neuer Highscore!\n");
		printf("Trage deinen Namen ein:\n");
		scanf("%s",&name);
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
	int i,j;
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
	printf("Highscore gespeichert!\n", filename);
	return 0;
}

void roulette_highscore_sort()
{
	FILE *datei;
	int i, j, n, data[NUMHS+1], itmp, index[NUMHS+1];
	char *filename = RHSS;
	char rest[NUMHS+1][100], strtmp;
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

// gibt eine Pokerhand
struct card *karten_geber(struct card *hand)
{
    int karte[5], i;
//    srand( (unsigned) time(NULL) ) ; //schon am Anfang von main()
    for(i=0;i<5;i++)
    {
        do
        {
        karte[i]=((rand()%52)+1);
        } while((karte[i]==karte[0] && i!=0 ) || (karte[i]==karte[1] && i!=1) || (karte[i]==karte[2] && i!=2) || (karte[i]==karte[3] && i!=3) || (karte[i]==karte[4] && i!=4));

        if(karte[i] <= 13)
        {
            hand[i].f=herz;
            hand[i].w=karte[i];
        }
        else if(karte[i] <= 26)
        {
            hand[i].f=pik;
            hand[i].w=karte[i]-13;
        }
        else if(karte[i] <= 39)
        {
            hand[i].f=karo;
            hand[i].w=karte[i]-26;
        }
        else if(karte[i] <= 52)
        {
            hand[i].f=kreuz;
            hand[i].w=karte[i]-39;
        }
    }
    return hand;
}
// Zeigt eine Pokerhand an
void karten_zeiger(struct card *hand)
{
    int i;
    for(i=0;i<5;i++)
    {
        switch (hand[i].f)
        {
            case herz:  printf("\nHerz  "); break;
            case pik:   printf("\nPik   "); break;
            case karo:  printf("\nKaro  "); break;
            case kreuz: printf("\nKreuz "); break;
        }
        switch (hand[i].w)
        {
            case ass: printf("Ass"); break;
            case 2: printf("Zwei"); break;
            case 3: printf("Drei"); break;
            case 4: printf("Vier"); break;
            case 5: printf("Fünf"); break;
            case 6: printf("Sechs"); break;
            case 7: printf("Sieben"); break;
            case 8: printf("Acht"); break;
            case 9: printf("Neun"); break;
            case 10: printf("Zehn"); break;
            case bube: printf("Bube"); break;
            case dame: printf("Dame"); break;
            case konig: printf("König"); break;
        }
    }
    printf("\n\n");
}
// überprüft, ob ein Fullhouse auf der Hand ist
int is_fullhouse(struct card *hand)
{
    int i,n=1,l,m=1;
    for(i=1;i<5;i++)
    {
        if(hand[0].w==hand[i].w)
        {
            n++;
        }
    }
    if( (n==2) || (n==3) )
    {
        i=1;
        while(hand[0].w==hand[i].w)
        {
            i++;
        }
        for(l=i+1;l<5;l++)
        {
            if(hand[i].w==hand[l].w)
            {
                m++;
            }
        }
    }
    if( ( (m==2) && (n==3) ) || ( (m==3) && (n==2) ) )
    {
        return 1;
    }
    return 0;
}
// überprüft, ob ein Flush auf der Hand ist
int is_flush(struct card *hand)
{
    int i;
    for(i=1;i<5;i++)
        if(hand[0].f!=hand[i].f)
            return 0;
    return 1;
}
// überprüft, ob eine Straße auf der Hand ist
int is_straight(struct card *hand)
{
	int i;
    karten_sortierer(hand);
    if(hand[1].w==10 && hand[2].w==bube && hand[3].w==dame && hand[4].w==konig && hand[0].w==ass)
        return 2;

    for(i=0;i<4;i++)
        if(hand[i].w+1!=hand[i+1].w)
            return 0;

    return 1;
}
// sortiert eine Pokerhand aufsteigend, (ass, zwei, drei...)
struct card *karten_sortierer(struct card *hand)
{
    int i, j, temp, n=0;
    // Bubble Sort; effizient, da nur 5 Werte sortiert werden müssen; qsort würde mehr "overhead" erzeugen
    // n ist ein Zähler, der feststellt, ob in der Sortierschleife etwas umgestellt wurde, falls nicht, bricht die Schleife ab
    // marginale Geschwindigkeitsvorteile. durch overhead eventuell sogar Nachteile
	for(i=0;i<4;i++)
	{
        for(j=4;i<j;j--)
            if(hand[j-1].w>hand[j].w)
            {
                temp = hand[j-1].w;
                hand[j-1].w = hand[j].w;
                hand[j].w = temp;
                n++;
            }
            if(n==0)
				break;
			n=0;
    }
    return(hand);
}

// für qsort
//int cmp_integer(const void *wert1, const void *wert2) {
//   return (*(int*)wert1 – *(int*)wert2);
//}
// bsp:  qsort(test_array, MAX, sizeof(int), cmp_integer);


// Funktion zur Simulation eines Münzwurfes
void muenzwurf(int wuerfe, int *kopf, int *zahl)
{
    int i,ergebnis=0; // 1 = Kopf; 0 = Zahl
    //srand( (unsigned) time(NULL) ) ; //schon am Anfang von main()
    for(i=0;i<wuerfe;i++)
    {
        ergebnis=rand()%2;
        if(ergebnis)
        {
            *kopf+=1;
        }
        else
        {
            *zahl+=1;
        }
    }
    return;
}

// Funktion zur Lösung des Geburtstagsproblems per Monte Carlo Methode
int monteCarloGeburtstagsProblem(k)
{
    int monat, verteilung[12], i, treffer=0, n;
    //srand( (unsigned) time(NULL) ) ; //schon am Anfang von main()
    for(i=0;i<12;i++)
    {
        verteilung[i]=0;
    }

    for(n=0;n<100;n++)
    {
        for(i=0;i<k;i++)
        {
            monat = rand()%12;
            verteilung[monat]++;
        }

        for(i=0;i<12;i++)
        {
            if(verteilung[i]>=2)
            {
                treffer++;
                break;
            }
        }
        for(i=0;i<12;i++)
        {
            verteilung[i]=0;
        }
    }

    return treffer;
}

// Monte Carlo Pi
double pi(int versuche)
{
	int i;
	double x,y, betrag, treffer=0;
	for(i=0;i<versuche;i++)
	{
		x = rand();
		x /= RAND_MAX;
		y = rand();
		y /= RAND_MAX;
		betrag = x*x + y*y;
		if(betrag<=1)
			treffer++;
	}
	return(treffer/versuche*4);
}

double pi_benchmark(double *v)
{
	int begin,end;
	begin = clock();
	*v=pi(100000000);
	end = clock();
	return((double)(end-begin)/1000000);
}

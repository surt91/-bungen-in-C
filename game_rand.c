#include "game_rand.h"

// liefert eine Zahl zwischen 0 und 36
int roulette()
{
    //srand( (unsigned) time(NULL) ) ; //schon am Anfang von main()
    return (rand()%37);
}
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
	printf("7: Zahl     \t\t %d€\n",tmp);
	printf("666: zum Beenden\n");
	printf("1337: zum Speichern\n");
	printf("1338: zum Laden\n\n");

	scanf("%d", &tmp);
	return tmp;
}
// berechnet wie Groß der Gewinn-Faktor ist
int roulette_gewinn(int *liste, int kugel)
{
	int i, gewinn = 0;
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
    // Zahl
    liste[kugel] *= 36;
    if(liste[kugel])
		printf("Treffer: Dein Einsatz ver-36-facht sich!\n");

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
	kugel = roulette();
	//~ *runde++;
	printf("Die Kugel ist auf %d liegen geblieben!\n", kugel);

	for(i=0;i<=42;i++)
		einsatz += liste[i];

	gewinn=roulette_gewinn(liste, kugel);
	*besitz+=gewinn;
	if(gewinn-einsatz > 0)
	{
		printf("Du hast Gewonnen!\nDu hast %d€ gesetzt und %d€ gewonnen.\nDu hast jetzt %d€\n\n",einsatz, gewinn, *besitz);
	}
	else if(gewinn-einsatz <= 0 && *besitz > 0)
	{
		printf("Leider verloren!\nDu hast %d€ gesetzt und %d€ gewonnen\nDu hast noch %d€\n\n",einsatz, gewinn, *besitz);
	}
	else
	{
		printf("Du bist leider Pleite und wirst aus dem Kasino geworfen!\n\n");
		return;
	}
}
// schreibt einen Roulette Spielstand in eine Datei
int roulette_save(int runde, int geld, char *filename)
{
	int i,j;
	FILE *datei;
	//~ char *filename = "roulette_save.dat";
	datei = fopen (filename, "w");
	if (datei == NULL)
	{
		printf("Fehler beim Öffnen der Datei!\n");
		return 1;
	}
	fprintf (datei, "%d;%d\n", runde, geld);
	fclose (datei);
	printf("Spielstand erfolgreich gespeichert!\n", filename);
	return 0;
}
int roulette_load(int *runde, int *geld, char *filename)
{
	int i,j;
	FILE *datei;
	//~ char *filename = "roulette_save.dat";
	datei = fopen (filename, "r");
	if (datei == NULL)
	{
		printf("Fehler beim Öffnen der Datei!\n");
		return 1;
	}
	fscanf (datei, "%d;%d\n", runde, geld);
	fclose (datei);
	printf("\nSpielstand erfolgreich geladen!\n\n");
	printf("Dein Geld:\t%5d €\n",*geld);
	printf("Runde    :\t%5d\n",*runde);
	printf("\n\n");
	return 0;
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

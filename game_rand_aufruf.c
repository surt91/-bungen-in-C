#include "game_rand_aufruf.h"

void aufg_GAME_1()
{
    //~ int x, k, kugel, besitz, einsatz, gewinn,runde;
    int x, besitz, runde, i, k;
    int liste[42];
    for(i=0;i<=42;i++)
		liste[i] = 0;
    k=-1;
    runde=1;
    besitz=100;
    while(1)
    {
        x = roulette_menu(liste, runde, besitz);

		if(x==7)
		{
			printf("Auf welche Zahl zwischen 0 und 36 setzt du?\n");
			while(k<0 || k>36)
			{
				scanf("%d",&k);
				if(k<0 || k>36)
				{
					printf("Wähle eine Zahl zwischen 0 und 36.\n");
				}
				else
				{
					printf("Du setzt auf die %d!\n",k);
				}
			}
			roulette_setzen(&besitz, liste, k);
		}
		else if(x==0)
		{
			roulette_drehen(liste, &besitz);
			runde++;
		}
		else if(x==1)
		{
			roulette_setzen(&besitz, liste, GERADE);
		}
		else if(x==2)
		{
			roulette_setzen(&besitz, liste, UNGERADE);
		}
		else if(x==3)
		{
			roulette_setzen(&besitz, liste, ROT);
		}
		else if(x==4)
		{
			roulette_setzen(&besitz, liste, SCHWARZ);
		}
		else if(x==5)
		{
			roulette_setzen(&besitz, liste, NIEDRIG);
		}
		else if(x==6)
		{
			roulette_setzen(&besitz, liste, HOCH);
		}
		else if(x==666)
		{
			return;
		}
		else if(x==1337)
		{
			roulette_save(runde, besitz, "roulette_save.dat");
		}
		else if(x==1338)
		{
			roulette_load(&runde, &besitz, "roulette_save.dat");
		}
		else
		{
			printf("unzulässig, bitte wähle erneut");
		}
    }
    return;
}

void aufg_GAME_2()
{
    struct card hand[5];
    karten_geber(hand);
    karten_sortierer(hand);
    karten_zeiger(hand);
    return;
}

void aufg_GAME_3()
{
    struct card hand[5];
    int i, flush=0, fullhouse=0, straight=0, straight_flush=0, royal_flush=0, runden=0, limit;
    printf("Wieviele Runden sollen gegeben werden?\n");
    scanf("%d", &limit);
    for(i=0;i<limit;i++)
    {
        karten_geber(hand);
        if(is_straight(hand)==2)
        {
            if(is_flush(hand))
            {
                royal_flush++;
                runden++;
                printf("#%4d: Royal Flush!", runden);
                karten_zeiger(hand);
            }
            else
            {
                straight++;
                runden++;
                printf("#%4d: Straße!", runden);
                karten_zeiger(hand);
            }
        }
        else if(is_straight(hand))
        {
            if(is_flush(hand))
            {
                straight_flush++;
                runden++;
                printf("#%4d: Straight Flush!", runden);
                karten_zeiger(hand);
            }
            else
            {
                straight++;
                runden++;
                printf("#%4d: Straße!", runden);
                karten_zeiger(hand);
            }
        }
        else if(is_flush(hand))
        {
            flush++;
            runden++;
            printf("#%4d: Flush!", runden);
            karten_zeiger(hand);
        }
        else if(is_fullhouse(hand))
        {
            fullhouse++;
            runden++;
            printf("#%4d: Fullhouse!", runden);
            karten_zeiger(hand);
        }
        else
        {
            runden++;
        }
    }
    printf("In %d Runden wurden\n %4d Straßen\n %4d Flushs\n %4d Fullhouses\n %4d Straight Flush\n %4d Royal Flush\nverteilt\n", runden, straight, flush, fullhouse, straight_flush, royal_flush);
    return;
}
void aufg_GAME_4()
{
    int zahl=0, kopf=0, k;
    printf("Wie oft soll die Münze geworfen werden?\n");
    scanf("%d",&k);
    muenzwurf(k, &kopf, &zahl);
    printf("Würfe: %d\nKopf: %d\nZahl: %d\n", k, kopf, zahl);
    return;
}

void aufg_GAME_5()
{
    int k, e;
    printf("Wie wieviele Personen stehen im Raum?\n");
    scanf("%d",&k);
    e=monteCarloGeburtstagsProblem(k);
    printf("Die Wahrscheinlichkeit, dass mindestens 2 im gleichen Monat Geburtstag haben liegt bei etwa %d Prozent\n", e);
    return;
}
void aufg_GAME_6()
{
	int versuche;
	printf("Hier ermitteln wir Pi, indem wir Dartpfeile auf eine Kreisscheibe werfen. Weil wir nicht gut sind im Dart, treffen wir gleichverteilt. Anhand der Treffer können wir dann Pi ermitteln.\n");
	printf("Wieviele Dartpfeile sollen geworfen werden?\n");
	scanf("%d", &versuche);
	printf("Mit %d Dartpfeilen haben wir Pi als %.9lf ermittelt:\n", versuche, pi(versuche));
	return;
}

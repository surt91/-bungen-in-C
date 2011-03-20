#include "game_rand_aufruf.h"

void aufg_GAME_1()
{
    //~ int x, k, kugel, besitz, einsatz, gewinn,runde;
    int x, k, besitz, runde;
    k=-1;
    runde=1;
    besitz=100;
    while(1)
    {
        printf("Roulette\t\tRunde%d\nWorauf setzt du?\n",runde);
        printf("1: Gerade\n");
        printf("2: Ungerade\n");
        printf("3: Rot\n");
        printf("4: Schwarz\n");
        printf("5: niedrig\n");
        printf("6: hoch\n");
        printf("7: Zahl\n");
        printf("666: zum Beenden\n");
        printf("1337: zum Speichern und Beenden\n");
        printf("1338: zum Laden\n\n");
        while(x!=1 && x!=2 && x!=3 && x!=4 && x!=5 && x!=6 && x!=7 && x!=666 && x!=1337 && x!=1338)
        {
            scanf("%d", &x);

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
                roulette_setzen(&besitz, k, &runde);
            }
            else if(x==1)
            {
                k=37;
                roulette_setzen(&besitz, k, &runde);
            }
            else if(x==2)
            {
                k=38;
                roulette_setzen(&besitz, k, &runde);
            }
            else if(x==3)
            {
                k=39;
                roulette_setzen(&besitz, k, &runde);
            }
            else if(x==4)
            {
                k=40;
                roulette_setzen(&besitz, k, &runde);
            }
            else if(x==5)
            {
                k=41;
                roulette_setzen(&besitz, k, &runde);
            }
            else if(x==6)
            {
                k=42;
                roulette_setzen(&besitz, k, &runde);
            }
            else if(x==666)
            {
                return;
            }
            else if(x==1337)
            {
				roulette_save(runde, besitz, "roulette_save.dat");
                return;
            }
            else if(x==1338)
            {
				roulette_load(&runde, &besitz, "roulette_save.dat");
				break;
            }
            else
            {
                printf("Wähle eine der genannten Zahlen:\n");
                printf("1: Gerade\n");
				printf("2: Ungerade\n");
				printf("3: Rot\n");
				printf("4: Schwarz\n");
				printf("5: niedrig\n");
				printf("6: hoch\n");
				printf("7: Zahl\n");
				printf("666: zum Beenden\n");
				printf("1337: zum Speichern und Beenden\n");
				printf("1338: zum Laden\n\n");
            }
        }
        x=0;
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

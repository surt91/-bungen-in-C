#include "game_rand_aufruf.h"

//~ void aufg_GAME_2()
//~ {
    //~ struct card hand[5];
    //~ karten_geber(hand);
    //~ karten_sortierer(hand);
    //~ karten_hand_zeiger(hand);
    //~ return;
//~ }

//~ void aufg_GAME_3()
//~ {
    //~ struct card hand[5];
    //~ int i, flush=0, fullhouse=0, straight=0, straight_flush=0, royal_flush=0, runden=0, limit;
    //~ printf("Wieviele Runden sollen gegeben werden?\n");
    //~ scanf("%d", &limit);
    //~ for(i=0;i<limit;i++)
    //~ {
        //~ karten_geber(hand);
        //~ if(is_straight(hand)==2)
        //~ {
            //~ if(is_flush(hand))
            //~ {
                //~ royal_flush++;
                //~ runden++;
                //~ printf("\n#%4d: Royal Flush!\n", runden);
                //~ karten_hand_zeiger(hand);
            //~ }
            //~ else
            //~ {
                //~ straight++;
                //~ runden++;
                //~ printf("\n#%4d: Straße!\n", runden);
                //~ karten_hand_zeiger(hand);
            //~ }
        //~ }
        //~ else if(is_straight(hand))
        //~ {
            //~ if(is_flush(hand))
            //~ {
                //~ straight_flush++;
                //~ runden++;
                //~ printf("\n#%4d: Straight Flush!\n", runden);
                //~ karten_hand_zeiger(hand);
            //~ }
            //~ else
            //~ {
                //~ straight++;
                //~ runden++;
                //~ printf("\n#%4d: Straße!\n", runden);
                //~ karten_hand_zeiger(hand);
            //~ }
        //~ }
        //~ else if(is_flush(hand))
        //~ {
            //~ flush++;
            //~ runden++;
            //~ printf("\n#%4d: Flush!\n", runden);
            //~ karten_hand_zeiger(hand);
        //~ }
        //~ else if(is_fullhouse(hand))
        //~ {
            //~ fullhouse++;
            //~ runden++;
            //~ printf("\n#%4d: Fullhouse!\n", runden);
            //~ karten_hand_zeiger(hand);
        //~ }
        //~ else
        //~ {
            //~ runden++;
        //~ }
    //~ }
    //~ printf("\nIn %d Runden wurden\n %4d Straßen\n %4d Flushs\n %4d Fullhouses\n %4d Straight Flush\n %4d Royal Flush\nverteilt\n", runden, straight, flush, fullhouse, straight_flush, royal_flush);
    //~ return;
//~ }
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
	printf("Mit %d Dartpfeilen haben wir Pi als %.9f ermittelt:\n", versuche, pi(versuche));
	return;
}

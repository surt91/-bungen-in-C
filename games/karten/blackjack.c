#include "blackjack.h"

void bj_test()
{
    int i;
    struct deck *stapel, *spieler;
    stapel = (struct deck *) malloc(sizeof(struct deck));
    karten_init_deck(stapel, 1);
    // Mischen
    for(i=0;i<200;i++)
        karten_vertausche_zwei_karten(&stapel, rand()%53+1, rand()%53+1);

    // TODO: Karten an Spieler ausgeben, und zählen (Blackjack Logik)
    // TODO: In blackjack.c und poker.c beide Kartenspiele schreiben
    spieler = NULL;

    karten_gebe_karte(&stapel, &spieler);
    karten_gebe_karte(&stapel, &spieler);
    //~ karten_gebe_karte(&stapel, &spieler);

    printf("Deine Hand:\n");
    karten_show(spieler);
    printf("Punkte: %d\n", bj_summiere_augen(spieler));
    //~ karten_show(stapel);
    return;
}

int bj_summiere_augen(struct deck *hand)
{
    int summe=0, n_ass=0;
    enum wert now;
    while(hand != NULL)
    {
        now = hand -> karte.w;
        if(now == konig || now == dame || now == bube)
            summe += 10;
        else if(now == ass)
            n_ass++;
        else
            summe += now;
        hand = hand -> next;
    }
    if(n_ass)
    {
        if(summe < 11)
            summe += 11;
        else
            summe += 1;
    }
    return summe;
}

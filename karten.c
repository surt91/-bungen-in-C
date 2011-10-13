#include "karten.h"

void karten_test()
{
    int i;
    struct deck *stapel, *spieler, *bank;
    stapel = (struct deck *) malloc(sizeof(struct deck));
    karten_init_deck(stapel, 1);
    // Mischen
    for(i=0;i<200;i++)
        karten_vertausche_zwei_karten(&stapel, rand()%53+1, rand()%53+1);

    // TODO: Karten an Spieler ausgeben, und zählen (Blackjack Logik)
    spieler = NULL;
    bank = NULL;

    karten_gebe_karte(&stapel, &spieler);
    karten_gebe_karte(&stapel, &spieler);
    //~ karten_gebe_karte(&stapel, &spieler);

    printf("Deine Hand:\n");
    karten_show(spieler);
    printf("Punkte: %d\n", karten_summiere_augen(spieler));
    //~ karten_show(stapel);
    return;
}

void karten_gebe_karte(struct deck **stapel, struct deck **hand)
{
    struct deck *tmp, *tmp2;
    tmp2 = *stapel;
    if(*hand == NULL)
    {
        *hand = (struct deck *) malloc(sizeof(struct deck));
        (*hand) -> karte = karten_pop(&tmp2);
        (*hand) -> next = NULL;
    }
    else
    {
        tmp = *hand;
        while((*hand) -> next != NULL)
        {
            *hand = (*hand) -> next;
        }
        (*hand) -> next = (struct deck *) malloc(sizeof(struct deck));
        *hand = (*hand) -> next;
        (*hand) -> karte = karten_pop(&tmp2);
        (*hand) -> next = NULL;
        *hand = tmp;
    }
    *stapel = tmp2;
}

int karten_summiere_augen(struct deck *hand)
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

void karten_init_deck(struct deck *stapel, int anz)
{
    int i,j,n, init=1;
    for(n=0; n<anz; n++)
        for(i=1; i<5; i++)
            for(j=1; j<14; j++)
            {
                if(!init)
                {
                    stapel -> next = (struct deck *) malloc(sizeof(struct deck));
                    stapel = stapel->next;
                }
                stapel->karte.f = i;
                stapel->karte.w = j;
                init = 0;
            }
    stapel -> next = NULL;
    return;
}

struct card karten_pop(struct deck **stapel)
{
    struct card ctmp;
    struct deck *tmp;
    tmp = *stapel;
    *stapel = tmp -> next;
    ctmp = tmp->karte;
    free(tmp);
    return ctmp;
}

void karten_show(struct deck *stapel)
{
    while(stapel != NULL)
    {
        karten_zeiger(stapel->karte);
        stapel = stapel -> next;
    }
    return;
}

void karten_vertausche_zwei_karten(struct deck **stapel, int eins, int zwei)
{
    int i=1, t;
    struct deck *tmp, *temp;
    tmp = *stapel;
    temp = *stapel;
    struct card ctmp;

    if(eins==zwei)
        return;
    if(zwei<eins)
    {
        t=eins;
        eins=zwei;
        zwei=t;
    }

    do
    {
        if(i==eins)
        {
            tmp = temp;
            ctmp = temp->karte;
        }
        if(i==zwei)
        {
            tmp->karte = temp->karte;
            temp->karte = ctmp;
            break;
        }
        temp = temp->next;
        i++;
    } while(temp != NULL);
    temp = *stapel;
    return;
}

void karten_zeiger(struct card karte)
{
    switch (karte.f)
    {
        case herz:  printf("♥"); break;
        case pik:   printf("♠"); break;
        case karo:  printf("♦"); break;
        case kreuz: printf("♣"); break;
        default:    printf("E"); break;
    }
    switch (karte.w)
    {
        case ass: printf(" A"); break;
        case 2: printf(" 2"); break;
        case 3: printf(" 3"); break;
        case 4: printf(" 4"); break;
        case 5: printf(" 5"); break;
        case 6: printf(" 6"); break;
        case 7: printf(" 7"); break;
        case 8: printf(" 8"); break;
        case 9: printf(" 9"); break;
        case 10: printf("10"); break;
        case bube: printf(" J"); break;
        case dame: printf(" Q"); break;
        case konig: printf(" K"); break;
        default: printf("E"); break;
    }
    printf("\n");
    return;
}

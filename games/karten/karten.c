#include "karten.h"

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
    struct deck *tmp1, *tmp2;
    tmp1 = *stapel;
    tmp2 = *stapel;
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
            tmp1 = tmp2;
            ctmp = tmp2->karte;
        }
        if(i==zwei)
        {
            tmp1->karte = tmp2->karte;
            tmp2->karte = ctmp;
            break;
        }
        tmp2 = tmp2->next;
        i++;
    } while(tmp2 != NULL);
    tmp2 = *stapel;
    return;
}

void karten_zeiger(struct card karte)
{
    int x, y;
    switch (karte.f)
    {
        case herz:  printw("♥"); break;
        case pik:   printw("♠"); break;
        case karo:  printw("♦"); break;
        case kreuz: printw("♣"); break;
        default:    printw("E"); break;
    }
    switch (karte.w)
    {
        case ass:   printw(" A"); break;
        case 2:     printw(" 2"); break;
        case 3:     printw(" 3"); break;
        case 4:     printw(" 4"); break;
        case 5:     printw(" 5"); break;
        case 6:     printw(" 6"); break;
        case 7:     printw(" 7"); break;
        case 8:     printw(" 8"); break;
        case 9:     printw(" 9"); break;
        case 10:    printw("10"); break;
        case bube:  printw(" J"); break;
        case dame:  printw(" Q"); break;
        case konig: printw(" K"); break;
        default:    printw(" E"); break;
    }
    getyx(stdscr, y, x);
    move(y+1,x-3);
    refresh();
    return;
}

// sortiert aufsteigend, (ass, zwei, drei, ...)
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

void karten_delete_stapel(struct deck **stapel)
{
    struct deck *tmp;
    tmp = *stapel;
    while(*stapel != NULL)
    {
        tmp = *stapel;
        *stapel = tmp -> next;
        free(tmp);
    }
    return;
}

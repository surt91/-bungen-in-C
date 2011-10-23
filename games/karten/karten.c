#include "karten.h"

void karten_gebe_karte(struct deck **stapel, struct deck **hand)
{
    struct deck *tmp1, *tmp2;
    tmp2 = *stapel;
    if(*hand == NULL)
    {
        *hand = (struct deck *) malloc(sizeof(struct deck));
        (*hand) -> karte = karten_pop(&tmp2);
        (*hand) -> next = NULL;
    }
    else
    {
        tmp1 = *hand;
        while((*hand) -> next != NULL)
        {
            *hand = (*hand) -> next;
        }
        (*hand) -> next = (struct deck *) malloc(sizeof(struct deck));
        *hand = (*hand) -> next;
        (*hand) -> karte = karten_pop(&tmp2);
        (*hand) -> next = NULL;
        *hand = tmp1;
    }
    *stapel = tmp2;
}

void karten_init_deck(struct deck *stapel, int anz)
{
    int i,j,n, init=1;
    for(n=0; n<anz; n++)
        for(i=0; i<4; i++)
            for(j=0; j<13; j++)
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
        case zwei:  printw(" 2"); break;
        case drei:  printw(" 3"); break;
        case vier:  printw(" 4"); break;
        case funf:  printw(" 5"); break;
        case sechs: printw(" 6"); break;
        case sieben:printw(" 7"); break;
        case acht:  printw(" 8"); break;
        case neun:  printw(" 9"); break;
        case zehn:  printw("10"); break;
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

int karten_counter(struct deck *stapel)
{
    int ret=0;
    while(stapel != NULL)
    {
        ret++;
        stapel = stapel -> next;
    }
    return ret;
}

// sortiert aufsteigend, (ass, zwei, drei, ...)
void karten_sortierer(struct deck **hand)
{
    struct deck *kopf, *q;
    struct card tmp;
    int n = 0, i, j, m, c;
    // Bubble Sort

    kopf = *hand;
    q  = kopf;

    c = karten_counter(*hand);

    for(i=0;i<c-1;i++)
    {
        for(j=c-1;i<j;j--)
        {
            for(m=0; m<j-1; m++)
            {
                q = q -> next;
            }
            if(q -> karte.w > q -> next -> karte.w)
            {
                tmp = q -> karte;
                q -> karte = q -> next -> karte;
                q -> next -> karte = tmp;
                n++;
            }
            q = kopf;
        }
        if(n==0)
            break;
        n=0;
    }
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

struct card karten_get_card_by_index(struct deck *stapel, int idx)
{
    int i;
    // erste karte => idx = 0;
    for(i=0; i<idx; i++)
    {
        if(stapel -> next == NULL)
            break;
        stapel = stapel -> next;
    }
    return stapel -> karte;
}

#include "karten.h"

void karten_test()
{
    int i;
    struct deck *stapel;
    stapel = (struct deck *) malloc(sizeof(struct deck));
    karten_init_deck(stapel);
    for(i=0;i<200;i++)
        karten_vertausche_zwei_karten(&stapel, rand()%53+1, rand()%53+1);
    karten_zeiger(&stapel->karte);
    while(stapel->next != NULL)
    {
        karten_delete_card_from_deck(&stapel);
        karten_zeiger(&stapel->karte);
    }
    return;
}

void karten_init_deck(struct deck *stapel)
{
    int i,j, init=1;
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

void karten_delete_card_from_deck(struct deck **stapel)
{
    struct deck *tmp;
    tmp = *stapel;
    *stapel = tmp -> next;
    free(tmp);
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

void karten_zeiger(struct card *karte)
{
    switch (karte->f)
    {
        case herz:  printf("♥"); break;
        case pik:   printf("♠"); break;
        case karo:  printf("♦"); break;
        case kreuz: printf("♣"); break;
        default:    printf("E"); break;
    }
    switch (karte->w)
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

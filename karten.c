#include "karten.h"

void karten_test()
{
    struct deck stapel;
    karten_init_deck(&stapel);
    printf("deck fertig\n");
    karten_zeiger(&stapel.karte);
    printf("das war die erste karte\n");
    karten_zeiger(&stapel.next->karte);
}

void karten_init_deck(struct deck *stapel)
{
    int i,j;
    for(i=1; i<5; i++)
        for(j=1; j<14; j++)
        {
            stapel->karte.f = i;
            stapel->karte.w = j;
            stapel -> next = (struct deck *) malloc(sizeof(struct deck));
            stapel = stapel->next;
        }
    stapel -> next = NULL;
}

//~ void karten_delete_card_from_deck(struct deck *stapel)

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
}

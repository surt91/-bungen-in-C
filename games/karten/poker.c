#include "poker.h"

void poker_start()
{
    struct deck *stapel = NULL, *spieler = NULL;
    int i, n;
    const static int anzHand = 5, anzDeck = 1, anzPerDeck = 52;
    int flush = 0, straight = 0, straight_flush = 0, royal_flush = 0;
    int fullhouse = 0, runden = 0;
    setlocale(LC_ALL,"");
    initscr();
    raw();
    cbreak();
    echo();
    keypad(stdscr, TRUE);

    for(n=0; n<10000; n++)
    {
        karten_delete_stapel(&spieler);
        karten_delete_stapel(&stapel);

        stapel = (struct deck *) malloc(sizeof(struct deck));
        karten_init_deck(stapel, anzDeck);
        for(i=0;i<200*anzDeck;i++)
            karten_vertausche_zwei_karten(&stapel, \
                                    rand()%(anzDeck*anzPerDeck+1)+1, \
                                    rand()%(anzDeck*anzPerDeck+1)+1);

        for(i=0; i < anzHand; i++)
        {
            karten_gebe_karte(&stapel, &spieler);
        }
        if(is_straight(spieler)==2)
        {
            if(is_flush(spieler))
                royal_flush++;
            else
                straight++;
        }
        else if(is_straight(spieler))
        {
            if(is_flush(spieler))
                straight_flush++;
            else
                straight++;
        }
        else if(is_flush(spieler))
            flush++;
        else if(is_fullhouse(spieler))
            fullhouse++;
        runden++;
    }

    printw("Verteilung über\n\
    % 12d Runden:\n\
    \n\
    % 12d Straßen\n\
    % 12d Flushs\n\
    % 12d Fullhouses\n\
    % 12d Straight Flush\n\
    % 12d Royal Flush\n",\
    runden, straight, flush, fullhouse, straight_flush, royal_flush);

    getch();
    endwin();
}

void poker_monte_carlo(int anzahl, int leute, int **ergebnis)
{
    struct deck *stapel = NULL, *spieler[leute];
    int i, j, n;
    const static int anzHand = 5, anzDeck = 1, anzPerDeck = 52;
    int flush[leute], straight[leute], royal_flush[leute];
    int fullhouse[leute], runden[leute], straight_flush[leute];

    for(j=0; j<leute; j++)
    {
        flush[j] = straight[j] = straight_flush[j]\
         = royal_flush[j] = fullhouse[j] = runden[j] = 0;
         spieler[j] = NULL;
    }
    for(n=0; n<anzahl; n++)
    {
        for(j=0; j<leute; j++)
            karten_delete_stapel(&(spieler[j]));
        karten_delete_stapel(&stapel);

        stapel = (struct deck *) malloc(sizeof(struct deck));
        karten_init_deck(stapel, anzDeck);
        for(i=0;i<200*anzDeck;i++)
            karten_vertausche_zwei_karten(&stapel, \
                                    rand()%(anzDeck*anzPerDeck+1)+1, \
                                    rand()%(anzDeck*anzPerDeck+1)+1);

        for(i=0; i < anzHand; i++)
            for(j=0; j<leute; j++)
                karten_gebe_karte(&stapel, &spieler[j]);

        for(j=0; j<leute; j++)
        {
            if(is_straight(spieler[j])==2)
            {
                if(is_flush(spieler[j]))
                    royal_flush[j]++;
                else
                    straight[j]++;
            }
            else if(is_straight(spieler[j]))
            {
                if(is_flush(spieler[j]))
                    straight_flush[j]++;
                else
                    straight[j]++;
            }
            else if(is_flush(spieler[j]))
                flush[j]++;
            else if(is_fullhouse(spieler[j]))
                fullhouse[j]++;
            runden[j]++;
        }
    }
    *ergebnis = (int *) malloc(6 * leute * sizeof(int));
    for(j=0; j<leute; j++)
    {
        (*ergebnis)[6 * j + 0] = straight[j];
        (*ergebnis)[6 * j + 1] = flush[j];
        (*ergebnis)[6 * j + 2] = fullhouse[j];
        (*ergebnis)[6 * j + 3] = straight_flush[j];
        (*ergebnis)[6 * j + 4] = royal_flush[j];
        (*ergebnis)[6 * j + 5] = runden[j];
    }
}

void poker_monte_carlo_darstellen(int *u)
{
    int i, j, tmp;
    double runden = 0;

    char *bezeichnungen[5];
    char *straight       = "      Straight", \
                      *flush          = "         Flush", \
                      *fullhouse      = "     Fullhouse", \
                      *straight_flush = "Straight Flush", \
                      *royal_flush    = "   Royal Flush";

    bezeichnungen[0] = straight;
    bezeichnungen[1] = flush;
    bezeichnungen[2] = fullhouse;
    bezeichnungen[3] = straight_flush;
    bezeichnungen[4] = royal_flush;

    for (i=5; i < 48; i+=6)
        runden += u[i];

    printf("Über %g Runden (%g verteilte Karten) gesammelte Messwerte\n", runden, runden*5);
    printf("             # % 5d % 5d % 5d % 5d % 5d % 5d % 5d % 5d  Summe          %%\n", 1, 2, 3, 4, 5, 6, 7, 8);

    for(j=0; j < 5; j++)
    {
        printf("%s", bezeichnungen[j]);
        for (tmp = 0, i=j; i < 48; i+=6)
        {
            printf(" % 5d", u[i]);
            tmp += u[i];
        }
        printf(" % 6d", tmp);
        printf(" % 9.4f%%", 100*tmp/runden);
        printf("\n");
    }
    return;
}

// überprüft, ob ein Fullhouse auf der Hand ist
int is_fullhouse(struct deck *hand)
{
    int i,n=1,l,m=1;
    for(i=1;i<5;i++)
        if(    karten_get_card_by_index(hand, 0).w \
            == karten_get_card_by_index(hand, i).w  )
            n++;
    if( (n==2) || (n==3) )
    {
        i=1;
        while(    karten_get_card_by_index(hand, 0).w \
               == karten_get_card_by_index(hand, i).w  )
            i++;
        for(l=i+1;l<5;l++)
            if(    karten_get_card_by_index(hand, i).w \
                == karten_get_card_by_index(hand, l).w  )
                m++;
    }
    if( ( (m==2) && (n==3) ) || ( (m==3) && (n==2) ) )
        return 1;
    else
        return 0;
}
// überprüft, ob ein Flush auf der Hand ist
int is_flush(struct deck *hand)
{
    int i;
    for(i=1;i<5;i++)
        if(    karten_get_card_by_index(hand, 0).f \
            != karten_get_card_by_index(hand, i).f  )
            return 0;
    return 1;
}
// überprüft, ob eine Straße auf der Hand ist
int is_straight(struct deck *hand)
{
    int i;
    karten_sortierer(&hand);
    if(   karten_get_card_by_index(hand, 1).w == 10    \
       && karten_get_card_by_index(hand, 2).w == bube  \
       && karten_get_card_by_index(hand, 3).w == dame  \
       && karten_get_card_by_index(hand, 4).w == konig \
       && karten_get_card_by_index(hand, 0).w == ass    )
        return 2;

    for(i=0;i<4;i++)
        if(    karten_get_card_by_index(hand, i).w+1 \
            != karten_get_card_by_index(hand, i+1).w  )
            return 0;
    return 1;
}

int is_straight_flush(struct deck *hand)
{
    return is_flush(hand) && is_straight(hand) ? 1 : 0;
}

int is_royal_flush(struct deck *hand)
{
    return is_flush(hand) && is_straight(hand) == 2 ? 1 : 0;
}

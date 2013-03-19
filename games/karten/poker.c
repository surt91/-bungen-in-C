#include "poker.h"

void poker_start()
{
    struct deck *stapel = NULL, *spieler = NULL;
    int i, n, konto = 100, einsatz = 0;
    char yn, k;
    const static int anzHand = 5, anzDecks = 1, anzPerDeck = 52;
    int runde = 0;
    int *toggle;
    toggle = (int *) calloc(anzHand, sizeof(int));

    setlocale(LC_ALL,"");
    initscr();
    raw();
    cbreak();
    echo();
    keypad(stdscr, TRUE);

    hs_highscore_init(POKER_HIGHSCORE_FILENAME);

    while(1)
    {
        karten_delete_stapel(&stapel);
        stapel = (struct deck *) malloc(sizeof(struct deck));
        karten_init_deck(stapel, anzDecks);
        // Mischen
        for(i=0;i<200*anzDecks;i++)
            karten_vertausche_zwei_karten(&stapel, rand()%(anzPerDeck*anzDecks+1)+1, rand()%(anzPerDeck*anzDecks+1)+1);

        einsatz = 0;

        mvprintw(1, 0, "Konto                % 5d", konto);
        mvprintw(2, 0, "Einsatz              % 5d", einsatz);
        mvprintw(3, 0, "Runde                % 5d", ++runde);

        einsatz = bj_setzen(konto);
        konto -= einsatz;

        mvprintw(1, 0, "Konto                % 5d", konto);
        mvprintw(2, 0, "Einsatz              % 5d", einsatz);
        refresh();

        for(i=0;i<anzHand;i++)
            karten_gebe_karte(&stapel, &spieler);
        move(5,0);
        karten_sortierer(&spieler);
        karten_show(spieler);

        mvprintw(BJ_BOT + 2, 0, "Welche Karten willst du Tauschen?");
        move(BJ_BOT + 3, 0);
        noecho();
        for(i=0;i<anzHand;i++)
            toggle[i] = 0;
        do
        {
            k = getch();
            if(k-'0'>0 && k-'0'<=5)
            {
                toggle[k-'0'-1]++;
                toggle[k-'0'-1] %= 2;
                if(toggle[k-'0'-1])
                    mvprintw(5 + k-'0'-1, 5, "X");
                else
                    mvprintw(5 + k-'0'-1, 5, " ");
                refresh();
            }
        } while(k != '\n');
        move(BJ_BOT + 2, 0);
        clrtoeol();
        echo();
        n=0;
        for(i=0;i<anzHand;i++)
            if(toggle[i])
            {
                karten_delete_by_index(&spieler, i-n);
                n++;
                karten_gebe_karte(&stapel, &spieler);
                mvprintw(5 + i, 5, " ");
            }

        move(5,0);
        karten_sortierer(&spieler);
        karten_show(spieler);

        konto += poker_gewinn(spieler, einsatz);
        karten_delete_stapel(&spieler);

        if(konto <= 0)
        {
            getch();
            hs_show_highscore(konto, "Geld", runde, "Runde", POKER_HIGHSCORE_FILENAME);
            getch();
            break;
        }

        mvprintw(BJ_BOT + 2, 0, "Enter: zum Weiterspielen.");
        mvprintw(BJ_BOT + 3, 0, "    Q: Beenden.");
        //~ mvprintw(BJ_BOT + 4, 0, "   F1: Hilfe");
        refresh();

        yn = 0;
        yn = getch();

        if(yn == 'Q' || yn == 'q')
        {
            hs_show_highscore(konto, "Geld", runde, "Runde", POKER_HIGHSCORE_FILENAME);
            break;
        }

        erase();
        refresh();
    }
    endwin();
    return;
}

int poker_gewinn(struct deck *hand, int einsatz)
{
    int faktor = 0;
    char *nachricht   = "Nichts!          Verloren!";
    switch(is_pair(hand))
    {
        case 1:
            faktor = 0;
            nachricht = "Pair!            Verloren!";
            break;
        case 2:
            faktor = 1;
            nachricht = "Jacks or Better! Gewinn: %d";
            break;
        case 5:
            faktor = 2;
            nachricht = "Two Pair!        Gewinn: %d";
            break;
        case 3:
            faktor = 3;
            nachricht = "Three of a Kind! Gewinn: %d";
            break;
        case 4:
            faktor = 25;
            nachricht = "Four of a Kind!  Gewinn: %d";
            break;
    }
    if(is_fullhouse(hand))
    {
        faktor = 9;
        nachricht     = "Fullhouse!       Gewinn: %d";
    }
    if(is_royal_flush(hand))
    {
        faktor = 250;
        nachricht     = "Royal Flush!     Gewinn: %d";
    }
    else if (is_straight_flush(hand))
    {
        faktor = 50;
        nachricht     = "Straight Flush!  Gewinn: %d";
    }
    else if (is_straight(hand))
    {
        faktor = 4;
        nachricht     = "Straight!        Gewinn: %d";
    }
    else if (is_flush(hand) && faktor != 25)
    {
        faktor = 6;
        nachricht     = "Flush!           Gewinn: %d";
    }
    mvprintw(BJ_BOT, 0, nachricht, faktor * einsatz);
    refresh();
    return faktor * einsatz;
}
void poker_monte_carlo_start()
{
    int runden, spieler;
    int *u;
    printf("Wieviele Runden?\n");
    scanf("%d",&runden);
    printf("Wieviele Mitspieler?\n");
    scanf("%d",&spieler);
    poker_monte_carlo(runden, spieler, &u);
    poker_monte_carlo_darstellen(u, spieler);
}
void poker_monte_carlo(int anzahl, int leute, int **ergebnis)
{
    struct deck *stapel = NULL, *spieler[leute];
    int i, j, n, flag=0;
    const static int anzHand = 5, anzDeck = 1, anzPerDeck = 52;
    //~ int flush[leute], straight[leute], royal_flush[leute];
    //~ int fullhouse[leute], runden[leute], straight_flush[leute];
    //~ int pair[leute], three_of_a_kind[leute], two_pair[leute];
    //~ int four_of_a_kind[leute];
    int *flush, *straight, *royal_flush, *fullhouse, *runden, *pair,
        *straight_flush, *three_of_a_kind, *two_pair, *four_of_a_kind;

    //~ *spieler        = (struct deck *) calloc(leute, sizeof(struct deck));
    flush           = (int *) calloc(leute, sizeof(int));
    straight        = (int *) calloc(leute, sizeof(int));
    royal_flush     = (int *) calloc(leute, sizeof(int));
    straight_flush  = (int *) calloc(leute, sizeof(int));
    three_of_a_kind = (int *) calloc(leute, sizeof(int));
    two_pair        = (int *) calloc(leute, sizeof(int));
    pair            = (int *) calloc(leute, sizeof(int));
    four_of_a_kind  = (int *) calloc(leute, sizeof(int));
    fullhouse       = (int *) calloc(leute, sizeof(int));
    runden          = (int *) calloc(leute, sizeof(int));

    for(j=0; j<leute; j++)
    {
        flush[j] = straight[j] = straight_flush[j] \
         = royal_flush[j] = fullhouse[j] = pair[j] =two_pair[j] \
         = three_of_a_kind[j] = four_of_a_kind[j] = runden[j] = 0;
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
            flag = 0;
            switch(is_pair(spieler[j]))
            {
                case 1:
                case 2:
                    pair[j]++;
                    break;
                case 5:
                    two_pair[j]++;
                    break;
                case 3:
                    three_of_a_kind[j]++;
                    break;
                case 4:
                    four_of_a_kind[j]++;
                    flag = 1;
                    break;
                case 6:
                    fullhouse[j]++;
                    flag = 1;
                    break;
            }
            if(!flag)
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
            }
            runden[j]++;
        }
    }
    *ergebnis = (int *) malloc(10 * leute * sizeof(int));
    for(j=0; j<leute; j++)
    {
        (*ergebnis)[10 * j + 0] = pair[j];
        (*ergebnis)[10 * j + 1] = two_pair[j];
        (*ergebnis)[10 * j + 2] = three_of_a_kind[j];
        (*ergebnis)[10 * j + 3] = straight[j];
        (*ergebnis)[10 * j + 4] = flush[j];
        (*ergebnis)[10 * j + 5] = fullhouse[j];
        (*ergebnis)[10 * j + 6] = four_of_a_kind[j];
        (*ergebnis)[10 * j + 7] = straight_flush[j];
        (*ergebnis)[10 * j + 8] = royal_flush[j];
        (*ergebnis)[10 * j + 9] = runden[j];
    }

    for(j=0; j<leute; j++)
        karten_delete_stapel(&(spieler[j]));
    karten_delete_stapel(&stapel);

    free(flush);
    free(straight);
    free(royal_flush);
    free(straight_flush);
    free(three_of_a_kind);
    free(two_pair);
    free(pair);
    free(four_of_a_kind);
    free(fullhouse);
    free(runden);
}

void poker_monte_carlo_darstellen(int *u, int anzSpieler)
{
    int i, j, tmp;
    double runden = 0;
    const static int anzWins = 9;

    char *bezeichnungen[anzWins];
    char  *pair            = "           Pair", \
          *two_pair        = "       Two Pair", \
          *three_of_a_kind = "Three of a Kind", \
          *straight        = "       Straight", \
          *flush           = "          Flush", \
          *fullhouse       = "      Fullhouse", \
          *four_of_a_kind  = " Four of a Kind", \
          *straight_flush  = " Straight Flush", \
          *royal_flush     = "    Royal Flush";

    //~ *bezeichnungen = (char *) calloc(anzWins, sizeof(char));
    bezeichnungen[0] = pair;
    bezeichnungen[1] = two_pair;
    bezeichnungen[2] = three_of_a_kind;
    bezeichnungen[3] = straight;
    bezeichnungen[4] = flush;
    bezeichnungen[5] = fullhouse;
    bezeichnungen[6] = four_of_a_kind;
    bezeichnungen[7] = straight_flush;
    bezeichnungen[8] = royal_flush;

    for (i=anzWins; i < anzSpieler*(anzWins+1); i+=(anzWins+1))
        runden += u[i];

    printf("Über %g Runden (%g verteilte Karten) gesammelte Messwerte\n", runden, runden*5);
    printf("             #");
    for(i=0;i<anzSpieler;i++)
        printf(" % 5d", i+1);
    printf("  Summe          %%\n");

    for(j=0; j < anzWins; j++)
    {
        printf("%s", bezeichnungen[j]);
        for (tmp = 0, i=j; i < (anzWins+1)*anzSpieler; i+=(anzWins+1))
        {
            if(u[i]>=10000000)
                printf(" % 4dM", u[i]/1000);
            else if(u[i]>=10000)
                printf(" % 4dk", u[i]/1000);
            else
                printf(" % 5d", u[i]);
            tmp += u[i];
        }
        if(tmp>=100000000)
                printf(" % 5dM", u[i]/1000);
        else if(tmp>=100000)
            printf(" % 5dk", tmp/1000);
        else
            printf(" % 6d", tmp);
        printf(" % 8.4f%%", 100*tmp/runden);
        printf("\n");
    }
    return;
}

int is_pair(struct deck *hand)
{
    int i, j, n=0, l[13], m=0;
    enum wert tmp = zwei;

    for(j=0;j<13;j++)
        l[j] = 0;

    for(i=0;i<5;i++)
        l[karten_get_card_by_index(hand, i).w]++;
    for(j=0;j<13;j++)
        if(l[j]>1)
        {
            if(!n)
            {
                n=l[j];
                tmp = j;
            }
            else
                m=l[j];
        }
    if(!n)
        return 0;
    if(n==4)
        return 4;
    if(( (m==2) && (n==3) ) || ( (m==3) && (n==2) ))
        return 6;
    if(n==3)
        return 3;
    if(n==2 && m==2)
        return 5;
    if(n==2 && tmp >= bube)
        return 2;
    if(n==2)
        return 1;
    return -1;
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
    if(   karten_get_card_by_index(hand, 0).w == zehn  \
       && karten_get_card_by_index(hand, 1).w == bube  \
       && karten_get_card_by_index(hand, 2).w == dame  \
       && karten_get_card_by_index(hand, 3).w == konig \
       && karten_get_card_by_index(hand, 4).w == ass    )
        return 2;

    if(   karten_get_card_by_index(hand, 0).w == zwei \
       && karten_get_card_by_index(hand, 1).w == drei \
       && karten_get_card_by_index(hand, 2).w == vier \
       && karten_get_card_by_index(hand, 3).w == funf \
       && karten_get_card_by_index(hand, 4).w == ass   )
        return 1;

    for(i=0;i<4;i++)
        if( (   karten_get_card_by_index(hand, i).w+1  \
             != karten_get_card_by_index(hand, i+1).w ) )
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

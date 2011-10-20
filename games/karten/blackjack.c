#include "blackjack.h"

void bj_test()
{
    int i, tmpS, tmpB, status, x, y;
    char yn;
    struct deck *stapel, *spieler, *bank;

    setlocale(LC_ALL,"");
    initscr();
    raw();
    cbreak();
    echo();
    keypad(stdscr, TRUE);

    stapel = (struct deck *) malloc(sizeof(struct deck));
    karten_init_deck(stapel, 1);
    // Mischen
    for(i=0;i<200;i++)
        karten_vertausche_zwei_karten(&stapel, rand()%53+1, rand()%53+1);

    // TODO: Wetteinsätze

    status = 0;

    spieler = NULL;
    bank    = NULL;

    karten_gebe_karte(&stapel, &spieler);
    karten_gebe_karte(&stapel, &bank);
    karten_gebe_karte(&stapel, &spieler);

    if(bj_summiere_augen(spieler) == 21)
    {
        printw("Blackjack! Du gewinnst.\n");
        status = 2;
    }
    if(!status)
        while(1)
        {
            move(BJ_TOP, 0);
            printw("Croupier:");
            move(BJ_TOP + 1, 0);
            karten_show(bank);
            move(BJ_TOP, BJ_RIGHT);
            printw("Deine Hand:");
            move(BJ_TOP + 1, BJ_RIGHT);
            karten_show(spieler);
            tmpS =  bj_summiere_augen(spieler);
            tmpB =  bj_summiere_augen(bank);
            getyx(stdscr, y, x);
            move(y+1, 0);
            printw("Punkte: %d", tmpB);
            move(y+1, BJ_RIGHT);
            printw("Punkte: %d", tmpS);
            move(y+2, BJ_RIGHT);
            if(tmpS > 21)
            {
                move(y+3, 7);
                printw("Du hast dich überkauft! Die Bank gewinnt.");
                status = 1;
                break;
            }
            printw("Weitere Karte? (y/n) ");
            refresh();
            yn = getch();
            if(yn == 'n' || yn == 0)
                break;
            karten_gebe_karte(&stapel, &spieler);
            erase();
        }

    if(!status)
    {
        while(bj_summiere_augen(bank)<17)
            karten_gebe_karte(&stapel, &bank);
        move(BJ_TOP, 0);
        printw("Croupier:");
        move(BJ_TOP + 1, 0);
        karten_show(bank);
        tmpB =  bj_summiere_augen(bank);
        move(y+1, 0);
        printw("Punkte: %d", tmpB);
        move(y+1, BJ_RIGHT);
        printw("Punkte: %d", tmpS);
        move(y+5, 0);
        if(tmpB > 21)
            printw("Die Bank hat sich überkauft! Du gewinnst.");
        else if(tmpS > tmpB)
            printw("Du gewinnst.");
        else if(tmpS < tmpB)
            printw("Die Bank gewinnt.");
        else if(tmpS == tmpB)
            printw("Unentschieden.");
    }
    refresh();
    getch();
    endwin();
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

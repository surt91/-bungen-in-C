#include "blackjack.h"

void blackjack_start()
{
    int i, tmpS, tmpB, status, x=0, y=0, konto = 100, einsatz = 0, tmp, runde = 0;
    char yn;
    struct deck *stapel, *spieler, *bank;

    setlocale(LC_ALL,"");
    initscr();
    raw();
    cbreak();
    echo();
    keypad(stdscr, TRUE);

    hs_highscore_init(BLACKJACK_HIGHSCORE_FILENAME);

    stapel = (struct deck *) malloc(sizeof(struct deck));
    karten_init_deck(stapel, 1);
    // Mischen
    for(i=0;i<200;i++)
        karten_vertausche_zwei_karten(&stapel, rand()%53+1, rand()%53+1);

    while(1)
    {
        einsatz = 0;
        mvprintw(1, x, "Konto   % 5d", konto);
        mvprintw(2, 0, "Einsatz % 5d", einsatz);
        mvprintw(3, 0, "Runde   % 5d", ++runde);

        do
        {
            mvprintw(15, 0, "Wieviel setzt du? ");
            move(16,0);
            scanw("%d", &tmp);
            if(tmp>konto)
            {
                mvprintw(17, 0,"Soviel Geld hast du nicht!");
                getch();
            }
            move(17, 0);
            clrtoeol();
        } while(tmp > konto);
        move(15, 0);
        clrtoeol();
        move(16, 0);
        clrtoeol();

        einsatz = tmp;
        konto -= einsatz;
        mvprintw(1, 0, "Konto   % 5d", konto);
        mvprintw(2, 0, "Einsatz % 5d", einsatz);
        refresh();

        status = BJ_HIT;

        spieler = NULL;
        bank    = NULL;

        karten_gebe_karte(&stapel, &spieler);
        karten_gebe_karte(&stapel, &bank);
        karten_gebe_karte(&stapel, &spieler);

        if(bj_summiere_augen(spieler) == 21)
        {
            mvprintw(15, 0,"Blackjack! Du gewinnst %d€.", 3*einsatz);
            konto += 3*einsatz;
            karten_show(spieler);
            status = BJ_BLACKJACK;
        }

        while(status == BJ_HIT)
        {
            bj_zeige_hande(spieler, bank);
            printw("Weitere Karte? Verdoppeln? (y/n/d) ");
            refresh();
            yn = getch();
            if(yn == 'd')
            {
                if(einsatz > konto)
                    mvprintw(y+3, BJ_RIGHT, "Dazu bist du zu arm");
                else
                {
                    konto -= einsatz;
                    einsatz *= 2;
                    karten_gebe_karte(&stapel, &spieler);
                    status = BJ_STAY;
                }
            }
            else if(yn == 'y' || yn == 1)
                karten_gebe_karte(&stapel, &spieler);
            else if(yn == 'n' || yn == 0)
               status = BJ_STAY;
            if(bj_summiere_augen(spieler) > 21)
            {
                move(y+3, 7);
                printw("Du hast dich überkauft! Die Bank gewinnt.");
                status = BJ_BUST;
            }
            refresh();
        }

        if(status != BJ_BLACKJACK && status != BJ_BUST)
        {
            while(bj_summiere_augen(bank)<17)
                karten_gebe_karte(&stapel, &bank);

            tmpS =  bj_summiere_augen(spieler);
            tmpB =  bj_summiere_augen(bank);
            bj_zeige_hande(spieler, bank);
            if(tmpB > 21)
            {
                mvprintw(15, 0,"Die Bank hat sich überkauft! Du gewinnst %d€.", 2*einsatz);
                konto += 2*einsatz;
            }
            else if(tmpS > tmpB)
            {
                mvprintw(15, 0,"Du gewinnst %d€.", 2*einsatz);
                konto += 2*einsatz;
            }
            else if(tmpS < tmpB)
            {
                mvprintw(15, 0,"Die Bank gewinnt.");
            }
            else if(tmpS == tmpB)
            {
                mvprintw(15, 0,"Unentschieden. Du erhälst die %d€ Einsatz zurück.", einsatz);
                konto += einsatz;
            }
        }
        bj_zeige_hande(spieler, bank);
        if(konto <= 0)
        {
            getch();
            hs_show_highscore(konto, "Geld", runde, "Runde", BLACKJACK_HIGHSCORE_FILENAME);
            getch();
            break;
        }
        mvprintw(17, 0, "Enter zum Weiterspielen. Q zum Beenden.");
        yn = 0;
        yn = getch();
        if(yn == 'Q' || yn == 'q')
        {
            hs_show_highscore(konto, "Geld", runde, "Runde", BLACKJACK_HIGHSCORE_FILENAME);
            break;
        }
        erase();
        refresh();
    }
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

void bj_zeige_hande(struct deck *spieler, struct deck *bank)
{
    int x=0, y=0, tmpB, tmpS;
    move(BJ_TOP, 0);
    clrtobot();
    move(BJ_TOP, x);
    printw("Croupier:");
    move(BJ_TOP + 1, x);
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
    refresh();
    return;
}

#include "blackjack.h"

void blackjack_start()
{
    int i, tmpS, tmpB, status, anzKarten = 0;
    int konto = 100, einsatz = 0, runde = 0;
    const static int anzDecks = 6, anzPerDeck = 52;
    char yn;
    struct deck *stapel = NULL, *spieler = NULL, *bank = NULL;

    setlocale(LC_ALL,"");
    initscr();
    raw();
    cbreak();
    echo();
    keypad(stdscr, TRUE);

    hs_highscore_init(BLACKJACK_HIGHSCORE_FILENAME);

    while(1)
    {
        if(anzKarten<=40)
        {
            karten_delete_stapel(&stapel);
            stapel = (struct deck *) malloc(sizeof(struct deck));
            karten_init_deck(stapel, anzDecks);
            // Mischen
            for(i=0;i<200*anzDecks;i++)
                karten_vertausche_zwei_karten(&stapel, rand()%(anzPerDeck*anzDecks+1)+1, rand()%(anzPerDeck*anzDecks+1)+1);
            anzKarten = anzPerDeck * anzDecks;
        }

        einsatz = 0;
        status = BJ_START;

        mvprintw(1, 0, "Konto                % 5d", konto);
        mvprintw(2, 0, "Einsatz              % 5d", einsatz);
        mvprintw(3, 0, "Runde                % 5d", ++runde);
        mvprintw(4, 0, "Karten im Schlitten  % 5d", anzKarten);

        einsatz = bj_setzen(konto);
        konto -= einsatz;

        mvprintw(1, 0, "Konto                % 5d", konto);
        mvprintw(2, 0, "Einsatz              % 5d", einsatz);
        refresh();

        karten_gebe_karte(&stapel, &spieler);
        karten_gebe_karte(&stapel, &bank);
        karten_gebe_karte(&stapel, &spieler);
        anzKarten -= 3;

        if(bj_summiere_augen(spieler) == 21)
            status = BJ_BLACKJACK;

        while(status == BJ_HIT)
        {
            mvprintw(4, 0, "Karten im Schlitten  % 5d", anzKarten);
            bj_zeige_hande(spieler, bank);

            printw("Weitere Karte? Verdoppeln? (y/n/d) ");
            refresh();

            yn = getch();

            if(yn == 'd')
            {
                if(einsatz > konto)
                    mvprintw(BJ_BOT + 2, BJ_RIGHT, "Dazu bist du zu arm");
                else
                {
                    konto -= einsatz;
                    einsatz *= 2;
                    karten_gebe_karte(&stapel, &spieler);
                    anzKarten--;
                    status = BJ_STAY;
                }
            }
            else if(yn == 'y' || yn == 1)
            {
                karten_gebe_karte(&stapel, &spieler);
                anzKarten--;
            }
            else if(yn == 'n' || yn == 0)
                status = BJ_STAY;
            if(bj_summiere_augen(spieler) > 21)
                status = BJ_BUST;
        }

        if(status != BJ_BLACKJACK && status != BJ_BUST)
        {
            while(bj_summiere_augen(bank)<17)
            {
                karten_gebe_karte(&stapel, &bank);
                anzKarten--;
            }

            tmpS =  bj_summiere_augen(spieler);
            tmpB =  bj_summiere_augen(bank);

            if(tmpB > 21)
                status = BJ_BANK_BUST;
            else if(tmpS > tmpB)
                status = BJ_WIN;
            else if(tmpS < tmpB)
                status = BJ_LOST;
            else if(tmpS == tmpB)
                status = BJ_REMIS;

        }

        mvprintw(4, 0, "Karten im Schlitten  % 5d", anzKarten);
        bj_zeige_hande(spieler, bank);
        konto += bj_gewinn(status, einsatz);

        karten_delete_stapel(&spieler);
        karten_delete_stapel(&bank);

        if(konto <= 0)
        {
            getch();
            hs_show_highscore(konto, "Geld", runde, "Runde", BLACKJACK_HIGHSCORE_FILENAME);
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
            summe += now + 2;
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
    int yS=0, yB=0, tmpB, tmpS, y=0, x=0;
    move(BJ_TOP, 0);
    clrtobot();
    mvprintw(BJ_TOP, x, "Croupier:");
    move(BJ_TOP + 1, x);
    karten_show(bank);
    getyx(stdscr, yB, x);
    mvprintw(BJ_TOP, BJ_RIGHT, "Deine Hand:");
    move(BJ_TOP + 1, BJ_RIGHT);
    karten_show(spieler);
    getyx(stdscr, yS, x);
    tmpS =  bj_summiere_augen(spieler);
    tmpB =  bj_summiere_augen(bank);
    y = yS > yB ? yS : yB;
    mvprintw(y+1, BJ_LEFT,  "Punkte: %d", tmpB);
    mvprintw(y+1, BJ_RIGHT, "Punkte: %d", tmpS);
    move(y+2, BJ_RIGHT);
    refresh();
    return;
}

int bj_gewinn(int status, int einsatz)
{
    int faktor;
    char *nachricht;
    switch(status)
    {
        case BJ_WIN:
            faktor = 2;
            nachricht = "Du gewinnst %d€.";
            break;
        case BJ_LOST:
            faktor = 0;
            nachricht = "Die Bank gewinnt.";
            break;
        case BJ_REMIS:
            faktor = 1;
            nachricht = "Unentschieden. Du erhälst die %d€ Einsatz zurück.";
            break;
        case BJ_BUST:
            faktor = 0;
            nachricht = "Du hast dich überkauft! Die Bank gewinnt.";
            break;
        case BJ_BANK_BUST:
            faktor = 2;
            nachricht = "Die Bank hat sich überkauft! Du gewinnst %d€.";
            break;
        case BJ_BLACKJACK:
            faktor = 3;
            nachricht = "Blackjack! Du gewinnst %d€.";
            break;
        default:
            faktor = 666;
            nachricht = "Irgendetwas böses geht hier ab!";
            break;
    }
    mvprintw(BJ_BOT, 0, nachricht, faktor * einsatz);
    refresh();
    return faktor * einsatz;
}

int bj_setzen(int konto)
{
    int tmp;
    do
    {
        mvprintw(BJ_BOT, 0, "Wieviel setzt du? ");
        move(BJ_BOT + 1, 0);
        scanw("%d", &tmp);
        if(tmp>konto)
        {
            mvprintw(BJ_BOT + 2, 0,"Soviel Geld hast du nicht!");
            move(BJ_BOT + 1, 0);
            clrtoeol();
        }
    } while(tmp > konto);
    move(BJ_BOT, 0);
    clrtobot();
    return tmp;
}

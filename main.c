#include "main.h"

void aufg_4_5()
{
    double netto_preis, mwsteuer, preis;
    mwsteuer = preis = 0;
    printf("Nettopreis?\n");
    scanf("%lf", &netto_preis);
    mwsteuer=netto_preis*0.19;
    preis=mwsteuer+netto_preis;
    printf("Das Produkt kostet:\nNetto   :\t%.2lf€\nSteuern :\t%.2lf€\nBrutto  :\t%.2lf€\n", netto_preis, mwsteuer, preis);
}

void aufg_4_13()
{
    int n;
    printf("Es wird von n bis 2n aufsummiert.\nn?\n");
    scanf("%d", &n);
    printf("%d", aufsummieren(n));
}

void aufg_4_17()
{
    int sum_g=0, sum_ug=0, n;
    printf("Die ersten wieviel geraden/ungeraden Zahlen sollen aufaddiert werden?\n");
    scanf("%d", &n);
    summe_g_ug(n, &sum_g, &sum_ug);
    printf("Gerade  : %d\nUngerade: %d", sum_g, sum_ug);
}

void aufg_4_25()
{
    int n,i,fibo=0,k=0;
    printf("Wieviele Fibonacci-Primzahlen sollen ausgegeben werden?\n");
    scanf("%d", &n);
    for(i=3;k<n;i++)
    {
        fibo=fibonacci(i);
        if(ist_prim(fibo) && fibo > 1)
        {
            printf("%d, ", fibo);
            k++;
        }
    }
    printf(" sind die ersten %d Fibonacci Zahlen, die auch Primzahlen sind",k);
}

void aufg_5_2()
{
    int n, x;
    printf("Basis?\n");
    scanf("%d", &x);
    printf("Potenz?\n");
    scanf("%d", &n);
    printf("Ergebnis: %d", power(x,n));
    return;
}

void aufg_5_3()
{
    int i;
    char h = 'H', leer = ' ';

    for(i=1;i<=4;i++){
        schreibe_zeichen(h,2);
        schreibe_zeichen(leer,8);
        schreibe_zeichen(h,2);
        printf("\n");
    }
    for(i=1;i<=2;i++){
        schreibe_zeichen(h,12);
        printf("\n");
    }
    for(i=1;i<=4;i++){
        schreibe_zeichen(h,2);
        schreibe_zeichen(leer,8);
        schreibe_zeichen(h,2);
        printf("\n");
    }
    return;
}

void aufg_5_4()
{
    int k;
    printf("Aus welcher Zahl soll die 4te Wurzel gezogen werden?\n");
    scanf("%d",&k);
    printf("%f", wurzel4(k));
    return;
}

void aufg_5_8()
{
    int x, a, b, c;
    printf("f(x)=ax^2+bx+c\nGib die Parameter in der Reihenfolge: x a b c getrennt durch Leerzeichen ein.\n");
    scanf("%d %d %d %d", &x, &a, &b, &c);
    printf("f(x)=%d\n", f(x, a, b, c));
}

void aufg_5_12()
{
    int k,q;
    printf("Die wievielte Fibonacci Zahl soll überprüft werden?\n");
    scanf("%d",&k);
    q=fibonacci(k+1);
    if(ist_prim(q))
    {
        printf("Die %d. Fibonacci Zahl %d ist eine Primzahl\n", k, q);
    }
    else
    {
        printf("Die %d. Fibonacci Zahl %d ist keine Primzahl\n", k, q);
    }
    return;
}

void aufg_5_14()
{
    int k;
    printf("Welche Zahl soll in ihre Primfaktoren zerlegt werden?\n");
    scanf("%d",&k);
    primfaktoren(k);
    return;
}

void aufg_5_18()
{
    int zahl=0, kopf=0, k;
    printf("Wie oft soll die Münze geworfen werden?\n");
    scanf("%d",&k);
    muenzwurf(k, &kopf, &zahl);
    printf("Würfe: %d\nKopf: %d\nZahl: %d\n", k, kopf, zahl);
    return;
}

void aufg_5_19()
{
    int k, e;
    printf("Wie wieviele Personen stehen im Raum?\n");
    scanf("%d",&k);
    e=monteCarloGeburtstagsProblem(k);
    printf("Die Wahrscheinlichkeit, dass mindestens 2 im gleichen Monat Geburtstag haben liegt bei etwa %d Prozent\n", e);
    return;
}

void aufg_6_2()
{
    float k;
    printf("Zu welcher Zahl soll das Inverse (Reziproken Wert) gebildet werden?\n");
    scanf("%f", &k);
    printf("Inverses von %g ist %g", k, invers(k));
    return;
}

void aufg_6_8()
{
    int n;
    short a;
    printf("Welche Zahl soll geshiftet werden? (max. 16 Bit)\n");
    scanf("%hd", &a);
    d2b(a,16);
    printf("\nUm wieviele Stellen soll sie geshiftet werden?\n");
    scanf("%d", &n);
    printf("%d\n", zyklischer_shift(a,n));
    d2b(zyklischer_shift(a,n),16);

    return;
}

void aufg_6_9()
{
    short a;
    printf("Welche Zahl soll bitweise gespiegelt werden? (max 16 Bit)\n");
    scanf("%hd", &a);
    d2b(a,16);
    printf("\nGespiegelt ergibt sich %d\n",spiegel(a));
    d2b(spiegel(a),16);
    return;
}

void aufg_6_12()
{
    int x, y, z, w;
    printf("Von welchen 4 Zahlen, soll das Maximum gefunden werden? (getrennt durch Kommata)\n");
    scanf("%d,%d,%d,%d", &x, &y,&z,&w);
    printf("%d ist die größte der vier Zahlen\n", max4(x,y,z,w));
    return;
}

void aufg_6_16()
{
    int x, k, kugel, besitz, einsatz, gewinn,runde;
    k=-1;
    runde=1;
    besitz=100;
    while(1)
    {
        printf("Roulette\t\tRunde%d\nWorauf setzt du?\n1: Gerade\n2: Ungerade\n3: Zahl\n666: zum Beenden\n\n",runde);
        while(x!=1 && x!=2 && x!=3 && x!=666)
        {
            scanf("%d", &x);

            if(x==3)
            {
                printf("Auf welche Zahl zwischen 0 und 35 setzt du?\n");
                while(k<0 || k>35)
                {
                    scanf("%d",&k);
                    if(k<0 || k>35)
                    {
                        printf("Wähle eine Zahl zwischen 0 und 35.\n");
                    }
                    else
                    {
                        printf("Du setzt auf die %d!\n",k);
                    }
                }
            }
            else if(x==1)
            {
                k=36;
            }
            else if(x==2)
            {
                k=37;
            }
            else if(x==666)
            {
                return;
            }
            else
            {
                printf("Wähle eine der genannten Zahlen:\n1: Gerade\n2: Ungerade\n3: Zahl\n666: zum Beenden\n\n");
            }
        }
        x=0;
        printf("Wieviel setzt du?\nDu hast %d€\n", besitz);
        scanf("%d", &einsatz);
        besitz-=einsatz;
        kugel = roulette();
        runde++;
        printf("Die Kugel ist auf %d liegen geblieben!\n", kugel);
        gewinn=roulette_gewinn_faktor(k,kugel);
        if(gewinn)
        {
            besitz+=gewinn*einsatz;
            printf("Du hast Gewonnen!\nDu erhälst %d€\nDu hast jetzt %d€\n\n", gewinn*einsatz, besitz);
        }
        else if(besitz>0)
        {
            printf("Leider verloren. Du hast noch %d€\n\n", besitz);
        }
        else
        {
            printf("Du bist leider Pleite und wirst aus dem Kasino geworfen!\n\n");
            return;
        }
    }
    return;
}

void aufg_6_17()
{
    int tag, monat, jahr, gepackt, etag,emonat,ejahr,toggle;
    printf("Entpacken: 0\nPacken: 1\n");
    scanf("%d",&toggle);
    if(toggle)
    {
        printf("\n\nWelches Datum soll gepackt werden? (dd.mm.yy)\n");
        scanf("%d.%d.%d", &tag, &monat, &jahr);
        jahr%=100;
        printf("\nBinär: ");d2b(tag,5);d2b(monat,4);d2b(jahr,7);
        gepackt=datum_packer(tag,monat,jahr);
        printf("\nSo sieht das Datum gepackt aus:\nDezimal: %d\nBinär: ", gepackt);
        d2b(gepackt,16);
        datum_entpacker(gepackt,&etag,&emonat,&ejahr);
        printf("\nZur Kontrolle:\nentpackt:\nDezimal: %d.%d.%d\nBinär: ", etag, emonat, ejahr);
        d2b(etag,5);d2b(emonat,4);d2b(ejahr,7);
        printf("\n\ngepackt:\n%d", gepackt);
    }
    else
    {
        printf("\n\nWelches Datum soll entpackt werden? (dezimal)\n");
        scanf("%d", &gepackt);
        printf("\nBinär: ");d2b(gepackt,16);
        datum_entpacker(gepackt,&tag,&monat,&jahr);
        printf("\nSo sieht das Datum entpackt aus:\nDezimal: %d.%d.%d", tag,monat,jahr);
        gepackt=datum_packer(tag,monat,jahr);
        printf("\nZur Kontrolle:\ngepackt:\nDezimal: %d\nBinär: ", gepackt);
        d2b(gepackt,16);
        printf("\n\nentpackt:\n%d.%d.%d", tag,monat,jahr);
    }

    return;
}

void aufg_6_23()
{
    struct card hand[5];
    karten_geber(hand);
    karten_sortierer(hand);
    karten_zeiger(hand);
}

void aufg_6_24()
{
    struct card hand[5];
    int i, flush=0, fullhouse=0, straight=0, straight_flush=0, royal_flush=0, runden=0, limit;
    printf("Wieviele Runden sollen gegeben werden?\n");
    scanf("%d", &limit);
    for(i=0;i<limit;i++)
    {
        karten_geber(hand);
        if(is_straight(hand)==2)
        {
            if(is_flush(hand))
            {
                royal_flush++;
                runden++;
                printf("#%4d: Royal Flush!", runden);
                karten_zeiger(hand);
            }
            else
            {
                straight++;
                runden++;
                printf("#%4d: Straße!", runden);
                karten_zeiger(hand);
            }
        }
        else if(is_straight(hand))
        {
            if(is_flush(hand))
            {
                straight_flush++;
                runden++;
                printf("#%4d: Straight Flush!", runden);
                karten_zeiger(hand);
            }
            else
            {
                straight++;
                runden++;
                printf("#%4d: Straße!", runden);
                karten_zeiger(hand);
            }
        }
        else if(is_flush(hand))
        {
            flush++;
            runden++;
            printf("#%4d: Flush!", runden);
            karten_zeiger(hand);
        }
        else if(is_fullhouse(hand))
        {
            fullhouse++;
            runden++;
            printf("#%4d: Fullhouse!", runden);
            karten_zeiger(hand);
        }
        else
        {
            runden++;
        }
    }
    printf("In %d Runden wurden\n %4d Straßen\n %4d Flushs\n %4d Fullhouses\n %4d Straight Flush\n %4d Royal Flush\nverteilt", runden, straight, flush, fullhouse, straight_flush, royal_flush);
}

void aufg_7_8()
{
	int *polynom=0, grad, i, x, fvonx;
	polynom=polynom_eingabe(polynom, &grad);
	printf("Welchen Wert soll x haben?\n");
	scanf("%d", &x);
	//fvonx=polynom_naiv(polynom, x, grad);
	fvonx=polynom_horner(polynom, x, grad);
	printf("\nf(%d) = %lld\n", x, fvonx);
}

void aufg_7_9()
{
	int *erstes_polynom, *zweites_polynom, *ergebnis_polynom, grad_eins, grad_zwei, grad_ergebnis;
	printf("Zwei Polynome addieren.\n");
	printf("Wie lautet das erste Polynom?\n");
	erstes_polynom = polynom_eingabe(erstes_polynom, &grad_eins);
	printf("Wie lautet das zweite Polynom?\n");
	zweites_polynom = polynom_eingabe(zweites_polynom, &grad_zwei);
	printf("Polynom eins: %d. Grad\nPolynom zwei: %d. Grad\n", grad_eins, grad_zwei);
	ergebnis_polynom = polynom_addierer(ergebnis_polynom, erstes_polynom, zweites_polynom, &grad_ergebnis, grad_eins, grad_zwei);
	printf("Das addierte Polynom(%d. Grad):\n", grad_ergebnis);
	polynom_anzeige(ergebnis_polynom, grad_ergebnis);
}

void aufg_7_10()
{
	int *erstes_polynom, *zweites_polynom, *ergebnis_polynom, grad_eins, grad_zwei, grad_ergebnis;
	printf("Zwei Polynome multiplizieren.\n");
	printf("Wie lautet das erste Polynom?\n");
	erstes_polynom = polynom_eingabe(erstes_polynom, &grad_eins);
	printf("Wie lautet das zweite Polynom?\n");
	zweites_polynom = polynom_eingabe(zweites_polynom, &grad_zwei);
	printf("Polynom eins: %d. Grad\nPolynom zwei: %d. Grad\n", grad_eins, grad_zwei);
	ergebnis_polynom = polynom_multiplizierer(ergebnis_polynom, erstes_polynom, zweites_polynom, &grad_ergebnis, grad_eins, grad_zwei);
	printf("Das multiplizierte Polynom (%d. Grad):\n", grad_ergebnis);
	polynom_anzeige(ergebnis_polynom, grad_ergebnis);
}

void aufg_7_15()
{
	char *string;
	size_t laenge=100;
	string = (char *) calloc(laenge, sizeof(char));
	printf("Welcher String soll auf Palindromität untersucht werden.\n");
	//scanf("%s", string);
	laenge=getline(&string, &laenge, stdin);
	string[laenge-1]= '\0';
	printf("\"%s\", %d Buchstaben\n", string, laenge-1);
	if(ist_palindrom(string, laenge))
		printf("\"%s\" ist ein Palindrom\n", string);
	else
		printf("\"%s\" ist kein Palindrom\n", string);
}

int main(int argc, char **argv)
{
    int aufgnr, kapitel;
    srand( (unsigned) time(NULL) ) ;
    if(argc != 3)
    {
        printf("Welches Kapitel?\n");
        scanf("%d", &kapitel);
        printf("Welche Übungsaufgabe?\n");
        scanf("%d", &aufgnr);
    }
    else
    {
        kapitel=atoi(argv[1]);
        aufgnr =atoi(argv[2]);
    }
    switch (kapitel)
    {
        case 4:
            switch (aufgnr)
            {
                case 5:
                    aufg_4_5();
                    break;
                case 13:
                    aufg_4_13();
                    break;
                case 17:
                    aufg_4_17();
                    break;
                case 25:
                    aufg_4_25();
                    break;
            }
            break;
        case 5:
            switch (aufgnr)
            {
                case 2:
                    aufg_5_2();
                    break;
                case 3:
                    aufg_5_3();
                    break;
                case 4:
                    aufg_5_4();
                    break;
                case 8:
                    aufg_5_8();
                    break;
                case 12:
                    aufg_5_12();
                    break;
                case 14:
                    aufg_5_14();
                    break;
                case 18:
                    aufg_5_18();
                    break;
                case 19:
                    aufg_5_19();
                    break;

            }
            break;
        case 6:
            switch (aufgnr)
            {
                case 2:
                    aufg_6_2();
                    break;
                case 8:
                    aufg_6_8();
                    break;
                case 9:
                    aufg_6_9();
                    break;
                case 12:
                    aufg_6_12();
                    break;
                case 16:
                    aufg_6_16();
                    break;
                case 17:
                    aufg_6_17();
                    break;
                case 23:
                    aufg_6_23();
                    break;
                case 24:
                    aufg_6_24();
                    break;
            }
		case 7:
            switch (aufgnr)
            {
                case 8:
                    aufg_7_8();
                    break;
                case 9:
                    aufg_7_9();
                    break;
                case 10:
                    aufg_7_10();
                    break;
                case 15:
                    aufg_7_15();
                    break;
			}
            break;
    }
    return 0;
}

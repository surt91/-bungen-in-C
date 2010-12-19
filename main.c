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
    printf("sind die ersten %d Fibonacci Zahlen, die auch Primzahlen sind\n",k);
}
void aufg_4_26()
{    unsigned n,i, *fibo_array=0, prim_max;
    short *prim_array;
    printf("Wieviele Fibonacci-Primzahlen sollen ausgegeben werden?\n");
    scanf("%d", &n);
    fibo_array = (unsigned *) calloc(n+1, sizeof(unsigned));
    fibonacci_array(n, fibo_array);
    prim_max=fibo_array[n];
    prim_array = (short *) calloc(prim_max, sizeof(short));
    primzahl(prim_max, prim_array);
    for(i=1;i<=n;i++)
    {
		if(!prim_array[fibo_array[i]])
			printf("%d, ", fibo_array[i]);
	}
	free(prim_array);
	free(fibo_array);
    printf("sind die Primzahlen unter den ersten %d Fibonacci Zahlen\n",n);
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
    int k,q, *array;
    printf("Die wievielte Fibonacci Zahl soll überprüft werden?\n");
    scanf("%d",&k);
    array = (int *) calloc(k+1, sizeof(int));
    array=fibonacci_array(k, array);
    q=array[k];
    if(q<0)
    {
		printf("Bitte gebe eine ganze Zahl größer gleich 1 an.\n");
		return;
	}
    if(ist_prim_array(q))
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
	printf("\n");
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
    printf("\n");
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
    return;
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
    printf("In %d Runden wurden\n %4d Straßen\n %4d Flushs\n %4d Fullhouses\n %4d Straight Flush\n %4d Royal Flush\nverteilt\n", runden, straight, flush, fullhouse, straight_flush, royal_flush);
    return;
}

void aufg_7_8()
{
	int *polynom=0, grad, i, x, fvonx;
	polynom=polynom_eingabe(polynom, &grad);
	printf("Welchen Wert soll x haben?\n");
	scanf("%d", &x);
	//fvonx=polynom_naiv(polynom, x, grad);
	fvonx=polynom_horner(polynom, x, grad);
	printf("\nf(%d) = %d\n", x, fvonx);
	return;
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
	return;
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
	return;
}

void aufg_7_11()
{
	int *polynom_in, *polynom_out, grad_in, grad_out;
	printf("Ein Polynom ableiten.\n");
	printf("Wie lautet das Polynom?\n");
	polynom_in = polynom_eingabe(polynom_in, &grad_in);
	polynom_out = polynom_ableiter(polynom_out, polynom_in, &grad_out, grad_in);
	printf("Das differenzierte Polynom (%d. Grad):\n", grad_out);
	polynom_anzeige(polynom_out, grad_out);
	return;
}
void aufg_7_15()
{
	char *string;
	size_t laenge=100;
	string = (char *) calloc(laenge, sizeof(char));
	printf("Welcher String soll auf Palindromität untersucht werden.\n");
	laenge=getline(&string, &laenge, stdin);
	string[laenge-1]= '\0';
	printf("\"%s\", %d Buchstaben\n", string, (int)laenge-1);
	if(ist_palindrom(string, laenge))
		printf("\"%s\" ist ein Palindrom\n", string);
	else
		printf("\"%s\" ist kein Palindrom\n", string);
	free(string);
	return;
}

void aufg_7_16()
{
	struct mat matrix_in, matrix_out;
	matrix_in.zeilen = matrix_in.spalten = 0;
	printf("Eine Matrix Transponieren.\n");
	printf("Wie lautet die Matrix?\n");
	matrix_in = matrix_eingabe(matrix_in);
	printf("Deine Matrix:\n");
	matrix_anzeige(matrix_in);
	matrix_out = matrix_transponieren(matrix_in);
	printf("Die %d x %d transponierte Matrix lautet:\n", matrix_out.zeilen, matrix_out.spalten);
	matrix_anzeige(matrix_out);
	return;
}
void aufg_7_17()
{
	struct mat matrix1, matrix2, matrix_out;
	matrix1.zeilen = matrix1.spalten =  matrix2.zeilen = matrix2.spalten = 0;
	printf("Zwei Matrizen addieren.\n");
	printf("Wie lautet die erste Matrix?\n");
	matrix1 = matrix_eingabe(matrix1);
	printf("Die erste Matrix:\n");
	matrix_anzeige(matrix1);
	matrix2.zeilen=matrix1.zeilen;
	matrix2.spalten=matrix1.spalten;
	printf("Wie lautet die zweite %d x %d Matrix?\n", matrix2.zeilen, matrix2.spalten);
	matrix2 = matrix_eingabe(matrix2);
	printf("Die zweite Matrix:\n");
	matrix_anzeige(matrix2);
	
	matrix_out = matrix_addieren(matrix1, matrix2);
	printf("Die %d x %d Matrix lautet:\n", matrix_out.zeilen, matrix_out.spalten);
	matrix_anzeige(matrix_out);
	return;
}
void aufg_7_18()
{
	int faktor;
	struct mat matrix_in, matrix_out;
	matrix_in.zeilen = matrix_in.spalten = 0;
	printf("Eine Matrix mit einem Skalar multiplizieren.\n");
	printf("Wie lautet die Matrix?\n");
	matrix_in = matrix_eingabe(matrix_in);
	printf("Die Matrix:\n");
	matrix_anzeige(matrix_in);
	printf("Wie lautet der Skalar?\n");
	scanf("%d",&faktor);
	
	matrix_out = matrix_skalaprodukt(matrix_in, faktor);
	printf("Die %d x %d Matrix lautet:\n", matrix_out.zeilen, matrix_out.spalten);
	matrix_anzeige(matrix_out);
	return;
}
void aufg_7_19()
{
	struct mat matrix1, matrix2, matrix_out;
	matrix1.zeilen = matrix1.spalten =  matrix2.zeilen = matrix2.spalten = 0;
	printf("Eine Matrix mit einer Matrix multiplizieren.\n");
	printf("Wie lautet die erste Matrix?\n");
	matrix1 = matrix_eingabe(matrix1);
	printf("Die erste Matrix:\n");
	matrix_anzeige(matrix1);
	printf("Wie lautet die zweite Matrix?\n");
	matrix2 = matrix_eingabe(matrix2);
	printf("Die zweite Matrix:\n");
	matrix_anzeige(matrix2);
	
	if(matrix1.spalten != matrix2.zeilen)
	{
		printf("Die Dimension der Spalten der ersten Matrix stimmt nicht mit der Dimension der Zeilen der zweiten Matrix überein.\n");
		return;
	}

	matrix_out = matrix_matrixprodukt(matrix1, matrix2);
		
	printf("Die %d x %d Matrix lautet:\n", matrix_out.zeilen, matrix_out.spalten);
	matrix_anzeige(matrix_out);
	return;
}
void aufg_7_20()
{
	int faktor,k;
	struct mat matrix_in, matrix_out;
	matrix_in.zeilen = matrix_in.spalten = 0;
	printf("Elementare Zeilenumformung: Eine Zeile mit einem Skalar multiplizieren.\n");
	printf("Wie lautet die Matrix?\n");
	matrix_in = matrix_eingabe(matrix_in);
	printf("Die Matrix:\n");
	matrix_anzeige(matrix_in);
	printf("Welche Zeile soll mit dem Skalar multipliziert werden?\n");
	scanf("%d",&k);
	printf("Wie lautet der Skalar?\n");
	scanf("%d",&faktor);
	
	matrix_out = matrix_z_S(matrix_in, k-1, faktor);
	printf("Die %d x %d Matrix lautet:\n", matrix_out.zeilen, matrix_out.spalten);
	matrix_anzeige(matrix_out);
	return;
}
void aufg_7_21()
{
	int faktor, k, l;
	struct mat matrix_in, matrix_out;
	matrix_in.zeilen = matrix_in.spalten = 0;
	printf("Elementare Zeilenumformung: Eine Zeile k mit dem mu-fachen einer anderen Zeile l addieren.\n");
	printf("Wie lautet die Matrix?\n");
	matrix_in = matrix_eingabe(matrix_in);
	printf("Die Matrix:\n");
	matrix_anzeige(matrix_in);
	printf("Welche Zeile soll verändert werden??\n");
	scanf("%d",&k);
	printf("Welche Zeile soll darauf addiert werden?\n");
	scanf("%d",&l);
	printf("Mit welchem mu soll die addierte Zeile vorher multipliziert werden??\n");
	scanf("%d",&faktor);
	
	matrix_out = matrix_z_Q(matrix_in, k-1, l-1, faktor);
	printf("Die %d x %d Matrix lautet:\n", matrix_out.zeilen, matrix_out.spalten);
	matrix_anzeige(matrix_out);
	return;
}
void aufg_7_22()
{
	int k, l;
	struct mat matrix_in, matrix_out;
	matrix_in.zeilen = matrix_in.spalten = 0;
	printf("Elementare Zeilenumformung: Eine Zeile k mit der Zeile l vertauschen.\n");
	printf("Wie lautet die Matrix?\n");
	matrix_in = matrix_eingabe(matrix_in);
	printf("Die Matrix:\n");
	matrix_anzeige(matrix_in);
	printf("erste Zeile k, die vertauscht werden soll?\n");
	scanf("%d",&k);
	printf("zweite Zeile l, die vertauscht werden soll?\n");
	scanf("%d",&l);
	
	matrix_out = matrix_z_P(matrix_in, k-1, l-1);
	printf("Die %d x %d Matrix lautet:\n", matrix_out.zeilen, matrix_out.spalten);
	matrix_anzeige(matrix_out);
	return;
}

int main(int argc, char **argv)
{
    int aufgnr, kapitel;
    srand( (unsigned) time(NULL) ) ;
    if(*argv[1]=='?')
		help();
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
                case 26:
                    aufg_4_26();
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
            break;
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
                case 11:
                    aufg_7_11();
                    break;
                case 15:
                    aufg_7_15();
                    break;
                case 16:
                    aufg_7_16();
                    break;
                case 17:
                    aufg_7_17();
                    break;
                case 18:
                    aufg_7_18();
                    break;
                case 19:
                    aufg_7_19();
                    break;
                case 20:
                    aufg_7_20();
                    break;
                case 21:
                    aufg_7_21();
                    break;
                case 22:
                    aufg_7_22();
                    break;
			}
            break;
    }
    return 0;
}


void help()
{
	printf("Mögliche Operationen:\n");
	printf("Kap:\tAufg:\t//Kommentar\n");
	printf("4\t5\t//Mehrwertsteuer\n");
	printf("4\t13\t//Summe n+n+1+n+2+...+2n\n");
	printf("4\t17\t//Summe aller Un-/Geraden Zahlen\n");
	printf("4\t25\t//Fibonacci && Primzahl\n");
	printf("4\t26\t//wie 25, mit Primzahlensieb\n");
	printf("-------------\n");
	printf("5\t2\t//potenzieren\n");
	printf("5\t3\t//großes H\n");
	printf("5\t4\t//vierte Wurzel\n");
	printf("5\t8\t//ax^2+bx+c\n");
	printf("5\t12\t//Fibonacci Zahl auf Prim prüfen\n");
	printf("5\t14\t//Primfaktoren\n");
	printf("5\t18\t//Münzwurf\n");
	printf("5\t19\t//Geburtstagsproblem\n");
	printf("-------------\n");
	printf("6\t2\t//Reziproke\n");
	printf("6\t8\t//16 Bit shift (zyklisch)\n");
	printf("6\t9\t//16 Bit spiegeln\n");
	printf("6\t12\t//Maximum von vier Zahlen\n");
	printf("6\t16\t//Roulette\n");
	printf("6\t17\t//Datum binär packen\n");
	printf("6\t23\t//Pokerhand\n");
	printf("6\t24\t//Viele Pokerrunden\n");
	printf("-------------\n");
	printf("7\t8\t//Polynom berechnen\n");
	printf("7\t9\t//Polynome addieren\n");
	printf("7\t10\t//Polynome multiplizieren\n");
	printf("7\t11\t//Polynom ableiten\n");
	printf("7\t15\t//100 Zeichen Palindromität prüfen\n");
	printf("7\t16\t//Matrix transponieren\n");
	printf("7\t17\t//Matrix addieren\n");
	printf("7\t18\t//Matrix mit Skalar multiplizieren\n");
	printf("7\t19\t//Matrix mit Matrix multiplizieren\n");
	printf("\n");
	printf("Verwendug:\n");
	printf("[Programm] [Kapitel] [Aufgabe]\n");
}
	

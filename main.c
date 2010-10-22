#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// summiert alle Zahlen zwischen n und 2n auf
int aufsummieren(int n)
{
    int i,ergebnis;
    if(n>0)
    {
        for(i=n,ergebnis=0;i<=2*n;ergebnis+=i,i++)
            ;
    }
    else if (n<0)
    {
       for(i=2*n,ergebnis=0;i<=n;ergebnis+=i,i++)
            ;
    }
    else if (n==0)
    {
        return 0;
    }
    return ergebnis;
}

void summe_g_ug(int n, int *sum_g, int *sum_ug)
{
    int i;
    for(i=0; i<n; *sum_ug+=2*i+1 , *sum_g+=2*(i+1) , i++)
        ;
    return;
}
// Funktion für die n-te Potenz
int power(int x,int n)
{
    int i;
    long long y=x;
    for(i=2;i<=n; i++)
    {
        y=x*y;
    }
    return y;
}

// Funtion zum Wiederholten Schreiben des gleichen Zeichens
void schreibe_zeichen(char c,int n)
{
    int i;
    for(i=1;i<=n;i++)
        printf("%c",c);
}

// Funktion, die die 4te Wurzel zieht
double wurzel4(int k)
{
    return sqrt(sqrt(k));
    //return -1;
}

// Funktion zur Berechnung eines Polynoms zweiten Grades
int f(x,a,b,c)
{
    return((a*x+b)*x+c);
}

// Funktion zur Berechnung der n-ten Fibonacci-Zahl
int fibonacci(n)
{
    int i, j = 1, k=0,tmp=0;
    if(n==1)
        return 1;
    if(n==2)
        return 1;
    for(i=3;i<=n;i++)
    {
        k=j;
        j=k+tmp;
        tmp=k;
    }
    return j;
}

// Funktion die testet, ob eine Primzahl vorliegt
int ist_prim(test)
{
    int grenze = sqrt(test), i;
    for(i=2;i<=grenze;i++)
    {
        if(test%i==0 || test == 1)
        {
            return 0;
        }
    }
    return 1;
}

// Funktion zur Zerlegung einer Zahl in ihre Primfaktoren
void primfaktoren(zahl)
{
    int i;
    printf("1 ");
    for(i=2;i<=zahl;)
    {
        if(zahl%i==0)
        {
            printf("x %d ", i);
            zahl /= i;
        }
        else
        {
            i++;
        }
    }
    return;
}

// Funktion zur Simulation eines Münzwurfes
void muenzwurf(int wuerfe, int *kopf, int *zahl)
{
    int i,ergebnis=0; // 1 = Kopf; 0 = Zahl
    srand( (unsigned) time(NULL) ) ;
    for(i=0;i<wuerfe;i++)
    {
        ergebnis=rand()%2;
        if(ergebnis)
        {
            *kopf+=1;
        }
        else
        {
            *zahl+=1;
        }
    }
    return;
}

// Funktion zur Lösung des Geburtstagsproblems per Monte Carlo Methode
int monteCarloGeburtstagsProblem(k)
{
    int monat, verteilung[12], i, treffer=0, n;
    srand( (unsigned) time(NULL) ) ;
    for(i=0;i<12;i++)
    {
        verteilung[i]=0;
    }

    for(n=0;n<100;n++)
    {
        for(i=0;i<k;i++)
        {
            monat = rand()%12;
            verteilung[monat]++;
        }

        for(i=0;i<12;i++)
        {
            if(verteilung[i]>=2)
            {
                treffer++;
                break;
            }
        }
        for(i=0;i<12;i++)
        {
            verteilung[i]=0;
        }
    }

    return treffer;
}

// Funktion zur Bildung des Reziproken Wertes
float invers(float zahl)
{
    if (zahl != 0)
    {
        return (1.0/zahl);
    }
    else
    {
        return 0;
    }
}

// Funktion zur Anzeige eines int in binär Schreibweise
void d2b(v,n)
{
    int i, maske;
    maske = 1;
    maske<<=n-1;

    for(i=1;i<=n;i++)
    {
        putchar(((v&maske)==0) ? '0' : '1');
        v<<=1;
    }
    return;
}

// verschiebt eine binäre Zhal um a nach links und fügt die "herausgeschobenen ziffern am Ende wieder an
int zyklischer_shift(a,n)
{
    int maske,i,k;
    maske=1;
    maske<<=15;
    k=0;
    for(i=1;i<=n;i++)
    {
        k = (((a & maske)==0) ? 0 : 1);
        a = a << 1;
        a = k | a;
    }
    return a;
}

// schreibt die binäre Schreibweise einer Zahl rückwärts auf
int spiegel(a)
{
    int maske,i,k, out;
    out=0;
    maske=1;
    k=0;
    for(i=1;i<=16;i++)
    {
        k = (((a & maske)==0) ? 0 : 1);

        out = k | out;
        if(i!=16)
            out = out << 1;
        a = a >> 1;
    }
    return out;
}

// findet das Maximum von vier Werten
int max(x,y,z,w)
{
    int max;
    max=(x>y) ? ((x>z) ? ((x>w) ?  x : w ) : (z>w) ? z : w) : (y>z) ? ((y>w) ? y : z) : (w>z) ? w : z;
    return max;
}

// liefert eine Zahl zwischen 0 und 35
int roulette()
{
    srand( (unsigned) time(NULL) ) ;
    return (rand()%36);
}

// berechnet wie Groß der Gewinn-Faktor ist
int roulette_gewinn_faktor(k,kugel)
{
    if(kugel==0 && k!=0)
        return 0;
    if(k==36 && kugel%2==0)
        return 2;
    if(k==37 && kugel%2==1)
        return 2;
    if(k==kugel)
        return 35;
    return 0;
}

// verpackt ein dd.mm.yy Datum in ein short
short datum_packer(tag,monat,jahr)
{
    short date;
    date = tag;
    date = ( date << 4 ) | monat;
    date = ( date << 7 ) | jahr;
    return date;
}

// entpackt ein Datum aus einem short
void datum_entpacker(short gepackt, int *tag, int *monat, int *jahr)
{
    *jahr = gepackt & 0b1111111;
    *monat = (gepackt & 0b11110000000) >> 7;
    *tag = (gepackt & 0b1111100000000000) >> 11;
    return;
}

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
    printf("%d ist die größte der vier Zahlen\n", max(x,y,z,w));
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
        printf("\n\nWelches Datum soll gepackt werden? (Tag.Monat.Jahr)\n");
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
    struct card
    {
        enum farbe {herz = 1, pik, karo, kreuz} f;
        enum wert {ass = 1, zwei, drei, vier, funf, sechs, sieben, acht, neun, zehn, bube, dame, konig} w;
    } hand[5];
    int karte[5], i;
    srand( (unsigned) time(NULL) ) ;

    for(i=0;i<5;i++)
    {
        do
        {
        karte[i]=((rand()%52)+1);
        } while((karte[i]==karte[0] && i!=0 ) || (karte[i]==karte[1] && i!=1) || (karte[i]==karte[2] && i!=2) || (karte[i]==karte[3] && i!=3) || (karte[i]==karte[4] && i!=4));

        if(karte[i] <= 13)
        {
            hand[i].f=herz;
            hand[i].w=karte[i];
            printf("\nHerz %d", hand[i].w);
        }
        else if(karte[i] <= 26)
        {
            hand[i].f=pik;
            hand[i].w=karte[i]-13;
            printf("\nPik %d", hand[i].w);
        }
        else if(karte[i] <= 39)
        {
            hand[i].f=karo;
            hand[i].w=karte[i]-26;
            printf("\nKaro %d", hand[i].w);
        }
        else if(karte[i] <= 52)
        {
            hand[i].f=kreuz;
            hand[i].w=karte[i]-39;
            printf("\nKreuz %d", hand[i].w);
        }
        //printf("\n%d, %d -- %d", hand[i].f, hand[i].w, karte[i]);
    }
}

int main()
{
    int aufgnr, kapitel;
    printf("Welches Kapitel?\n");
    scanf("%d", &kapitel);
    printf("Welche Übungsaufgabe?\n");
    scanf("%d", &aufgnr);
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
            }
            break;
    }
    return 0;
}

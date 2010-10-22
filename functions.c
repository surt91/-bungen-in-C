#include "functions.h"

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
void d2b(short v,int n)
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
int zyklischer_shift(short a,int n)
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
int spiegel(short a)
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

struct card *karten_geber(struct card *hand)
{
    //struct card hand[5];
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
//            printf("\nHerz %d", hand[i].w);
        }
        else if(karte[i] <= 26)
        {
            hand[i].f=pik;
            hand[i].w=karte[i]-13;
//            printf("\nPik %d", hand[i].w);
        }
        else if(karte[i] <= 39)
        {
            hand[i].f=karo;
            hand[i].w=karte[i]-26;
//            printf("\nKaro %d", hand[i].w);
        }
        else if(karte[i] <= 52)
        {
            hand[i].f=kreuz;
            hand[i].w=karte[i]-39;
//            printf("\nKreuz %d", hand[i].w);
        }
        //printf("\n%d, %d -- %d", hand[i].f, hand[i].w, karte[i]);
    }
    return hand;
}


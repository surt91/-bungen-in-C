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
    if(n==0)
		return 1;
	if(n==1)
		return x;
	if(n<=0)
		return -1;
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
    //srand( (unsigned) time(NULL) ) ; //schon am Anfang von main()
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
    //srand( (unsigned) time(NULL) ) ; //schon am Anfang von main()
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
int max4(x,y,z,w)
{
    return( (x>y) ? ((x>z) ? ((x>w) ?  x : w ) : (z>w) ? z : w) : (y>z) ? ((y>w) ? y : z) : (w>z) ? w : z );
}
int max2(int x,int y)
{
	return( (x>y) ? x : y );
}
int min2(int x,int y)
{
	return( (x<y) ? x : y );
}

// liefert eine Zahl zwischen 0 und 35
int roulette()
{
    //srand( (unsigned) time(NULL) ) ; //schon am Anfang von main()
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

// gibt eine Pokerhand
struct card *karten_geber(struct card *hand)
{
    int karte[5], i;
//    srand( (unsigned) time(NULL) ) ; //schon am Anfang von main()
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
        }
        else if(karte[i] <= 26)
        {
            hand[i].f=pik;
            hand[i].w=karte[i]-13;
        }
        else if(karte[i] <= 39)
        {
            hand[i].f=karo;
            hand[i].w=karte[i]-26;
        }
        else if(karte[i] <= 52)
        {
            hand[i].f=kreuz;
            hand[i].w=karte[i]-39;
        }
    }
    return hand;
}
// Zeigt eine Pokerhand an
void karten_zeiger(struct card *hand)
{
    int i;
    for(i=0;i<5;i++)
    {
        switch (hand[i].f)
        {
            case herz:  printf("\nHerz  "); break;
            case pik:   printf("\nPik   "); break;
            case karo:  printf("\nKaro  "); break;
            case kreuz: printf("\nKreuz "); break;
        }
        switch (hand[i].w)
        {
            case ass: printf("Ass"); break;
            case 2: printf("Zwei"); break;
            case 3: printf("Drei"); break;
            case 4: printf("Vier"); break;
            case 5: printf("Fünf"); break;
            case 6: printf("Sechs"); break;
            case 7: printf("Sieben"); break;
            case 8: printf("Acht"); break;
            case 9: printf("Neun"); break;
            case 10: printf("Zehn"); break;
            case bube: printf("Bube"); break;
            case dame: printf("Dame"); break;
            case konig: printf("König"); break;
        }
    }
    printf("\n\n");
}
// überprüft, ob ein Fullhouse auf der Hand ist
int is_fullhouse(struct card *hand)
{
    int i,n=1,l,m=1;
    for(i=1;i<5;i++)
    {
        if(hand[0].w==hand[i].w)
        {
            n++;
        }
    }
    if( (n==2) || (n==3) )
    {
        i=1;
        while(hand[0].w==hand[i].w)
        {
            i++;
        }
        for(l=i+1;l<5;l++)
        {
            if(hand[i].w==hand[l].w)
            {
                m++;
            }
        }
    }
    if( ( (m==2) && (n==3) ) || ( (m==3) && (n==2) ) )
    {
        return 1;
    }
    return 0;
}
// überprüft, ob ein Flush auf der Hand ist
int is_flush(struct card *hand)
{
    int i;
    for(i=1;i<5;i++)
    {
        if(hand[0].f!=hand[i].f)
        {
            return 0;
        }
    }
    return 1;
}
// überprüft, ob eine Straße auf der Hand ist
int is_straight(struct card *hand)
{
    karten_sortierer(hand);
    int i;
    if(hand[1].w==10 && hand[2].w==bube && hand[3].w==dame && hand[4].w==konig && hand[0].w==ass)
    {
        return 2;
    }
    for(i=0;i<4;i++)
    {
        if(hand[i].w+1!=hand[i+1].w)
        {
            return 0;
        }
    }
    return 1;
}
// sortiert eine Pokerhand aufsteigend, (ass, zwei, drei...)
struct card *karten_sortierer(struct card *hand)
{
    int i, j, temp, n=0;
    // Bubble Sort; effizient, da nur 5 Werte sortiert werden müssen; qsort würde mehr "overhead" erzeugen
    // n ist ein Zähler, der feststellt, ob in der Sortierschleife etwas umgestellt wurde, falls nicht, bricht die Schleife ab
    // marginale Geschwindigkeitsvorteile. durch overhead eventuell sogar Nachteile
	for(i=0;i<4;i++)
	{
        for(j=4;i<j;j--)
            if(hand[j-1].w>hand[j].w)
            {
                temp = hand[j-1].w;
                hand[j-1].w = hand[j].w;
                hand[j].w = temp;
                n++;
            }
            if(n==0)
				break;
			n=0;
    }
    return(hand);
}

// für qsort
//int cmp_integer(const void *wert1, const void *wert2) {
//   return (*(int*)wert1 – *(int*)wert2);
//}
// bsp:  qsort(test_array, MAX, sizeof(int), cmp_integer);

// Nimmt Eingaben zur Erstellung eines Polynoms entgegen
int *polynom_eingabe(int *polynom, int *grad)
{
	int i;
	printf("Welchen Grad soll das Polynom haben?\n");
	scanf("%d",grad);
	// erstellt ein Array variabler Länge
	polynom = (int *) calloc(*grad, sizeof(int));
	for(i=*grad;i>=0;i--)
	{
		printf("a%d (%d. Koeffizient (vor x^%d))?\n", i, *grad-i+1, i);
		scanf("%d", &polynom[i]);
	}
	printf("Dein Polynom:\n");
	polynom_anzeige(polynom, *grad);
	return (polynom);
}
void polynom_anzeige(int *polynom, int grad)
{
	int i;
	printf("f(x)= ");
	for(i=grad;i>0;i--)
	{
		printf("%dx^%d + ", polynom[i], i);
	}
	printf("%d\n\n",polynom[i]);
}
// Errechnet ein Polynom n-ten Grades
long long polynom_naiv(int *polynom, int x, int grad)
{
	int i;
	long long ergebnis=0;
	for(i=grad;i>=0;i--)
	{
		ergebnis += (power(x, grad-i)*polynom[i]);
	}
	return (ergebnis);
}
// Errechnet ein Polynom n-ten Grades nach dem Horner Schema
long long polynom_horner(int *polynom, int x, int grad)
{
	int i;
	long long ergebnis=0;
	//a0 + x(a1 + x(a2 + x(....(a_grad-1 + x(a_grad))...)))
	//letzte Klammer (-> a_grad)
	ergebnis = polynom[grad];
	for(i=grad-1;i>=0;i--)
	{
		ergebnis *= x;
		ergebnis += polynom[i];
	}
	return (ergebnis);
}

// addiert zwei Polynome
int *polynom_addierer(int *ergebnis_poly, int *poly1, int *poly2, int *grad_ergebnis, int grad1, int grad2)
{
	int i, grad_max, grad_min;
	if(grad1==grad2)
	{
		grad_min = grad_max = grad1;
	}
	else
	{
		grad_max = max2(grad1, grad2);
		grad_min = min2(grad1, grad2);
	}
	*grad_ergebnis=grad_max;
	ergebnis_poly = (int *) calloc(*grad_ergebnis, sizeof(int));
	for(i=0;i<=grad_min;i++)
	{
		ergebnis_poly[i]=poly1[i]+poly2[i];
	}
	if(grad1==grad2)
		;
	else if (grad1>grad2)
		for(;i<=grad_max;i++)
			ergebnis_poly[i]=poly1[i];
	else if (grad1<grad2)
		for(;i<=grad_max;i++)
			ergebnis_poly[i]=poly2[i];
	else
		return;
	return (ergebnis_poly);
}

// multipliziert zwei Polynome
int *polynom_multiplizierer(int *ergebnis_poly, int *poly1, int *poly2, int *grad_ergebnis, int grad1, int grad2)
{
	int i, j;
	*grad_ergebnis = grad1 + grad2; //Potenzgesetzte ftw!
	ergebnis_poly = (int *) calloc(*grad_ergebnis, sizeof(int));
	for(i=0;i<=grad1;i++)
		for(j=0;j<=grad2;j++)
			ergebnis_poly[i+j] += poly1[i] * poly2[j];
	return (ergebnis_poly);
}

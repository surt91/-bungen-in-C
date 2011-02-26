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
    if(n<1)
        return -1;
    if(n==1)
        return 0;
    if(n==2)
        return 1;
    if(n==3)
        return 1;
    for(i=3;i<=n;i++)
    {
        k=j;
        j=k+tmp;
        tmp=k;
    }
    return j;
}
// Funktion zur Berechnung der ersten n Fibonacci-Zahlen (als Array, das >= n sein muss)
int *fibonacci_array(int n, int *fibo_array)
{
    int i;
    if(n<1)
        return 0;
    fibo_array[0]=0;
    fibo_array[1]=0;
    fibo_array[2]=1;
    for(i=3;i<=n;i++)
    {
		fibo_array[i]=fibo_array[i-2]+fibo_array[i-1];
    }
    return fibo_array;
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
// Funktionsgruppe, die schneller große Primzahlen errechnet
void prim_ermitteln(unsigned long max)
{
    unsigned laenge=0, *prim_liste;
    short *array=0;
    if(max==0)
    {
        printf("Bis zu Welcher Zahl, sollen Primzahlen gesucht werden?\n");
        scanf("%lu", &max);
        printf("\n\n");
    }
    array = (short *) calloc(max, sizeof(short));
    primzahl(max, array);
    prim_liste = prim_array_bereinigen(array, max, &laenge);
    prim_ausgabe(prim_liste, laenge);
    free(array);
}
// Primzahlenermittlung mit Array
void primzahl(unsigned max, short *a)
{
    unsigned pot,wurzpot, i, n;
    short *c;
    pot=sqrt(max);
    wurzpot=sqrt(pot);
    c = (short *) calloc(pot, sizeof(short));

    a[0]=1; a[1]=1;
    c[0]=1; c[1]=1;

    for(i=2;i<=wurzpot;i++)
        for(n=i+1;n<=pot;n++)
            if(n%i==0)
                if(c[n]!=1)
                    c[n]=1;

    for(n=2;n<=pot;n++)
        if(c[n]==0)
            for(i=n+n;i<=max;i=i+n)
                if(a[i]!=1)
                    a[i]=1;
    free(c);
    return;
}
unsigned *prim_array_bereinigen(short *alt_array, unsigned alt_array_laenge, unsigned *neu_array_laenge)
{
    unsigned i, n=0, *neu_array;

    for(i=0; i<=alt_array_laenge; i++){
        if(alt_array[i]!=1){
            n++;
        }
    }

    *neu_array_laenge=n;
    neu_array = (unsigned *) calloc(*neu_array_laenge, sizeof(unsigned));
    n=0;
    for(i=0; i<=alt_array_laenge; i++){
        if(alt_array[i]!=1){
            neu_array[n]=i;
            n++;
        }
    }
    return neu_array;
}
unsigned prim_max(unsigned *prim_liste, unsigned letzte)
{
    return (prim_liste[letzte-1]);
}
void prim_ausgabe(unsigned *prim_liste, unsigned anzahl_prim)
{
    unsigned i;
    short tmp=0;

    for(i=0; i<anzahl_prim; i++){
        printf("%10ud ",prim_liste[i]);
        tmp++;
        if(tmp%5==0)
            printf("\n");
    }
    printf("\n#%d\n", anzahl_prim);
    return;
}
int ist_prim_array(test)
{
	short *array=0;
	unsigned *prim_liste, laenge;
	if(test<=1)
		return 0;
	array = (short *) calloc(test, sizeof(short));
	primzahl(test, array);
	prim_liste = prim_array_bereinigen(array, test, &laenge);
	free(array);
	if(prim_max(prim_liste, laenge) == test)
		return 1;
	else
		return 0;
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
    printf("\n");
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
		return 0;
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

// differenziert ein Polynom
int *polynom_ableiter(int *poly_out, int *poly_in, int *grad_out, int grad_in)
{
	int i;
	*grad_out = grad_in - 1;
	poly_out = (int *) calloc(*grad_out, sizeof(int));
	for(i=0;i<=*grad_out;i++)
		poly_out[i]=(poly_in[i+1]*(i+1));
	return (poly_out);
}

// Monte Carlo Pi
double pi(int versuche)
{
	int i;
	double x,y, betrag, treffer=0;
	for(i=0;i<versuche;i++)
	{
		x = rand();
		x /= RAND_MAX;
		y = rand();
		y /= RAND_MAX;
		betrag = x*x + y*y;
		if(betrag<=1)
			treffer++;
	}
	return(treffer/versuche*4);
}

// findet heraus, ob der Parameter String ein Palindrom ist
int ist_palindrom(char *string, size_t laenge)
{
	int i, j;
	char *neu_string;
	laenge = strlen(string);
	neu_string = (char *) calloc(laenge, sizeof(char));
	for(j=i=0;string[i]!='\0';i++)
	{
        if(string[i]!=' ')
            neu_string[j++]=string[i];
        else
			laenge--;
		if(neu_string[j-1]<97)
			neu_string[j-1] += 32;
	}
	for(i=0;i<(laenge-1)/2;i++)
	{
		if(neu_string[i]!=neu_string[laenge-1-i])
		{
			free(neu_string);
			return 0;
		}
	}
	free(neu_string);
	return 1;
}

// Nimmt Eingaben zur Erstellung einer Matrix
struct mat matrix_eingabe(struct mat matrix_out)
{
	int i, j;
	if(matrix_out.zeilen == 0 || matrix_out.spalten == 0){
		printf("Anzahl Zeilen der Matrix?\n");
		scanf("%d",&matrix_out.zeilen);
		printf("Anzahl Spalten der Matrix?\n");
		scanf("%d",&matrix_out.spalten);
	}
	// erstellt ein Array variabler Länge
	matrix_out.matrix = (double *) calloc(matrix_out.zeilen * matrix_out.spalten, sizeof(double));
	printf("Zeilen und Spalten beginnen bei Null und Enden bei #Zeilen-1 bzw. #Spalten-1\n");
	for(i=0;i< matrix_out.zeilen ;i++)
		for(j=0;j< matrix_out.spalten ;j++)
		{
			printf("%d-te Zeile, %d-te Spalte\n", i+1, j+1);
			scanf("%lf", &matrix_out.matrix[i * matrix_out.spalten + j]);
		}
	return (matrix_out);
}
// Erzeugt eine n x n Einheitsmatrix
struct mat matrix_e(int n)
{
	int i, j;
	struct mat matrix_out;
	matrix_out.zeilen = matrix_out.spalten = n;
	matrix_out.matrix = (double *) calloc(n * n, sizeof(double));
	for(i=0;i<matrix_out.zeilen;i++)
		for(j=0;j<matrix_out.spalten;j++)
		{
			if(i==j)
				matrix_out.matrix[j* matrix_out.spalten+i] = 1;
			else
				matrix_out.matrix[j* matrix_out.spalten+i] = 0;
		}
	return matrix_out;
}

//~ struct mat matrix_auslesen(struct mat matrix_out)
//~ {
	//~ FILE *fp;
	//~ FILE *fopen(char *, char *);
	//~ char c, zahl[20];
	//~ int i;
	//~ fp = fopen(name, mode);
	//~ while(c != 'Q')
		//~ while(c != '\n')
		//~ {
			//~ i=0;
			//~ n=0;
			//~ while(c != ',')
			//~ {
				//~ c = getc(fp);
				//~ zahl[i]=c;
				//~ i++;
			//~ }
			//~ (const char) *zahl;
			//~ matrix[n] = atoi(*zahl);
			//~ n++;
		//~ }
//~
	//~ fclose(fp);
	//~ int i, j;
	//~ if(matrix_out.zeilen == 0 || matrix_out.spalten == 0){
		//~ printf("Anzahl Zeilen der Matrix?\n");
		//~ scanf("%d",&matrix_out.zeilen);
		//~ printf("Anzahl Spalten der Matrix?\n");
		//~ scanf("%d",&matrix_out.spalten);
	//~ }
	//~ // erstellt ein Array variabler Länge
	//~ matrix_out.matrix = (int *) calloc(matrix_out.zeilen * matrix_out.spalten, sizeof(int));
	//~ printf("Zeilen und Spalten beginnen bei Null und Enden bei #Zeilen-1 bzw. #Spalten-1\n");
	//~ for(i=0;i< matrix_out.zeilen ;i++)
		//~ for(j=0;j< matrix_out.spalten ;j++)
		//~ {
			//~ printf("%d-te Zeile, %d-te Spalte\n", i, j);
			//~ scanf("%d", &matrix_out.matrix[i * matrix_out.spalten + j]);
		//~ }
	//~ return (matrix_out);
//~ }
void matrix_anzeige(struct mat matrix_in)
{
	int i, j;
	for(i=0;i<matrix_in.zeilen;i++)
	{
		printf(" ");
		for(j=0;j<matrix_in.spalten;j++)
		{
			printf(" % #5.3f ", matrix_in.matrix[i* matrix_in.spalten+j]);
		}
		printf("\n");
	}
}
//~ void matrix_schreiben(struct mat matrix_in)
//~ {
	//~ int i, j;
	//~ for(i=0;i<matrix_in.zeilen;i++)
	//~ {
		//~ printf("| ");
		//~ for(j=0;j<matrix_in.spalten;j++)
		//~ {
			//~ printf("%d ", matrix_in.matrix[i* matrix_in.spalten+j]);
		//~ }
		//~ printf("|\n");
	//~ }
//~ }
struct mat matrix_transponieren(struct mat matrix_in)
{
	int i, j;
	struct mat matrix_out;
	matrix_out.zeilen = matrix_in.spalten;
	matrix_out.spalten = matrix_in.zeilen;
	matrix_out.matrix = (double *) calloc(matrix_out.zeilen * matrix_out.spalten, sizeof(double));
	for(i=0;i<matrix_in.zeilen;i++)
		for(j=0;j<matrix_in.spalten;j++)
			matrix_out.matrix[j* matrix_out.spalten+i] = matrix_in.matrix[i* matrix_in.spalten+j];

	return matrix_out;
}
struct mat matrix_addieren(struct mat matrix1, struct mat matrix2)
{
	int i, j;
	struct mat matrix_out;
	matrix_out.zeilen = matrix1.zeilen;
	matrix_out.spalten = matrix1.spalten;
	matrix_out.matrix = (double *) calloc(matrix_out.zeilen * matrix_out.spalten, sizeof(double));
	for(i=0;i<matrix_out.zeilen;i++)
		for(j=0;j<matrix_out.spalten;j++)
			matrix_out.matrix[i* matrix_out.spalten+j] = matrix1.matrix[i* matrix1.spalten+j]+matrix2.matrix[i* matrix2.spalten+j];

	return matrix_out;
}
struct mat matrix_skalaprodukt(struct mat matrix_out, double faktor)
{
	int i, j;
	for(i=0;i<matrix_out.zeilen;i++)
		for(j=0;j<matrix_out.spalten;j++)
			matrix_out.matrix[i* matrix_out.spalten+j] = matrix_out.matrix[i* matrix_out.spalten+j]*faktor;

	return matrix_out;
}
struct mat matrix_matrixprodukt(struct mat matrix1, struct mat matrix2)
{
	int i, j, k;
	struct mat matrix_out;
	if(matrix1.spalten != matrix2.zeilen)
	{
		printf("Die Dimension der Spalten der ersten Matrix stimmt nicht mit der Dimension der Zeilen der zweiten Matrix überein.\n");
		return;
	}
	matrix_out.zeilen = matrix1.zeilen;
	matrix_out.spalten = matrix2.spalten;
	matrix_out.matrix = (double *) calloc(matrix_out.zeilen * matrix_out.spalten, sizeof(double));
	for(i=0;i<matrix_out.zeilen;i++)
		for(j=0;j<matrix_out.spalten;j++)
			for(k=0;k<matrix1.spalten;k++)
				matrix_out.matrix[i*matrix_out.spalten+j] += matrix2.matrix[k*matrix2.spalten+j]*matrix1.matrix[i*matrix1.spalten+k];

	return matrix_out;
}
//Multiplikation der k-ten Zeile mit einem Skalar
struct mat matrix_z_S(struct mat matrix_out, int k, double faktor)
{
	int j;
	for(j=0;j<matrix_out.spalten;j++)
		matrix_out.matrix[k* matrix_out.spalten+j] = matrix_out.matrix[k* matrix_out.spalten+j]*faktor;

	return matrix_out;
}
//Addition des mu-fachen der l-ten zeile zur k-ten Zeile
struct mat matrix_z_Q(struct mat matrix_out, int k, int l, double faktor)
{
	int j;
	if(k!=l)
		for(j=0;j<matrix_out.spalten;j++)
			matrix_out.matrix[k* matrix_out.spalten+j] += matrix_out.matrix[l* matrix_out.spalten+j]*faktor;

	return matrix_out;
}
//Vertauschen der k-ten und l-ten Zeile
struct mat matrix_z_P(struct mat matrix_in, int k, int l)
{
	int i, j;
	struct mat matrix_out;
	matrix_out.zeilen = matrix_in.zeilen;
	matrix_out.spalten = matrix_in.spalten;
	matrix_out.matrix = (double *) calloc(matrix_out.zeilen * matrix_out.spalten, sizeof(double));
	for(i=0;i<matrix_out.zeilen;i++)
		for(j=0;j<matrix_out.spalten;j++)
			matrix_out.matrix[i* matrix_out.spalten+j] = matrix_in.matrix[i* matrix_in.spalten+j];

	for(j=0;j<matrix_in.spalten;j++)
	{
		matrix_out.matrix[k* matrix_out.spalten+j] = matrix_in.matrix[l* matrix_in.spalten+j];
		matrix_out.matrix[l* matrix_out.spalten+j] = matrix_in.matrix[k* matrix_in.spalten+j];
	}

	return matrix_out;
}
// ref / Gaußsche Normalform / Dreiecksform
struct mat matrix_gnf(struct mat matrix_out)
{
	int i, p, q, k;
	double tmp;

	for(q=0;q<matrix_out.zeilen;q++)
	{
		for(p=q+1;p<matrix_out.zeilen;p++)
		{
			tmp = matrix_out.matrix[q * matrix_out.spalten + q];
			if(tmp<FLOATNULL && tmp>-FLOATNULL)
			{
				for(i=q;i<matrix_out.zeilen;i++)
				{
					tmp=matrix_out.matrix[i * matrix_out.spalten + q];
					if(tmp>FLOATNULL || tmp<-FLOATNULL)
					{
						matrix_out = matrix_z_P(matrix_out,i,q);
						break;
					}
				}
			}
			else
				matrix_out = matrix_z_Q(matrix_out, p, q, -1 * matrix_out.matrix[p * matrix_out.spalten + q]/tmp);
		}
		//tmp=matrix_out.matrix[q * matrix_out.spalten + q];
		for(k=q;k<matrix_out.spalten;k++)
		{
			tmp=matrix_out.matrix[q * matrix_out.spalten + k];
			if(tmp>FLOATNULL || tmp<-FLOATNULL)
			{
				matrix_out = matrix_z_S(matrix_out,q,1/tmp);
				break;
			}
		}
	}
	return matrix_out;
}
// Diagonalform
struct mat matrix_dgf(struct mat matrix_out)
{
	// Auch das rechte obere Dreieck mit Nullen füllen (reduzierte Gaußsche Normalform)
	int i, j, p;
	double tmp;

	matrix_out = matrix_gnf(matrix_out);
	for(i=matrix_out.zeilen;i>=0;i--)
		for(j=0;j<matrix_out.spalten;j++)
		{
			tmp=matrix_out.matrix[i* matrix_out.spalten+j];
			if(tmp>1+FLOATNULL || tmp<1-FLOATNULL) //Element ungleich 1, sprich: kein Pivotelement
				continue;
			else
				for(p=0;p<i;p++)
					matrix_out=matrix_z_Q(matrix_out, p, i, -matrix_out.matrix[p* matrix_out.spalten+j]);
		}
return matrix_out;
}
// invertieren
struct mat matrix_invertieren(struct mat matrix_in)
{
	// An die zu invertierende Matrix (muss quadratisch und linear unabhängig sein) wird die Einheitsmatrix drangehängt. Die große Matrix wird danach auf Diagonalform gebracht. Die ehemalige einheitsmatrix wird wieder abgeschnitten. Fertig ist die invertierte.
	int i, j;
	double det;
	struct mat einheit;
	einheit=matrix_e(matrix_in.zeilen);
	struct mat tmp, matrix_out, tmp2;
	tmp2.spalten = matrix_in.spalten;
	tmp2.zeilen = matrix_in.zeilen;
	tmp2.matrix = (double *) calloc(tmp2.zeilen * tmp2.spalten, sizeof(double));
	for(i=0;i<tmp2.zeilen;i++)
		for(j=0;j<tmp2.spalten;j++)
			tmp2.matrix[i* tmp2.spalten+j] = matrix_in.matrix[i* matrix_in.spalten+j];

	det = matrix_det(tmp2);

	if(det < -FLOATNULL || det > FLOATNULL)
	{
		tmp.spalten = matrix_in.spalten*2;
		tmp.zeilen = matrix_in.zeilen;
		tmp.matrix = (double *) calloc(tmp.zeilen * tmp.spalten, sizeof(double));
		matrix_out.spalten = matrix_in.spalten;
		matrix_out.zeilen = matrix_in.zeilen;
		matrix_out.matrix = (double *) calloc(matrix_out.zeilen * matrix_out.spalten, sizeof(double));

		for(i=0;i<matrix_in.zeilen;i++)
			for(j=0;j<matrix_in.spalten;j++)
				tmp.matrix[i* tmp.spalten+j] = matrix_in.matrix[i* matrix_in.spalten+j];

		for(i=0;i<matrix_in.zeilen;i++)
			for(j=0;j<matrix_in.spalten;j++)
				tmp.matrix[i* tmp.spalten+j+matrix_in.spalten] = einheit.matrix[i* einheit.spalten+j];
		tmp = matrix_dgf(tmp);;
		for(i=0;i<matrix_in.zeilen;i++)
			for(j=0;j<matrix_in.spalten;j++)
				matrix_out.matrix[i* matrix_in.spalten +j] = tmp.matrix[i* tmp.spalten + (j+matrix_in.spalten)];
		return matrix_out;
	}
	else
	{
		printf("Die Matrix ist nicht invertierbar.\n");
		return;
	}
}
// Determinante
double matrix_det(struct mat matrix_out)
{
	int i, p, q;
	double det=1, tmp;

	if(matrix_out.zeilen != matrix_out.spalten)
		return 0;

	for(q=0;q<matrix_out.zeilen;q++)
	{
		for(p=q+1;p<matrix_out.zeilen;p++)
		{
			tmp = matrix_out.matrix[q * matrix_out.spalten + q];
			if(tmp<FLOATNULL && tmp>-FLOATNULL)
			{
				for(i=q;i<matrix_out.zeilen;i++)
				{
					tmp=matrix_out.matrix[i * matrix_out.spalten + q];
					if(tmp>FLOATNULL || tmp<-FLOATNULL)
					{
						matrix_out = matrix_z_P(matrix_out,i,q);
						det *= -1;
						break;
					}
				}
			}
			else
			{
				matrix_out = matrix_z_Q(matrix_out, p, q, -1 * matrix_out.matrix[p * matrix_out.spalten + q]/tmp);
			}
		}
		tmp=matrix_out.matrix[q * matrix_out.spalten + q];
		if(tmp>FLOATNULL || tmp<-FLOATNULL)
		{
			matrix_out = matrix_z_S(matrix_out,q,1/tmp);
			det *= tmp;
		} else { tmp = 0; }
	}

	for(i=0;i<matrix_out.spalten;i++)
		det *= matrix_out.matrix[i* matrix_out.spalten+i];
	return det;
}
// Zeile/Spalte streichen
struct mat matrix_streichen(struct mat matrix_in, int i, int j)
{
	int p, q, n, m;
	struct mat tmp;

	tmp.spalten = matrix_in.spalten - 1;
	tmp.zeilen = matrix_in.zeilen - 1;
	tmp.matrix = (double *) calloc(tmp.zeilen * tmp.spalten, sizeof(double));

	for(m=0,q=0;q<matrix_in.zeilen;q++,m++)
	{
		if(q==j)
				{
					m--;
					continue;
				}
		for(n=0,p=0;p<matrix_in.spalten;p++,n++)
			{
				if(p==i)
				{
					n--;
					continue;
				}

				tmp.matrix[m* tmp.spalten+n] = matrix_in.matrix[q* matrix_in.spalten+p];
			}
	}
	return(tmp);
}
// Adjunkte Matrix finden
struct mat matrix_adjunkte(struct mat matrix_in)
{
	int i, j;
	double det=0;
	struct mat tmp, matrix_out;
	matrix_out.spalten = matrix_in.spalten;
	matrix_out.zeilen = matrix_in.zeilen;
	matrix_out.matrix = (double *) calloc(matrix_out.zeilen * matrix_out.spalten, sizeof(double));

	if(matrix_out.zeilen != matrix_out.spalten)
		return;

	for(i=0;i<matrix_in.zeilen;i++)
		for(j=0;j<matrix_in.spalten;j++)
		{
			det = matrix_det(matrix_streichen(matrix_in,i,j));
			if(i%2==1)
				det*=-1;
			if(j%2==1)
				det*=-1;
			matrix_out.matrix[i* matrix_in.spalten+j]=det;
		}
	return matrix_out;
}
// invertieren mit Adjunkter
struct mat matrix_invertieren_adjunkte(struct mat matrix_in)
{
	double det;
	struct mat tmp;
	tmp.spalten = matrix_in.spalten;
	tmp.zeilen = matrix_in.zeilen;
	tmp.matrix = (double *) calloc(tmp.zeilen * tmp.spalten, sizeof(double));

	tmp=matrix_adjunkte(matrix_in);
	det=matrix_det(matrix_in);
	det=1/det;

	return(matrix_skalaprodukt(tmp,det));
}

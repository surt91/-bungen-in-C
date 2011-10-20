#include "trivia.h"

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
    //~ return( (x>y) ? ((x>z) ? ((x>w) ?  x : w ) : (z>w) ? z : w) : (y>z) ? ((y>w) ? y : z) : (w>z) ? w : z );
    return( max2(max2(x,y),max2(z,w)) );
}
int max2(int x,int y)
{
    return( (x>y) ? x : y );
}
int min2(int x,int y)
{
    return( (x<y) ? x : y );
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

// findet heraus, ob der Parameter String ein Palindrom ist
//int ist_palindrom(char *string, size_t laenge)
//{
//	int i, j;
//	char *neu_string;
//	laenge = strlen(string);
//	neu_string = (char *) calloc(laenge, sizeof(char));
//	for(j=i=0;string[i]!='\0';i++)
//	{
//        if(string[i]!=' ')
//            neu_string[j++]=string[i];
//        else
//			laenge--;
//		if(neu_string[j-1]<97)
//			neu_string[j-1] += 32;
//	}
//	for(i=0;i<(laenge-1)/2;i++)
//	{
//		if(neu_string[i]!=neu_string[laenge-1-i])
//		{
//			free(neu_string);
//			return 0;
//		}
//	}
//	free(neu_string);
//	return 1;
//}

char* dec2base(unsigned number, unsigned base, char *out)
{
    static const char digit[36] = {"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    char tmp[256];
    int i=0,n=0;
    if(base > 36)
    {
        printf("Bitte wähle eine Basis kleiner gleich 36");
        return NULL;
    }
    do {
        tmp[i] = digit[number % base];
        number /= base;
        i++;
    } while(number > 0);
    //~ out = (char *) calloc(i+1, sizeof(char));
    i--;
    while(i>=0)
    {
        out[n]=tmp[i];
        n++;
        i--;
    }
    return out;
}

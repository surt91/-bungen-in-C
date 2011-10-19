#include "game_rand.h"

// gibt eine Pokerhand
//~ struct card *karten_geber(struct card *hand)
//~ {
    //~ int karte[5], i;
//~ //    srand( (unsigned) time(NULL) ) ; //schon am Anfang von main()
    //~ for(i=0;i<5;i++)
    //~ {
        //~ do
        //~ {
        //~ karte[i]=((rand()%52)+1);
        //~ } while((karte[i]==karte[0] && i!=0 ) || (karte[i]==karte[1] && i!=1) || (karte[i]==karte[2] && i!=2) || (karte[i]==karte[3] && i!=3) || (karte[i]==karte[4] && i!=4));
//~
        //~ if(karte[i] <= 13)
        //~ {
            //~ hand[i].f=herz;
            //~ hand[i].w=karte[i];
        //~ }
        //~ else if(karte[i] <= 26)
        //~ {
            //~ hand[i].f=pik;
            //~ hand[i].w=karte[i]-13;
        //~ }
        //~ else if(karte[i] <= 39)
        //~ {
            //~ hand[i].f=karo;
            //~ hand[i].w=karte[i]-26;
        //~ }
        //~ else if(karte[i] <= 52)
        //~ {
            //~ hand[i].f=kreuz;
            //~ hand[i].w=karte[i]-39;
        //~ }
    //~ }
    //~ return hand;
//~ }
//~ // Zeigt eine Pokerhand an
//~ void karten_hand_zeiger(struct card *hand)
//~ {
    //~ int i;
    //~ for(i=0;i<5;i++)
        //~ karten_zeiger(hand[i]);
    //~ return;
//~ }

//~ void karten_zeiger(struct card *hand)
//~ {
    //~ int i;
    //~ for(i=0;i<5;i++)
    //~ {
        //~ switch (hand[i].f)
        //~ {
            //~ case herz:  printf("Herz  "); break;
            //~ case pik:   printf("Pik   "); break;
            //~ case karo:  printf("Karo  "); break;
            //~ case kreuz: printf("Kreuz "); break;
        //~ }
        //~ switch (hand[i].w)
        //~ {
            //~ case ass: printf("Ass"); break;
            //~ case 2: printf("Zwei"); break;
            //~ case 3: printf("Drei"); break;
            //~ case 4: printf("Vier"); break;
            //~ case 5: printf("Fünf"); break;
            //~ case 6: printf("Sechs"); break;
            //~ case 7: printf("Sieben"); break;
            //~ case 8: printf("Acht"); break;
            //~ case 9: printf("Neun"); break;
            //~ case 10: printf("Zehn"); break;
            //~ case bube: printf("Bube"); break;
            //~ case dame: printf("Dame"); break;
            //~ case konig: printf("König"); break;
        //~ }
        //~ printf("\n");
    //~ }
//~ }



// für qsort
//int cmp_integer(const void *wert1, const void *wert2) {
//   return (*(int*)wert1 – *(int*)wert2);
//}
// bsp:  qsort(test_array, MAX, sizeof(int), cmp_integer);


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

double pi_benchmark(double *v)
{
	int begin,end;
	begin = clock();
	*v=pi(100000000);
	end = clock();
	return((double)(end-begin)/CLOCKS_PER_SEC);
}

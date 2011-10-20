#include "poker.h"

// überprüft, ob ein Fullhouse auf der Hand ist
int is_fullhouse(struct card *hand)
{
    int i,n=1,l,m=1;
    for(i=1;i<5;i++)
        if(hand[0].w==hand[i].w)
            n++;
    if( (n==2) || (n==3) )
    {
        i=1;
        while(hand[0].w==hand[i].w)
            i++;
        for(l=i+1;l<5;l++)
            if(hand[i].w==hand[l].w)
                m++;
    }
    if( ( (m==2) && (n==3) ) || ( (m==3) && (n==2) ) )
        return 1;
    else
        return 0;
}
// überprüft, ob ein Flush auf der Hand ist
int is_flush(struct card *hand)
{
    int i;
    for(i=1;i<5;i++)
        if(hand[0].f!=hand[i].f)
            return 0;
    return 1;
}
// überprüft, ob eine Straße auf der Hand ist
int is_straight(struct card *hand)
{
	int i;
    karten_sortierer(hand);
    if(hand[1].w==10 && hand[2].w==bube && hand[3].w==dame && hand[4].w==konig && hand[0].w==ass)
        return 2;

    for(i=0;i<4;i++)
        if(hand[i].w+1!=hand[i+1].w)
            return 0;

    return 1;
}

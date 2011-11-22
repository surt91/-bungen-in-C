#include "bin_uhr.h"

bin_uhr_zeit bin_uhr_packer(int h, int min, int s)
{
    bin_uhr_zeit zeit;
    zeit = h;
    zeit = ( zeit << 6 ) | min;
    zeit = ( zeit << 6 ) | s;
    return zeit;
}

void bin_uhr_entpacker(bin_uhr_zeit gepackt, int *h, int *min, int *s)
{
    *s   =  gepackt & 0b0000000000111111;
    *min = (gepackt & 0b0000111111000000) >> 6;
    *h   = (gepackt & 0b1111000000000000) >> 12;
    return;
}

void bin_uhr_anzeige(bin_uhr_zeit zeit)
{
    int i;
    char anzeige[22];
    for(i=19;i>1;i--)
    {
        if(i!=6 && i!=13)
        {
            if(zeit & 0b1)
                anzeige[i]='1';
            else
                anzeige[i]='0';
            zeit>>=1;
        }
    }
    anzeige[6]='\n';
    anzeige[13]='\n';
    anzeige[1]=' ';
    anzeige[0]=' ';
    anzeige[20]='\n';
    anzeige[21]='\0';
    printf("%s", anzeige);
}

void bin_uhr()
{
    //~ int h, min, s;
    struct tm *now;
    time_t rawtime;
    bin_uhr_zeit jetzt;

    time ( &rawtime );
    now = localtime(&rawtime);
    jetzt = bin_uhr_packer((now->tm_hour-1)%12+1,now->tm_min,now->tm_sec);

    //~ bin_uhr_entpacker(jetzt, h, min, s);
    bin_uhr_anzeige(jetzt);
}

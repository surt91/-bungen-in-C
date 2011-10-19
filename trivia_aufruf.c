#include "trivia_aufruf.h"

void aufg_TRIV_1()
{
    double netto_preis, mwsteuer, preis;
    mwsteuer = preis = 0;
    printf("Nettopreis?\n");
    scanf("%lf", &netto_preis);
    mwsteuer=netto_preis*0.19;
    preis=mwsteuer+netto_preis;
    printf("Das Produkt kostet:\nNetto   :\t%.2lf€\nSteuern :\t%.2lf€\nBrutto  :\t%.2lf€\n", netto_preis, mwsteuer, preis);
}

void aufg_TRIV_2()
{
    int n;
    printf("Es wird von n bis 2n aufsummiert.\nn?\n");
    scanf("%d", &n);
    printf("%d", aufsummieren(n));
}

void aufg_TRIV_3()
{
    int sum_g=0, sum_ug=0, n;

    printf("Die ersten wieviel geraden/ungeraden Zahlen sollen aufaddiert werden?\n");
    scanf("%d", &n);
    summe_g_ug(n, &sum_g, &sum_ug);
    printf("Gerade  : %d\nUngerade: %d", sum_g, sum_ug);
}

void aufg_TRIV_4()
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

void aufg_TRIV_5()
{
    int k;
    printf("Aus welcher Zahl soll die 4te Wurzel gezogen werden?\n");
    scanf("%d",&k);
    printf("%f", wurzel4(k));
    return;
}

void aufg_TRIV_6()
{
    int x, a, b, c;
    printf("f(x)=ax^2+bx+c\nGib die Parameter in der Reihenfolge: x a b c getrennt durch Leerzeichen ein.\n");
    scanf("%d %d %d %d", &x, &a, &b, &c);
    printf("f(x)=%d\n", f(x, a, b, c));
}


void aufg_TRIV_7()
{
    float k;
    printf("Zu welcher Zahl soll das Inverse (Reziproken Wert) gebildet werden?\n");
    scanf("%f", &k);
    printf("Inverses von %g ist %g", k, invers(k));
    return;
}

void aufg_TRIV_8()
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

void aufg_TRIV_9()
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

void aufg_TRIV_10()
{
    int x, y, z, w;
    printf("Von welchen 4 Zahlen, soll das Maximum gefunden werden? (getrennt durch Kommata)\n");
    scanf("%d,%d,%d,%d", &x, &y,&z,&w);
    printf("%d ist die größte der vier Zahlen\n", max4(x,y,z,w));
    return;
}

void aufg_TRIV_11()
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

//void aufg_TRIV_12()
//{
//	char *string;
//	size_t laenge=100;
//	string = (char *) calloc(laenge, sizeof(char));
//	printf("Welcher String soll auf Palindromität untersucht werden.\n");
//	laenge=getline(&string, &laenge, stdin);
//	string[laenge-1]= '\0';
//	printf("\"%s\", %d Buchstaben\n", string, (int)laenge-1);
//	if(ist_palindrom(string, laenge))
//		printf("\"%s\" ist ein Palindrom\n", string);
//	else
//		printf("\"%s\" ist kein Palindrom\n", string);
//	free(string);
//	return;
//}

void aufg_TRIV_13()
{
	unsigned base, number;
	char out[100];
	printf("Welche Zahl soll in einer anderen Basis dargestellt werden? (max. 32 bit unsigned)\n");
	scanf("%ull", &number);
	printf("auf welcher Basis soll die Zahl dargestellt werden? (2 - 36)\n");
	scanf("%d", &base);
	printf("Basis 10:\t %d\nBasis %d:\t %s\n",number,base,dec2base(number,base,out));
	return;
}

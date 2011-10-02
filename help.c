#include "help.h"

void todo()
{
    printf("\nTODO\n\n");
    printf("Highscore Datei für Roulette\n");
    printf("Krypt\n");
    //~ printf("Alle Kapitel auslagern\n");
    //~ printf("Kapitel \"Trivia\" anlegen und andere konsequenter sortieren\n");
}
void bugs()
{
    printf("\nBUGS\n\n");
    printf("Dateinamen können nicht länger sein, als 80 Zeichen.\n");
}

void version()
{
    printf( "Version: %d.%d.%d\n",V_MAJOR,V_MINOR,V_FIX);
    //~ printf( "Copyright (C) 2010 Hendrik Schawe\n");
    printf( "License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>.\n");
    printf( "This is free software: you are free to change and redistribute it.\n");
    printf( "There is NO WARRANTY, to the extent permitted by law.\n");
    printf( "\n");
    printf( "Written by Hendrik Schawe <hendrik.schawe@gmail.com>\n\n");
}

void help( int chap )
{
    printf("-------------\n\n");
    printf("Verwendug:\n");
    printf("[Programm] [Kapitel] [Aufgabe]\n");
    printf("\n");
    printf("Mögliche Operationen:\n");
    printf("Kap:\tAufg:\t//Kommentar\n");
    switch(chap)
    {
        case 0:
        case MAT:
            printf("\nKapitel %d: Lineare Algebra\n\n",MAT);
            printf("%d\t 1\t//Matrix transponieren\n",MAT);
            printf("%d\t 2\t//Matrix addieren\n",MAT);
            printf("%d\t 3\t//Matrix mit Skalar multiplizieren\n",MAT);
            printf("%d\t 4\t//Matrix mit Matrix multiplizieren\n",MAT);
            printf("%d\t 5\t//el. Zeilenumformung S\n",MAT);
            printf("%d\t 6\t//el. Zeilenumformung Q\n",MAT);
            printf("%d\t 7\t//el. Zeilenumformung P\n",MAT);
            printf("%d\t 8\t//Gaussche Normalform\n",MAT);
            printf("%d\t 9\t//Diagonalform\n",MAT);
            printf("%d\t10\t//Determinante\n",MAT);
            printf("%d\t11\t//Adjunkte\n",MAT);
            printf("%d\t12\t//Inverse\n",MAT);
            printf("%d\t13\t//Inverse mit Adjunkter\n",MAT);
            printf("%d\t14\t//Zufällige Matrix erzeugen\n",MAT);
            //~ printf("%d\t15\t//Bench: Linpack :D\n",MAT);
            printf("%d\t16\t//gespeicherte Matrix anzeigen\n",MAT);
            printf("%d\t17\t//Matrix speichern\n",MAT);
            if(chap==MAT) break;
        case GAME:
            printf("\nKapitel %d: Spiele und Zufall\n\n",GAME);
            printf("%d\t 1\t//Roulette\n",GAME);
            printf("%d\t 2\t//Pokerhand\n",GAME);
            printf("%d\t 3\t//Viele Pokerrunden\n",GAME);
            printf("%d\t 4\t//Münzwurf\n",GAME);
            printf("%d\t 5\t//Geburtstagsproblem\n",GAME);
            printf("%d\t 6\t//Monte Carlo Pi (Dart)\n",GAME);
            printf("%d\t 7\t//Snake\n",GAME);
            if(chap==GAME) break;
        //~ case KRYPTO:
            //~ printf("\nKapitel %d: Krypto\n\n",KRYPTO);
            //~ printf("TODO\n");
            //~ if(chap==KRYPTO) break;
        case PRIM:
            printf("\nKapitel %d: Primzahlen\n\n",PRIM);
            printf("%d\t 1\t//Primfaktoren\n",PRIM);
            printf("%d\t 2\t//erste x Primzahlen\n",PRIM);
            printf("%d\t 3\t//potenzieren\n",PRIM);
            printf("%d\t 4\t//Fibonacci Zahl auf Prim prüfen\n",PRIM);
            printf("%d\t 5\t//Fibonacci && Primzahl\n",PRIM);
            printf("%d\t 6\t//wie 25, mit Primzahlensieb\n",PRIM);
            if(chap==PRIM) break;
        //~ case POLY:
            //~ printf("\nKapitel %d: Polynome\n\n",POLY);
            //~ printf("%d\t 1\t//Polynom berechnen\n",POLY);
            //~ printf("%d\t 2\t//Polynome addieren\n",POLY);
            //~ printf("%d\t 3\t//Polynome multiplizieren\n",POLY);
            //~ printf("%d\t 4\t//Polynom ableiten\n",POLY);
            //~ if(chap==POLY) break;
        case TRIV:
            printf("\nKapitel %d: Trivia\n\n",TRIV);
            printf("%d\t 1\t//Mehrwertsteuer\n",TRIV);
            printf("%d\t 2\t//Summe n+n+1+n+2+...+2n\n",TRIV);
            printf("%d\t 3\t//Summe aller Un-/Geraden Zahlen\n",TRIV);
            printf("%d\t 4\t//großes H\n",TRIV);
            printf("%d\t 5\t//vierte Wurzel\n",TRIV);
            printf("%d\t 6\t//ax^2+bx+c\n",TRIV);
            printf("%d\t 7\t//Reziproke\n",TRIV);
            printf("%d\t 8\t//16 Bit shift (zyklisch)\n",TRIV);
            printf("%d\t 9\t//16 Bit spiegeln\n",TRIV);
            printf("%d\t10\t//Maximum von vier Zahlen\n",TRIV);
            printf("%d\t11\t//Datum binär packen\n",TRIV);
            printf("%d\t12\t//100 Zeichen Palindromität prüfen\n",TRIV);
            printf("%d\t13\t//dec2base36\n",TRIV);
            printf("%d\t15\t//Benchmark\n",TRIV);
            if(chap==TRIV) break;
        case CONWAY:
            printf("\nKapitel %d: Conways Game of Life\n\n",CONWAY);
            printf("%d\t 1\t//Gleiter, 10x10, 32Gen\n",CONWAY);
            printf("%d\t 2\t//HWSS, 100x20, 200Gen\n",CONWAY);
            printf("%d\t 3\t//Pulsator, 30x30, 15Gen\n",CONWAY);
            printf("%d\t 4\t//stabil, 19x19, 19Gen\n",CONWAY);
            printf("%d\t 3\t//Ramdom, 100x100, 300Gen\n",CONWAY);
            if(chap==CONWAY) break;
    }
}

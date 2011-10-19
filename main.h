#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <time.h>
#include "help.h"
//~ #include "mat.h"
//~ #include "trivia.h"
//~ #include "game_rand.h"
//~ #include "prim.h"
//~ #include "karten.h"

//~ #include "polynom.h"
//~ #include "polynom_aufruf.h"

int menu(int argc, char **argv);

#define V_MAJOR 0
#define V_MINOR 1
#define V_FIX 01

#define MAT 1
#define GAME 2
#define KRYPTO 3
#define PRIM 4
//~ #define POLY 5
#define TRIV 5
#define CONWAY 6

#endif

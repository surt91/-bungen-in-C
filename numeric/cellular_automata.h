#ifndef CELLULAR_AUTOMATA_H
#define CELLULAR_AUTOMATA_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <cairo/cairo.h>

typedef struct
{
    uint8_t rule;
    uint8_t *status;
    int x;
    int gen;
} ca_line_t;

void ca_90();

#endif //CELLULAR_AUTOMATA_H

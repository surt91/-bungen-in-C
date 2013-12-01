#include "cellular_automata.h"
#define CAIRO_SCALE 15

// returns 0, if every entry is 0, else 1
int ca_get_next_status(uint8_t *status, int x, uint8_t rule)
{
    int i;
    int all_zero = 1;
    uint8_t *tmp_status;
    uint8_t l,c,r;
    uint8_t pack;

    tmp_status = (uint8_t *) calloc(x, sizeof(uint8_t));

    for(i=0;i<x;i++)
    {
        if(status[i])
        {
            all_zero = 0;
            break;
        }
    }
    if(all_zero)
        return 0;

    for(i=0;i<x;i++)
    {
        // periodische RB
        if(i-1 >= 0)
            l = status[i-1];
        else
            l = status[x-1];
        c = status[i];
        if(i+1 < x)
            r = status[i+1];
        else
            r = status[0];

        // pack bytes
        pack = ((l & 1) << 2) | ((c & 1) << 1) | (r & 1);
        // 0 <= pack <= 7

        switch(pack)
        {
            case 0b000:
                if(rule & 1<<0)
                    tmp_status[i] = 1;
                break;
            case 0b001:
                if(rule & 1<<1)
                    tmp_status[i] = 1;
                break;
            case 0b010:
                if(rule & 1<<2)
                    tmp_status[i] = 1;
                break;
            case 0b011:
                if(rule & 1<<3)
                    tmp_status[i] = 1;
                break;
            case 0b100:
                if(rule & 1<<4)
                    tmp_status[i] = 1;
                break;
            case 0b101:
                if(rule & 1<<5)
                    tmp_status[i] = 1;
                break;
            case 0b110:
                if(rule & 1<<6)
                    tmp_status[i] = 1;

                break;
            case 0b111:
                if(rule & 1<<7)
                    tmp_status[i] = 1;
                break;
        }
    }

    memcpy(status, tmp_status, x);

    free(tmp_status);

    return 1;
}

void ca_print_on_stdout(uint8_t *out, int x, int y)
{
    int i, j;

    for(j=0;j<y;j++)
    {
        for(i=0;i<x;i++)
            if(out[i+x*j])
                printf("*");
            else
                printf(" ");
        printf("\n");
    }
}

void ca_main(uint8_t rule, int x, int y, uint8_t *out)
{
    int i;

    uint8_t *status;

    status = (uint8_t *) calloc( x, sizeof(uint8_t));
    status[x/2] = 1;

    for(i=0;i<y;i++)
    {
        memcpy(out+i*x, status, x);
        ca_get_next_status(status, x, rule);
    }

    free(status);
}

void ca_90()
{
    uint8_t *out;

    int x = 201;
    int y = 100;

    out = (uint8_t *) calloc( x * y, sizeof(uint8_t));

    ca_main(90, x, y, out);

    ca_print_on_stdout(out, x, y);

    free(out);
}

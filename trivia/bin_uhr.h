#ifndef BIN_UHR_H
#define BIN_UHR_H

#include <stdio.h>
#include <stdint.h>
#include <time.h>

typedef uint16_t bin_uhr_zeit;

bin_uhr_zeit bin_uhr_packer(int h, int min, int s);
void bin_uhr_entpacker(bin_uhr_zeit gepackt, int *h, int *min, int *s);
void bin_uhr();

#endif //BIN_UHR_H


#ifndef STEGO_H_
#define STEGO_H_

#include "bmp.h"
#define get_bit(a) (a & 1)
#define change_bit(a, b) (get_bit(a) == b ? a : a ^ 1)

int make_hash(const char symbol);
char symbol_by_hash(const int hash);
void insert_bit(const int bit, const char color_channel, pixel_t *pixel);
int extract_bit(const char color_channel, const pixel_t pixel);

#endif
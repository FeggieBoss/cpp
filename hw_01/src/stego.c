#include "stego.h"

static const int space_hash = 26;
static const int point_hash = 27;
static const int comma_hash = 28;

int make_hash(const char symbol)
{
    if ('A' <= symbol && symbol <= 'Z')
        return (symbol - 'A');
    else if (symbol == ' ')
        return space_hash;
    else if (symbol == '.')
        return point_hash;
    else if (symbol == ',')
        return comma_hash;

    return 404;
}

char symbol_by_hash(const int hash)
{
    if (0 <= hash && hash <= 25)
        return (char)('A' + hash);
    else if (hash == space_hash)
        return ' ';
    else if (hash == point_hash)
        return '.';
    else
        return ',';
}

void insert_bit(const int bit, const char color_channel, pixel_t *pixel)
{

    if (color_channel == 'R')
        pixel->r = change_bit(pixel->r, bit);
    else if (color_channel == 'G')
        pixel->g = change_bit(pixel->g, bit);
    else
        pixel->b = change_bit(pixel->b, bit);
}

int extract_bit(const char color_channel, const pixel_t pixel)
{
    if (color_channel == 'R')
        return get_bit(pixel.r);
    else if (color_channel == 'G')
        return get_bit(pixel.g);
    else
        return get_bit(pixel.b);
}
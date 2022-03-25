#ifndef BMP_H_
#define BMP_H_
#define calc_padding(x) (4 - (3 * x) % 4) % 4

#include "stdint.h"
#include "stdio.h"
#include "string.h"

typedef struct bmp_file_header bmp_file_header_t;
typedef struct pixel pixel_t;
typedef struct bmp_dib_header bmp_dib_header_t;

struct bmp_file_header
{
    uint16_t signature;
    uint32_t file_size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t pixel_array_offset;
} __attribute__((packed));

struct bmp_dib_header
{
    uint32_t dib_size;
    uint32_t image_width;
    uint32_t image_height;
    uint16_t planes;
    uint16_t bits_per_pixel;
    uint32_t compression;
    uint32_t image_size;
    uint32_t x_pixels_per_meter;
    uint32_t y_pixels_per_meter;
    uint32_t colors;
    uint32_t important_color_count;
} __attribute__((packed));

struct pixel
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} __attribute__((packed));

void load_bmp(FILE *in_bmp, const size_t pixel_array_offset,
              const uint32_t w, const uint32_t h, const int padding, pixel_t **pixel_matrix);

void crop(pixel_t **pixel_matrix, const int x, const int y,
          const int dx, const int dy, pixel_t **fragment_matrix);

void rotate(pixel_t **fragment_matrix,
            const int dx, const int dy, pixel_t **rev_fragment_matrix);

void save_bmp(const int dx, const int dy, FILE *out_bmp,
              pixel_t **rev_fragment_matrix,
              const bmp_file_header_t file_header,
              const bmp_dib_header_t dib_header);

#endif
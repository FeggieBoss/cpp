#include "bmp.h"

void load_bmp(FILE *in_bmp, const size_t pixel_array_offset,
              const uint32_t w, const uint32_t h, const int padding,
              pixel_t **pixel_matrix)
{
    fseek(in_bmp, pixel_array_offset, SEEK_SET);
    for (uint32_t i = 0; i < h; ++i)
    {
        fread(pixel_matrix[i], sizeof(pixel_t), w, in_bmp);
        fseek(in_bmp, padding, SEEK_CUR);
    }
}

void crop(pixel_t **pixel_matrix, const int x, const int y,
          const int dx, const int dy, pixel_t **fragment_matrix)
{
    for (int i = y - dy + 1; i <= y; ++i)
    {
        for (int j = x; j < x + dx; ++j)
        {
            int local_x = i - (y - dy + 1);
            int local_y = j - x;
            fragment_matrix[local_x][local_y] = pixel_matrix[i][j];
        }
    }
}

void rotate(pixel_t **fragment_matrix,
            const int dx, const int dy, pixel_t **rev_fragment_matrix)
{
    for (int i = 0; i < dy; ++i)
    {
        for (int j = 0; j < dx; ++j)
        {
            rev_fragment_matrix[(dx - 1) - j][i] = fragment_matrix[i][j];
        }
    }
}

void save_bmp(const int dx, const int dy, FILE *out_bmp,
              pixel_t **rev_fragment_matrix,
              const bmp_file_header_t file_header,
              const bmp_dib_header_t dib_header)
{
    int padding = calc_padding(dx);
    uint32_t out_image_size = (sizeof(pixel_t) * dx + padding) * dy;
    uint32_t out_file_size = file_header.file_size - dib_header.image_size + out_image_size;

    bmp_file_header_t out_file_header = file_header;
    out_file_header.file_size = out_file_size;

    bmp_dib_header_t out_dib_header = dib_header;
    out_dib_header.image_width = dx;
    out_dib_header.image_height = dy;
    out_dib_header.image_size = out_image_size;

    fwrite(&out_file_header, sizeof(bmp_file_header_t), 1, out_bmp);
    fwrite(&out_dib_header, sizeof(bmp_dib_header_t), 1, out_bmp);

    int empty = 0;
    for (int i = 0; i < dy; ++i)
    {
        fwrite(rev_fragment_matrix[i], sizeof(pixel_t), dx, out_bmp);
        fwrite(&empty, padding, 1, out_bmp);
    }
}

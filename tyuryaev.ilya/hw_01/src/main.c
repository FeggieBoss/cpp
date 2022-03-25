#include "stego.h"
#include "stdlib.h"

static void make_matrix(void **array, pixel_t ***matrix, const int n, const int m)
{
    *array = malloc(n * m * sizeof(pixel_t));
    *matrix = malloc(n * sizeof(pixel_t *));
    for (int i = 0; i < n; ++i)
    {
        pixel_t *ptr = *array;
        (*matrix)[i] = &ptr[i * m];
    }
}

int main(int argc, char **argv)
{
    if (argc < 3)
        return 0;

    FILE *in_bmp = fopen(argv[2], "rb");
    if (in_bmp == NULL)
        return 0;

    bmp_file_header_t file_header;
    fread(&file_header, sizeof(file_header), 1, in_bmp);

    bmp_dib_header_t dib_header;
    fread(&dib_header, sizeof(dib_header), 1, in_bmp);

    uint32_t w = dib_header.image_width;
    uint32_t h = dib_header.image_height;

    int padding = calc_padding(w);

    void *pixels = NULL;
    pixel_t **pixel_matrix = NULL;
    make_matrix(&pixels, &pixel_matrix, h, w);

    load_bmp(in_bmp, file_header.pixel_array_offset,
             w, h, padding, pixel_matrix);

    if (strcmp(argv[1], "crop-rotate") == 0 && argc == 8)
    {
        int x = atoi(argv[4]), y = atoi(argv[5]), dx = atoi(argv[6]), dy = atoi(argv[7]);
        if (0 <= x && x < x + dx && x + dx <= (int)w && 0 <= y && y < y + dy && y + dy <= (int)h)
        {
            void *fragment = NULL;
            pixel_t **fragment_matrix = NULL;
            make_matrix(&fragment, &fragment_matrix, dy, dx);

            crop(pixel_matrix, x, (h - 1) - y, dx, dy, fragment_matrix);

            void *rev_fragment = NULL;
            pixel_t **rev_fragment_matrix = NULL;
            make_matrix(&rev_fragment, &rev_fragment_matrix, dx, dy);

            rotate(fragment_matrix, dx, dy, rev_fragment_matrix);

            FILE *out_bmp = fopen(argv[3], "wb");
            save_bmp(dy, dx, out_bmp, rev_fragment_matrix, file_header, dib_header);

            fclose(out_bmp);
            free(fragment);
            free(fragment_matrix);
            free(rev_fragment);
            free(rev_fragment_matrix);
        }
    }
    else if (strcmp(argv[1], "insert") == 0 && argc == 6)
    {
        FILE *key = fopen(argv[4], "r");
        FILE *msg = fopen(argv[5], "r");

        char symbol = '\0';
        while (fscanf(msg, "%c", &symbol) != EOF)
        {
            int hash = make_hash(symbol);
            if (hash == 404)
                break;
            for (int i = 0; i < 5; ++i)
            {
                int x = 0, y = 0;
                char color_channel = '\0';
                fscanf(key, "%d %d %c", &x, &y, &color_channel);
                y = (h - 1) - y;

                int cur = (1 << i);
                insert_bit((hash & cur)>0, color_channel, &pixel_matrix[x][y]);
            }
        }

        FILE *out_bmp = fopen(argv[3], "wb");
        save_bmp(w, h, out_bmp, pixel_matrix, file_header, dib_header);

        fclose(key);
        fclose(msg);
        fclose(out_bmp);
    }
    else if (strcmp(argv[1], "extract") == 0 && argc == 5)
    {
        FILE *key = fopen(argv[3], "r");
        FILE *msg = fopen(argv[4], "w");

        int x = 0, y = 0, counter = 0, hash = 0;
        char color_channel = '\0';
        while (fscanf(key, "%d %d %c", &x, &y, &color_channel) != EOF)
        {
            y = (h - 1) - y;

            int cur = (1 << counter);
            hash += cur * extract_bit(color_channel, pixel_matrix[x][y]);

            counter++;
            if (counter == 5)
            {
                char symbol = symbol_by_hash(hash);
                fwrite(&symbol, 1, 1, msg);

                counter = 0;
                hash = 0;
            }
        }

        fclose(key);
        fclose(msg);
    }

    fclose(in_bmp);
    free(pixels);
    free(pixel_matrix);
    return 0;
}
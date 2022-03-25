#include "point_list.h"
#include "string.h"
#include "assert.h"

const size_t bin_size = 3;

void my_print(intrusive_node_t *node, void *data)
{
    point_t *p = container_of(node, point_t, node);
    printf((char *)data, p->x, p->y);
}

void my_count(intrusive_node_t *node, void *data)
{
    if (node != NULL)
        (*(int *)data)++;
}

int main(int argc, char **argv)
{
    assert(argc > 1);
    FILE *file = fopen(argv[2], (strcmp(argv[1], "loadtext") == 0 ? "r" : "rb"));

    intrusive_list_t my_list;
    init_list(&my_list);

    int x, y;
    x = 0;
    y = 0;
    if (strcmp(argv[1], "loadtext") == 0)
    {
        while (fscanf(file, "%d %d", &x, &y) != EOF)
            add_point(&my_list, x, y);
    }
    else
    {
        while (fread(&x, bin_size, 1, file) == 1 &&
               fread(&y, bin_size, 1, file) == 1)
            add_point(&my_list, x, y);
    }

    intrusive_node_t *head = my_list.head;
    while (head->next)
        head = head->next;

    if (strcmp(argv[3], "print") == 0)
    {
        apply(head, my_print, argv[4]);
        printf("\n");
    }
    else if (strcmp(argv[3], "count") == 0)
    {
        int size = 0;
        apply(head, my_count, &size);
        printf("%d\n", size);
    }
    else
    {
        FILE *out_file = fopen(argv[4], (strcmp(argv[3], "savetext") == 0 ? "w" : "wb"));

        while (head->prev)
        {
            point_t *p = container_of(head, point_t, node);

            if (strcmp(argv[3], "savetext") == 0)
                fprintf(out_file, "%d %d\n", p->x, p->y);
            else
            {
                fwrite(&p->x, bin_size, 1, out_file);
                fwrite(&p->y, bin_size, 1, out_file);
            }

            head = head->prev;
        }

        fclose(out_file);
    }

    remove_all_points(&my_list);
    free(my_list.head);

    fclose(file);
    return 0;
}

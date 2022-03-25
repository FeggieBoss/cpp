#include "mergesort.h"

int int_comparator(const void *a, const void *b)
{
    return *(int *)b - *(int *)a;
}

int char_comparator(const void *a, const void *b)
{
    return *(char *)b - *(char *)a;
}

int string_comparator(const void *a, const void *b)
{
    char *s1 = *(char **)a;
    char *s2 = *(char **)b;
    while (*s1 != '\0' && *s2 != '\0')
    {
        if (*s1 != *s2)
            return char_comparator(s1, s2);
        s1++;
        s2++;
    }
    if (*s1 == '\0' && *s2 != '\0')
        return 1;
    if (*s1 != '\0' && *s2 == '\0')
        return -1;
    return 0;
}

int main(int argc, char **argv)
{
    size_t elements = argc - 2;
    size_t element_size;

    if (strcmp(argv[1], "str") == 0)
    {
        element_size = sizeof(char *);
        char **array = malloc(elements * element_size);

        for (int i = 2; i < 2 + elements; ++i)
        {
            array[i - 2] = malloc(strlen(argv[i]) * element_size);
            strcpy(array[i - 2], argv[i]);
        }

        int succes = mergesort(array, elements, element_size, string_comparator);

        if (succes == 0)
        {
            for (int i = 0; i < elements; ++i)
                printf("%s ", array[i]);
        }
        else
        {
            printf("Error: memory allocation failed.");
        }

        for (int i = 2; i < 2 + elements; ++i)
            free(array[i - 2]);
        free(array);
    }
    else if (strcmp(argv[1], "char") == 0)
    {
        element_size = sizeof(char);
        char *array = malloc(elements * element_size);

        for (int i = 2; i < 2 + elements; ++i)
            array[i - 2] = *argv[i];

        int succes = mergesort(array, elements, element_size, char_comparator);

        if (succes == 0)
        {
            for (int i = 0; i < elements; ++i)
                printf("%c ", array[i]);
        }
        else
        {
            printf("Error: memory allocation failed.");
        }

        free(array);
    }
    else
    {
        element_size = sizeof(int);
        int *array = malloc(elements * element_size);

        for (int i = 2; i < 2 + elements; ++i)
            array[i - 2] = atoi(argv[i]);

        int succes = mergesort(array, elements, element_size, int_comparator);

        if (succes == 0)
        {
            for (int i = 0; i < elements; ++i)
                printf("%d ", array[i]);
        }
        else
        {
            printf("Error: memory allocation failed.");
        }

        free(array);
    }

    return 0;
}
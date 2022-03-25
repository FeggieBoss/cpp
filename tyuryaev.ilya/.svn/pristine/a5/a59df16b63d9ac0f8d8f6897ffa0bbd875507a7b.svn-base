#include "mergesort.h"
#include "assert.h"

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

int main()
{
    size_t elements;
    size_t element_size;

    // str
    elements = 2;
    element_size = sizeof(char *);
    char **array1 = malloc(elements * element_size);

    array1[0] = malloc(strlen("chip") * element_size);
    strcpy(array1[0], "chip");
    array1[1] = malloc(strlen("dale") * element_size);
    strcpy(array1[1], (char *)"chip");

    mergesort(array1, elements, element_size, string_comparator);
    assert(strcmp(array1[0], "chip") == 0);

    // int
    elements = 3;
    element_size = sizeof(int);

    int *array2 = malloc(elements * element_size);
    array2[0] = 1;
    array2[1] = -1;
    array2[2] = 1030405;
    mergesort(array2, elements, element_size, int_comparator);

    assert(array2[0] == -1);
    assert(array2[1] == 1);
    assert(array2[2] == 1030405);

    // char
    elements = 5;
    element_size = sizeof(char);
    char *array3 = malloc(elements * element_size);

    array3[0] = 'g';
    array3[1] = 'a';
    array3[2] = 'y';
    array3[3] = 'k';
    array3[4] = 'a';

    mergesort(array3, elements, element_size, char_comparator);

    assert(array3[0] == 'a');
    assert(array3[1] == 'a');
    assert(array3[2] == 'g');
    assert(array3[3] == 'k');
    assert(array3[4] == 'y');

    free(array1[0]);
    free(array1[1]);
    free(array1);
    free(array2);
    free(array3);
    return 0;
}
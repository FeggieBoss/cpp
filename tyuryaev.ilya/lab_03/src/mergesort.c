#include "mergesort.h"

int merge(void *left, void *mid, void *right,
          size_t element_size, int (*comparator)(const void *, const void *))
{
    size_t n = right - left;
    char *it1 = left;
    char *it2 = mid;
    char *result = malloc(n * element_size);
    if (result == NULL)
        return -1;
    char *start = result;

    while (it1 < (char *)mid && it2 < (char *)right)
    {
        if (comparator(it1, it2) >= 0)
        {
            for (int i = 0; i < element_size; ++i)
                result[i] = it1[i];
            it1 += element_size;
        }
        else
        {
            for (int i = 0; i < element_size; ++i)
                result[i] = it2[i];
            it2 += element_size;
        }

        result += element_size;
    }

    while (it1 < (char *)mid)
    {
        for (int i = 0; i < element_size; ++i)
            result[i] = it1[i];

        result += element_size;
        it1 += element_size;
    }

    while (it2 < (char *)right)
    {
        for (int i = 0; i < element_size; ++i)
            result[i] = it2[i];

        result += element_size;
        it2 += element_size;
    }

    char *dop_start = start;
    while (left < right)
    {
        for (int i = 0; i < element_size; ++i)
            *((char *)left + i) = *(start + i);

        left += element_size;
        start += element_size;
    }

    free(dop_start);
    return 0;
}

int mergesort(void *array, size_t elements, size_t element_size,
              int (*comparator)(const void *, const void *))
{
    for (int i = 1; i < elements; i *= 2)
    {
        for (int j = 0; j < elements - i; j += 2 * i)
        {
            int pi = i * element_size;
            int pj = j * element_size;

            int min = pj + 2 * pi;
            if (min > elements * element_size)
                min = elements * element_size;

            int succes = merge(array + pj, array + pj + pi, array + min, element_size, comparator);
            if (succes == -1)
                return -1;
        }
    }
    return 0;
}
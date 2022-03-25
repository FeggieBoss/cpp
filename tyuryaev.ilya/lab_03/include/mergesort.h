#pragma once
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int mergesort(void *array, size_t elements, size_t element_size,
               int (*comparator)(const void *, const void *));
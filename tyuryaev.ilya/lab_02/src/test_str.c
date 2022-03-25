#include "test_str.h"

void test_strcpy()
{
    char a[] = "feggie", b[] = "boss";
    assert(my_strcmp(my_strcpy(a, b), b) == 0);

    char c[] = "rescue", d[] = "rangers";
    assert(my_strcmp(my_strcpy(c, d), b) == 1);

    assert(my_strcmp(my_strcpy(c, c), b) == 1);
    assert(my_strcmp(my_strcpy(c, c), c) == 0);
}

void test_strcat()
{
    char a[11] = "feggie", b[] = "boss", c[] = "feggieboss";
    assert(my_strcmp(my_strcat(a, b), c) == 0);

    char d[] = "";
    assert(my_strcmp(my_strcat(b, d), b) == 0);
    assert(my_strcmp(my_strcat(d, a), c) == 0);
}

void test_strlen()
{
    char a[] = "feggie";
    assert(my_strlen(a) == 6);

    char b[] = "";
    assert(my_strlen(b) == 0);
}

void test_strcmp()
{
    char a[] = "feggie", b[] = "boss";
    assert(my_strcmp(a, b) == 1);
    assert(my_strcmp(b, a) == -1);
    assert(my_strcmp(a, a) == 0);

    char c[] = "Chip", d[] = "Dale", m[] = "Monty", g[] = "Gadget", z[] = "Zipper";
    assert(my_strcmp(c, d) == -1);
    assert(my_strcmp(c, m) == -1);
    assert(my_strcmp(c, g) == -1);
    assert(my_strcmp(g, z) == -1);
    assert(my_strcmp(z, m) == 1);
}
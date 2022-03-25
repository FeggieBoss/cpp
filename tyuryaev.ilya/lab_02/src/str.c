#include "str.h"

char *my_strcpy(char *s1, char *s2)
{
    char *start = s1;
    while (*s2 != '\0')
        *s1++ = *s2++;
    *s1 = '\0';

    return start;
}

char *my_strcat(char *s1, char *s2)
{
    char *start = s1;
    while (*s1 != '\0')
        s1++;

    while (*s2 != '\0')
        *s1++ = *s2++;
    *s1 = '\0';

    return start;
}

int my_strcmp(char *s1, char *s2)
{
    while (*s1 != '\0' || *s2 != '\0')
    {
        if (*s1 > *s2)
            return 1;
        if (*s1 < *s2)
            return -1;
        s1++;
        s2++;
    }
    if (*s1 == '\0' && *s2 != '\0')
        return -1;
    if (*s1 != '\0' && *s2 == '\0')
        return 1;

    return 0;
}

int my_strlen(char *s)
{
    int ret = 0;
    while (*s != '\0')
    {
        s++;
        ret++;
    }

    return ret;
}

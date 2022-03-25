#ifndef P_CLIST_H_
#define P_CLIST_H_

#define container_of(ptr, type, member) (type *)((char *)(ptr)-offsetof(type, member))

#include "clist.h"
#include "stdio.h"

struct point
{
    int x, y;
    struct intrusive_node node;
};

void add_point(intrusive_list_t *my_list, int x, int y);
void remove_point(intrusive_list_t *my_list, int x, int y);
void show_all_points(intrusive_list_t *my_list);
void remove_all_points(intrusive_list_t *my_list);

#endif
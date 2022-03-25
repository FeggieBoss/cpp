#ifndef CLIST_H_
#define CLIST_H_

#include "stddef.h"
#include "stdlib.h"

typedef struct intrusive_list intrusive_list_t;
typedef struct intrusive_node intrusive_node_t;
typedef struct point point_t;

struct intrusive_node
{
    struct intrusive_node *next;
    struct intrusive_node *prev;
};

struct intrusive_list
{
    struct intrusive_node *head;
};

void init_list(intrusive_list_t *my_list);
void add_node(intrusive_list_t *my_list, intrusive_node_t *node);
void remove_node(intrusive_node_t *node);

int get_length(intrusive_list_t *my_list);

#endif
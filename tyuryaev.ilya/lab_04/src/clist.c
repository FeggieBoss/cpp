#include "clist.h"

void init_list(intrusive_list_t *my_list)
{
    my_list->head = malloc(sizeof(intrusive_node_t));
    my_list->head->prev = my_list->head->next = NULL;
}

void add_node(intrusive_list_t *my_list, intrusive_node_t *node)
{
    intrusive_node_t *head = my_list->head;
    if (head->next)
    {
        intrusive_node_t *next = head->next;
        head->next = node;
        node->prev = head;
        node->next = next;
        next->prev = node;
    }
    else
    {
        head->next = node;
        head->next->prev = head;
        head->next->next = NULL;
    }
}

void remove_node(intrusive_node_t *node)
{
    intrusive_node_t *pred = node->prev;

    if (node->next)
    {
        pred->next = node->next;
        node->next->prev = pred;
    }
    else
    {
        pred->next = NULL;
    }
}

int get_length(intrusive_list_t *my_list)
{
    intrusive_node_t *head = my_list->head;

    int size = 0;
    while (head->next)
    {
        head = head->next;
        size++;
    }
    return size;
}
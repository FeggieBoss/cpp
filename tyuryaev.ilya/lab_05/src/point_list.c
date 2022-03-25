#include "point_list.h"

void add_point(intrusive_list_t *my_list, int x, int y)
{
    point_t *p = malloc(sizeof(point_t));
    p->x = x;
    p->y = y;
    add_node(my_list, &(p->node));
}

void remove_point(intrusive_list_t *my_list, int x, int y)
{
    intrusive_node_t *head = my_list->head;
    while (head->next)
    {
        intrusive_node_t *cur = head->next;

        point_t *p = container_of(cur, point_t, node);
        if (p->x != x || p->y != y)
        {
            head = head->next;
            continue;
        }

        remove_node(cur);
        free(p);
    }
}

void show_all_points(intrusive_list_t *my_list)
{
    intrusive_node_t *head = my_list->head;
    while (head->next)
    {
        head = head->next;
        point_t *p = container_of(head, point_t, node);

        printf("(%d %d)", p->x, p->y);
        if (head->next)
            printf(" ");
    }
    printf("\n");
}

void remove_all_points(intrusive_list_t *my_list)
{
    intrusive_node_t *head = my_list->head;
    while (head->next)
    {
        intrusive_node_t *cur = head->next;
        point_t *p = container_of(cur, point_t, node);

        remove_node(cur);
        free(p);
    }
}
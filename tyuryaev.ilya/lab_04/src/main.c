#include "clist.h"
#include "stdio.h"
#include "string.h"
#define container_of(ptr, type, member) (type *)((char *)(ptr)-offsetof(type, member))

struct point
{
    int x, y;
    struct intrusive_node node;
};

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

int main(int argc, char **argv)
{
    intrusive_list_t my_list;
    init_list(&my_list);

    char input[239];
    while (1)
    {
        scanf("%239s", input);

        if (strcmp(input, "add") == 0)
        {
            int x, y;
            scanf("%d %d", &x, &y);
            add_point(&my_list, x, y);
        }
        else if (strcmp(input, "rm") == 0)
        {
            int x, y;
            scanf("%d %d", &x, &y);
            remove_point(&my_list, x, y);
        }
        else if (strcmp(input, "print") == 0)
        {
            show_all_points(&my_list);
        }
        else if (strcmp(input, "rma") == 0)
        {
            remove_all_points(&my_list);
        }
        else if (strcmp(input, "len") == 0)
        {
            printf("%d\n", get_length(&my_list));
        }
        else if (strcmp(input, "exit") == 0)
        {
            break;
        }
        else
        {
            printf("Unknown command\n");
        }
    }

    remove_all_points(&my_list);
    free(my_list.head);
    return 0;
}
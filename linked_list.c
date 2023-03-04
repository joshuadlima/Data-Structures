#include <stdio.h>
#include <stdlib.h>
#define sint(x) scanf("%d", &x)

struct node
{
    int data;
    struct node *next;
};

// add new node
struct node *add_at_beginning(struct node *start, int value);

struct node *add_at_end(struct node *start, int value);

struct node *add_after(struct node *start, int target, int value);

struct node *add_before(struct node *start, int target, int value);

struct node *add_at_position(struct node *start, int target, int value);

// deletion
struct node *Delete_at_beginning(struct node *start);

struct node *Delete_at_end(struct node *start);

struct node *Delete_value(struct node *start, int value);

// reverse
struct node *reverse(struct node *start);

// display
void display(struct node *start);

int main()
{
    int value, target;
    struct node *start = NULL;

    while (1)
    {
        int sc;
        printf("enter 1 -> add at beg\n");
        printf("enter 2 -> add at end\n");
        printf("enter 3 -> add after\n");
        printf("enter 4 -> add before\n");
        printf("enter 5 -> add at position\n");
        printf("enter 6 -> Delete at beginning\n");
        printf("enter 7 -> Delete at end\n");
        printf("enter 8 -> Delete value\n");
        printf("enter 9 -> reverse\n");
        printf("enter 10 -> display\n");
        sint(sc);

        switch (sc)
        {
        case 1:
            sint(value), start = add_at_beginning(start, value);
            break;

        case 2:
            sint(value), start = add_at_end(start, value);
            break;

        case 3:
            sint(target), sint(value), start = add_after(start, target, value);
            break;

        case 4:
            sint(target), sint(value), start = add_before(start, target, value);
            break;

        case 5:
            sint(target), sint(value), start = add_at_position(start, target, value);
            break;

        case 6:
            start = Delete_at_beginning(start);
            break;

        case 7:
            start = Delete_at_end(start);
            break;

        case 8:
            sint(value), start = Delete_value(start, value);
            break;

        case 9:
            start = reverse(start);
            break;

        case 10:
            display(start);
            break;

        default:
            exit(1);
        }
    }

    return 0;
}

struct node *add_at_beginning(struct node *start, int value)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->data = value, temp->next = NULL;

    if (start == NULL) // add in empty
        return temp;
    else // add at beginning
    {
        temp->next = start;
        start = temp;
        return start;
    }
}

struct node *add_at_end(struct node *start, int value)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->data = value, temp->next = NULL;

    if (start == NULL) // add in empty
        return temp;
    else // add at end
    {
        struct node *p = start;
        while (p->next != NULL)
            p = p->next;

        p->next = temp;
        return start;
    }
}

struct node *add_after(struct node *start, int target, int value)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->data = value, temp->next = NULL;

    struct node *p = start;
    while (p != NULL && p->data != target)
        p = p->next;

    if (p == NULL)
        printf("node not found\n");
    else
        temp->next = p->next, p->next = temp;
    return start;
}

struct node *add_before(struct node *start, int target, int value)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->data = value, temp->next = NULL;

    struct node *p = start;
    if (p == NULL) // empty list
        return start;

    // take p to the node before required one
    while (p->next != NULL && p->next->data != target)
        p = p->next;

    if (p->next == NULL)
        printf("node not found\n");
    else
        temp->next = p->next, p->next = temp;
    return start;
}

struct node *add_at_position(struct node *start, int target, int value)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->data = value, temp->next = NULL;

    if (target == 1)
    {
        temp->next = start, start = temp;
        return start;
    }

    struct node *p = start;
    for (int i = 1; i < target - 1 && p != NULL; i++)
        p = p->next;

    if (p == NULL)
        printf("node not found\n");
    else
        temp->next = p->next, p->next = temp;
    return start;
}

void display(struct node *start)
{
    printf("linked list : ");
    while (start != NULL)
        printf("%d ", start->data), start = start->next;
}

struct node *Delete_at_beginning(struct node *start)
{
    if (start == NULL)
        printf("linked list is empty\n");

    struct node *temp = start;
    start = start->next;
    free(temp);

    return start;
}

struct node *Delete_at_end(struct node *start)
{
    if (start == NULL)
        printf("linked list is empty\n");
    else if (start->next == NULL)
        start = NULL;

    struct node *temp = start;
    while (temp->next->next != NULL)
        temp = temp->next;

    free(temp->next);
    temp->next = NULL;

    return start;
}

struct node *Delete_value(struct node *start, int value)
{
    struct node *temp = start;
    if (start == NULL)
        printf("linked list is empty\n");
    else if (start->data == value)
        temp = start, start = start->next;
    else
    {
        while (temp->next != NULL && temp->next->data != value)
            temp = temp->next;

        struct node *p;
        if (temp->next == NULL)
            printf("node not found\n");
        else
            p = temp->next, temp->next = temp->next->next, free(p);
    }

    return start;
}

struct node *reverse(struct node *start)
{
    if (start == NULL) // empty case
        return start;
    else if (start->next == NULL) // normal case
        return start;
    else
    {
        struct node *new_start = reverse(start->next);
        struct node *forward = start->next;
        forward->next = start;
        start->next = NULL;
        return new_start;
    }
}
#include <stdio.h>
#include <stdlib.h>
#define sint(x) scanf("%d", &x)
#define MAX 10

int stack_arr[MAX], top = -1;

// using array
int isEmpty();

int isFull();

void push(int value);

void pop();

int peek();

void display();

int main()
{
    int value;

    while (1)
    {
        int sc;
        printf("enter 1 -> push\n");
        printf("enter 2 -> pop\n");
        printf("enter 3 -> peek\n");
        printf("enter 4 -> display\n");
        sint(sc);

        switch (sc)
        {
        case 1:
            sint(value), push(value);
            break;

        case 2:
            pop();
            break;

        case 3:
            printf("%d\n", peek());
            break;

        case 4:
            display();
            break;

        default:
            exit(1);
        }
    }

    return 0;
}

int isEmpty()
{
    return top == -1;
}

int isFull()
{
    return top == MAX - 1;
}

void push(int value)
{
    if (isFull())
        printf("STACK OVERFLOW\n");
    else
        stack_arr[++top] = value;
}

void pop()
{
    if (isEmpty())
        printf("STACK UNDERFLOW\n");
    else
        top--;
}

int peek()
{
    if (isEmpty())
        printf("Stack is empty\n");
    else
        return stack_arr[top];
    return -1;
}

void display()
{
    printf("Stack contents are: ");
    int i = top;
    while (i >= 0)
        printf("%d ", stack_arr[i]), i--;
    printf("\n");
}
#include <stdio.h>
#include <stdlib.h>
#define sint(x) scanf("%d", &x)
#define MAX 10

int queue_arr[MAX], front = -1, rear = -1;

// using array
int isEmpty();

int isFull();

void enqueue(int value);

void dequeue();

int peek();

void display();

int main()
{
    int value;

    while (1)
    {
        int sc;
        printf("enter 1 -> enqueue\n");
        printf("enter 2 -> dequeue\n");
        printf("enter 3 -> peek\n");
        printf("enter 4 -> display\n");
        sint(sc);

        switch (sc)
        {
        case 1:
            sint(value), enqueue(value);
            break;

        case 2:
            dequeue();
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
    if (front == -1) // initial and only stage
        return 1;
    else
        return 0;
}

int isFull()
{
    if (front == (rear + 1) % MAX)
        return 1;
    else
        return 0;
}

void enqueue(int value)
{
    if (isFull())
        printf("QUEUE OVERFLOW\n");
    else
    {
        if (front == -1) // first element
            front = 0;
        rear = (rear + 1) % MAX;
        queue_arr[rear] = value;
    }
}

void dequeue()
{
    if (isEmpty())
        printf("QUEUE UNDERFLOW\n");
    else if (front == rear) // single element in queue
    {
        front = -1, rear = -1; // reset
    }
    else
    {
        front = (front + 1) % MAX;
    }
}

int peek()
{
    if (isEmpty())
        printf("queue is empty\n");
    else
    {
        return queue_arr[front];
    }

    return -1;
}

void display()
{
    printf("queue contents are : ");
    if (isEmpty())
        return;
    else
    {
        int i = front;
        while (i != rear)
        {
            printf("%d ", queue_arr[i]);
            i = (i + 1) % MAX;
        }

        // print rear
        printf("%d ", queue_arr[rear]);
    }
    printf("\n");
}
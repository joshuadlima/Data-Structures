// ***************************** ALGORITHM *****************************
// The steps involved to evaluate the prefix expression
// 1) Scan the symbol of array prefix one by one from right to left.

// a) If symbol is an operand
// Push it on the stack.
// b) If symbol is operator

// Pop two elements from stack and apply the operator to
// these two elements.
// Suppose first A is popped and then B is popped.
// result = A operator B.
// Push result on the stack.

// 2) After all the symbols of prefix have been scanned, pop the only element
// in the stack and it is the value of prefix expression.
// *********************************************************************

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define sint(x) scanf("%d", &x)
#define MAX 10

double stack_arr[MAX];
int top = -1;

int isEmpty()
{
    return top == -1;
}

int isFull()
{
    return top == MAX - 1;
}

void push(double value)
{
    if (isFull())
        printf("STACK OVERFLOW\n");
    else
        stack_arr[++top] = value;
}

double pop()
{
    if (isEmpty())
        printf("STACK UNDERFLOW\n");
    else
        return stack_arr[top--];
    return -1;
}

double peek()
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

int isOperator(char c)
{
    if (c == '^')
        return 3;
    else if (c == '%' || c == '*' || c == '/')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else // in case of operand
        return 0;
}

int main()
{
    char prefix[100];
    scanf("%s", prefix);

    int size = 0;
    for (; prefix[size] != '\0'; size++)
        ; // compute size

    for (int i = size - 1; i >= 0; i--)
    {
        if (!isOperator(prefix[i]))
        {
            push(prefix[i] - '0');
        }
        else
        {
            double oprn1 = pop(), oprn2 = pop();
            if (prefix[i] == '^')
                push(pow(oprn1, oprn2));
            else if (prefix[i] == '%')
                push((int)oprn1 % (int)oprn2);
            else if (prefix[i] == '*')
                push(oprn1 * oprn2);
            else if (prefix[i] == '/')
                push(oprn1 / oprn2);
            else if (prefix[i] == '+')
                push(oprn1 + oprn2);
            else if (prefix[i] == '-')
                push(oprn1 - oprn2);
        }
    }

    printf("answer = %lf", pop());

    return 0;
}
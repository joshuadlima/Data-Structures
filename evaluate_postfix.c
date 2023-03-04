// ***************************** ALGORITHM *****************************
// The steps involved to evaluate the postfix expression
// 1) Scan the symbol of array postfix one by one from left to right.

// a) If symbol is an operand
// Push it on the stack.

// b) If symbol is operator
// Pop two elements from stack and apply the operator to
// these two elements.
// Suppose first A is popped and then B is popped.
// result = B operator A.
// Push result on the stack.

// 2) After all the symbols of postfix have been scanned, pop the only element
// in the stack and it is the value of postfix expression.
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
    return (c == '^' || c == '%' || c == '*' || c == '/' || c == '+' || c == '-');
}

int main()
{
    char postfix[100];
    scanf("%s", postfix);

    for (int i = 0; postfix[i] != '\0'; i++)
    {
        if (!isOperator(postfix[i]))
        {
            push(postfix[i] - '0');
        }
        else
        {
            double oprn1 = pop(), oprn2 = pop();
            if (postfix[i] == '^')
                push(pow(oprn2, oprn1));
            else if (postfix[i] == '%')
                push((int)oprn2 % (int)oprn1);
            else if (postfix[i] == '*')
                push(oprn2 * oprn1);
            else if (postfix[i] == '/')
                push(oprn2 / oprn1);
            else if (postfix[i] == '+')
                push(oprn2 + oprn1);
            else if (postfix[i] == '-')
                push(oprn2 - oprn1);
        }
    }

    printf("answer = %lf", pop());

    return 0;
}
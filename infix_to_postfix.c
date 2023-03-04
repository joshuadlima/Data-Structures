// ***************************** ALGORITHM *****************************
// The steps involved to convert infix expression into postfix expression
// 1) Scan the symbol of array infix one by one from left to right.

// a) If symbol is an operand, Add it to the postfix array
// b) If symbol is a left parenthesis ‘(‘, Push it on the stack
// c) If symbol is right parenthesis ‘)’, Pop all the operators from stack up to the first left
//    parenthesis and add these operators to array postfix. Discard both left and right parenthesis.
// d) If symbol is an operator, Pop the operators which have in-stack priority greater than or
//    equal to the priority of the symbol operator (remember case for '^'), and add these popped
//    operators to array postfix.
//    Push the scanned symbol operator on the stack.

// 2) After all the symbols of array infix has been scanned, pop all the operators remaining on the
//    stack and add them to the array postfix.
// *********************************************************************

#include <stdio.h>
#include <stdlib.h>
#define sint(x) scanf("%d", &x)
#define MAX 10

int stack_arr[MAX], top = -1;

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

int pop()
{
    if (isEmpty())
        printf("STACK UNDERFLOW\n");
    else
        return stack_arr[top--];
    return -1;
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

int operatorPrec(char c)
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

int isOperator(char c)
{
    return (c == '^' || c == '%' || c == '*' || c == '/' || c == '+' || c == '-');
}

int main()
{
    char infix[100];
    scanf("%s", infix);

    for (int i = 0; infix[i] != '\0'; i++)
    {
        if (infix[i] == '(')
        {
            push(infix[i]);
        }
        else if (infix[i] == ')')
        {
            while (peek() != '(')
                printf("%c", pop());
            pop(); // remove '('
        }
        else if (!isOperator(infix[i]))
        {
            printf("%c", infix[i]); // print operand
        }
        else
        {
            int op_prec = operatorPrec(infix[i]);
            if (op_prec == 3) // case of ^
            {
                // while (!isEmpty() && peek() != '(' && operatorPrec(peek()) > op_prec)
                //     printf("%c", pop());
                push(infix[i]);
            }
            else
            {
                while (!isEmpty() && peek() != '(' && operatorPrec(peek()) >= op_prec)
                    printf("%c", pop());
                push(infix[i]);
            }
        }
    }

    while (!isEmpty())
        printf("%c", pop());

    return 0;
}
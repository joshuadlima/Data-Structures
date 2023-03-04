// ***************************** ALGORITHM *****************************
// The steps involved to convert infix expression into prefix expression
// 1) Scan the symbol of array infix one by one from right to left.

// a) If symbol is an operand, Add it to the prefix array

// b) If symbol is right parenthesis ')', Push it on the stack

// c) If symbol is left parenthesis '(', Pop all the operators from stack up to the first right
// parenthesis and add these operators to array prefix. Discard both left and right parenthesis.

// d) If symbol is an operator, Pop the operators which have in-stack priority greater to
// the priority of the symbol operator, and add these popped operators to array prefix.
// Push the scanned symbol operator on the stack.

// 2) After all the symbols of array infix has been scanned, pop all the
// operators remaining on the stack and add them to the array prefix.

// 3) Reverse the prefix array.
// *********************************************************************

#include <stdio.h>
#include <stdlib.h>
#define sint(x) scanf("%d", &x)
#define MAX 10

char stack_arr[MAX];
int top = -1;

int isEmpty()
{
    return top == -1;
}

int isFull()
{
    return top == MAX - 1;
}

void push(char value)
{
    if (isFull())
        printf("STACK OVERFLOW\n");
    else
        stack_arr[++top] = value;
}

char pop()
{
    if (isEmpty())
        printf("STACK UNDERFLOW\n");
    else
        return stack_arr[top--];
    return -1;
}

char peek()
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
    char infix[100], prefix[100];
    int size = 0, pf_index = 0;
    scanf("%s", infix);

    for (; infix[size] != '\0'; size++); // compute size

    for (int i = size - 1; i >= 0; i--)
    {
        if (infix[i] == ')')
        {
            push(infix[i]);
        }
        else if (infix[i] == '(')
        {
            while (peek() != ')')
                prefix[pf_index++] = pop();
            pop(); // remove ')'
        }
        else if (!isOperator(infix[i]))
        {
            prefix[pf_index++] = infix[i];
        }
        else
        {
            int op_prec = isOperator(infix[i]);
            while (!isEmpty() && peek() != ')' && isOperator(peek()) > op_prec)
                prefix[pf_index++] = pop();
            push(infix[i]);
        }
    }

    while (!isEmpty())
        prefix[pf_index++] = pop();

    // reversal
    for (int i = pf_index - 1; i >= 0; i--)
        printf("%c", prefix[i]);

    return 0;
}
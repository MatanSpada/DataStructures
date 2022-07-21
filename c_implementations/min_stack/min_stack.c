#include <stdio.h>      /* printf() */
#include <stdlib.h>     /* malloc() */
#include "stack/stack.h"

typedef struct minstack
{
    stack_t *stack;
    int min;
} minstack_t;



/* MinStack implementation */
/************************/

minstack_t *MinStackCreate(int size)
{
    minstack_t *min_stack = (minstack_t *)malloc(sizeof(minstack_t));
    if(NULL == min_stack)
    {
        return NULL;
    }

    min_stack->stack = StackCreate(size);
    if(NULL == min_stack->stack)
    {
        return NULL;
    }

    return min_stack;
}


void MinStackPush(minstack_t *stack, int data)
{
    if(StackIsEmpty(stack->stack))
    {
        stack->min = data;
    }

    else if(data < stack->min)
    {
        int real_min = data;
        data = data * 2 - stack->min;
        stack->min = real_min;
    }

    StackPush(stack->stack, data);
}

void MinStackPop(minstack_t *stack)
{
    int top = StackPeek(stack->stack);

    if(stack->min > top)
    {
        stack->min = stack->min * 2 - top;
    }
    StackPop(stack->stack);
}

int MinStackPeek(minstack_t *stack)
{
    int top = StackPeek(stack->stack);

    if(stack->min > top)
    {
        top = stack->min;
    }

    return top;
}

int StackMinGetMin(minstack_t *stack)
{
    return stack->min;
}



int main()
{
    minstack_t *min_stack = MinStackCreate(5);

    printf("empty? ");
    printf(1 == StackIsEmpty(min_stack->stack) ? "YES\n" : "NO\n");

    MinStackPush(min_stack, 13);
    printf("and now? ");
    printf(1 == StackIsEmpty(min_stack->stack) ? "YES\n" : "NO\n");

    MinStackPop(min_stack);
    printf("and now? ");
    printf(1 == StackIsEmpty(min_stack->stack) ? "YES\n" : "NO\n");

    MinStackPush(min_stack, 13);
    printf("min = %d\n", StackMinGetMin(min_stack));

    printf("and now? ");
    MinStackPush(min_stack, 6);
    printf("min = %d\n", StackMinGetMin(min_stack));

    printf("and after the pop? ");
    MinStackPop(min_stack);
    printf("min = %d\n", StackMinGetMin(min_stack));

    return 0;
}


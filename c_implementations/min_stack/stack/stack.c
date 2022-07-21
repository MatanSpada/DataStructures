#include <stdio.h>      /* printf() */
#include <stdlib.h>     /* malloc() */

typedef struct stack
{
    int top;
    int *stack_arr;
} stack_t;



/* Stack implementation */
/************************/

stack_t *StackCreate(size_t stack_size)
{
    stack_t *stack = (stack_t *)malloc(sizeof(stack_t));
    if(NULL == stack)
    {
        return NULL;
    }

    stack->stack_arr = malloc(sizeof(int) * stack_size);
    if(NULL == stack->stack_arr)
    {
        free(stack);
        stack = NULL;

        return NULL;
    }

    stack->top = -1; /*idx*/

    return stack;
}

void StackDestroy(stack_t *stack)
{
    free(stack->stack_arr);
    stack->stack_arr = NULL;

    free(stack);
    stack = NULL;
}

void StackPush(stack_t *stack, int data)
{
    stack->stack_arr[++stack->top] = data;
}

void StackPop(stack_t *stack)
{
    --stack->top;
}

int StackPeek(stack_t *stack)
{
    return stack->stack_arr[stack->top];
}

int StackSize(stack_t *stack)
{
    return stack->top + 1;
}

int StackIsEmpty(stack_t *stack)
{
    return stack->top == -1;
}


/*int main()
{
    stack_t *stack = StackCreate(5);

    printf("empty? ");
    printf(1 == StackIsEmpty(stack) ? "YES\n" : "NO\n");

    StackPush(stack, 13);
    printf("and now? ");
    printf(1 == StackIsEmpty(stack) ? "YES\n" : "NO\n");

    StackPop(stack);
    printf("and now? ");
    printf(1 == StackIsEmpty(stack) ? "YES\n" : "NO\n");


    return 0;
}*/




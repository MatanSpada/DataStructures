#include <assert.h>					/* assert() */					/*reviewed by lior*/
#include <string.h>					/* memcpy() */
#include <stdio.h>					/* printf() */
#include "../include/stack.h"		/* header file */


#define EMPTY ((size_t)-1)

struct stack
{
    void *stack_array;
    size_t size;
    size_t top_index;
    size_t element_size;
};
	



stack_t *CreateStack(size_t num_of_elements, size_t element_size)
{
	void *stack_array = NULL;
	stack_t *new_stack = NULL;

	new_stack = (stack_t*)malloc(sizeof(stack_t));		
	if (NULL == new_stack)
	{
		return NULL;
	}

	stack_array = malloc(num_of_elements * element_size);	
	if (NULL == stack_array)
	{
		free(new_stack);
		new_stack = NULL;
		
		return NULL;
	}

	new_stack->size = num_of_elements;
	new_stack->top_index = -1;
	new_stack->stack_array = stack_array;
	new_stack->element_size = element_size;
	return new_stack;
}



void StackPush(stack_t *stack, const void *element)
{
	assert(NULL != stack);
	assert(NULL != element);

	stack->top_index += 1;
	memcpy((char *)stack->stack_array + (stack->top_index*stack->element_size), element, stack->element_size);
}



void StackPop(stack_t *stack)
{
	assert(NULL != stack);

	--stack->top_index;
}



int StackIsEmpty(const stack_t *stack)
{
	assert(NULL != stack);

	return EMPTY == stack->top_index;
}



void StackDestroy(stack_t *stack)
{
	assert(NULL != stack);

	free(stack->stack_array);
	stack->stack_array = NULL;

	free(stack);
	stack = NULL;
}



void *StackPeek(const stack_t *stack)
{
	assert(NULL != stack);

	return (char *)stack->stack_array + (stack->top_index * stack->element_size);
}



size_t StackCapacity(const stack_t *stack)
{
	assert(NULL != stack);

	return stack->size;
}



size_t StackSize(const stack_t *stack)
{
	assert(NULL != stack);

	return stack->top_index + 1;
}







#ifndef __STACK_H__
#define __STACK_H__

#include <stdlib.h>     /* malloc() */

typedef struct stack stack_t;


/* DESCRIPTION: 
 * create a stack based on given parameters
 * allocate memory according to params
 *
 * at the end of use, call for StackDestroy() to free memory
 *
 * PARAMS: 
 * stack_size - total number of elements requested by the user
 *  
 * RETURN:
 * stack_t *ptr to the created stack,
 * NULL in case of failure.
 */
stack_t *StackCreate(size_t stack_size);


/* DESCRIPTION: 
 * perform free for the allocated memory of the stack
 * must be called at the end of the stack usage 

 * PARAMS: 
 * stack_t *ptr - pointer to the stack to be destroyed.
 *
 * 
 * RETURN:
 * none.
 */
void StackDestroy(stack_t *stack);


/* DESCRIPTION: 
 * push element on to top of the stack.
 * the user is responsible for knowing the stack capacity. If the size is exceeded the function behaviour is undefined.

 * PARAMS: 
 * stack_t *stack - pointer to the stack;
 * *data - data to push onto the stack.
 *
 * RETURN:
 * no return value, 
 */
void StackPush(stack_t *stack, int data);


/* DESCRIPTION: 
 * pops out the top element of the stack.
 * popping an empty stack causes undefined behaviour. 
 
 * PARAMS: 
 * stack_t *stack - pointer to the stack
 * 
 *
 * RETURN:
 * no return value,
 */
void StackPop(stack_t *stack);


/* DESCRIPTION: 
 * peek to the top element of the stack, 
 * peeking an empty stack causes undefined behaviour.
 *
 *
 * PARAMS: 
 * stack_t *ptr - pointer to the stack
 * 
 *
 * RETURN:
 * Top element integer.
 */
int StackPeek(stack_t *stack);


/* DESCRIPTION: 
 * checks how many elements are occupied.
 *
 * PARAMS: 
 * const stack_t *sptr - pointer to the stack 
 * 
 * RETURN:
 * return number of occupied elements of the stack.
 */
int StackSize(stack_t *stack);


/* DESCRIPTION: 
 * checks if stack_t is empty
 * 
 * PARAMS: 
 * stack_t *ptr - pointer to the stack
 * 
 * RETURN:
 * return 1 if empty, 0 if otherwise.
 */
int StackIsEmpty(stack_t *stack);



#endif /* __STACK_H__ */
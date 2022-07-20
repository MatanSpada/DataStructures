#include <stdio.h>  	/* printf */
#include <assert.h> 	/* assert */

#include "../include/stack.h"

void test1(void)
{
	int num = 13;
	void *peek_call = NULL;

	stack_t *st = CreateStack(10, 4);

	assert(0 == StackSize(st));
	assert(1 == StackIsEmpty(st));

	StackPush(st, &num);

	assert(0 == StackIsEmpty(st));

	peek_call = StackPeek(st);

	assert(num == *(int *)peek_call);

	StackDestroy(st);

	printf("test 1: SUCCESS! \n");
}

void test2(void)
{
	int num1 = 10;
	int num2 = 55;
	int num3 = 561856;
	void *peek_call = NULL;

	stack_t *st = CreateStack(35, 4);
	
	StackPush(st, &num1);
	StackPush(st, &num2);
	StackPush(st, &num3);

	assert(3 == StackSize(st));
	
	peek_call = StackPeek(st);
	assert(num3 == *(int *)peek_call);

	StackPop(st);

	assert(2 == StackSize(st));

	peek_call = StackPeek(st);
	assert(num2 == *(int *)peek_call);

	StackPop(st);

	assert(1 == StackSize(st));	
	assert(0 == StackIsEmpty(st));

	peek_call = StackPeek(st);
	assert(num1 == *(int *)peek_call);

	StackPop(st);
	assert(0 == StackSize(st));	
	assert(1 == StackIsEmpty(st));

	StackDestroy(st);

	printf("test 2: SUCCESS! \n");	

}

int main()
{
	test1();
	test2();
	return 0;
}



#define __TESTS_NUM_1__

#include "../include/dynamic_vector.h"
#include "../include/dynamic_vector_tests.h"

#define	COND_MULTI(var, cond, value) (var) = ((cond) ? (value) : (var));

int main()
{
	size_t i = 0;

	for(; i < TESTS_NUM; ++i)
	{
		(*tests_arr[i])();
	}

	return 0;
}


void test1()
{
	short push_num = 1;
	short *peek_num = NULL;
	size_t cur_size = 0;
	size_t i = 0;
	size_t elements_counter = 0;
	size_t capacity_counter = 10;
	vector_t *test_vector = VectorCreate(2, capacity_counter);

	PRINT_TEST(elements_counter, VectorSize, (test_vector));
	PRINT_TEST(capacity_counter, VectorCapacity, (test_vector));

	VectorReserve(test_vector, 1);
	capacity_counter = 1;

	PRINT_TEST(elements_counter, VectorSize, (test_vector));
	PRINT_TEST(capacity_counter, VectorCapacity, (test_vector));

	for(; push_num <= 3; ++push_num)
	{
		VectorPushBack(test_vector, &push_num);	
		COND_MULTI(capacity_counter, capacity_counter == elements_counter, 2 * capacity_counter);
		++elements_counter;
	}

	PRINT_TEST(elements_counter, VectorSize, (test_vector));
	PRINT_TEST(capacity_counter, VectorCapacity, (test_vector));

	cur_size = VectorSize(test_vector);

	for(i = 0; i < cur_size; ++i)
	{
		peek_num = (short *)VectorGetAccessToElement(test_vector, i);
		PRINT_BOOL(*peek_num, (short)i + 1);
	}

	peek_num = (short *)VectorGetAccessToElement(test_vector, 1);
	*peek_num = 8;
	peek_num = (short *)VectorGetAccessToElement(test_vector, 1);
	PRINT_BOOL(*peek_num, 8);

	push_num = 5;

	for(i = 0; i < 8; ++i)
	{
		VectorPushBack(test_vector, &push_num);
		COND_MULTI(capacity_counter, capacity_counter == elements_counter, 2 * capacity_counter);
		++elements_counter;
	}
	
	PRINT_TEST(elements_counter, VectorSize, (test_vector));
	PRINT_TEST(capacity_counter, VectorCapacity, (test_vector));

	for(i = 0; i < 8; ++i)
	{
		VectorPopBack(test_vector);
		--elements_counter;
		COND_MULTI(capacity_counter, capacity_counter >= 4 * elements_counter, 2 * elements_counter);
	}
	
	PRINT_TEST(elements_counter, VectorSize, (test_vector));
	PRINT_TEST(capacity_counter, VectorCapacity, (test_vector));

	peek_num = (short *)VectorGetAccessToElement(test_vector, elements_counter - 1);
	
	PRINT_BOOL(3, *peek_num);
	
	VectorDestroy(test_vector);
}

/*
void test2()
{
	void test2()
{
	size_t arr1[] = {
				1 , 0,
				2, 0,
				3 , 0,
				4 , 0 };

	size_t arr2[] = {
				5 , 0,
				6, 0,
				7 , 0,
				8 , 0 };

	size_t words_in_element = 2;
	size_t size = sizeof(arr1) / sizeof(arr[0]);
	size_t i = 0;
	void *peek_ptr = NULL;
	stack_t *test_vector = VectorCreate(words_in_element * sizeof(size_t), 2);
	
	PRINT_TEST(2, VectorCapacity, (test_vector));
	PRINT_TEST(0, VectorSize, (test_vector));
		
	for(i = 0; i < size; i += words_in_element)
	{
		VectorPushBack(test_vector, arr + i);
	}
	
	PRINT_TEST((size_t)4, VectorSize, (test_vector));
	
	for (i = 0; i < ; i += words_in_element)
	{
		peek_ptr = VectorGetAccessToElement(test_vector, i / 2);
		PRINT_TEST(0, memcmp, (arr1 + i, *peek_ptr, words_in_element * sizeof(size_t)));

		memcpy(peek_ptr, arr2 + i, 2 * sizeof(size_t));
	}

	for (i = 0; i < ; i += words_in_element)
	{
		peek_ptr = VectorGetAccessToElement(test_vector, i / 2);
		PRINT_TEST(0, memcmp, (arr2 + i, *peek_ptr, words_in_element * sizeof(size_t)));	
	}

	for (i = ; i < ; i += words_in_element)
	{
		peek_ptr = VectorGetAccessToElement(test_vector, i / 2);
		PRINT_TEST(0, memcmp, (arr2 + i, *peek_ptr, words_in_element * sizeof(size_t)));	
	}
	
	StackDestroy(test_vector);
}







*/

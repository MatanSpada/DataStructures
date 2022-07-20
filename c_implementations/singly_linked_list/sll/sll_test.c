#define __TESTS_NUM_6__

#include <stdlib.h>
#include "../include/sll_test.h"
#include "../include/sll.h"

#define NOT_ARRAY_VALUE (2000)

static size_t arr[] = {0, 1, 2, 3, 4};
static size_t arr_size = sizeof(arr) / sizeof(arr[0]);

int print_func(void *data, void *param);
int comp_func(const void *data, void *param);
int print_all(void *data, void *param);

void print_list(slist_t *list);

int main()
{
	size_t i = 0;

	for(i = 0; i < TESTS_NUM; ++i)
	{
		(*tests_arr[i])();
		printf("\n\n");
	}

	return 0;
}


void test1()
{
	slist_t *test_list = SListCreate();
	printf("Test 1 : Create, IsEmpty & Destroy :\n");
	
	PRINT_TEST(1, SListIsEmpty, (test_list));
	
	SListDestroy(test_list);
}

void test2()
{
	slist_t *test_list = SListCreate();
	size_t num = 8;

	printf("Test 2 : Create, InsertBefore, GetData, IsEmpty & Destroy :\n");

	SListInsertBefore(SListEnd(test_list), (void *)(long)num);
	
	PRINT_TEST((void *)num, SListGetData, (SListBegin(test_list)));
	PRINT_TEST(0, SListIsEmpty, (test_list));
	
	SListDestroy(test_list);
}

void test3()
{
	slist_t *test_list = SListCreate();
	size_t num = 8;
	size_t cur_size = 0;
	size_t iter_num = 6;

	printf("Test 3 : InsertBefore, GetData, Conut :\n");

	PRINT_TEST(1, SListIsEqual, (SListBegin(test_list), SListEnd(test_list)));
	PRINT_TEST(cur_size, SListCount, (test_list));

	for(; iter_num > 0; --iter_num)
	{
		SListInsertBefore(SListBegin(test_list), (void *)num);
		++cur_size;

		PRINT_TEST(cur_size, SListCount, (test_list));
		PRINT_TEST((void *)num, SListGetData, (SListBegin(test_list)));
		PRINT_TEST(0, SListIsEqual, (SListBegin(test_list), SListEnd(test_list)));
		
		++num;
	}
	
	SListDestroy(test_list);
}


void test4()
{
	slist_t *test_list = SListCreate();
	size_t num = 8;
	size_t cur_size = 0;
	size_t iter_num = 6;
	slist_iter_t test_iter = SListBegin(test_list);

	printf("Test 4 : InsertBefore, InsertAfter, GetData, Conut :\n");

	SListInsertBefore(SListBegin(test_list), (void *)num);
	++cur_size;
	PRINT_TEST(cur_size, SListCount, (test_list));

	for(; iter_num > 0; --iter_num)
	{
		test_iter = SListInsertAfter(test_iter, (void *)num);
		++cur_size;

		PRINT_TEST(cur_size, SListCount, (test_list));
		PRINT_TEST((void *)num, SListGetData, (test_iter));
		
		++num;
	}
	
	SListDestroy(test_list);
}
/*
void test5()
{
	slist_t *test_list = SListCreate();
	size_t num = 8;
	size_t cur_size = 0;
	size_t iter_num = 6;
	slist_iter_t test_iter = SListBegin(test_list);


	SListInsertBefore(SListBegin(test_list), (void *)num);
	++cur_size;
	PRINT_TEST(cur_size, SListCount, (test_list));

	for(; iter_num > 0; --iter_num)
	{
		test_iter = SListInsertAfter(test_iter, (void *)num);
		++cur_size;

		PRINT_TEST(cur_size, SListCount, (test_list));
		PRINT_TEST(num, SListGetData, test_iter);
		
		++num;
	}
	
	SListDestroy(test_list);
}


*/

void test5()
{
	size_t num = 8;
	size_t cur_size = 0;
	size_t arr_index = 0;
	slist_t *test_list = SListCreate();
	slist_iter_t test_iter = SListEnd(test_list);
	slist_iter_t free_iterator = test_iter;

	printf("Test 5 : Integration Test :\n");

	PRINT_TEST(cur_size, SListCount, (test_list));
	PRINT_TEST(1, SListIsEmpty, (test_list));

	test_iter = SListInsertBefore(SListEnd(test_list), (void *)(long)num);
	++cur_size;

	PRINT_TEST(num, (size_t) SListGetData, (SListBegin(test_list)));

	free_iterator = SListRemove(SListBegin(test_list));
	free(free_iterator);
	--cur_size;	

	PRINT_TEST(cur_size, SListCount, (test_list));

	for(arr_index = 0; arr_index < arr_size; ++arr_index)
	{
		SListInsertBefore(SListEnd(test_list), (void *)(long)arr[arr_index]);
		++cur_size;

		PRINT_TEST(cur_size, SListCount, (test_list));
	}

	SListForEach(SListBegin(test_list), SListEnd(test_list), &print_func, (void *)arr_size);

	test_iter = SListBegin(test_list);
	arr_index = 0;

	test_iter = SListNext(test_iter);
	++arr_index;
	
	test_iter = SListNext(test_iter);
	++arr_index;

	SListSetData(test_iter, (void *)(long)num);
	arr[arr_index] = num;

	PRINT_TEST((void *)num, SListGetData, (test_iter));

	SListForEach(SListBegin(test_list), SListEnd(test_list), &print_func, (void *)arr_size);

	PRINT_TEST(test_iter, SListFind, (SListBegin(test_list), SListEnd(test_list), &comp_func, (void *)(long)(arr[arr_index])));
	PRINT_TEST(SListEnd(test_list), SListFind, (SListBegin(test_list), SListEnd(test_list), &comp_func, (void *)(long)NOT_ARRAY_VALUE));

	free_iterator = SListRemove(test_iter);
	free(free_iterator);
	--cur_size;

	SListForEach(SListBegin(test_list), SListEnd(test_list), &print_func, (void *)arr_index);

	PRINT_TEST(cur_size, SListCount, (test_list));

	SListDestroy(test_list);
}

void test6()
{
    slist_t *src = SListCreate();
    slist_t *dest = SListCreate();
    slist_t *empty_src = SListCreate();
    long test_arr[] = {0, 1, 2, 3, 4, 5};
    size_t test_arr_size = sizeof(test_arr) / sizeof(test_arr[0]);
    size_t cur_src_size = 0;
    size_t cur_dest_size = 0;
    slist_iter_t test_iter = NULL;
    size_t index = 0;


    printf("Test 6 : Append :\n");

    for(index = 0; 2 * index < test_arr_size; ++index)
    {    
        SListInsertBefore(SListEnd(dest), (void *)arr[index]);
        SListInsertBefore(SListEnd(src), (void *)arr[index + test_arr_size / 2]);
		++cur_src_size;
    	++cur_dest_size;
    
    }
    
   	PRINT_TEST(cur_dest_size, SListCount, (src));
   	PRINT_TEST(cur_dest_size, SListCount, (dest));

   	SListAppend(dest, src);
   	cur_dest_size += cur_src_size;
   	cur_src_size = 0;

	PRINT_TEST(cur_dest_size, SListCount, (dest));  
	PRINT_TEST(cur_src_size, SListCount, (src));  	
	PRINT_TEST(1, SListIsEmpty, (src));

   	test_iter = SListBegin(dest);
   	for(index = 0; index < cur_dest_size; ++index)
   	{
   		PRINT_TEST((void *)arr[index], SListGetData, (test_iter));
   		test_iter = SListNext(test_iter);
   	}


   	SListAppend(src, dest);

   	cur_src_size += cur_dest_size;
   	cur_dest_size = 0;

	PRINT_TEST(cur_src_size, SListCount, (src));   	
	PRINT_TEST(1, SListIsEmpty, (dest));

   	test_iter = SListBegin(src);
   	for(index = 0; index < cur_src_size; ++index)
   	{
   		PRINT_TEST((void *)arr[index], SListGetData, (test_iter));
   		test_iter = SListNext(test_iter);
   	}

   	SListAppend(dest, empty_src);

	PRINT_TEST(1, SListIsEmpty, (dest));
	PRINT_TEST(1, SListIsEmpty, (empty_src));

   	SListDestroy(dest);
   	SListDestroy(src);
   	SListDestroy(empty_src);
}



int print_func(void *data, void *skip_index)
{
	static size_t index = 0;

	if((size_t)skip_index == index)
	{
		index = (index + 1) % arr_size;
	}

	PRINT_BOOL(arr[index], (size_t)data);

	index = (index + 1) % arr_size;

	return 0;
}


int comp_func(const void *data, void *param)
{
	return data == param;
}


#define __TESTS_NUM_8__

#include <stdlib.h>     /* qsort(), rand()  */
#include <time.h>       /* time()           */
#include "../include/heap.h"       /* DS to be tested  */
#include "../include/utils/tests.h"      /* tests macro*/


static int LongComp(const void *, const void *);
static int QsortComp(const void *, const void *);
static void ShuffleArr(long *arr, size_t arr_size);
static void RandomArr(long *arr, size_t arr_size);
static int IsEqualLong(const void *element, const void *search);

int main()
{
    PrintAllTests();
    /* PrintSingleTest(8); */

    return 0;
}

void test1()
{
    heap_t *test_heap = HeapCreate(&LongComp);

    printf("Create & Destroy:\n");

    HeapDestroy(test_heap);
}

void test2()
{
    heap_t *test_heap = HeapCreate(&LongComp);

    printf("IsEmpty & Size:\n");

    PRINT_TEST(0, HeapSize, (test_heap));
    PRINT_TEST(TRUE, HeapIsEmpty, (test_heap));

    HeapDestroy(test_heap);
}

void test3()
{
    heap_t *test_heap = HeapCreate(&LongComp);

    printf("Push & IsEmpty & Size:\n");

    PRINT_TEST(SUCCESS, HeapPush, (test_heap, (void *)1L));

    PRINT_TEST(1, HeapSize, (test_heap));
    PRINT_TEST(FALSE, HeapIsEmpty, (test_heap));
    
    HeapDestroy(test_heap);
}

void test4()
{
    heap_t *test_heap = HeapCreate(&LongComp);
    static long insert_arr[] =  {7, 9, 5, 8, 6, 2, 3, 4, 1};
    static long cur_top[] =     {7, 7, 5, 5, 5, 2, 2, 2, 1};
    size_t arr_size = ARR_SIZE(insert_arr);
    size_t cur_size = 0;
    size_t i = 0;

    printf("Peek & Push:\n");

    for(i = 0; i < arr_size; ++i)
    {
        HeapPush(test_heap, (void *)insert_arr[i]);
        ++cur_size;
        PRINT_TEST_LINE(cur_size, HeapSize, (test_heap), (i));
        PRINT_TEST_LINE((void *)cur_top[i], HeapPeek, (test_heap), (i));
    }

    HeapDestroy(test_heap);
}

void test5()
{
    heap_t *test_heap = HeapCreate(&LongComp);

    printf("Pop:\n");
    HeapPush(test_heap, (void *)1L);

    HeapPop(test_heap);

    PRINT_TEST(0, HeapSize, (test_heap));
    PRINT_TEST(TRUE, HeapIsEmpty, (test_heap));
    
    HeapDestroy(test_heap);       
 
}

void test6()
{
    heap_t *test_heap = HeapCreate(&LongComp);
    static long insert_arr[] =  {7, 9, 5 , 8, 6, 2, 3, 4, 1}; 
    size_t arr_size = ARR_SIZE(insert_arr);
    size_t cur_size = 0;
    size_t i = 0;

    printf("Pop & Push:\n");

    INSERT_ARR(arr_size, insert_arr, HeapPush, test_heap, cur_size);

    qsort(insert_arr, arr_size, sizeof(*insert_arr), &QsortComp);

    for(i = 0; i < arr_size; ++i)
    {
        PRINT_TEST_LINE((void *)insert_arr[i], HeapPeek, (test_heap), (i));
        HeapPop(test_heap);
        --cur_size;
        PRINT_TEST_LINE(cur_size, HeapSize, (test_heap), (i));
    }

    PRINT_TEST(TRUE, HeapIsEmpty, (test_heap));

    HeapDestroy(test_heap);
}

void test7()
{
    heap_t *test_heap = HeapCreate(&LongComp);

    printf("Remove :\n");

    PRINT_TEST(NULL, HeapRemove, (test_heap, &IsEqualLong, (void *)1L));

    PRINT_TEST(SUCCESS, HeapPush, (test_heap, (void *)1L));

    PRINT_TEST((void *)1L, HeapRemove, (test_heap, &IsEqualLong, (void *)1L));

    PRINT_TEST(0, HeapSize, (test_heap));
    PRINT_TEST(TRUE, HeapIsEmpty, (test_heap));

    HeapDestroy(test_heap);
} 

#define TESTS8_ARR_SIZE (5000)
#define NOT_INCLUDED (5412)
void test8()
{
    heap_t *test_heap = HeapCreate(&LongComp);
    static long insert_arr[TESTS8_ARR_SIZE] = {0};
    size_t arr_size = TESTS8_ARR_SIZE;
    size_t cur_size = 0;
    size_t i = 0;
    size_t first_remove = arr_size >> 2;

    printf("Remove :\n");

    RandomArr(insert_arr, arr_size);

    INSERT_ARR(arr_size, insert_arr, HeapPush, test_heap, cur_size);

    PRINT_TEST(NULL, HeapRemove, (test_heap, &IsEqualLong, (void *)NOT_INCLUDED));

    ShuffleArr(insert_arr, arr_size);

    for(i = arr_size; i > arr_size - first_remove ; --i)
    {
        PRINT_TEST_LINE((void *)insert_arr[i - 1], HeapRemove, (test_heap, &IsEqualLong, (void *)insert_arr[i - 1]), (i));
        --cur_size;
        PRINT_TEST_LINE(cur_size, HeapSize, (test_heap), (i));
    }
    arr_size = i;
    qsort(insert_arr, arr_size, sizeof(*insert_arr), &QsortComp);

    PRINT_TEST(FALSE, HeapIsEmpty, (test_heap))

    PRINT_TEST((void *)insert_arr[0], HeapPeek, (test_heap));

    for(i = 0; i < arr_size ; ++i)
    {
        PRINT_TEST_LINE((void *)insert_arr[i], HeapPeek, (test_heap), (i));
        HeapPop(test_heap);
        --cur_size;
        PRINT_TEST_LINE(cur_size, HeapSize, (test_heap), (i));
    }

    HeapDestroy(test_heap);
}

static int LongComp(const void *num1, const void *num2)
{
    return (long)num1 - (long)num2;
}

static int QsortComp(const void *num1, const void *num2)
{
    return *(long *)num1 - *(long *)num2;
}

static void ShuffleArr(long *arr, size_t arr_size)
{
    size_t i = arr_size;

    srand(time(NULL));

    for(i = arr_size; i > 1; --i)
    {
        size_t rand_index = rand() % i;
        GEN_SWAP(long, arr[i - 1], arr[rand_index]);
    }
}

static long NotInclude(int num)
{
    return num + (NOT_INCLUDED == num);
}

static void RandomArr(long *arr, size_t arr_size)
{
    size_t i = 0;

    srand(time(NULL));

    for(i = 0; i < arr_size; ++i)
    {
        arr[i] = NotInclude(rand() + 1);
    }
}

static int IsEqualLong(const void *element, const void *search)
{
    return element == search;
}

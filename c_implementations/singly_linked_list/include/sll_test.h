

#ifndef __TEST_H__
#define __TEST_H__

#include <string.h>				/* strcmp() */
#include <stdio.h>				/* printf() */

/* Font colors */

#define BLACK printf("\033[0;30m");

#define BOLD_BLACK printf("\033[1;30m");

#define RED printf("\033[0;31m");

#define BOLD_RED printf("\033[1;31m");

#define GREEN printf("\033[0;32m");

#define BOLD_GREEN printf("\033[1;32m");

#define YELLOW printf("\033[0;33m");

#define BOLD_YELLOW printf("\033[1;33m");

#define BLUE printf("\033[0;34m");

#define BOLD_BLUE printf("\033[1;34m");

#define PURPLE printf("\033[0;35m");

#define BOLD_PURPLE printf("\033[1;35m");

#define CYAN printf("\033[0;36m");

#define BOLD_CYAN printf("\033[1;36m");

#define WHITE printf("\033[0;37m");

#define BOLD_WHITE printf("\033[1;37m");


/* args should be inside () */

#define CALL_FUNC(func, args) (func args)

#define TEST_FUNC(expect, func, args) ((expect) == CALL_FUNC(func, args))

#define TEST_STRING_FUNC(expect, func, args) (0 == strcmp(expect, CALL_FUNC(func, args)))

#define PRINT_BOOL(expect, args) {\
						if((expect) == (args))\
						{\
							GREEN\
							printf("PASS!. line : %u\n", __LINE__);\
						}\
						else\
						{\
							RED\
							printf("FAIL!. line : %u\n", __LINE__);\
						}\
						WHITE\
					}


#define PRINT_TEST(expect, func, args) {\
						if(TEST_FUNC(expect, func, args))\
						{\
							GREEN\
							printf("PASS!. line : %u\n", __LINE__);\
						}\
						else\
						{\
							RED\
							printf("FAIL!. line : %u\n", __LINE__);\
						}\
						WHITE\
					}

#define PRINT_TEST_STRING(expect, result) {\
						if(0 == strcmp(expect, result))\
						{\
							GREEN\
							printf("PASS!. line : %u\n", __LINE__);\
						}\
						else\
						{\
							RED\
							printf("FAIL!. line : %u\n", __LINE__);\
						}\
						WHITE\
					}

					
#define PRINT_TEST_STRING_FUNC(expect, func, args) {\
						if(TEST_STRING_FUNC(expect, func, args))\
						{\
							GREEN\
							printf("PASS!. line : %u\n", __LINE__);\
						}\
						else\
						{\
							RED\
							printf("FAIL!. line : %u\n", __LINE__);\
						}\
						WHITE\
					}

/* Tests function pointers arr */

typedef void (*tests_func_t)(void);

/* tests_arr - array of test function 	*/
/* TESTS_NUM - the size of test array 	*/

#ifdef __TESTS_NUM_1__

void test1();

#define TESTS_NUM 1

const tests_func_t tests_arr[] = {
				&test1 };




#endif

#ifdef __TESTS_NUM_2__

void test1();
void test2();


#define TESTS_NUM 2

const tests_func_t tests_arr[] = {
				&test1,
				&test2 };




#endif

#ifdef __TESTS_NUM_3__

void test1();
void test2();
void test3();

#define TESTS_NUM 3

const tests_func_t tests_arr[] = {
				&test1,
				&test2,
				&test3 };





#endif

#ifdef __TESTS_NUM_4__

void test1();
void test2();
void test3();
void test4();

#define TESTS_NUM 4

const tests_func_t tests_arr[] = {
				&test1,
				&test2,
				&test3,
				&test4 };




#endif

#ifdef __TESTS_NUM_5__

void test1();
void test2();
void test3();
void test4();
void test5();

#define TESTS_NUM 5

const tests_func_t tests_arr[] = {
				&test1,
				&test2,
				&test3,
				&test4,
				&test5 };




#endif

#ifdef __TESTS_NUM_6__

void test1();
void test2();
void test3();
void test4();
void test5();
void test6();


#define TESTS_NUM 6

const tests_func_t tests_arr[] = {
				&test1,
				&test2,
				&test3,
				&test4,
				&test5,
				&test6 };



#endif

#ifdef __TESTS_NUM_7__

void test1();
void test2();
void test3();
void test4();
void test5();
void test6();
void test7();

#define TESTS_NUM 7

const tests_func_t tests_arr[] = {
				&test1,
				&test2,
				&test3,
				&test4,
				&test5,
				&test6,
				&test7 };




#endif

#ifdef __TESTS_NUM_8__

void test1();
void test2();
void test3();
void test4();
void test5();
void test6();
void test7();
void test8();

#define TESTS_NUM 8

const tests_func_t tests_arr[] = {
				&test1,
				&test2,
				&test3,
				&test4,
				&test5,
				&test6,
				&test7,
				&test8 };




#endif

#ifdef __TESTS_NUM_9__

void test1();
void test2();
void test3();
void test4();
void test5();
void test6();
void test7();
void test8();
void test9();

#define TESTS_NUM 9

const tests_func_t tests_arr[] = {
				&test1,
				&test2,
				&test3,
				&test4,
				&test5,
				&test6,
				&test7,
				&test8,
				&test9 };




#endif


#ifdef __TESTS_NUM_10__

void test1();
void test2();
void test3();
void test4();
void test5();
void test6();
void test7();
void test8();
void test9();
void test10();

#define TESTS_NUM 10

const tests_func_t tests_arr[] = {
				&test1,
				&test2,
				&test3,
				&test4,
				&test5,
				&test6,
				&test7,
				&test8,
				&test9,
				&test10 };




#endif

		
#ifdef __TESTS_NUM_11__

void test1();
void test2();
void test3();
void test4();
void test5();
void test6();
void test7();
void test8();
void test9();
void test10();
void test11();

#define TESTS_NUM 11

const tests_func_t tests_arr[] = {
				&test1,
				&test2,
				&test3,
				&test4,
				&test5,
				&test6,
				&test7,
				&test8,
				&test9,
				&test10,
				&test11 };




#endif

#ifdef __TESTS_NUM_12__

void test1();
void test2();
void test3();
void test4();
void test5();
void test6();
void test7();
void test8();
void test9();
void test10();
void test11();
void test12();

#define TESTS_NUM 12

const tests_func_t tests_arr[] = {
				&test1,
				&test2,
				&test3,
				&test4,
				&test5,
				&test6,
				&test7,
				&test8,
				&test9,
				&test10,
				&test11,
				&test12 };



#endif

#ifdef __TESTS_NUM_13__

void test1();
void test2();
void test3();
void test4();
void test5();
void test6();
void test7();
void test8();
void test9();
void test10();
void test11();
void test12();
void test13();

#define TESTS_NUM 13

const tests_func_t tests_arr[] = {
				&test1,
				&test2,
				&test3,
				&test4,
				&test5,
				&test6,
				&test7,
				&test8,
				&test9,
				&test10,
				&test11,
				&test12,
				&test13 };



#endif



#ifdef __TESTS_NUM_14__

void test1();
void test2();
void test3();
void test4();
void test5();
void test6();
void test7();
void test8();
void test9();
void test10();
void test11();
void test12();
void test13();
void test14();

#define TESTS_NUM 14

const tests_func_t tests_arr[] = {
				&test1,
				&test2,
				&test3,
				&test4,
				&test5,
				&test6,
				&test7,
				&test8,
				&test9,
				&test10,
				&test11,
				&test12,
				&test13,
				&test14 };



#endif
		

		
#endif /*__GUY_TEST_H__*/

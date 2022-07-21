

#ifndef __TEST_ARR_H__
#define __TEST_ARR_H__


/* Tests function pointers arr */

typedef void (*tests_func_t)(void);

/* tests_arr - array of test function 	*/
/* TESTS_NUM - the size of test array 	*/

#ifdef __TESTS_NUM_1__

void test1();

#define TESTS_NUM 1

const tests_func_t tests_arr[] = {
				&test1 };




#endif /* __TESTS_NUM_1__ */

#ifdef __TESTS_NUM_2__

void test1();
void test2();


#define TESTS_NUM 2

const tests_func_t tests_arr[] = {
				&test1,
				&test2 };




#endif /* __TESTS_NUM_2__ */

#ifdef __TESTS_NUM_3__

void test1();
void test2();
void test3();

#define TESTS_NUM 3

const tests_func_t tests_arr[] = {
				&test1,
				&test2,
				&test3 };





#endif	/* __TESTS_NUM_3__ */

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




#endif /* __TESTS_NUM_4__ */

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




#endif	/* __TESTS_NUM_5__ */

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



#endif	/* __TESTS_NUM_6__ */

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




#endif	/* __TESTS_NUM_7__ */

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




#endif	/* __TESTS_NUM_8__ */

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




#endif	/* __TESTS_NUM_9__ */


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




#endif	/* __TESTS_NUM_10__ */

		
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




#endif	/* __TESTS_NUM_11__ */

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



#endif	/* __TESTS_NUM_12__ */

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



#endif	/* __TESTS_NUM_13__ */



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

#endif	/* __TESTS_NUM_14__ */


#ifdef __TESTS_NUM_15__

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
void test15();

#define TESTS_NUM 15

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
				&test14,
				&test15, };


#endif	/* __TESTS_NUM_15__ */
		

#endif /*__TEST_ARR_H__	*/

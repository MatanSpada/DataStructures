

#ifndef __GUY_TEST_H__
#define __GUY_TEST_H__

#include <string.h>				/* strcmp() */
#include <stdio.h>				/* printf() */
#include "colors.h"				/* COLORS' macro	*/
#include "tests_arr.h"			/* array of tests function	*/
#include "utils.h"			/* default utilities	*/

/* args should be inside () */

#define CALL_FUNC(func, args) (func args)

#define TEST_FUNC(expect, func, args) ((expect) == CALL_FUNC(func, args))

#define TEST_STRING_FUNC(expect, func, args) (0 == strcmp(expect, CALL_FUNC(func, args)))

							/*GREEN\
							printf("PASS!. line : %u\n", __LINE__);\*/
#ifdef TESTS_NUM
	
	#define FAIL_TEST (cur_test_pass = FALSE)

#else /* !TESTS_NUM	*/

	#define FAIL_TEST ()

#endif

#define PRINT_NOT_EQUAL_LINE(expect, args, line) {\
						if((expect) == (args))\
						{\
							RED\
							if (__LINE__ != (line))\
							{\
								printf("FAIL!. line : %u:%u\n", (unsigned int)(line), __LINE__);\
							}\
							else\
							{\
								printf("FAIL!. line : %u\n", (unsigned int)(line));\
							}\
							WHITE\
							FAIL_TEST;\
						}\
					}

#define PRINT_BOOL_LINE(expect, args, line) {\
						if((expect) != (args))\
						{\
							RED\
							if (__LINE__ != (line))\
							{\
								printf("FAIL!. line : %u:%u\n", (unsigned int)(line), __LINE__);\
							}\
							else\
							{\
								printf("FAIL!. line : %u\n", (unsigned int)(line));\
							}\
							WHITE\
							FAIL_TEST;\
						}\
					}

#define PRINT_LESS_THAN_LINE(epsilon, value, line) {\
						if((epsilon) < (value))\
						{\
							RED\
							if (__LINE__ != (line))\
							{\
								printf("FAIL!. line : %u:%u\n", (unsigned int)(line), __LINE__);\
							}\
							else\
							{\
								printf("FAIL!. line : %u\n", (unsigned int)(line));\
							}\
							WHITE\
							FAIL_TEST;\
						}\
					}

#define PRINT_BOOL(expect, args) PRINT_BOOL_LINE(expect, args, __LINE__)

#define PRINT_LESS_THAN(epsilon, value) PRINT_LESS_THAN_LINE(epsilon, value, __LINE__)

#define PRINT_NOT_EQUAL(expect, args) PRINT_NOT_EQUAL_LINE(expect, args, __LINE__)

#define PRINT_TEST_LINE(expect, func, args, line) PRINT_BOOL_LINE(expect, func args, line)

#define PRINT_TEST(expect, func, args) PRINT_BOOL(expect, func args)

#define PRINT_TEST_STRING(expect, result) PRINT_TEST(0, strcmp, (expect, result))

#define PRINT_TEST_ARRAY_EQUALS_LINE(expect_arr, arr, size, line) {\
						size_t index = 0;\
						for(; index < (size) && (expect_arr)[index] == (arr)[index]; ++index);\
						PRINT_BOOL_LINE(index, (size), line);\
				}

#define PRINT_TEST_ARRAY_EQUALS(expect_arr, arr, size) PRINT_TEST_ARRAY_EQUALS_LINE(expect_arr, arr, size, __LINE__)

#define PRINT_TEST_ARRAY_IS_SORTED_LINE(arr, size, line) {\
						size_t index = 0;\
						for(; index < (size) - 1 && (arr)[index] <= (arr)[index + 1]; ++index);\
						PRINT_BOOL_LINE(index, (size) - 1, line);\
				}

#define PRINT_TEST_ARRAY_IS_SORTED(arr, size) PRINT_TEST_ARRAY_IS_SORTED_LINE(arr, size, __LINE__)



					
#define PRINT_TEST_STRING_FUNC(expect, func, args) {\
						if(TEST_STRING_FUNC(expect, func, args))\
						{\
						}\
						else\
						{\
							RED\
							printf("FAIL!. line : %u\n", __LINE__);\
							WHITE\
							cur_test_pass = FALSE;\
							all_tests_pass = FALSE;\
							all_tests_pass = 0;\
						}\
					}

#define INSERT(how_many, value, insert_func, struct_var, cur_size) {\
						size_t index = 0;\
						for(; index < (how_many); ++index)\
						{\
							insert_func((struct_var), (value));\
							++(cur_size);\
						}\
					}

#define INSERT_ARR(how_many, array, insert_func, struct_var, cur_size) {\
						size_t index = 0;\
						size_t end_index =  (how_many);\
						for(; index < end_index; ++index)\
						{\
							insert_func((struct_var), (void *)((array)[index]));\
							++(cur_size);\
						}\
					}

#define INSERT_ARR_BY_REF(how_many, array, insert_func, struct_var, cur_size) {\
						size_t index = 0;\
						size_t end_index =  (how_many);\
						for(; index < end_index; ++index)\
						{\
							insert_func((struct_var), (void *)((array) + index));\
							++(cur_size);\
						}\
					}

#define REMOVE(how_many, remove_func, struct_var, cur_size) {\
						size_t index = 0;\
						size_t copy_many = (how_many);\
						for(; index < copy_many; ++index)\
						{\
							remove_func(struct_var);\
							--(cur_size);\
						}\
					}

#define PRINT_TEST_INSERT(how_many, value, insert_func, struct_var, cur_size, size_func) {\
						size_t index = 0;\
						size_t copy_many = (how_many);\
						PRINT_TEST((cur_size), size_func, (struct_var));\
						for(; index < copy_many; ++index)\
						{\
							insert_func((struct_var), (void *)(value));\
							++(cur_size);\
							PRINT_TEST((cur_size), size_func, (struct_var));\
						}\
					}

#define PRINT_TEST_INSERT_ARR(how_many, array, insert_func, struct_var, cur_size, size_func) {\
						size_t index = 0;\
						size_t end_index = (how_many);\
						PRINT_TEST_LINE((cur_size), size_func, (struct_var), index);\
						for(; index < end_index; ++index)\
						{\
							insert_func((struct_var), (void *)((array)[index]));\
							++(cur_size);\
							PRINT_TEST_LINE((cur_size), size_func, (struct_var), index + 1);\
						}\
					}

#define PRINT_TEST_REMOVE(how_many, remove_func, struct_var, cur_size, size_func) {\
						size_t index = 0;\
						size_t cpy_size = how_many;\
						PRINT_TEST((cur_size), size_func, (struct_var));\
						for(; index < cpy_size; ++index)\
						{\
							remove_func(struct_var);\
							--(cur_size);\
							PRINT_TEST((cur_size), size_func, (struct_var));\
						}\
					}

#define REMOVE_ARR(how_many, array, remove_func, struct_var, cur_size) {\
						size_t index = 0;\
						size_t cpy_size = how_many;\
						for(; index < cpy_size; ++index)\
						{\
							remove_func(struct_var, (void *)((array)[index]));\
							--(cur_size);\
						}\
					}
#define PRINT_TEST_REMOVE_ARR(how_many, array, remove_func, struct_var, cur_size, size_func) {\
						size_t index = 0;\
						size_t cpy_size = how_many;\
						PRINT_TEST((cur_size), size_func, (struct_var));\
						for(; index < cpy_size; ++index)\
						{\
							remove_func(struct_var, (void *)((array)[index]));\
							--(cur_size);\
							PRINT_TEST((cur_size), size_func, (struct_var));\
						}\
					}

#define PRINT_TEST_PEEK(how_many, value, peek_func, remove_func, struct_var, cur_size) {\
						size_t index = 0;\
						size_t end_index =  (how_many);\
						for(; index < end_index; ++index)\
						{\
							PRINT_TEST((value), peek_func, (struct_var));\
							remove_func(struct_var);\
							--(cur_size);\
						}\
					}

#define PRINT_TEST_PEEK_ARR(how_many, array, peek_func, remove_func, struct_var, cur_size) {\
						size_t index = 0;\
						size_t end_index = (how_many);\
						for(; index < end_index; ++index)\
						{\
							PRINT_TEST((void *)((array)[index]), peek_func, (struct_var));\
							remove_func(struct_var);\
							--(cur_size);\
						}\
					}

#define PRINT_TEST_PEEK_ARR_BY_REF(how_many, array, peek_func, remove_func, struct_var, cur_size, type) {\
						size_t index = 0;\
						size_t end_index = (how_many);\
						for(; index < end_index; ++index)\
						{\
							PRINT_TEST(((array)[index]), *(type *)peek_func, (struct_var));\
							remove_func(struct_var);\
							--(cur_size);\
						}\
					}
					
#define PRINT_TEST_POP(how_many, value, pop_func, struct_var, cur_size) {\
						size_t index = 0;\
						size_t end_index =  (how_many);\
						for(; index < end_index; ++index)\
						{\
							PRINT_TEST((value), pop_func, (struct_var));\
							--(cur_size);\
						}\
					}

#define PRINT_TEST_POP_ARR(how_many, array, pop_func, struct_var, cur_size) {\
						size_t index = 0;\
						size_t end_index = (how_many);\
						for(; index < end_index; ++index)\
						{\
							PRINT_TEST((void *)((array)[index]), pop_func, (struct_var));\
							--(cur_size);\
						}\
					}

#define PRINT_TEST_POP_ARR_BY_REF(how_many, array, pop_func, struct_var, cur_size, type) {\
						size_t index = 0;\
						size_t end_index = (how_many);\
						for(; index < end_index; ++index)\
						{\
							PRINT_TEST(((array)[index]), *(type *)pop_func, (struct_var));\
							--(cur_size);\
						}\
					}



#ifdef TESTS_NUM

static int all_tests_pass = TRUE;
static int cur_test_pass = TRUE;

void PrintAllTests();
void PrintSingleTest(size_t test_num);

void PrintSingleTest(size_t test_num)
{
	all_tests_pass = TRUE;
	cur_test_pass = TRUE;

	if(0 < test_num && TESTS_NUM >= test_num)

	printf("Test %lu : ", test_num);
	(*tests_arr[test_num - 1])();

	NEW_LINE;

	if(TRUE == cur_test_pass)
	{
		BOLD_CYAN;
		printf("Test %lu PASSED!", test_num);
		WHITE;
		NEW_LINE;
	}

	NEW_LINE;
}

void PrintAllTests()
{
	size_t index = 0;

	for(; index < TESTS_NUM; ++index)
	{
		cur_test_pass = TRUE;
		printf("Test %lu : ", index + 1);
		(*tests_arr[index])();

		NEW_LINE;

		if(TRUE == cur_test_pass)
		{
			BOLD_CYAN;
			printf("Test %lu PASSED!", index + 1);
			WHITE;
			NEW_LINE;
		}
		else
		{
			all_tests_pass = FALSE;
		}

		NEW_LINE;
	}
	
	if (TRUE == all_tests_pass)
	{
		BOLD_BLUE;
		printf("PASSED ALL TESTS!!!\n\n");
		WHITE;
	}
}

#endif	/* TESTS_NUM */
	
#endif /*__GUY_TEST_H__*/

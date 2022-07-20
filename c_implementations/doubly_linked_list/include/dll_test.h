#ifndef __TEST_H__
#define __TEST_H__

/* Includes */
#include <string.h>
#include "dll_colors.h"

/* Defines */
#define TRUE (1)
#define FALSE (0)
#define TERM_CHAR (1)
#define SUCCESS (0)
#define FAILURE (1)

/* Macros */
#define RUNTEST(test){\
		if (TRUE == test)\
		{\
			BOLD_GREEN;\
			printf("\nTest passed!\n");\
			WHITE;\
		}\
		else\
		{\
			BOLD_RED;\
			printf("\nTest failed in line %d in %s\n\n", __LINE__, __FILE__);\
			WHITE;\
		}\
	}

#define RUNFUNCTIONTEST(func, args, expect){\
	if ((expect) == (func args))\
	{\
		BOLD_GREEN;\
		printf("\nTest passed!\n");\
		WHITE;\
	}\
	else\
	{\
		BOLD_RED;\
		printf("\nTest failed in line %d in file '%s'\n\n", __LINE__, __FILE__);\
		WHITE;\
	}\
}

#define RUNSTRINGFUNCTIONTEST(func, args, expect){\
	if (0 == strcmp(func args, expect))\
	{\
		BOLD_GREEN;\
		printf("\nTest passed!\n");\
		WHITE;\
	}\
	else\
	{\
		BOLD_RED;\
		printf("\nTest failed in line %d in %s\n\n", __LINE__, __FILE__);\
		WHITE;\
	}\
}

#define RUNCONDITIONTEST(side1, side2){\
	if ((side1) == (side2))\
	{\
		BOLD_GREEN;\
		printf("\nTest condition passed!\n");\
		WHITE;\
	}\
	else\
	{\
		BOLD_RED;\
		printf("\nTest failed in line %d in %s\n\n", __LINE__, __FILE__);\
		WHITE;\
	}\
}

#define RUNTESTNOTNULL(arg){\
	if (NULL != (arg))\
	{\
		BOLD_GREEN;\
		printf("\nTest not NULL passed!\n");\
		WHITE;\
	}\
	else\
	{\
		BOLD_RED;\
		printf("\nTest failed in line %d in %s\n\n", __LINE__, __FILE__);\
		WHITE;\
	}\
}

#define RUNINSERTORREMOVE(func, args, num_of_times) {\
	while (0 < (num_of_times))\
		{\
			func args;\
			--(num_of_times);\
		}\
}

#define RUNINSERTOBJ(func, args, obj, num_of_times) {\
	while (0 < (num_of_times))\
		{\
			obj = func args;\
			--(num_of_times);\
		}\
}


#define NEWLINE (printf("\n"))

/* Function Typedef */
typedef void (*selection_func_ptr)(void);

typedef long (*long_uint_uint_func_ptr_t)(unsigned int, unsigned int);

typedef int (*int_int_func_ptr_t)(int);

typedef int (*int_uint_func_ptr_t)(unsigned int);

typedef int (*int_uchar_func_ptr_t)(unsigned char);

typedef unsigned char (*uchar_uchar_ptr_t)(unsigned char);

typedef unsigned int (*uint_uint_func_ptr_t)(unsigned int);

typedef size_t (*size_t_uint_func_ptr_t)(unsigned int);


#endif /* __TEST_H__ */

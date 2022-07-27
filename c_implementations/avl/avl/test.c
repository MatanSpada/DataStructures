#include <stdio.h> /* printf() */
#include <assert.h>	/* assert() */

#include "../include/avl.h"
#include "../include/dll_colors.h"

#define SIZE (5)
#define EXACT_SIZE_FOR_HEIGHT_TEN (512)

int IntCmp(const void *val1, const void *val2)
{
	return *(int *)val1 - *(int *)val2;
}

static int PrintTree(void *data, void *param)
{
	printf("%d, ", *(int *)data);
	(void)param;
	return 0;
}

void Test();
void TestCreateNdestroy();
void TestInsertSizeNHeight();
void TestAVLFind();
void TestForEach();
void TestRemove();
void TestBalance();

int main()
{
	BOLD_WHITE; printf("\nRunning AVL Test:\n");
    
   Test();

	BOLD_WHITE; printf("\nTest status: ");
	BOLD_GREEN; printf("PASSED\n\n"); WHITE;

	return 0;
}

void Test()
{
	TestCreateNdestroy();
	TestInsertSizeNHeight();
	TestAVLFind();
	TestForEach();
	TestRemove();
	TestBalance();
}

void TestCreateNdestroy()
{
	avl_t *tree = NULL;
	
	CYAN; printf("\nAVLCreate & AVLDestroy Test status: ");
	tree = AVLCreate(IntCmp);
	assert(NULL != tree);
	assert(AVLIsEmpty(tree));
	AVLDestroy(tree);
    GREEN; printf("PASSED\n"); WHITE; 
}

void TestInsertSizeNHeight()
{
	avl_t *tree = NULL;
	int vals[] = {910, 45, 678, 13, 53, 10, 12};

	size_t i = 0;

	tree = AVLCreate(IntCmp);
	assert(NULL != tree);
	assert(AVLIsEmpty(tree));
	assert(0 == AVLHeight(tree));

	CYAN; printf("\nAVLInsert & AVLSize Test status: ");

	for(i = 0; i < SIZE; ++i)
	{	
		assert(i == AVLSize(tree));
		assert(0 == AVLInsert(tree, vals + i));	
	} 										/*910, 45, 678, 13, 53*/
	assert(SIZE == AVLSize(tree));
    GREEN; printf("PASSED\n"); WHITE;

   	CYAN; printf("\nAVLIsEmpty Test status: ");
   	assert(!AVLIsEmpty(tree));
    GREEN; printf("PASSED\n"); WHITE;

   	CYAN; printf("\nAVLHeight Test status: ");
	assert(3 == AVLHeight(tree));

	AVLInsert(tree, vals + (SIZE + 1));    /*910, 45, 678, 13, 53, 10*/
	assert(3 == AVLHeight(tree));
	assert(SIZE + 1 == AVLSize(tree));

	GREEN; printf("PASSED\n"); WHITE;

	AVLDestroy(tree);
}

void TestAVLFind()
{
	avl_t *tree = NULL;
	int vals[] = {910, 45, 678, 13, 53, 10, 12};
	size_t i = 0;

	tree = AVLCreate(IntCmp);
	assert(NULL != tree);
	assert(AVLIsEmpty(tree));
	assert(0 == AVLHeight(tree));

	CYAN; printf("\nAVLFind Test status: ");
	for(i = 0; i < SIZE; ++i)
	{	
		assert(i == AVLSize(tree));
		assert(0 == AVLInsert(tree, vals + i));	/*910, 45, 678, 13, 53*/
		assert(vals + i == AVLFind(tree, vals + i));
	} 							
	assert(NULL == AVLFind(tree, vals + (SIZE + 1))); /* 10 */

    GREEN; printf("PASSED\n"); WHITE;
   	AVLDestroy(tree);
}

void TestForEach()
{
	avl_t *tree = NULL;
	int vals[] = {910, 45, 678, 13, 953, 10, 954};
	size_t i = 0;

	tree = AVLCreate(IntCmp);
	assert(NULL != tree);
	assert(AVLIsEmpty(tree));
	assert(0 == AVLHeight(tree));

	CYAN; printf("\nAVLForEach Test status: \n");
	for(i = 0; i < SIZE + 2; ++i)
	{	
		assert(i == AVLSize(tree));
		assert(0 == AVLInsert(tree, vals + i));	/*910, 45, 678, 13, 953, 10, 954*/
	} 							

	WHITE; printf("\n\tprint PRE_ORDER:(root-->%d)\n\t\t", vals[0]);CYAN;
	AVLForEach(tree, &PrintTree, NULL, PRE_ORDER);

	WHITE; printf("\n\n\tprint IN_ORDER:(root-->%d)\n\t\t", vals[0]);CYAN;
	AVLForEach(tree, &PrintTree, NULL, IN_ORDER);

	WHITE; printf("\n\n\tprint POST_ORDER:(root-->%d)\n\t\t", vals[0]);CYAN;
	AVLForEach(tree, &PrintTree, NULL, POST_ORDER);
    GREEN; printf("\nPASSED\n"); WHITE;
	
	AVLDestroy(tree);
}

void TestRemove()
{
	avl_t *tree = NULL;
	int vals[] = {910, 45, 678, 13, 953, 10, 954};
	int ordered_vals[] = {10, 13, 45, 678, 910, 953, 954};

	int non_present_val = 55;
	size_t i = 0;

	tree = AVLCreate(IntCmp);
	assert(NULL != tree);
	assert(AVLIsEmpty(tree));
	assert(0 == AVLHeight(tree));

	CYAN; printf("\nAVLRemove Test status: ");
	for(i = 0; i < SIZE + 2; ++i)
	{	
		assert(i == AVLSize(tree));
		assert(0 == AVLInsert(tree, vals + i));	/*910, 45, 678, 13, 953, 10, 954*/
	}
	assert(3 == AVLHeight(tree));

	for(i = 0; i < SIZE + 1; ++i)
	{	
		assert((SIZE + 2) - i == AVLSize(tree));
		AVLRemove(tree, vals + i);	/*910, 45, 678, 13, 953, 10*/
	} 
	assert(1 == AVLHeight(tree)); /* 954 */
	AVLRemove(tree, vals + (SIZE + 1));
	assert(AVLIsEmpty(tree));
	AVLRemove(tree, &non_present_val);

	for(i = 0; i < SIZE + 2; ++i)
	{	
		assert(i == AVLSize(tree));
		assert(0 == AVLInsert(tree, vals + i));	/*910, 45, 678, 13, 953, 10, 954*/
	}
	assert(3 == AVLHeight(tree));
 
	for(i = 0; i < SIZE - 2; ++i)
	{	
		assert((SIZE + 2) - i == AVLSize(tree));
		AVLRemove(tree, ordered_vals + i);	/*10, 13, 45, 678, 910, 953, 954*/
	} 
	assert(3 == AVLHeight(tree)); /* 678, 910, 953, 954 */
	AVLRemove(tree, ordered_vals + 3);
	assert(2 == AVLHeight(tree)); /* 910, 953, 954 */
	AVLRemove(tree, ordered_vals + 4);
	assert(2 == AVLHeight(tree)); /* 953, 954 */
	AVLRemove(tree, ordered_vals + 5);
	assert(1 == AVLHeight(tree)); /* 954 */
	AVLRemove(tree, ordered_vals + 6);
	assert(AVLIsEmpty(tree));
	assert(0 == AVLHeight(tree));
	GREEN; printf("PASSED\n"); WHITE;
	
	AVLDestroy(tree);
}

void TestBalance()
{	
	avl_t *tree = NULL;
	int from_one_to_five_g_n_twelve[EXACT_SIZE_FOR_HEIGHT_TEN] = {0};
	int from_one_to_sixteen[16]  = {0};
	size_t i = 0;
	
	tree = AVLCreate(IntCmp);
	assert(NULL != tree);
	assert(AVLIsEmpty(tree));
	assert(0 == AVLHeight(tree));

	for (i = 0; i < EXACT_SIZE_FOR_HEIGHT_TEN; ++i)
	{
		from_one_to_five_g_n_twelve[i] = i + 1;
	}

	CYAN; printf("\nIs The Tree Balanced Test status: \n");
	for(i = 0; i < EXACT_SIZE_FOR_HEIGHT_TEN - 1; ++i)
	{	
		assert(i == AVLSize(tree));
		assert(0 == AVLInsert(tree, from_one_to_five_g_n_twelve + i));	
	}
	assert(9 == AVLHeight(tree));

	AVLInsert(tree, from_one_to_five_g_n_twelve + EXACT_SIZE_FOR_HEIGHT_TEN - 1);
	assert(10 == AVLHeight(tree));

	for(i = 0; i < EXACT_SIZE_FOR_HEIGHT_TEN; ++i)
	{	
		AVLRemove(tree, from_one_to_five_g_n_twelve + i);
	} 
	assert(0 == AVLHeight(tree));

	for (i = 0; i < 17; ++i)
	{
		from_one_to_sixteen[i] = i + 1;
	}

	for(i = 0; i < 10; ++i)
	{	
		assert(i == AVLSize(tree));
		assert(0 == AVLInsert(tree, from_one_to_sixteen + i));	
	}
	assert(4 == AVLHeight(tree));
	WHITE; printf("\nBEFORE:\n"); 
	PrintTreeByLevels(tree);

	AVLRemove(tree, from_one_to_sixteen + 4);
	AVLRemove(tree, from_one_to_sixteen + 7);
	AVLRemove(tree, from_one_to_sixteen + 9);
	WHITE; printf("\nAFTER:\n"); 

	WHITE; PrintTreeByLevels(tree);

	assert(3 == AVLHeight(tree));

	GREEN; printf("PASSED\n"); WHITE;

	AVLDestroy(tree);
}

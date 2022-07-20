#include <stdio.h> /* printf */
#include <stdlib.h> /* free */
#include "../include/dll.h" /* custom library */
#include "../include/dll_test.h" /* test library */

#define COUNTSIZE (3)

int Find(const void *data1, const void *data2);
int Print(void *data1, void *data2);

void TestCreateNDestroy()
{
	dlist_t *dll = DListCreate();
	NEWLINE;
	BOLD_CYAN;
	printf("Testing DListCreate and DListDestroy:");
	WHITE;
	NEWLINE;
	RUNTESTNOTNULL(dll);

	DListDestroy(dll);
	dll = NULL;
}

void TestEmptyNSize()
{
	dlist_t *dll = DListCreate();

	NEWLINE;
	BOLD_CYAN;
	printf("Testing DListIsEmpty and DListSize:");
	WHITE;
	NEWLINE;

	BOLD_YELLOW;
	printf("DListIsEmpty");
	WHITE;
	RUNFUNCTIONTEST(DListIsEmpty, (dll), TRUE);

	NEWLINE;

	BOLD_YELLOW;
	printf("DListSize");
	WHITE;
	RUNFUNCTIONTEST(DListSize, (dll), 0);

	DListDestroy(dll);
	dll = NULL;
}

void TestInsertBeginNEnd()
{
	dlist_t *dll = DListCreate();
	dlist_iter_t iter = NULL;
	size_t counter = COUNTSIZE;

	NEWLINE;
	BOLD_CYAN;
	printf("Testing DListBegin, DListEnd and DListInsert:");
	WHITE;
	NEWLINE;

	BOLD_YELLOW;
	printf("DListBegin");
	WHITE;

	iter = DListBegin(dll);
	RUNTESTNOTNULL(iter);

	NEWLINE;

	BOLD_YELLOW;
	printf("DListEnd");
	WHITE;

	iter = DListEnd(dll);
	RUNTESTNOTNULL(iter);

	NEWLINE;

	BOLD_YELLOW;
	printf("DListInsert:");
	WHITE;
	NEWLINE;

	RUNINSERTOBJ(DListInsert, (iter, (void*)counter), iter, counter);

	BOLD_BLUE;
	printf("DListIsEmpty");
	WHITE;
	RUNFUNCTIONTEST(DListIsEmpty, (dll), FALSE);

	NEWLINE;
	BOLD_BLUE;
	printf("DListSize");
	WHITE;
	RUNFUNCTIONTEST(DListSize, (dll), COUNTSIZE);

	DListDestroy(dll);
	iter = NULL;
	dll = NULL;
}

void TestNextNPrev()
{
	dlist_t *dll = DListCreate();
	dlist_iter_t iter = NULL;
	size_t counter = COUNTSIZE;

	NEWLINE;
	BOLD_CYAN;
	printf("Testing DListNext, DListGetData and DListPrev:");
	WHITE;
	NEWLINE;

	iter = DListEnd(dll);
	RUNINSERTOBJ(DListInsert, (iter, (void*)counter), iter, counter);

	BOLD_YELLOW;
	printf("DListNext:");
	WHITE;

	iter = DListBegin(dll);
	for (counter = 1; counter <= COUNTSIZE; ++counter)
	{
		RUNCONDITIONTEST(DListGetData(iter), (void*)counter);
		iter = DListNext(iter);
	}

	NEWLINE;

	BOLD_YELLOW;
	printf("DListPrev:");
	WHITE;

	iter = DListEnd(dll);
	for (counter = COUNTSIZE; 0 < counter; --counter)
	{
		iter = DListPrev(iter);
		RUNCONDITIONTEST(DListGetData(iter), (void*)counter);
	}

	DListDestroy(dll);
	iter = NULL;
	dll = NULL;
}

void TestPushNRemove()
{
	dlist_t *dll = DListCreate();
	dlist_iter_t iter = NULL;
	size_t counter = COUNTSIZE;

	NEWLINE;
	BOLD_CYAN;
	printf("Testing DListPushFront, DListPushBack, and DListRemove:");
	WHITE;
	NEWLINE;

	BOLD_YELLOW;
	printf("DListPushFront:");
	WHITE;

	RUNINSERTOBJ(DListPushFront, (dll, (void*)counter), iter, counter);

	NEWLINE;
	BOLD_BLUE;
	printf("DListSize");
	WHITE;

	RUNFUNCTIONTEST(DListSize, (dll), COUNTSIZE);

	NEWLINE;
	BOLD_BLUE;
	printf("DListNext");
	WHITE;

	iter = DListBegin(dll);
	for (counter = 1; counter <= COUNTSIZE; ++counter)
	{
		RUNCONDITIONTEST(DListGetData(iter), (void*)counter);
		iter = DListNext(iter);
	}

	NEWLINE;
	BOLD_BLUE;
	printf("DListPrev");
	WHITE;

	iter = DListEnd(dll);
	for (counter = COUNTSIZE; 0 < counter; --counter)
	{
		iter = DListPrev(iter);
		RUNCONDITIONTEST(DListGetData(iter), (void*)counter);
	}

	NEWLINE;

	BOLD_YELLOW;
	printf("DListRemove:");
	WHITE;

	for (counter = 0; counter < COUNTSIZE; ++counter)
	{

		iter = DListBegin(dll);
		DListRemove(iter);
	}

	NEWLINE;
	BOLD_BLUE;
	printf("DListIsEmpty");
	WHITE;
	RUNFUNCTIONTEST(DListIsEmpty, (dll), TRUE);

	NEWLINE;
	BOLD_YELLOW;
	printf("DListPushBack:");
	WHITE;

	RUNINSERTOBJ(DListPushBack, (dll, (void*)counter), iter, counter);

	NEWLINE;
	BOLD_BLUE;
	printf("DListNext");
	WHITE;

	iter = DListBegin(dll);
	for (counter = 1; counter <= COUNTSIZE; ++counter)
	{
		RUNCONDITIONTEST(DListGetData(iter), (void*)((COUNTSIZE + 1) - counter));
		iter = DListNext(iter);
	}

	NEWLINE;
	BOLD_BLUE;
	printf("DListPrev");
	WHITE;

	iter = DListEnd(dll);
	for (counter = COUNTSIZE; 0 < counter; --counter)
	{
		iter = DListPrev(iter);
		RUNCONDITIONTEST(DListGetData(iter), (void*)((COUNTSIZE + 1) - counter));
	}

	DListDestroy(dll);
	iter = NULL;
	dll = NULL;
}

void TestPopsNIsEqual()
{
	dlist_t *dll = DListCreate();
	dlist_iter_t iter = NULL;
	size_t counter = COUNTSIZE;

	NEWLINE;
	BOLD_CYAN;
	printf("Testing DListPopFront, DListPopBack and DListIsEqual:");
	WHITE;
	NEWLINE;
	
	iter = DListEnd(dll);
	RUNINSERTOBJ(DListInsert, (iter, (void*)counter), iter, counter);

	BOLD_YELLOW;
	printf("DListPopFront:");
	WHITE;

	for (counter = 1; counter <= COUNTSIZE; ++counter)
	{
		RUNFUNCTIONTEST(DListPopFront, (dll), (void*)counter);
	}

	NEWLINE;
	BOLD_YELLOW;
	printf("DListIsEqual:");
	WHITE;

	iter = DListEnd(dll);
	RUNINSERTOBJ(DListInsert, (iter, (void*)counter), iter, counter);

	iter = DListBegin(dll);
	while (NULL != DListNext(iter))
	{
		iter = DListNext(iter);
	}

	
	RUNFUNCTIONTEST(DListIsEqual, (iter, DListEnd(dll)), TRUE);

	NEWLINE;
	BOLD_YELLOW;
	printf("DListPopBacks:");
	WHITE;

	for (counter = COUNTSIZE; 0 < counter; --counter)
	{
		RUNFUNCTIONTEST(DListPopFront, (dll), (void*)((COUNTSIZE + 1) - counter));
	}

	DListDestroy(dll);
	iter = NULL;
	dll = NULL;
}

void TestSplice()
{
	dlist_t *dll1 = DListCreate();
	dlist_t *dll2 = DListCreate();
	dlist_iter_t iter = NULL;
	size_t counter = COUNTSIZE;

	NEWLINE;
	BOLD_CYAN;
	printf("Testing DListSplice:");
	WHITE;
	NEWLINE;

	iter = DListEnd(dll1);
	RUNINSERTOBJ(DListInsert, (iter, (void*)counter), iter, counter);

	iter = DListEnd(dll1);
	for (counter = 0; counter < 3; ++counter)
	{
		iter = DListPrev(iter);
	}

	DListSplice(DListEnd(dll2), iter, DListEnd(dll1));

	BOLD_YELLOW;
	printf("Size of first list");
	WHITE;
	RUNFUNCTIONTEST(DListSize, (dll1), COUNTSIZE - 3);

	NEWLINE;
	BOLD_YELLOW;
	printf("Size of second list");
	WHITE;
	RUNFUNCTIONTEST(DListSize, (dll2), 3);

	NEWLINE;
	BOLD_YELLOW;
	printf("Checking nodes in the first list:");
	WHITE;
	for (counter = 1; counter <= (COUNTSIZE - 3); ++counter)
	{
		RUNFUNCTIONTEST(DListPopFront, (dll1), (void*)((COUNTSIZE + 1 ) - (counter + 3)));
	}

	NEWLINE;
	BOLD_YELLOW;
	printf("Checking nodes in the second list:");
	WHITE;
	for (counter = 1; counter <= 3; ++counter)
	{
		RUNFUNCTIONTEST(DListPopFront, (dll2), (void*)((COUNTSIZE - 3) + counter));
	}

	


	DListDestroy(dll1);
	DListDestroy(dll2);
	iter = NULL;
	dll1 = NULL;
	dll2 = NULL;
}

void TestForEachNFind()
{
	dlist_t *dll = DListCreate();
	dlist_iter_t iter = NULL;
	size_t counter = COUNTSIZE;

	NEWLINE;
	BOLD_CYAN;
	printf("Testing DListForEach and DListFind:");
	WHITE;

	iter = DListEnd(dll);
	RUNINSERTOBJ(DListInsert, (iter, (void*)counter), iter, counter);

	BOLD_YELLOW;
	printf("\nTesting DListFind:\n");
	WHITE;

	BOLD_BLUE;
	printf("Success Test:");
	WHITE;
	RUNFUNCTIONTEST(DListGetData, (DListFind(DListBegin(dll), DListEnd(dll), Find, (void*)(COUNTSIZE / 2))), (void*)(COUNTSIZE / 2));
	
	NEWLINE;
	BOLD_BLUE;
	printf("Failure Test:");
	WHITE;
	RUNFUNCTIONTEST(DListFind, (DListBegin(dll), DListEnd(dll), Find, (void*)(COUNTSIZE + 1)), DListEnd(dll));

	BOLD_YELLOW;
	printf("\nTesting DListForEach:\n");
	WHITE;

	RUNFUNCTIONTEST(DListForEach, (DListBegin(dll), DListEnd(dll), Print, (void*)1), SUCCESS);

	DListDestroy(dll);
	iter = NULL;
	dll = NULL;
}

void TestMultiFind()
{
	dlist_t *dll1 = DListCreate();
	dlist_t *dll2 = DListCreate();
	dlist_iter_t iter = NULL;
	size_t counter = COUNTSIZE;
	size_t helper = ((COUNTSIZE % 2) == 1) ? 1 : 0;

	NEWLINE;
	BOLD_CYAN;
	printf("Testing DListMultiFind:");
	WHITE;
	NEWLINE;

	iter = DListEnd(dll1);
	RUNINSERTOBJ(DListInsert, (iter, (void*)(counter % 2)), iter, counter);

	counter = 1;
	DListMultiFind(DListBegin(dll1), DListEnd(dll1), Find, (void*)counter, dll2);


	iter = DListNext(DListBegin(dll2));
	RUNFUNCTIONTEST(DListSize, (dll2), ((COUNTSIZE + helper) / 2));

	DListDestroy(dll1);
	DListDestroy(dll2);
	iter = NULL;
	dll1 = NULL;
	dll2 = NULL;
}

int Find(const void *data1, const void *data2)
{
	return (data1 == data2);
}

int Print(void *data1, void *data2)
{
	printf("data1 = %d\tdata2 = %d\n", *(int*)&data1, *(int*)&data2);
	return SUCCESS;
}


int main()
{
	TestCreateNDestroy();
	TestEmptyNSize();
	TestInsertBeginNEnd();
	TestNextNPrev();
	TestPushNRemove();
	TestPopsNIsEqual();
	TestSplice();
	TestForEachNFind();
	TestMultiFind();

	NEWLINE;
	BOLD_PURPLE;
	printf("All Done!");
	NEWLINE;
	WHITE;

	return (0);
}

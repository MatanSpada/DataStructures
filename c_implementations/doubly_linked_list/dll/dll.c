/***********************************
 * doubly Linked List Source Code  *
 * Developer: Matan Spada          *
 * Written: 2021-12-20             *
 *                                 *
 * Approved by:       guy          *
 ***********************************/

#include <stdlib.h>			 /* malloc(), free(), NULL */ 
#include <assert.h>			 /* assert() */

#include "../include/dll.h"			 /* header file */

#define SUCCESS (0)
#define FAILURE (-1)



struct dlist
{
	struct dlist_node *head;
	struct dlist_node *tail;
};



typedef struct dlist_node
{
	void *data;
	struct dlist_node *next;
	struct dlist_node *prev;
} dlist_node_t;

/******************* Auxilary Functions **********************/
static dlist_iter_t CreateNode(dlist_node_t *insertion_place ,void *data);

/******************* Exercise Functions **********************/


/****** Exercise 1 ******/

dlist_t *DListCreate(void)
{
	dlist_node_t *dummy_tail = NULL;
	dlist_node_t *dummy_head = NULL;

	dlist_t *new_list = (dlist_t *)malloc(sizeof(dlist_t));
	if (NULL == new_list)
	{
		return NULL;
	}

	dummy_head = (struct dlist_node *)malloc(sizeof(struct dlist_node));
	if (NULL == dummy_head )
	{
		free(new_list);
		new_list = NULL;

		return NULL;
	}

	dummy_tail = (struct dlist_node *)malloc(sizeof(struct dlist_node));
	if (NULL == dummy_tail)
	{
		free(dummy_head);
		dummy_head = NULL;

		free(new_list);
		new_list = NULL;

		return NULL;
	}

	new_list->head = dummy_head;
	new_list->tail = dummy_tail;
	dummy_head->data = NULL;						/*for NEXT() and PREV() - marking the dummy nodes*/
	dummy_tail->data = NULL;						/*for NEXT() and PREV() - marking the dummy nodes*/	

	new_list->head->next = dummy_tail;				/*by default*/
	new_list->head->prev = NULL;			/*head prev points tail*/

	new_list->tail->next = NULL;			/*tail next points head*/
	new_list->tail->prev = dummy_head;				/*by default*/



	return (new_list);
}




/****** Exercise 2 ******/

void DListDestroy(dlist_t *list)
{
	dlist_node_t *runner = NULL;

	assert(NULL != list);

	runner = list->head;
	while (runner != list->tail)				
	{
		runner = runner->next;
		free(list->head);
		list->head = runner;
	}	

	free(list->tail);				/*check if distroy both dummys*/
	list->tail = NULL;

	free(list);							
	list = NULL;									
}





/****** Exercise 3 ******/

int DListIsEmpty(const dlist_t *list)
{
	assert(NULL != list);

	return (list->head->next == list->tail);
}





/****** Exercise 4 ******/

size_t DListSize(const dlist_t *list)
{
	size_t count = 0;
	dlist_node_t *runner = NULL;

	assert(NULL != list);

	runner = list->head;

	while (runner->next != list->tail)
	{
		++count;
		runner = runner->next;
	}
	return (count);
}



/****** Exercise 5 ******/

dlist_iter_t DListInsert(dlist_iter_t insertion_place, void *data)
{
	dlist_node_t *new_node = NULL;	

	assert(NULL != insertion_place);

	new_node = CreateNode(insertion_place ,data);		/* creates and recnnects all next&prev pointers */
	if(NULL == new_node)								/* if malloc failed */	
	{ 
		new_node = insertion_place;
		while (new_node->next != NULL)					/*run to the last element and return END*/
		{
			new_node = new_node->next;
		}

	}
	return (new_node);
}



/****** Exercise 6 ******/

dlist_iter_t DListRemove(dlist_iter_t node)
{
	dlist_node_t *next_node = NULL;

    assert(NULL != node);
    assert(NULL != node->next);
    assert(NULL != node->prev);

    next_node = node->next;

 	node->prev->next = node->next;
	node->next->prev = node->prev;
	node->next = NULL;							/*maybe unnecessery*/
	node->prev = NULL;							/*maybe unnecessery*/
	
	free(node);
												/*maybe that's not how you write unnecessery...*/
    return (next_node);                
}




/****** Exercise 7 ******/

dlist_iter_t DListPushFront(dlist_t *dll, void *data)
{
	   assert(NULL != dll);

	   return (DListInsert(DListBegin(dll), data));				/*BEGIN() should return the first element(not head)*/
}





/****** Exercise 8 ******/

dlist_iter_t DListPushBack(dlist_t *dll, void *data)
{
	assert(NULL != dll);

	return (DListInsert(DListEnd(dll), data));						/*END() return the last element. that is why */
}																	/*i'm passing the func the next element(aka dummy_tail)*/





/****** Exercise 9 ******/

void *DListPopFront(dlist_t *dll)									/*POP() on empty list - undefined*/
{
	dlist_iter_t node = NULL;
	void *data = NULL;

	assert(NULL != dll);
	assert(!DListIsEmpty(dll));

	node = DListBegin(dll);
	data = DListGetData(node);										/*the user need to free with Destroy()*/
	DListRemove(node);
																	/*+ same as comment above*/
	return data;			
}																	





/****** Exercise 10 ******/

void *DListPopBack(dlist_t *dll)									/*POP() on empty list - undefined*/
{
	void *data = NULL;

	assert(NULL != dll);
	assert(dll->tail->prev != dll->head);

	data = dll->tail->prev->data;
	DListRemove(dll->tail->prev);

	return data;				
}


/****** Exercise 11 ******/

void DListSplice(dlist_iter_t where, dlist_iter_t from, dlist_iter_t to)
{
	dlist_node_t *end_node = NULL; 

	assert(NULL != where);
    assert(NULL != from);
	assert(NULL != to);

	from->prev->next = to;
	end_node = to->prev;
	to->prev = from->prev;

	end_node->next = where;
	from->prev = where->prev;
	from->prev->next = from;
	where->prev = end_node;
}






/****** Exercise 12 ******/

dlist_iter_t DListBegin(const dlist_t *dll)
{
	assert(NULL != dll);									/*BEGIN() on empty list - undefined*/

	return dll->head->next;									/*head is dummy, therefore return first element*/
}





/****** Exercise 13 ******/

dlist_iter_t DListEnd(const dlist_t *dll)
{
	assert(NULL != dll);										/*END() on empty list - undefined*/

	return dll->tail;										/*tail is a dummy, thus i return the first user-element */
}





/****** Exercise 14 ******/

dlist_iter_t DListNext(dlist_iter_t iter)
{
	assert(NULL != iter);

	return (iter->next);					/*what happens user use NEXT() on the last element (before dummy)?*/							
}										/*is that IF is the solution?*/





/****** Exercise 15 ******/

dlist_iter_t DListPrev(dlist_iter_t iter)
{
	assert(NULL != iter);

	return iter->prev;					/*same question as above*/
}




void *DListGetData(dlist_iter_t iter)
{
	assert(NULL != iter);

	return iter->data;	
}



/****** Exercise 16 ******/

int DListIsEqual(dlist_iter_t iter1, dlist_iter_t iter2)
{
	assert(NULL != iter1);
	assert(NULL != iter2);

	return (iter1 == iter2);
}




/****** Exercise 17 ******/

dlist_iter_t DListFind(dlist_iter_t from, dlist_iter_t to, match_func_t is_match, void *param)
{
	assert(NULL != from);
	assert(NULL != to);


	while ((from != to) && (!is_match(from->data, param)))
	{
		from = from->next;
	}

	if(is_match(from->data, param))
	{
		return from;
	}

	return to;		/*if not found, return END*/
}



/****** Exercise 18 ******/

int DListMultiFind(dlist_iter_t from, dlist_iter_t to,
	match_func_t is_match, void *param, dlist_t *result_list)
{
	struct dlist_node *found_node = NULL;

	assert(NULL != result_list);
	assert(NULL != from);
	assert(NULL != to);

	found_node = from;

	while (found_node != to && NULL != found_node)
	{
		found_node = DListFind(found_node, to, is_match, param);
		if (found_node != to)
		{
			if (DListEnd(result_list) == DListInsert(DListEnd(result_list), found_node->data))
			{
				return FAILURE;
			}
		}
		found_node = found_node->next;
	}
	return SUCCESS;
}






/****** Exercise 19 ******/

int DListForEach(dlist_iter_t from, dlist_iter_t to, action_func_t action_func, void *param)
{
	int error_code = SUCCESS;

	assert(NULL != from);
	assert(NULL != to);

	while ((from != to) && (SUCCESS == error_code))
	{
		error_code = action_func(from->data, param);
		from = from->next;
	}

	return error_code;
}










/******************* Auxilary Functions **********************/



static dlist_iter_t CreateNode(dlist_node_t *insertion_place ,void *data)
{
	dlist_node_t *new_node = (dlist_node_t *)malloc(sizeof(struct dlist_node));
	if (NULL == new_node) 
	{
		return NULL;
	}

	new_node->data = data;						
	new_node->prev = insertion_place->prev;				/*if list empty - insertion place is head?*/
	new_node->next = insertion_place;
	insertion_place->prev->next = new_node;
	insertion_place->prev = new_node;

	return new_node;	
}


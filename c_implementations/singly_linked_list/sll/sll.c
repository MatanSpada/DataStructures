#include <stdlib.h>				/* malloc(), free(), NULL, size_t */
#include <assert.h>				/* assert() */

#include "../include/sll.h"		/* header file */

#define SUCCESS (0)

struct slist	
{
	struct slist_node *head;
	struct slist_node *tail;
};

struct slist_node
{	
	void *data;
	struct slist_node *next;
};






/******************* Auxilary Functions **********************/

static slist_iter_t CreateNode(void *data);
static int ListCount(void *data, void *count);


/******************* Exercise Functions **********************/


/****** Exercise 1 ******/

slist_t *SListCreate(void)
{
	slist_t *new_list = (slist_t *)malloc(sizeof(slist_t));
	if (NULL == new_list)
	{
		return NULL;
	}

	new_list->tail = (struct slist_node *)malloc(sizeof(struct slist_node));
	if (NULL == new_list->tail)
	{
		free(new_list);		
		new_list = NULL;

		return NULL;
	}

	new_list->tail->data = new_list;	
	new_list->tail->next = NULL;
	new_list->head = new_list->tail;

	return new_list;
}



/****** Exercise 2 ******/

void SListDestroy(slist_t *list)
{
	assert(NULL != list);

	while (list->head != list->tail)				
	{
		slist_iter_t temp = SListRemove(list->head);
		free(temp);
	}	

	free(list->tail);
	list->tail = NULL;

	free(list);							
	list = NULL;									
}


/****** Exercise 3 ******/

slist_iter_t SListInsertAfter(slist_iter_t insertion_place, const void *data)
{
	slist_iter_t new_node = NULL;	

	assert(NULL != insertion_place);

	new_node = CreateNode((void*)data);			
	if(NULL == new_node)							
	{ 
		new_node = insertion_place;

		while (new_node->next != NULL)		
		{
			new_node = new_node->next;
		}

		return new_node;
	}

	new_node->data = (void*)data;
	new_node->next = insertion_place->next;
	insertion_place->next = new_node;

	return new_node;								
}	

/****** Exercise 4 ******/

slist_iter_t SListInsertBefore(const slist_iter_t node, const void *data)
{
	slist_iter_t new_node = CreateNode((void*)data);
	
	assert(NULL != node);

	if(NULL == new_node)							
	{ 
		new_node = node;

		while (new_node->next != NULL)	
		{
			new_node = new_node->next;
		}

		return new_node;
	}
	new_node->data = node->data;			
	node->data = (void *)data;
	new_node->next = node->next;			
	node->next = new_node;



	if(NULL == new_node->next)
	{
		((slist_t *)(new_node->data))->tail = new_node;
	}
	return new_node;
}


/****** Exercise 5 ******/

slist_iter_t SListRemove(slist_iter_t node)
{
    slist_iter_t temp = NULL;

    assert(NULL != node);

    temp = node->next;
    node->data = node->next->data;
    node->next = node->next->next;

    if(NULL == node->next)
    {
        ((slist_t *)(node->data))->tail = node;
    }

    return temp;                
}



/****** Exercise 6 ******/

size_t SListCount(const slist_t *list)
{
	size_t count = 0;

	assert(NULL != list);

	SListForEach(list->head, list->tail, ListCount, &count);

	return count;
}



/****** Exercise 7 ******/

int SListIsEmpty(const slist_t *list)
{
	assert(NULL != list);

	return (list->head == list->tail);
}



/****** Exercise 8 ******/

slist_iter_t SListBegin(const slist_t *list)
{
	assert(NULL != list);

	return list->head;
}



/****** Exercise 9 ******/

slist_iter_t SListEnd(const slist_t *list)
{
	assert(NULL != list);

	return list->tail;
}



/****** Exercise 10 ******/

void *SListGetData(const slist_iter_t node)
{
	assert(NULL != node);

	return node->data;
}



/****** Exercise 11 ******/

void SListSetData(slist_iter_t node, const void *data)
{
	assert(NULL != node);
	assert(NULL != data);

	node->data = (void*)data;
}




/****** Exercise 12 ******/

slist_iter_t SListNext(const slist_iter_t node)
{
	assert(NULL != node);

	return node->next;
}



/****** Exercise 13 ******/

int SListIsEqual(const slist_iter_t node1, const slist_iter_t node2)
{
	assert(NULL != node1);
	assert(NULL != node2);

	return (node1 == node2);
}



/****** Exercise 14 ******/

int SListForEach(const slist_iter_t from, const slist_iter_t to,
				action_func_t action_func, void *param)
{
	int error_code = SUCCESS;
	slist_iter_t iter = from;

	assert(NULL != from);
	assert(NULL != to);

	while (iter != to && error_code == SUCCESS)
	{
		error_code = action_func(iter->data, param);
		iter = iter->next;
	}
	return error_code;
}



/****** Exercise 15 ******/

slist_iter_t SListFind(const slist_iter_t from, const slist_iter_t to,
						match_func_t is_match, void *param)
{
	struct slist_node *iterator = from;

	assert(NULL != from);
	assert(NULL != to);

	while (iterator != to)
	{
		if (is_match(iterator->data, param))
		{
			return iterator;
		}

		iterator = iterator->next;
	}

	/* if we did not find, we return End */
	while (iterator->next != NULL)
	{
		iterator = iterator->next;
	}

	return iterator;
}


/****** Exercise 16 ******/

void SListAppend(slist_t *first_list, slist_t *second_list)
{
	slist_iter_t first_list_tail = NULL;
	slist_iter_t second_list_head = NULL; 

    assert(NULL != first_list);
    assert(NULL != second_list);
    assert(first_list != second_list);

    if(SListIsEmpty(second_list))
    {
    	return;
    }

    first_list_tail = first_list->tail;
    second_list_head = second_list->head;

    first_list_tail->next = second_list_head->next; 
    first_list_tail->data = second_list_head->data; 

    second_list_head->next = NULL; 

    first_list->tail = second_list->tail; 
    first_list->tail->data = (void*)first_list;
    second_list->tail = second_list->head;
    second_list->tail->data = (void*)second_list;
}




/******************* Auxilary Functions **********************/



static slist_iter_t CreateNode(void *data)
{
	slist_iter_t iter = (slist_iter_t)malloc(sizeof(struct slist_node));
	if (NULL == iter) 
	{
		return NULL;
	}

	iter->data = data;
	iter->next = NULL;

	return iter;	
}



static int ListCount(void *data, void *count)
{
	(void)data;
	++(*(size_t *)count);
	return SUCCESS;
}
	

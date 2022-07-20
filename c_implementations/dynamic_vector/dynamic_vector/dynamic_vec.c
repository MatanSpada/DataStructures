								/* approved  by lior, not guy!  */

#include <string.h>				/* memcpy() */
#include <assert.h>				/* assert() */
#include "../include/dynamic_vector.h"		/* header file */

#define GROWTH_FACTOR (2)

struct vector
{
	void *vector_array;
	size_t capacity;
	size_t element_size;
	size_t current_size;	
}; 
	
enum status
{
	ALLOCATION_FAILURE = -1,
	SUCCESS
};



/*************exercise functions*************/



/*exercise 1*/

vector_t *VectorCreate(size_t element_size, size_t capacity)
{
	void *vector_array = NULL;
	vector_t *new_vector = NULL;

	new_vector = (vector_t*)malloc(sizeof(vector_t));		
	if (NULL == new_vector)
	{
		return NULL;
	}

	vector_array = malloc(capacity * element_size);	
	if (NULL == vector_array)
	{
		free(new_vector);
		new_vector = NULL;

		return NULL;
	}

	new_vector->capacity = capacity;									
	new_vector->vector_array = vector_array;
	new_vector->element_size = element_size;
	new_vector->current_size = 0;
	return new_vector;
}



/* exercise 2 */

void VectorDestroy(vector_t *vector)
{
	assert(NULL != vector);

	free(vector->vector_array);
	vector->vector_array = NULL;

	free(vector);
	vector = NULL;
}




/* exercise 3 */

void *VectorGetAccessToElement(vector_t *vector, size_t index)
{
	assert(NULL != vector);

	return (char *)vector->vector_array + (index * vector->element_size);
}




/* exercise 4 */

int VectorPushBack(vector_t *vector,const void *element)
{
	char *place_to_insert = NULL;

	assert(NULL != vector);
	assert(NULL != element);

	if(vector->current_size == vector->capacity)
	{
		vector = VectorReserve(vector, vector->capacity * GROWTH_FACTOR);
	}

	place_to_insert = vector->vector_array;		
	place_to_insert += (vector->current_size * vector->element_size);

	memcpy(place_to_insert, element, vector->element_size);
	++(vector->current_size);

	return SUCCESS;
}



/* exercise 5 */

void VectorPopBack(vector_t *vector)
{
	assert(NULL != vector);

	--(vector->current_size);

	if ((vector->current_size != 0) && (vector->current_size * (2 * GROWTH_FACTOR) <= vector->capacity))
	{
		vector = VectorReserve(vector, vector->current_size * GROWTH_FACTOR);
	}
}



/* exercise 6 */

size_t VectorSize(const vector_t *vector)
{
	assert(NULL != vector);

	return vector->current_size;
}



/* exercise 7 */

size_t VectorCapacity(const vector_t *vector)
{
	assert(NULL != vector);

	return vector->capacity;
}


/* exercise 8 */

vector_t *VectorReserve(vector_t *vector, size_t new_capacity)
{
	vector_t *temp_vector = NULL;

	assert(NULL != vector);
	assert(0 != new_capacity);

	temp_vector = realloc(vector->vector_array, 
							new_capacity * vector->element_size);

	/*temp vector for case it failed and the user vector won't be ruiend */

	if(NULL == temp_vector)
	{
		return NULL;
	}

	vector->vector_array = temp_vector;
	vector->capacity = new_capacity;

	if(vector->current_size > new_capacity)
	{
		vector->current_size = new_capacity;
	}

	return vector;
}



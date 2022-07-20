#ifndef __SLIST_H__
#define __SLIST_H__

#include <stddef.h>  /* size_t */

typedef struct slist slist_t;
typedef struct slist_node* slist_iter_t;   

typedef int (*match_func_t)(const void *data, void *param);
typedef int (*action_func_t)(void *data, void *param);


slist_t *SListCreate(void);

/* DESCRIPTION: 
 * create an empty singly linked list.
 * allocate memory dynamiclly.
 * at the end of use, call for SListDestroy() to free memory.
 *
 * PARAMS: 
 * none
 *	
 * RETURN:
 * slist_t * - 	a pointer to new empty list.
 * 				NULL in case of failure.
 *
 * time complexity: O(1), space complexity O(1).
 */

void SListDestroy(slist_t *slist);

/* DESCRIPTION: 
 * free the memory allocation of a list.
 *
 * PARAMS: 
 * slist *slist - 	pointer to the list.
 *	
 * RETURN:
 * none
 *
 * time complexity: O(n), space complexity O(1).
 */

slist_iter_t SListInsertAfter(slist_iter_t where,const void *data);

/* DESCRIPTION: 
 * create a new element after the given itarator.
 * Warning: insert afetr iterator END will follow an undefied behavier.
 *
 * PARAMS: 
 * slist_iter_t where 	-	an iterator.
 * void *data 			-	the new element's data
 *	
 * RETURN:
 * slist_iter_t 		-	iterator to the new element
 * if failed, return an iterator to the end
 *
 * time complexity: O(1), space complexity O(1)
 */

slist_iter_t SListInsertBefore(const slist_iter_t where, const void *data); 

/* DESCRIPTION: 
 * create a new element before the given itarator 'where'.
 *
 * PARAMS: 
 * slist_iter_t where 	-	an iterator.
 * void *data 			-	the new element's data.
 *	
 * RETURN:
 * slist_iter_t 		-	iterator to the new element.
 * if failed, return an iterator to the end.
 *
 * time complexity: O(1), space complexity O(1).
 */

size_t SListCount(const slist_t *slist);

/* DESCRIPTION: 
 * count the number of elements in the list.
 *
 * PARAMS: 
 * slist_t *slist 	-	list to be counted.
 *	
 * RETURN:
 * size_t 			-	number of elements.
 * 
 * time complexity: O(n), space complexity O(1).
 */

int SListIsEmpty(const slist_t *slist);

/* DESCRIPTION: 
 * checks if a list is empty.
 *
 * PARAMS: 
 * slist_t *slist 	-	list to be checked
 *	
 * RETURN:
 * int 				-	boolean value of an empty list.
 * 						TRUE (1) if list is empty,
 * 						otherwise, FALSE (0).
 * 
 * time complexity: O(1), space complexity O(1).
 */

slist_iter_t SListBegin(const slist_t *slist);

/* DESCRIPTION: 
 * get the first element in the list.
 *
 * PARAMS: 
 * slist_t *slist   -   list
 *
 * RETURN:
 * an iterator for the first elemenet.
 * 
 * time complexity: O(1), space complexity O(1).
 */

slist_iter_t SListEnd(const slist_t *slist); 

/* DESCRIPTION: 
 * get the last element of the list.
 *
 *
 * PARAMS: 
 * slist_t *slist   -   list.
 *  
 *
 * RETURN:
 * an iterator for the last elemenet.
 * 
 * time complexity: O(1), space complexity O(1).
 */

void *SListGetData(const slist_iter_t iterator);

/* DESCRIPTION: 
 * get the data of a givven iterator.
 *
 *
 * PARAMS: 
 * slist_iter_titerator -   iterator.
 *  
 *
 * RETURN:
 * value of the stored data.
 * 
 * time complexity: O(1), space complexity O(1).
 */

void SListSetData(slist_iter_t iterator, const void *data);

/* DESCRIPTION: 
 * set the new date to an iterator.
 *
 *
 * PARAMS: 
 * slist_iter_titerator -   iterator.
 * void *data           -   new data.
 *  
 *
 * RETURN:
 * none
 * 
 * time complexity: O(1), space complexity O(1).
 */

slist_iter_t SListNext(const slist_iter_t iterator);

/* DESCRIPTION: 
 * get the next iterator.
 *
 *
 * PARAMS: 
 * slist_iter_titerator -   iterator.
 *  
 *
 * RETURN:
 * the next iterator.
 * 
 * time complexity: O(1), space complexity O(1).
 */

int SListIsEqual(const slist_iter_t iterator1, const slist_iter_t iterator2);

/* DESCRIPTION: 
 * check if two iterators are equal.
 *
 *
 * PARAMS: 
 * slist_iter_t iterator1   -   first iterator
 * slist_iter_t iterator1   -   second iterator
 *  
 *
 * RETURN:
 * TRUE (1) if iterators are equal.
 * otherwise FALSE (0).
 * 
 * time complexity: O(1), space complexity O(1).
 */

slist_iter_t SListRemove(slist_iter_t iterator);

/* DESCRIPTION: 
 * remove element from the list.
 * Warning : remove iterator END is undefined behavier.
 *
 * PARAMS: 
 * slist_iter_t iterator 	-	iterator to be removed.
 *	
 * RETURN:
 * slist_iter_t 			-	iterator to the next element.
 * 
 * time complexity: O(1), space complexity O(1).
 */

int SListForEach(const slist_iter_t from, const slist_iter_t to, action_func_t action_func, void *param);

/* DESCRIPTION: 
 * iterate the list from "from" to "to", and use an action function from user on each iterator.
 *
 * PARAMS: 
 * slist_iter_t from            -   starting iterator.
 * const slist_iter_t to        -   endind iterator.
 * action_func_t action_func    -   action function.
 * void *param                  -   an argument for action functoin.
 *  
 * RETURN:
 * int 							-	stauts. if succeed return 0. else return user error code.
 * 
 * time complexity: O(n), space complexity O(1).
 */

slist_iter_t SListFind(const slist_iter_t from, const slist_iter_t to, match_func_t is_match, void *param); 

/* DESCRIPTION: 
 * find an iterator with a givven data to compare.
 * search from the iterator "from" to "to".
 *
 *
 * PARAMS: 
 * slist_iter_t from 		-	starting iterator.
 * const slist_iter_t to 	- 	endind iterator.
 * match_func_t is_match 	-	user compare function.
 * void *param 				-	data to be searched.
 *	
 * RETURN:
 * slist_iter_t 			-	iterator with the searched data.
 * 								if not found, return "to" iterator.
 * 
 * time complexity: O(n), space complexity O(1).
 */

void SListAppend(slist_t *dest, slist_t *src);

/* DESCRIPTION: 
 * Append 2 lists.
 * source list becomes an empty list.
 * Warning: append list to itself cause undefined behavier.
 *
 * PARAMS: 
 * slist_t dest    -   destination list.
 * slist_t source  -   source list.
 *  
 *
 * RETURN:
 * none
 * 
 * time complexity: O(1), space complexity O(1)
 */






/* time complexity: O(1), space complexity O(1) */
/* time complexity: O(n), space complexity O(1) */
/* time complexity: O(1), space complexity O(1) */
/* time complexity: O(1), space complexity O(1) */
/* time complexity: O(1), space complexity O(1) */
/* time complexity: O(n), space complexity O(1) */
/* time complexity: O(1), space complexity O(1) */
/* time complexity: O(n), space complexity O(1) */
/* time complexity: O(n), space complexity O(1) */
/* time complexity: O(1), space complexity O(1) */
/* time complexity: O(1), space complexity O(1) */
/* we want the list to work with exactly one dummy for something. after we will read about
dummies we will know what for*/
/* time complexity: O(1), space complexity O(1) */
/* time complexity: O(1), space complexity O(1) */
/* time complexity: O(1), space complexity O(1) */
/* time complexity: O(1), space complexity O(1) */

#endif /* __SLIST_H__ */
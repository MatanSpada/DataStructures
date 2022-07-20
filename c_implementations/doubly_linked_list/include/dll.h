#ifndef __DLIST_H__
#define __DLIST_H__

#include <stddef.h> /* size_t */




typedef struct dlist dlist_t;
typedef struct dlist_node* dlist_iter_t;
typedef int (*match_func_t)(const void *data, const void *param);
typedef int (*action_func_t)(void *data, void *param);

dlist_t *DListCreate(void);

/* DESCRIPTION: 
 * create an empty doubly linked list.
 * allocate memory dynamiclly.
 * at the end of use, call for SListDestroy() to free memory.
 *
 * PARAMS: 
 * none
 *	
 * RETURN:
 * dlist_t * -	pointer to new empty list.
 * NULL in case of failure.
 *
 * time complexity: O(1), space complexity O(1).
 */


void DListDestroy(dlist_t *dll);

/* DESCRIPTION: 
 * free the memory allocation of a list.
 *
 *
 * PARAMS: 
 * slist *slist 	-	pointer to the list.
 *	
 * RETURN:
 * none
 *
 * time complexity: O(n), space complexity O(1).
 */

int DListIsEmpty(const dlist_t *dll);

/* DESCRIPTION: 
 * return TRUE (1) if list is empty,
 * otherwise, FALSE (0)
 *
 *
 * PARAMS: 
 * dlist_t *slist 	-	list to be checked
 *	
 * RETURN:
 * TRUE/FALSE
 * 
 * time complexity: O(1), space complexity O(1)
*/

size_t DListSize(const dlist_t *dll);

/* DESCRIPTION: 
 * count the number of elements in the list.
 *
 *
 * PARAMS: 
 * dlist_t *slist 	-	list to be counted.
 *	
 * RETURN:
 * size_t 			-	number of elements.
 * 
 * time complexity: O(n), space complexity O(1).
 */


dlist_iter_t DListInsert(dlist_iter_t iter, void *data);

/* DESCRIPTION: 
 * create and insert new element before given itarator.
 *
 *
 * PARAMS: 
 * slist_iter_t where 	-	iterator of the list.
 * void *data 			-	the new element's data.
 *	
 * RETURN:
 * slist_iter_t 		-	iterator to the new element.
 * if fail, return iterator to the end.
 *
 * time complexity: O(1), space complexity O(1)
 */

dlist_iter_t DListRemove(dlist_iter_t iter);

/* DESCRIPTION: 
 * remove the element of given itarator.
 * Warning : remove end iterator is undefined behavier.
 *
 * PARAMS: 
 * slist_iter_t where 	-	iterator of the list.
 *	
 * RETURN:
 * slist_iter_t 		-	iterator to the next element.
 * 
 * time complexity: O(1), space complexity O(1).
 */

dlist_iter_t DListPushFront(dlist_t *dll, void *data);

/* DESCRIPTION: 
 * create and insert new element as first element of the list.
 *
 *
 * PARAMS: 
 * dlist_t *list 	-	the list
 * void *data 		-	the new element's data
 *	
 * RETURN:
 * slist_iter_t 	-	iterator to the new element
 * if fail, return iterator to the end
 *
 * time complexity: O(1), space complexity O(1)
 */

dlist_iter_t DListPushBack(dlist_t *dll, void *data);

/* DESCRIPTION: 
 * create new element as last element of the list.
 *
 *
 * PARAMS: 
 * dlist_t *list 	-	the list.
 * void *data 		-	the new element's data.
 *	
 * RETURN:
 * slist_iter_t 	-	iterator to the new element.
 * if fail, return iterator to the end.
 *
 * time complexity: O(1), space complexity O(1)
 */

void *DListPopFront(dlist_t *dll);

/* DESCRIPTION: 
 * get the data of first element of given list, and remove it.
 * Warning : pop with empty list wiil cause undefiend behavier.
 *
 * PARAMS: 
 * dlist_t *list 	-	the list.
 *	
 * RETURN:
 * void * 			-	data of the removed element
 * 
 * time complexity: O(1), space complexity O(1)
 */

void *DListPopBack(dlist_t *dll);

/* DESCRIPTION: 
 * get the data of last element of given list, and remove it.
 * Warning : pop with empty list wiil cause undefiend behavier .
 *
 * PARAMS: 
 * dlist_t *list 	-	the list
 *	
 * RETURN:
 * void *		 	-	data of the removed element
 * 
 * time complexity: O(1), space complexity O(1)
 */

void DListSplice(dlist_iter_t where, dlist_iter_t from, dlist_iter_t to);
/*



*/
dlist_iter_t DListBegin(const dlist_t *dll);

/* DESCRIPTION: 
 * get the begin iterator of the list
 *
 *
 * PARAMS: 
 * dlist_t *slist   -   list
 *  
 *
 * RETURN:
 * begin iterator
 * 
 * time complexity: O(1), space complexity O(1)
 */

dlist_iter_t DListEnd(const dlist_t *dll);

/* DESCRIPTION: 
 * get the end iterator of the list
 *
 *
 * PARAMS: 
 * dlist_t *slist   -   list
 *  
 *
 * RETURN:
 * an iterator to EOL.
 * 
 * time complexity: O(1), space complexity O(1)
*/

dlist_iter_t DListNext(dlist_iter_t iter);

/* DESCRIPTION: 
 * get the next iterator
 *
 *
 * PARAMS: 
 * slist_iter_titerator -   iterator
 *  
 *
 * RETURN:
 * the next iterator
 * 
 * time complexity: O(1), space complexity O(1)
*/

dlist_iter_t DListPrev(dlist_iter_t iter);

/* DESCRIPTION: 
 * get the previous iterator
 *
 *
 * PARAMS: 
 * slist_iter_titerator -   iterator
 *  
 *
 * RETURN:
 * the previous iterator
 * 
 * time complexity: O(1), space complexity O(1)
 */

void *DListGetData(dlist_iter_t iter);

/* DESCRIPTION: 
 * get the data of the iterator
 *
 *
 * PARAMS: 
 * slist_iter_titerator -   iterator
 *  
 *
 * RETURN:
 * value of the stored data
 * 
 * time complexity: O(1), space complexity O(1)
 */

int DListIsEqual(dlist_iter_t iter1, dlist_iter_t iter2);

/* DESCRIPTION: 
 * check if the two iterators are equal
 *
 *
 * PARAMS: 
 * slist_iter_t iterator1   -   first iterator
 * slist_iter_t iterator1   -   second iterator
 *  
 *
 * RETURN:
 * TRUE (1) if the iterator are equal,
 * otherwise FALSE (0)
 * 
 * time complexity: O(1), space complexity O(1)
 */


dlist_iter_t DListFind(dlist_iter_t from, dlist_iter_t to,
	match_func_t is_match, void *param);

/* DESCRIPTION: 
 * find iterator with data equal to input.
 * search from the iterator "from" to "to".
 * Using user compare function 
 *
 *
 * PARAMS: 
 * slist_iter_t from        -   starting iterator
 * const slist_iter_t to    -   endind iterator
 * match_func_t is_match    -   user compare function
 * void *param              -   data to be searched
 *  
 * RETURN:
 * slist_iter_t             -   iterator with the searched data
 * if not found, return "to" iterator
 * 
 * time complexity: O(n), space complexity O(1)
 */



int DListMultiFind(dlist_iter_t from, dlist_iter_t to,
	match_func_t is_match, void *param, dlist_t *result_list);

/* DESCRIPTION: 
 * find iterator with data equal to input.
 * search from the iterator "from" to "to".
 * Using user compare function 
 *
 *
 * PARAMS: 
 * slist_iter_t from        -   starting iterator
 * const slist_iter_t to    -   endind iterator
 * match_func_t is_match    -   user compare function
 * void *param              -   data to be searched
 * dlist_t result list      -   list of copies of the found element.
 *                              push new found element to the end of the list.
 *
 *  
 * RETURN:
 * int                      -   if succeed, return 0.
 * 
 * time complexity: O(n), space complexity O(1)
 */


int DListForEach(dlist_iter_t from, dlist_iter_t to,
	action_func_t action_func, void *param);

/* DESCRIPTION: 
 * iterate each iterators from "from" to "to", and use action function with the data
 * Using user action function 
 *
 *
 * PARAMS: 
 * slist_iter_t from            -   starting iterator
 * const slist_iter_t to        -   endind iterator
 * action_func_t action_func    -   action function
 * void *param                  -   additional input for action functoin
 *  
 * RETURN:
 * int                          -   stauts. if succeed return 0. else return user error code.
 * 
 * time complexity: O(n), space complexity O(1)
 */



#endif /* __DLIST_H__ */
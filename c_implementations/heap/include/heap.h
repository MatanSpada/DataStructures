#ifndef __HEAP_H__
#define __HEAP_H__

#include <stddef.h>     /* size_t */

typedef struct heap heap_t;
typedef int (*heap_cmp_func_t)(const void *data1, const void *data2);
typedef int (*heap_is_match_func_t)(const void *element, const void *param);


/* Heap:
*  Heap is a data structure used to store and retrieve elements in O(log n) and get O(1) access to 
*  max/min value with HeapPeek.


/* DESCRIPTION: 
 *  Create a new heap
 *
 * PARAMS: 
 * 	Compare function		- provided by user and built according to function pointer signature above.
 *
 * RETURN:
 *  pointer to the new heap.
 *  NULL will be returned in case of failure.
 *
 * Time complexity O(1) 
 * Space complexity O(1)
 */
heap_t *HeapCreate(heap_cmp_func_t comp_func); 



/* DESCRIPTION: 
 *  Destroy given heap.
 *
 * PARAMS: 
 *  Heap to destroy.
 *
 * RETURN:
 *  None.
 *
 * Time complexity O(1). 
 * Space complexity O(1).
 */
void HeapDestroy(heap_t *heap);



/* DESCRIPTION: 
 *  Push a new element to heap.
 *
 * PARAMS: 
 *  Heap to push into
 *  Data to push
 *
 * RETURN:
 *  0 - Success
 *  1 - Failure 
 *
 * Time complexity O(log n) 
 * Space complexity O(1)
 */
int HeapPush(heap_t *heap, void *data);



/* DESCRIPTION: 
 *  remove the top of heap (min / max element).
 *
 * PARAMS: 
 *  Heap to pop.
 *
 * RETURN:
 *  None.
 *
 * Time complexity O(log n). 
 * Space complexity O(1).
 */
void HeapPop(heap_t *heap);



/* DESCRIPTION: 
 *  Get the element in top of heap
 *
 * PARAMS: 
 *  Heap to peek into.
 *
 * RETURN:
 *  Data of element.
 *
 * Time complexity O(1).
 * Space complexity O(1).
 */
void *HeapPeek(const heap_t *heap);



/* DESCRIPTION: 
 *  Get size of heap
 *
 * PARAMS: 
 *  Heap to check
 *
 * RETURN:
 *  Size of heap
 *
 * Time complexity O(1) 
 * Space complexity O(1)
 */

size_t HeapSize(const heap_t *heap);



/* DESCRIPTION: 
 *  Check whether a heap is empty
 *
 * PARAMS: 
 *  Heap to check
 *
 * RETURN:
 *  1 - Heap is empty
 *  0 - Heap is not empty
 *
 * Time complexity O(1) 
 * Space complexity O(1)
 */
int HeapIsEmpty(const heap_t *heap);



/* DESCRIPTION: 
 *  Remove an element from heap
 *   an attempt to remove non existing element 
 *   will result in undefined behaviour
 *
 * PARAMS: 
 *  - Heap to remove from
 *  - Match function built according to function pointer above
 *  - Value to compare to
 *
 * RETURN:
 *  Reference to element removed
 *
 * Time complexity  O(n) (for the search)
 *                  O(log n) (for removal)
 * Space complexity O(1)
 */
void *HeapRemove(heap_t *heap, heap_is_match_func_t match_func, void *param);

void PrintHeapArr(heap_t *heap);

#endif /* __HEAP_H__ */
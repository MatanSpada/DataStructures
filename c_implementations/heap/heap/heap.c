/***********************************
 * heap Source code                *
 * Developer: Matan Spada          *
 * Written: 2022-02-08             *
 *                                 *
 * Approved by:      Dor           *
 ***********************************/

#include <stdlib.h>                             /* malloc(), calloc(), NULL*/
#include <assert.h>                             /* assert() */
#include <stdio.h>                              /* print */
#include "../include/heap.h"                    /* header file */
#include "../include/dynamic_vector.h"          /* vector API */

#define FAILURE (-1)
#define SUCCESS (0)
#define INIT_VEC_SIZE (16)
#define ROOT (0)
#define LEFT_CHILD(index) ((index) * (2)) + (1)
#define RIGHT_CHILD(index) ((index) * (2)) + (2)
#define PARENT(index) ((index - 1) / 2)


struct heap
{
    heap_cmp_func_t cmp_func;
    vector_t *vec;
};



/******************* Auxilary Functions **********************/
static void HeapifyDown(heap_t *heap, size_t index);
static void HeapifyUp(heap_t *heap, size_t index);
static void PointerSwap(void **x, void **y);
static size_t LeftChildOnlyHeapify(heap_t *heap, size_t index);
static int HeapFind(heap_t *heap, heap_is_match_func_t match_func, void *data);
static size_t HeapifyCorrectChild(heap_t *heap, size_t index, int cmp_left, int cmp_right, void **root, void **left_child, void **right_child);
/*************************************************************/


/******************* Exercise Functions **********************/

heap_t *HeapCreate(heap_cmp_func_t comp_func)
{
    heap_t *heap = NULL;

    assert(NULL != comp_func);

    heap = (heap_t *)malloc(sizeof(heap_t) * sizeof(char));
    if (NULL == heap)
    {
        return (NULL);
    }

    heap->vec = VectorCreate(sizeof(void *), INIT_VEC_SIZE);
    if (NULL == heap->vec)
    {
        free(heap); 
        heap = NULL;
        
        return (NULL);
    }

    heap->cmp_func = comp_func;

    return (heap);
}



void HeapDestroy(heap_t *heap)
{
    assert(heap);

    VectorDestroy(heap->vec);
    heap->vec = NULL;

    free(heap);
    heap = NULL;
}



int HeapPush(heap_t *heap, void *data)
{
    assert(NULL != heap);
    assert(NULL != data);

    if (FAILURE == VectorPushBack(heap->vec, &data))
    {
        return (FAILURE);
    }

    HeapifyUp(heap, HeapSize(heap) - 1);

    return (SUCCESS);
}



void HeapPop(heap_t *heap)
{
    size_t last_element_index = 0;
    void **root = NULL;
    void **last_element = NULL;

    assert(NULL != heap);

    last_element_index = VectorSize(heap->vec) - 1;
    last_element = VectorGetAccessToElement(heap->vec, last_element_index);
    root = VectorGetAccessToElement(heap->vec, ROOT);

    PointerSwap(root, last_element);
    VectorPopBack(heap->vec);
    HeapifyDown(heap, ROOT);
}



void *HeapPeek(const heap_t *heap)
{
    assert(!HeapIsEmpty(heap));

    return (*(void **)VectorGetAccessToElement(heap->vec, 0));
}



size_t HeapSize(const heap_t *heap)
{
    assert(NULL != heap);

    return (VectorSize(heap->vec));
}



int HeapIsEmpty(const heap_t *heap)
{
    assert(NULL != heap);

    return (0 == VectorSize(heap->vec));
}



void *HeapRemove(heap_t *heap, heap_is_match_func_t match_func, void *param)
{
    int found_element_index = 0;
    size_t last_element_index = HeapSize(heap) - 1;
    void **last_element = NULL;
    void **element_to_remove = NULL;
    void *data_to_return = NULL;

    assert(NULL != heap);
    assert(NULL != match_func);

    found_element_index = HeapFind(heap, match_func, param);

    if (FAILURE != found_element_index)
    {
        element_to_remove = (void **)VectorGetAccessToElement(heap->vec, found_element_index);
        last_element = VectorGetAccessToElement(heap->vec, last_element_index);
        data_to_return = *element_to_remove;
        PointerSwap(element_to_remove, last_element);

        VectorPopBack(heap->vec);

        if(found_element_index < last_element_index)
        {
            HeapifyDown(heap, found_element_index);
            HeapifyUp(heap, found_element_index);            
        }

        return (data_to_return);
    }

    return NULL;
}



/******************* Auxilary Functions **********************/

static void HeapifyDown(heap_t *heap, size_t index)
{
    void **left_child = NULL;
    void **right_child = NULL;
    void **root = NULL;
    int cmp_left = 0;
    int cmp_right = 0;

    while (LEFT_CHILD(index) < VectorSize(heap->vec))
    {
        root = VectorGetAccessToElement(heap->vec, index);
        left_child = VectorGetAccessToElement(heap->vec, LEFT_CHILD(index));

        if (RIGHT_CHILD(index) < VectorSize(heap->vec))
        {
            right_child = VectorGetAccessToElement(heap->vec, RIGHT_CHILD(index));
            cmp_left = heap->cmp_func(*left_child, *root);
            cmp_right = heap->cmp_func(*right_child, *root);
            index = HeapifyCorrectChild(heap, index, cmp_left, cmp_right, root, left_child, right_child);
        }
        else
        {
            index = LeftChildOnlyHeapify(heap, index);
        }   
    }
}


static size_t HeapifyCorrectChild(heap_t *heap, size_t index, int cmp_left, int cmp_right, void **root, void **left_child, void **right_child)
{
    if (cmp_left > 0 && cmp_right > 0)
    {
        index = VectorSize(heap->vec);
    }
    else if (cmp_left < cmp_right)
    {
        PointerSwap(root, left_child);
        index = LEFT_CHILD(index);
    }
    else
    {
        PointerSwap(root, right_child);
        index = RIGHT_CHILD(index);
    }

    return index;
}




static size_t LeftChildOnlyHeapify(heap_t *heap, size_t index)
{
    void **left_child = VectorGetAccessToElement(heap->vec, LEFT_CHILD(index));
    void **root = VectorGetAccessToElement(heap->vec, index);
    int cmp = heap->cmp_func(*left_child, *root);
    if (cmp < 0)
    {
        PointerSwap(left_child, root);
    }

    return VectorSize(heap->vec);
}



static void HeapifyUp(heap_t *heap, size_t index)
{
    void **current = NULL;
    void **parent = NULL;

    while(0 < index)
    {
        current = VectorGetAccessToElement(heap->vec, index);
        parent = VectorGetAccessToElement(heap->vec, PARENT(index));

        if((heap->cmp_func(*current, *parent)) < 0)
        {
            PointerSwap(parent, current);
            index = PARENT(index);
        }

        else
        {
            index = 0;
        }
    }
}



static void PointerSwap(void **x, void **y)
{
    void *temp = *x;
    *x = *y;
    *y = temp;
}



static int HeapFind(heap_t *heap, heap_is_match_func_t match_func, void *data)
{
    size_t i = 0;
    size_t vec_size = VectorSize(heap->vec);
    void **current_data = NULL;

    for(i = ROOT; i < vec_size; ++i)
    {
        current_data = VectorGetAccessToElement(heap->vec, i);

        if(1 == match_func(*current_data, data))
        {
            return (i);
        }
    }

    return (FAILURE);
}



/* different casting */
/*static int HeapFind(heap_t *heap, heap_is_match_func_t match_func, void *data)
{
    size_t i = 0;
    size_t size = VectorSize(heap->vec);
    void *current_data = NULL;

    for(i = ROOT; i < size; ++i)
    {
        current_data = *(void **)VectorGetAccessToElement(heap->vec, i);

        if(0 == match_func(current_data, data))
        {
            return (i);
        }
    }

    return FAILURE;
}*/


#ifdef DEBUG
void PrintHeapArr(heap_t *heap)
{
    size_t i = 0;

    printf("heap: {");
    for (i = 0; i < VectorSize(heap->vec); ++i)
    {
        printf("%d, ", **(int **)VectorGetAccessToElement(heap->vec, i));
    }
    printf("}\n");

}
#endif
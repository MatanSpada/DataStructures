/***********************************
 * Bst Source code                 *
 * Developer: Matan Spada          *
 * Written: 2022-01-18             *
 *                                 *
 * Approved by:   Ofer             *
 ***********************************/

#include <stdlib.h>                     /* malloc(), calloc(), NULL*/
#include <assert.h>                     /* assert() */
#include "../include/bst.h"             /* header file */

#define ROOT(tree) (tree->root_stub.children[LEFT])
#define RIGHT(node) ((node)->children[RIGHT])
#define LEFT(node) ((node)->children[LEFT])
#define PARENT(node) ((node)->parent)
#define WHICH_CHILD(node) (NULL != node->children[RIGHT])
#define IS_RIGHT(node) (node == node->parent->children[RIGHT])
#define CMP(tree, node, data) (tree->cmp(data, node->data))
#define SUCCESS (0)

/* managing struct */
typedef struct bst_node bst_node_t;

typedef enum children
{
    LEFT,
    RIGHT,
    NUM_OF_CHILDREN
}children;


struct bst_node
{
    void *data;
    bst_node_t *parent;
    bst_node_t *children[NUM_OF_CHILDREN];
};


struct bst
{
    bst_node_t root_stub;       /* dummy */
    bst_cmp_func_t cmp;
};



/******************* Auxilary Functions **********************/
static int HaveTwoChildren(bst_iter_t iter);
/*************************************************************/



/******************* Exercise Functions **********************/

bst_t *BSTCreate(bst_cmp_func_t cmp_func)
{
    bst_t *new_bst = NULL;

    assert(NULL != cmp_func);

    new_bst = (bst_t *)calloc(sizeof(bst_t), sizeof(char));
    if(NULL == new_bst)
    {
        return NULL;
    }

    new_bst->cmp = cmp_func;
     
    return new_bst;
}



void BSTDestroy(bst_t *tree)
{
    bst_iter_t next = NULL;
    bst_iter_t runner = NULL;

    assert(NULL != tree);

    runner = BSTBegin(tree);

    while (!BSTIsEmpty(tree))  
    {
        next = BSTNext(runner);
        BSTRemove(runner);
        runner = next;
    }  
    
    free(tree); 
    tree = NULL;
}



size_t BSTSize(const bst_t *tree)
{
    bst_iter_t runner = BSTBegin(tree);
    bst_iter_t end = BSTEnd(tree);
    size_t count = 0;

    assert(NULL !=  tree);

    while (!BSTIterIsEqual(runner, end))
    {
        ++count;
        runner = BSTNext(runner);
    }

    return count;
}



int BSTIsEmpty(const bst_t *tree)
{
    assert(NULL != tree);

    return (NULL == ROOT(tree));
}



bst_iter_t BSTInsert(bst_t *tree, void *data)
{
    bst_node_t *new_node = NULL;
    bst_node_t *runner = NULL;    
    bst_node_t *parent = NULL;    
    int CMP_result = 0;

    assert(NULL != tree);

    new_node = (bst_node_t *)calloc(sizeof(char), sizeof(bst_node_t));
    if(NULL == new_node)
    {
        return BSTEnd(tree);
    }

    new_node->data = data;
    runner = ROOT(tree);
    parent = &tree->root_stub;

    while(NULL != runner)
    {
        parent = runner;    
        runner = (0 < (CMP_result = CMP(tree, runner, data))) ? RIGHT(runner) : LEFT(runner);
        assert(0 != CMP_result);
    }

    PARENT(new_node) = parent;
    (0 < CMP_result) ? (RIGHT(parent) = new_node) : (LEFT(parent) = new_node);

    return new_node;
}



void BSTRemove(bst_iter_t iter)
{
    int child = 0;

    assert(NULL != iter);

    if (HaveTwoChildren(iter))
    {
        iter->data = (BSTNext(iter))->data;
        iter = BSTNext(iter);
    }

    child = WHICH_CHILD(iter);                                                  /*1 if RIGHT child exsit*/
    iter->parent->children[IS_RIGHT(iter)] = iter->children[child];             /*UPDATE parent point to child*/          

    if (NULL != iter->children[child])                                          /*only if child exist*/
    {
        iter->children[child]->parent = iter->parent;                           /*child points to parent*/
    }

    free(iter); 
    iter = NULL;
}




bst_iter_t BSTBegin(const bst_t *tree)
{
    bst_iter_t runner = NULL;

    assert(NULL != tree);

    runner = (bst_iter_t)&tree->root_stub;

    while (NULL != LEFT(runner))
    {
        runner = LEFT(runner);
    }

    return (runner);
}



bst_iter_t BSTEnd(const bst_t *tree)
{
    assert(NULL != tree);

    return (bst_iter_t)&(tree->root_stub);    
}



bst_iter_t BSTPrev(bst_iter_t iter)
{
    bst_iter_t child = NULL;

    if (NULL != LEFT(iter))         /*if RIGHT chlild exsit*/
    {
        for(iter = LEFT(iter); NULL != RIGHT(iter); iter = RIGHT(iter));
    }
    else
    {
        do
        {
            child = iter;
            iter = PARENT(iter);
        }
        while (LEFT(iter) == child);

    }

    return (iter); 
}



bst_iter_t BSTNext(bst_iter_t iter)                     
{
    bst_iter_t child = NULL;

    if (NULL != RIGHT(iter))
    {
        for(iter = RIGHT(iter); NULL != LEFT(iter); iter = LEFT(iter));
    }
    else
    {
        do
        {
            child = iter;
            iter = PARENT(iter);
        }
        while(iter->children[RIGHT] == child);

    }

    return iter; 
}



int BSTIterIsEqual(bst_iter_t iter1, bst_iter_t iter2)
{
    assert(NULL != iter1);
    assert(NULL != iter2);

    return (iter1 == iter2);
}



void *BSTGetData(bst_iter_t iter)
{
    assert(NULL != iter);

    return (iter->data);
}



bst_iter_t BSTFind(const bst_t *tree, void *data)
{
    int cmp_result = 0;
    bst_iter_t iter = NULL;

    assert(NULL != tree);

    iter = ROOT(tree);

    while(NULL != iter && 0 != (cmp_result = tree->cmp(BSTGetData(iter), data)))
    {
        iter = (0 < cmp_result) ? LEFT(iter) : RIGHT(iter);
    }

    return (0 == cmp_result ? iter : BSTEnd(tree));
}



int BSTForEach(bst_iter_t from, bst_iter_t to, bst_action_func_t action_func, void *param)
{
    bst_iter_t runner = from;
    int status = SUCCESS;

    assert(NULL != from);
    assert(NULL != to);

    while ((runner != to) && (SUCCESS == status))
    {
        status = action_func(BSTGetData(runner), param);
        runner = BSTNext(runner);
    }

    return status;
}




/******************* Auxilary Functions **********************/

static int HaveTwoChildren(bst_iter_t iter)
{
    return (NULL != RIGHT(iter) && NULL != LEFT(iter));
}
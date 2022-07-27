/***********************************
 * AVL Source code                 *
 * Developer: Matan Spada          *
 * Written: 2022-01-18             *
 *                                 *
 * Approved by:       polina       *
 ***********************************/

#include <stdlib.h>                     /* malloc(), calloc(), NULL*/
#include <assert.h>                     /* assert() */
#include <stdio.h>                      /*  */
#include "../include/avl.h"             /* header file */


#define LEAF_HEIGHT (1)
#define FAILURE (-1)
#define SUCCESS (0)
#define MAX(a,b) ((a > b) ? (a) : (b))
#define GET_HEIGHT(node) ((NULL == node) ? 0 : node->height)
#define UPADTE_HEIGHT(node) (1 + MAX(GET_HEIGHT(node->children[LEFT]), GET_HEIGHT(node->children[RIGHT])))
#define WHICH_CHILD(node) (NULL != node->children[RIGHT])
#define BALANCE_TO(bal_fac) (LEFT_UNBALANCED == (bal_fac))
#define IS_UNBALANCED(bal_fac) (RIGHT_UNBALANCED == (bal_fac) || LEFT_UNBALANCED == (bal_fac))
#define OTHER_SIDE(side) (!side) /* ((LEFT == side) ? RIGHT: LEFT) */

#define GET_BALANCE_FACTOR(node) (NULL == node) ? BALANCED :\
    GET_HEIGHT(node->children[RIGHT]) - GET_HEIGHT(node->children[LEFT])

#define IS_PARENT_FOR_TWO(node) ((NULL != node->children[LEFT]) &&\
                                 (NULL != node->children[RIGHT]))

#define IS_CHILD_HEAVY(child_bal_fac, dir) (((LEFT == (dir)) && ((size_t)LEFT_HEAVY == (child_bal_fac))) ||\
                                 ((RIGHT == (dir)) && ((size_t)RIGHT_HEAVY == (child_bal_fac))))


typedef struct avl_node avl_node_t;
typedef int (*order_func_t)(avl_node_t *, avl_action_func_t, void *);


typedef enum children
{
    LEFT,
    RIGHT,
    NUM_CHILDREN
}child_t;


typedef enum balance_factor
{
    LEFT_UNBALANCED = -2,
    LEFT_HEAVY,
    BALANCED,
    RIGHT_HEAVY,
    RIGHT_UNBALANCED
} balance_t;


struct avl_node
{
    void *data;
    size_t height;
    avl_node_t *children[NUM_CHILDREN];
};


struct avl
{
    avl_node_t *root;
    avl_cmp_func_t cmp_func;
};



/******************* Auxilary Functions **********************/
static void DestroyTree(avl_node_t *node);
static avl_node_t *FindData(const avl_node_t *node, const void *data, avl_cmp_func_t cmp_func);
static size_t CountTree(avl_node_t *node);
static avl_node_t *CreateNode(void *data, int *status);
static avl_node_t *InsertNode(avl_node_t *node, void *data, avl_cmp_func_t cmp_func, int *status);
static int PreOrderFE(avl_node_t *root, avl_action_func_t action_func, void *param);
static int InOrderFE(avl_node_t *root, avl_action_func_t action_func, void *param);
static int PostOrderFE(avl_node_t *root, avl_action_func_t action_func, void *param);
static avl_node_t *RemoveThisNode(avl_node_t *node);
static avl_node_t *AVLNext(avl_node_t *child);
static avl_node_t *RemoveNode(avl_node_t *node, avl_cmp_func_t cmp_func, const void *data);
static avl_node_t *BalanceNode(avl_node_t *node);
static avl_node_t *RotateSide(avl_node_t *node, child_t side);
static void PrintTreeCurrLevel(avl_node_t *root, int level);
/*************************************************************/




/******************* Exercise Functions **********************/

avl_t *AVLCreate(avl_cmp_func_t cmp_func)
{
    avl_t *tree = NULL;

    assert(NULL != cmp_func);

    tree = (avl_t *)calloc(sizeof(avl_t), sizeof(char));
    if(NULL == tree)
    {
        return NULL;
    }

    tree->cmp_func = cmp_func;
     
    return (tree);
}



void AVLDestroy(avl_t *tree)
{
    assert(NULL != tree);
    
    DestroyTree(tree->root);

    free(tree);
    tree = NULL;
}



size_t AVLSize(const avl_t *tree)
{
    assert(NULL != tree);

    if(NULL == tree->root)
    {
        return 0UL;
    }

    return (CountTree(tree->root));
}



int AVLIsEmpty(const avl_t *tree)
{
    /*assert(NULL != tree->root);*/

    return (NULL == tree->root);
}



int AVLInsert(avl_t *tree, void *data)
{
    int status = SUCCESS ;

    assert(NULL != tree);

    tree->root = InsertNode(tree->root, data, tree->cmp_func, &status);

    return status;
}



void AVLRemove(avl_t *tree, const void *data)              
{
    assert(NULL != tree);

    if (!AVLIsEmpty(tree))
    {
        tree->root = RemoveNode(tree->root, tree->cmp_func, data);
    }
}



size_t AVLHeight(const avl_t *tree)
{
    assert(NULL != tree);

    return (AVLIsEmpty(tree) ? 0UL : tree->root->height);
}



void *AVLFind(const avl_t *tree, const void *data)
{
    avl_node_t *found_node = NULL;

    assert(NULL != tree);

    found_node = FindData(tree->root, data, tree->cmp_func);

    return ((NULL == found_node) ? (NULL) : (found_node->data));
}




int AVLForEach(avl_t *tree, avl_action_func_t action_func, void *param, order_t order)
{   
    static order_func_t fe_funcs_lut[] = {&PreOrderFE, &InOrderFE, &PostOrderFE};

    assert(tree);
    assert(action_func);
    
    return fe_funcs_lut[order](tree->root, action_func, param);
}



/******************* Auxilary Functions **********************/

static int PreOrderFE(avl_node_t *root, avl_action_func_t action_func, void *param)     /* dad first (root) */
{
    if (root)
    {
        if (FAILURE == action_func(root->data, param))
        {
            return FAILURE;
        }

        PreOrderFE(root->children[LEFT], action_func, param);
        PreOrderFE(root->children[RIGHT], action_func, param);
    }

    return SUCCESS;
}



static int InOrderFE(avl_node_t *root, avl_action_func_t action_func, void *param)      /* by size */
{
    if (root)
    {
        InOrderFE(root->children[LEFT], action_func, param);

        if (FAILURE == action_func(root->data, param))
        {
            return FAILURE;
        }

        InOrderFE(root->children[RIGHT], action_func, param);
    }

    return SUCCESS;     
}



static int PostOrderFE(avl_node_t *root, avl_action_func_t action_func, void *param)    /* children first (sub-trees) */
{
    if (root)
    {
        PostOrderFE(root->children[LEFT], action_func, param);
        PostOrderFE(root->children[RIGHT], action_func, param);

        if (FAILURE == action_func(root->data, param))
        {
            return FAILURE;
        }
    }

    return SUCCESS;    
}



static avl_node_t *FindData(const avl_node_t *node, const void *data, avl_cmp_func_t cmp_func)
{
    int cmp_result = 0;
    int next_child = 0;

    if(NULL == node)
    {
        return NULL;
    }

    cmp_result = cmp_func(data, node->data);

    if(0 == cmp_result)
    {
        return (avl_node_t *)node;
    }

    (0 > cmp_result) ? (next_child = LEFT) : (next_child = RIGHT);
    
    return (FindData(node->children[next_child], data, cmp_func));    
}




static avl_node_t *InsertNode(avl_node_t *node, void *data, avl_cmp_func_t cmp_func, int *status)
{
    int cmp_result = 0;
    enum children next_child = LEFT;

    if(NULL == node)
    {
        node = CreateNode(data, status);
        return ((SUCCESS == *status) ? (node) : (NULL));
    }

    cmp_result = cmp_func(data, node->data);
    assert(0 != cmp_result);

    (0 > cmp_result) ? (next_child = LEFT) : (next_child = RIGHT);
    node->children[next_child] = InsertNode(node->children[next_child], 
                                            data, cmp_func, status);

    node->height = UPADTE_HEIGHT(node);

    return BalanceNode(node);
}



static avl_node_t *CreateNode(void *data, int *status)
{
    avl_node_t *new_node = (avl_node_t *)calloc(sizeof(avl_node_t), sizeof(char));
    if(NULL == new_node)
    {
        *status = FAILURE;
        return NULL;
    }

    new_node->data = data;
    new_node->height = LEAF_HEIGHT;

    *status = SUCCESS;

    return new_node;
}



static void DestroyTree(avl_node_t *node)
{
    if(NULL == node)
    {
        return;
    }

    DestroyTree(node->children[LEFT]);
    DestroyTree(node->children[RIGHT]);

    free(node);
    node = NULL;
}



static size_t CountTree(avl_node_t *node)
{
    if(NULL == node)
    {
        return 0UL;
    }

    return (CountTree(node->children[LEFT]) + CountTree(node->children[RIGHT]) + 1);    
}



static avl_node_t *AVLNext(avl_node_t *child)
{
  if (NULL == child->children[LEFT])
  {
       return child;
  }

  return AVLNext(child->children[LEFT]);
}



static avl_node_t *RemoveThisNode(avl_node_t *node)
{
    avl_node_t *child_keeper = node->children[WHICH_CHILD(node)];   /*returns enum LEFT or RIGHT*/

    free(node); 
    node = NULL;

    return child_keeper;        /* to update the father of the removal node to be the father of its child */
}



static avl_node_t *RemoveNode(avl_node_t *node, avl_cmp_func_t cmp_func, 
                                                         const void *data)
{
    if (NULL != node)
    {
        int cmp_result = cmp_func(node->data, data);
        enum children next_child = 2;

        if (0 == cmp_result)
        {   
            if (!IS_PARENT_FOR_TWO(node))   /* make sure the node has no children or one */
            {
                return RemoveThisNode(node); 
            }

            node->data = AVLNext(node->children[RIGHT])->data;      /* define one of the children is the new father */
            data = node->data;
        }
        next_child = (0 >= cmp_result);  /* by enum */
        node->children[next_child] = RemoveNode(node->children[next_child], cmp_func, data);
        node->height = UPADTE_HEIGHT(node);
    }

    return (BalanceNode(node));
}



static avl_node_t *BalanceNode(avl_node_t *node)
{
    balance_t balance_factor = GET_BALANCE_FACTOR(node);                    /* right balanced is from -1 to +1 */
    
    if (IS_UNBALANCED(balance_factor))                                      /* if RIGHT || LEFT == balance_factor */
    {
        int side_to_balance = BALANCE_TO(balance_factor);                   /* return 1 if LEFT UNBALANCED */
        avl_node_t *pivot = node->children[!side_to_balance];

        if(IS_CHILD_HEAVY(GET_BALANCE_FACTOR(pivot), side_to_balance))      /*who heavier to know the direction*/
        {
            node->children[!side_to_balance] = RotateSide(pivot, !side_to_balance);           
        }

        node = RotateSide(node, side_to_balance);
        node->height = UPADTE_HEIGHT(node);
    }
    
    return node;
}


static avl_node_t *RotateSide(avl_node_t *node, child_t side)
{
    avl_node_t *pivot = node->children[OTHER_SIDE(side)];

    node->children[OTHER_SIDE(side)] = pivot->children[side];
    pivot->children[side] = node;

    node->height = UPADTE_HEIGHT(node);
    pivot->height = UPADTE_HEIGHT(pivot);

    return pivot;
}


void PrintTreeByLevels(avl_t *tree)
{ 
    size_t h = AVLHeight(tree);
    int i = 1;

    for (i = 1; i <= (int)h; ++i)
    {
        printf("level %d: ", i);
        PrintTreeCurrLevel(tree->root, i);
        printf("\n");
    }
}



static void PrintTreeCurrLevel(avl_node_t *root, int level)
{
    if (NULL == root)
    {
        return;
    }

    if (1 == level)
    {
        printf("%d ,", *(int *)root->data);
    }

    else if (1 < level)
    {
        PrintTreeCurrLevel(root->children[LEFT], level - 1);
        PrintTreeCurrLevel(root->children[RIGHT], level - 1);
    }
}






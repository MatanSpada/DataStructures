/***********************************
 * Bst Source code                 *
 * Developer: Matan Spada          *
 * Written: 2022-01-18             *
 *                                 *
 * Approved by:   Ofer             *
 ***********************************/

#ifndef __BST_H__
#define __BST_H__

#include <stddef.h>             /* size_t */

typedef struct bst bst_t;
typedef struct bst_node *bst_iter_t;

typedef int (*bst_cmp_func_t)(const void *data1, const void *data2);
typedef int (*bst_action_func_t)(void *data, void *param);


/* DESCRIPTION: 
 *  Create a new Binary Search Tree 
 *
 * PARAMS: 
 * cmp_func     - Pointer to comparison function with the format above.
 *
 * RETURN:
 * Pointer to BST.
 * In case of FAILURE, NULL will be returned .
 *
 * Time complexity O(1) 
 * Space complexity O(1)
 */
bst_t *BSTCreate(bst_cmp_func_t cmp_func);


/* DESCRIPTION: 
 *  Destroy BST and all nodes.
 *
 * PARAMS: 
 * tree         - Pointer to the tree to be destroyed.
 *
 * RETURN:
 * None
 *
 * Time complexity O(n) 
 * Space complexity O(1)
 */
void BSTDestroy(bst_t *tree);


/* DESCRIPTION: 
 * display the size of givven BST (number of nodes).
 *
 * PARAMS: 
 * tree         - Pointer to the tree to be checked.
 *
 * RETURN:
 * Number of nodes exist in the BST.
 *
 * Time complexity O(n) 
 * Space complexity O(1)
 */
size_t BSTSize(const bst_t *tree);


/* DESCRIPTION: 
 *  Check whether a BST is empty
 *
 * PARAMS: 
 * tree         - Pointer to BST to be checked.
 *
 * RETURN:
 *  1 - BST is empty.
 *  0 - BST is not empty.
 *
 * Time complexity O(1) 
 * Space complexity O(1)
 */
int BSTIsEmpty(const bst_t *tree);





/* DESCRIPTION: 
 * Insert new node to the BST
 *
 * INSERTING DUPLICATE NODES WILL CAUSE AN UNDEFINED BEHAVIOR.
 *
 * PARAMS: 
 * tree         - Pointer to a tree.
 * data         - Data to be inserted   
 *
 * RETURN:
 * An iterator to the new node.
 * END Iterator in case of FAILURE

 * Time complexity O(log n) 
 * Space complexity O(1)
 */
bst_iter_t BSTInsert(bst_t *tree, void *data);


/* DESCRIPTION: 
 * Remove a specific node.
 *
 * WARRNING: after using this function, 
 * exisiting iterators might be unusable.
 * Create new iterators.
 *
 * PARAMS: 
 * iter         - Iterator to node to be removed.
 *
 * RETURN:
 * None
 *
 * Time complexity O(log n) average 
 * Space complexity O(1)
 */
void BSTRemove(bst_iter_t iter);


/* DESCRIPTION: 
 * Get an iterator to a node with the minimum value.
 *
 * PARAMS: 
 * tree         - Pointer to BST. 
 *
 * RETURN:
 * Iterator to Beginning of BST
 *
 * Time complexity O(log n) average case, O(n) worst case
 * Space complexity O(1)
 */
bst_iter_t BSTBegin(const bst_t *tree);


/* DESCRIPTION: 
 * Get END iterator.
 *
 * PARAMS: 
 * tree         - Pointer to BST. 
 *
 * RETURN:
 * Iterator to the end of the BST.
 *
 * Time complexity O(log n) average case, O(n) worst case
 * Space complexity O(1)
 */
bst_iter_t BSTEnd(const bst_t *tree);


/* DESCRIPTION: 
 * Get an iterator to the previous node.
 * Previous node is the node with the smallest closest value.
 *
 * WARRNING: Using Prev on an empty list will cause undefined behavior.
 *
 * PARAMS: 
 * iter         - Iterator to get its previous node.
 *
 * RETURN:
 *  Iterator to previous node.
 *
 * Time complexity O(log n) 
 * Space complexity O(1)
 */
bst_iter_t BSTPrev(bst_iter_t iter);


/* DESCRIPTION: 
 * Get an iterator to the next node.
 *  Next node is the node with the biggest closest value.
 *
 * WARRNING: Using Next on an empty list will cause undefined behavior.
 *
 * PARAMS: 
 * iter         - Iterator to get next node of 
 *
 * RETURN:
 * Iterator to next node.
 *
 * Time complexity O(log n) 
 * Space complexity O(1)
 */
bst_iter_t BSTNext(bst_iter_t iter);


/* DESCRIPTION: 
 * Checks whether two iterators are equal.
 *
 * PARAMS: 
 * iter1 - Iterator to be checked.
 * iter2 - Iterator to be checked.
 *
 * RETURN:
 *  1 - Iterators are equal.
 *  0 - Iterators are not equal.
 *
 * Time complexity O(1) 
 * Space complexity O(1)
 */
int BSTIterIsEqual(bst_iter_t iter1, bst_iter_t iter2);


/* DESCRIPTION: 
 * Display the data of a specific node.
 *
 * PARAMS: 
 * iter         - Iterator to get data from.
 *
 * RETURN:
 * The Data stored in the node.
 *
 * Time complexity O(1) 
 * Space complexity O(1)
 */
void *BSTGetData(bst_iter_t iter);


/* DESCRIPTION: 
 * Find a specific data in BST.
 *
 * PARAMS: 
 * tree         - Tree to be searched into.
 * data_to_find - Value to find.
 *
 * RETURN:
 * Found - iterator to node with stored the data.
 * Not found - Iterator to END
 *
 * Time complexity O(log n) 
 * Space complexity O(1)
 */
bst_iter_t BSTFind(const bst_t *tree, void *data_to_find);


/* DESCRIPTION: 
 * By givven to iterators, iterates from "from" to "to", 
 * and uses action function with an optional data.
 * The action function is givven by the user.
 *
 * PARAMS: 
 * from         - Iterator to the start of iteration.
 * to           - Iterator to the end of iteration(not included).
 * action func  - Action function to be activated. 
 * param        - Any added parameters for action function to work.        
 *
 * RETURN:
 * 0 - All nodes affected.
 * 1 - Something went wrong thrugh the iteration.
 *
 * Time complexity O(n) 
 * Space complexity O(1)
 */
int BSTForEach(bst_iter_t from, bst_iter_t to,
	bst_action_func_t action_func, void *param);


#endif /* __BST_H__ */
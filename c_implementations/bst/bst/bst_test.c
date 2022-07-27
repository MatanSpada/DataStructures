#include <stdio.h>                    
#include <stdlib.h>                   
#include "../include/bst.h"          



int PrintFunc(void *data, void *stam);


int BSTCmpFunc(const void *data1, const void *data2)
{
    return (long)data1 - (long)data2;
}


int main()
{
    bst_iter_t iter = NULL;
    bst_iter_t found = NULL;
    bst_t *new_tree = BSTCreate(BSTCmpFunc);
    if(NULL == new_tree)
    {
        printf("new_tree is NULL\n");
    }

    printf("empty: %d\n", BSTIsEmpty(new_tree));
    printf("size: %ld\n", BSTSize(new_tree));
    BSTInsert(new_tree, (void *)10);
    printf("size after insert: %ld\n", BSTSize(new_tree));
    BSTInsert(new_tree, (void *)20);
    printf("size after insert: %ld\n", BSTSize(new_tree));
    BSTInsert(new_tree, (void *)30);
    printf("size after insert: %ld\n", BSTSize(new_tree));
    printf("empty: %d\n", BSTIsEmpty(new_tree));

    found = BSTFind(new_tree, (void *)20);
    BSTRemove(found);
    found = BSTFind(new_tree, (void *)20);
    printf("is equal: %d\n", BSTIterIsEqual(found, BSTEnd(new_tree)));

    printf("size: %ld\n", BSTSize(new_tree));
    BSTInsert(new_tree, (void *)25);
    BSTInsert(new_tree, (void *)11);
    BSTInsert(new_tree, (void *)19);
    BSTInsert(new_tree, (void *)18);
    BSTInsert(new_tree, (void *)99);
    BSTInsert(new_tree, (void *)105);

    for(iter = BSTPrev(BSTEnd(new_tree)); iter != BSTBegin(new_tree); iter = BSTPrev(iter))
    {
        PrintFunc(BSTGetData(iter), NULL);
    }
    printf("%ld\n", (long)(BSTGetData(BSTBegin(new_tree))));
    printf("\n");
    BSTForEach(BSTBegin(new_tree), BSTEnd(new_tree), PrintFunc, NULL);
    printf("\n");


    BSTDestroy(new_tree);

    return 0;
}   


int PrintFunc(void *data, void *stam)
{
    (void)stam;
    printf("%ld\t", (long)data);

    return 0;
}
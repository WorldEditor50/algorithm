#ifndef BTREE_H
#define BTREE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../basic.h"
#ifdef __cplusplus
extern "C" {
#endif
typedef enum BTREE_ERROR{
	BTREE_OK ,					
	BTREE_ERR ,				
	BTREE_MEM_ERR ,		
	BTREE_SIZE_ERR ,			
	BTREE_EMPTY_POINTER		
} BTREE_ERROR;
typedef struct TriNode {
	void* element;
	struct TriNode *up;
	struct TriNode *left;
	struct TriNode *right;
} TriNode;
typedef struct BTree BTree;
struct BTree {
	TriNode *root;
	int currentNum;
	void* (*createElement)();
	int (*freeElement)(void* element);
	int (*compare)(void* element1, void* element2);
	int (*callBack)(void* element1, void* element2);
	int (*writeElement)(FILE *fp, void* element);
	int (*readElement)(FILE *fp, void* element);
	/* register function */
	int (*registerCreateElement)(BTree *pBTree, func createElement);
	int (*registerFreeElement)(BTree *pBTree, func1 freeElement);
	int (*registerCompare)(BTree *pBTree, func2 compare);
	int (*registerCallBack)(BTree *pBTree, func2 callBack);
	int (*registerWriteElement)(BTree *pBTree, funcIO writeElement);
	int (*registerReadElement)(BTree *pBTree, funcIO readElement);
	/* free */
	int (*free)(BTree *pBTree);
	/* delete */
	int (*delete)(BTree *pBTree);
	/* search */
	int (*search)(BTree *pBTree, void* element);
	/* insert */
	int (*insert)(BTree *pBTree, void* element);
	/* remove */
	int (*remove)(BTree *pBTree, void* element);
	/* traverse */
	int (*traverse)(BTree *pBTree, void* item);
	/* write to file */
	int (*save)(BTree *pBTree, char* fileName);
	/* read from file */
	int (*load)(BTree *pBTree, char* fileName, int num);
};
/* register function */
int BTree_registerCreateElement(BTree *pBTree, func createElement);
int BTree_registerFreeElement(BTree *pBTree, func1 freeElement);
int BTree_registerCompare(BTree *pBTree, func2 compare);
int BTree_registerCallBack(BTree *pBTree, func2 callBack);
int BTree_registerWriteElement(BTree *pBTree, funcIO writeElement);
int BTree_registerReadElement(BTree *pBTree, funcIO readElement);
/* new */
BTree* BTree_new(func2 comapre);
/* init */
void BTree_init(BTree *pBTree);
/* free */
int BTree_free(BTree *pBTree);
/* delete */
int BTree_delete(BTree *pBTree);
/* search */
int BTree_search(BTree *pBTree, void* element);
/* insert */
int BTree_insert(BTree *pBTree, void* element);
/* remove */
int BTree_remove(BTree *pBTree, void* element);
/* traverse */
int BTree_traverse(BTree *pBTree, void* item);
/* write to file */
int BTree_writeToFile(BTree *pBTree, char* fileName);
/* read from file */
int BTree_readFromFile(BTree *pBTree, char* fileName, int num);
#ifdef __cplusplus
}
#endif
#endif// BTREE_H

#include "btree.h"
/* init */
void BTree_init(BTree *pBTree)
{
	/* register function */
	pBTree->registerCreateElement = BTree_registerCreateElement;
	pBTree->registerFreeElement = BTree_registerFreeElement;
	pBTree->registerCompare = BTree_registerCompare;
	pBTree->registerCallBack = BTree_registerCallBack;
	pBTree->registerWriteElement = BTree_registerWriteElement;
	pBTree->registerReadElement = BTree_registerReadElement;
	/* free */
	pBTree->free = BTree_free;
	/* delete */
	pBTree->delete = BTree_delete;
	/* search */
	pBTree->search = BTree_search;
	/* insert */
	pBTree->insert = BTree_insert;
	/* remove */
	pBTree->remove = BTree_remove;
	/* traverse */
	pBTree->traverse = BTree_traverse;
	/* write to file */
	pBTree->save = BTree_writeToFile;
	/* read from file */
	pBTree->load = BTree_readFromFile;
	return;
}
/* register function */
int BTree_registerCreateElement(BTree *pBTree, func createElement)
{
	if (pBTree == NULL) {
		DEBUG_MESSAGE("tree is null");
		return BTREE_EMPTY_POINTER;
	}
	pBTree->createElement = createElement;
	return BTREE_OK;
}

int BTree_registerFreeElement(BTree *pBTree, func1 freeElement)
{
	if (pBTree == NULL) {
		DEBUG_MESSAGE("tree is null");
		return BTREE_EMPTY_POINTER;
	}
	pBTree->freeElement = freeElement;
	return BTREE_OK;
}

int BTree_registerCompare(BTree *pBTree, func2 compare)
{
	if (pBTree == NULL || compare == NULL) {
		DEBUG_MESSAGE("tree is null");
		return BTREE_EMPTY_POINTER;
	}
	pBTree->compare = compare;
	return BTREE_OK;
}

int BTree_registerCallBack(BTree *pBTree, func2 callBack)
{
	if (pBTree == NULL) {
		DEBUG_MESSAGE("tree is null");
		return BTREE_EMPTY_POINTER;
	}
	pBTree->callBack = callBack;
	return BTREE_OK;
}

int BTree_registerWriteElement(BTree *pBTree, funcIO writeElement)
{
	if (pBTree == NULL) {
		DEBUG_MESSAGE("tree is null");
		return BTREE_EMPTY_POINTER;
	}
	pBTree->writeElement = writeElement;
	return BTREE_OK;
}

int BTree_registerReadElement(BTree *pBTree, funcIO readElement)
{
	if (pBTree == NULL) {
		DEBUG_MESSAGE("tree is null");
		return BTREE_EMPTY_POINTER;
	}
	pBTree->readElement = readElement;
	return BTREE_OK;
}

TriNode* TriNode_New(void* element)
{
	if (element == NULL) {
		DEBUG_MESSAGE("element is null");
		return NULL;
	}
	TriNode *pNode = NULL;
	pNode = (TriNode*)malloc(sizeof(TriNode));
	if (pNode == NULL) {
		DEBUG_MESSAGE("Node malloc failed");
		return NULL;
	}
	pNode->element = element;
	pNode->up = NULL;
	pNode->left = NULL;
	pNode->right = NULL;
	return pNode;
}
/* new */
BTree* BTree_new(func2 compare)
{
	if (compare == NULL) {
		DEBUG_MESSAGE("compare is null");
		return NULL;
	}
	BTree *pBTree = NULL;
	pBTree = (BTree*)malloc(sizeof(BTree));
	if (pBTree == NULL) {
		DEBUG_MESSAGE("tree malloc failed");
		return NULL;
	}
	pBTree->root = NULL;
	pBTree->currentNum = 0;
	pBTree->compare = compare;
	BTree_init(pBTree);
	return pBTree;
}

/* delete */
int BTree_delete(BTree *pBTree)
{
	if (pBTree == NULL) {
		DEBUG_MESSAGE("pBTree is null");
		return BTREE_EMPTY_POINTER;
	}
	if (pBTree->root != NULL) {
		DEBUG_MESSAGE("root is not free");
		return BTREE_EMPTY_POINTER;
	}
	free(pBTree);
	return BTREE_OK;
}
/* free */
void btree_free(TriNode** root, func1 freeElement)
{
	if (*root == NULL) {
		return;
	}
	TriNode *pNode = *root;
	TriNode *pLeftNode = pNode->left;
	TriNode *pRightNode = pNode->right;
	btree_free(&pLeftNode, freeElement);
	btree_free(&pRightNode, freeElement);
	freeElement(pNode->element);
	pNode->element = NULL;
	free(pNode);
	*root = NULL;
	return;
}
int BTree_free(BTree *pBTree)
{
	if (pBTree == NULL || pBTree->root == NULL) {
		DEBUG_MESSAGE("pBTree or root is null");
		return BTREE_EMPTY_POINTER;
	}
	if (pBTree->freeElement == NULL) {
		DEBUG_MESSAGE("free element is not registered");
		return BTREE_EMPTY_POINTER;
	}
	TriNode *pNode = pBTree->root;
	btree_free(&pNode, pBTree->freeElement);
	pBTree->root = NULL;
	return BTREE_OK;
}

TriNode* btree_search(TriNode *root, func2 compare, void* element)
{
	TriNode *pNode = root;
	int flag = 1;
	while (pNode != NULL) {
		flag = compare(element, pNode->element);
		if (flag > 0) {
			pNode = pNode->left;
		} else if (flag < 0) {
			pNode = pNode->right;
		} else {
			break;
		}
	}
	return pNode;
}
/* search */
int BTree_search(BTree *pBTree, void* element)
{
	if (pBTree == NULL || pBTree->root == NULL) {
		DEBUG_MESSAGE("tree is null");
		return BTREE_EMPTY_POINTER;
	}
	if (pBTree->compare == NULL) {
		DEBUG_MESSAGE("compare is not registered");
		return BTREE_EMPTY_POINTER;
	}
	if (element == NULL) {
		DEBUG_MESSAGE("element is null");
		return BTREE_EMPTY_POINTER;
	}
	TriNode *pNode = NULL;
	pNode = btree_search(pBTree->root, pBTree->compare, element);
	if (pNode == NULL) {
		return BTREE_EMPTY_POINTER;
	}
	return BTREE_OK;
}
/* insert */
void btree_insert(TriNode *root, TriNode *pNode, func2 compare)
{
	TriNode *nextNode = root;	
	int flag = 1;
	while (nextNode != NULL) {
		flag = compare(pNode->element, nextNode->element);
		if (flag >= 0) {
			if (nextNode->left != NULL) {
				nextNode = nextNode->left;
			} else {
				nextNode->left = pNode;
				pNode->up = nextNode;
				break;
			} 
		} else {
			if (nextNode->right != NULL) {
				nextNode = nextNode->right;
			} else {
				nextNode->right = pNode;
				pNode->up = nextNode;
				break;
			} 
		}
	}
	return;
}
int BTree_insert(BTree *pBTree, void* element)
{
	if (pBTree == NULL) {
		DEBUG_MESSAGE("tree is null");
		return BTREE_EMPTY_POINTER;
	}
	if (pBTree->compare == NULL) {
		DEBUG_MESSAGE("compare is not registered");
		return BTREE_EMPTY_POINTER;
	}
	if (element == NULL) {
		DEBUG_MESSAGE("element is null");
		return BTREE_EMPTY_POINTER;
	}
	TriNode *pNode = NULL;
	pNode = TriNode_New(element);
	if (pNode == NULL) {
		DEBUG_MESSAGE("new node failed");
		return BTREE_MEM_ERR;
	}
	if (pBTree->root == NULL) {
		pBTree->root = pNode;
	} else {
		btree_insert(pBTree->root, pNode, pBTree->compare);
	}
	pBTree->currentNum++;
	return BTREE_OK;
}

int BTree_remove(BTree *pBTree, void* element)
{
	if (pBTree == NULL || pBTree->root == NULL) {
		DEBUG_MESSAGE("tree is null");
		return BTREE_EMPTY_POINTER;
	}
	if (pBTree->compare == NULL) {
		DEBUG_MESSAGE("compare is not registered");
		return BTREE_EMPTY_POINTER;
	}
	if (element == NULL) {
		DEBUG_MESSAGE("element is null");
		return BTREE_EMPTY_POINTER;
	}
	TriNode *pNode = NULL;
	TriNode *pLeftNode = NULL;
	TriNode *pRightNode = NULL;
	TriNode *pUpNode = NULL;
	TriNode *pTailNode = NULL;
	pNode = btree_search(pBTree->root, pBTree->compare, element);
	if (pNode == NULL) {
		DEBUG_MESSAGE("element is not exist");
		return BTREE_EMPTY_POINTER;
	}
	if (pNode->up == NULL) {
		if (pNode->left == NULL && pNode->right == NULL) {

		} else if (pNode->left == NULL && pNode->right != NULL) {
			pRightNode = pNode->right;
			pRightNode->up = NULL;
			pBTree->root = pRightNode;
		} else if (pNode->left != NULL && pNode->right == NULL) {
			pLeftNode = pNode->left;
			pLeftNode->up = NULL;
			pBTree->root = pLeftNode;
		} else if (pNode->left != NULL && pNode->right != NULL) {
			pLeftNode = pNode->left;
			pRightNode = pNode->right;
			pTailNode = pLeftNode;
			while (pTailNode->right != NULL) {
				pTailNode = pTailNode->right;
			}
			pTailNode->right = pRightNode;
			pLeftNode->up = NULL;
			pBTree->root = pLeftNode;
		}
	} else {
		if (pNode->left == NULL && pNode->right == NULL) {
			pUpNode = pNode->up;
			if (pBTree->compare(element, pUpNode->element) > 0) {
				pUpNode->left = NULL;
			} else {
				pUpNode->right = NULL;
			}
		} else if (pNode->left == NULL && pNode->right != NULL) {
			pUpNode = pNode->up;
			pRightNode = pNode->right;
			if (pBTree->compare(element, pUpNode->element) > 0) {
				pUpNode->left = pRightNode;
			} else {
				pUpNode->right = pRightNode;
			}
			pRightNode->up = pUpNode;
		} else if (pNode->left != NULL && pNode->right == NULL) {
			pUpNode = pNode->up;
			pLeftNode = pNode->left;
			if (pBTree->compare(element, pUpNode->element) >= 0) {
				pUpNode->left = pLeftNode;
			} else {
				pUpNode->right = pLeftNode;
			}
			pLeftNode->up = pUpNode;
		} else if (pNode->left != NULL && pNode->right != NULL) {
			pUpNode = pNode->up;
			pLeftNode = pNode->left;
			pRightNode = pNode->right;
			pTailNode = pLeftNode;
			if (pBTree->compare(element, pUpNode->element) >= 0) {
				pUpNode->left = pLeftNode;
			} else {
				pUpNode->right = pLeftNode;
			}
			while (pTailNode->right != NULL) {
				pTailNode = pTailNode->right;
			}
			pTailNode->right = pRightNode;	
			pLeftNode->up = pUpNode;
			pRightNode->up = pTailNode;
		}
	}
	if (pBTree->freeElement != NULL) {
		pBTree->freeElement(element);
	}
	free(pNode);
	pNode = NULL;
	pBTree->currentNum--;
	return BTREE_OK;
}

/* traverse */
void btree_traverse(TriNode* root, func2 callBack, void* item)
{
	if (root == NULL) {
		return;
	}
	btree_traverse(root->left, callBack, item);
	callBack(root->element, item);
	btree_traverse(root->right, callBack, item);
	return;
}
int BTree_traverse(BTree *pBTree, void* item)
{
	if (pBTree == NULL || pBTree->root == NULL) {
		DEBUG_MESSAGE("tree is null");
		return BTREE_EMPTY_POINTER;
	}
	if (pBTree->callBack == NULL) {
		DEBUG_MESSAGE("callBack is not registered");
		return BTREE_EMPTY_POINTER;
	}
	btree_traverse(pBTree->root, pBTree->callBack, item);
	return BTREE_OK;
}

/* write to file */
void btree_writeToFile(TriNode* root, funcIO writeElement, FILE* fp)
{
	if (root == NULL) {
		return;
	}
	btree_writeToFile(root->left, writeElement, fp);
	writeElement(fp, root->element);
	btree_writeToFile(root->right, writeElement, fp);
	return;
}
int BTree_writeToFile(BTree *pBTree, char* fileName)
{
	if (pBTree == NULL || pBTree->root == NULL) {
		DEBUG_MESSAGE("tree is null");
		return BTREE_EMPTY_POINTER;
	}
	if (pBTree->writeElement == NULL) {
		DEBUG_MESSAGE("writeElement is not registered");
		return BTREE_EMPTY_POINTER;
	}
	FILE *fp = NULL;
	fp = fopen(fileName, "w+");
	if (fp == NULL) {
		DEBUG_MESSAGE("open file failed");
		return BTREE_EMPTY_POINTER;
	}
	btree_writeToFile(pBTree->root, pBTree->writeElement, fp);
	fclose(fp);
	return BTREE_OK;
}

int BTree_readFromFile(BTree *pBTree, char* fileName, int num)
{
	if (pBTree == NULL) {
		DEBUG_MESSAGE("tree is null");
		return BTREE_EMPTY_POINTER;
	}
	if (pBTree->readElement == NULL) {
		DEBUG_MESSAGE("writeElement is not registered");
		return BTREE_EMPTY_POINTER;
	}
	if (pBTree->createElement == NULL) {
		DEBUG_MESSAGE("createElement is not registered");
		return BTREE_EMPTY_POINTER;
	}
	FILE *fp = NULL;
	fp = fopen(fileName, "r");
	if (fp == NULL) {
		DEBUG_MESSAGE("open file failed");
		return BTREE_EMPTY_POINTER;
	}
	int i = 0;
	void* element = NULL;
	for (i = 0; i < num; i++) {
		element = NULL;
		element = pBTree->createElement();
		if (element == NULL) {
			DEBUG_MESSAGE("create element failed");
		}
		pBTree->readElement(fp, element);
		pBTree->insert(pBTree, element);
	}
	fclose(fp);
	return BTREE_OK;
}


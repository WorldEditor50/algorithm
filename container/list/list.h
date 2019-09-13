#ifndef LIST_H
#define LIST_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../basic.h"
#ifdef __cplusplus
extern "C" {
#endif
typedef enum LIST_ERROR{
	LIST_OK ,					
	LIST_ERR ,				
	LIST_MEM_ERR ,		
	LIST_SIZE_ERR ,			
	LIST_EMPTY_POINTER		
} LIST_ERROR;
typedef struct Node {
	void* element;
	struct Node *pre;
	struct Node *next;
}Node;
typedef struct list list;
struct list {
	struct Node *head;
	struct Node *tail;
	int currentNum;
	int maxNum;
	void* (*createElement)();
	int (*freeElement)(void* element);
	int (*compare)(void* element1, void *element2);
	int (*callBack)(void* element1, void* element2);
	int (*writeElement)(FILE *fp, void* element);
	int (*readElement)(FILE *fp, void* element);
	/* register function */
	int (*registerCreateElement)(list *pList, func createElement);
	int (*registerFreeElement)(list *pList, func1 freeElement);
	int (*registerCompare)(list *pList, func2 compare);
	int (*registerCallBack)(list *pList, func2 callBack);
	int (*registerWriteElement)(list *pList, funcIO writeElement);
	int (*registerReadElement)(list *pList, funcIO readElement);
	/* free */
	int (*free)(list *pList);
	/* delete */
	int (*delete)(list *pList);
	/* search */
	Node* (*search)(const list *plist, void *element);
	/* push back */
	int (*push_back)(list *pList, void* element);
	/* pop back */
	int (*pop_back)(list *pList);
	/* push front */
	int (*push_front)(list *pList, void* element);
	/* pop front */
	int (*pop_front)(list *pList);
	/* insert by position */
	int (*insert1)(list *pList, void* element, int position);
	/* delete by position */
	int (*remove1)(list *pList, int position);
	/* insert by element */
	int (*insert2)(list *pList, void* preElement, void* element);
	/* delete by element */
	int (*remove2)(list *pList, void* element);
	/* sort */
	int (*sort)(list *pList);
	/* reverse */
	int (*reverse)(list *pList);
	/* traverse */
	int (*traverse)(const list *pList, void* item);
	/* write to file */
	int (*save)(list *pList, const char* fileName);
	/* read from file */
	int (*load)(list *pList, const char* fileName);
};
/* register function */
int list_registerCreateElement(list *pList, func createElement);
int list_registerFreeElement(list *pList, func1 freeElement);
int list_registerCompare(list *pList, func2 compare);
int list_registerCallBack(list *pList, func2 callBack);
int list_registerWriteElement(list *pList, funcIO writeElement);
int list_registerReadElement(list *pList, funcIO readElement);
/* new list */
list* list_new(int maxNum);
/* init list */
void list_init(list *pList);
/* free */
int list_free(list *pList);
/* delete list */
int list_delete(list *pList);
/* search */
Node *list_search(const list *plist, void *element);
/* push back */
int list_push_back(list *pList, void* element);
/* pop back */
int list_pop_back(list *pList);
/* push front */
int list_push_front(list *pList, void* element);
/* pop front */
int list_pop_front(list *pList);
/* insert by position */
int list_insertByPosition(list *pList, void* element, int position);
/* delete by position */
int list_deleteByPosition(list *pList, int position);
/* insert by element */
int list_insertByElement(list *pList, void* preElement, void* element);
/* delete by element */
int list_deleteByElement(list *pList, void* element);
/* sort */
int list_sort(list *pList);
/* reverse */
int list_reverse(list *pList);
/* traverse */
int list_traverse(const list *pList, void* item);
/* write to file */
int list_writeToFile(list *pList, const char* fileName);
/* read from file */
int list_readFromFile(list *pList, const char* fileName);
#ifdef __cplusplus
}
#endif// __cplusplus
#endif// LIST_H

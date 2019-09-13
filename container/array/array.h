#ifndef ARRAY_H
#define ARRAY_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../basic.h"
#ifdef __cplusplus
extern "C" {
#endif
typedef enum {
	ARRAY_OK ,				
	ARRAY_ERR ,				
	ARRAY_SIZE_ERR ,			
	ARRAY_MEM_ERR ,			
	ARRAY_EMPTY_POINTER ,		
	ARRAY_FULL ,				
	ARRAY_EMPTY 			
} ARRAY_NUM;
/* debug message*/
typedef struct Array Array;
struct Array {
	void** pElements;
	int currentSize;
	int maxSize;
	void* (*createElement)();
	void* (*createRegisterElement)(char* typeName);
	int (*freeElement)(void* element);
	int (*compare)(void* element1, void* element2);
	int (*swap)(void* element1, void* element2);
	int (*writeElement)(FILE *fp, void* element);
	int (*readElement)(FILE *fp, void* element);
	int (*callBack)(void* element1, void* element2);
	/* register new type */
	int (*registerCreateElement)(Array* pArray, func createElement);
	/* register delete type */
	int (*registerFreeElement)(Array* pArray, func1 freeElement);
	/* register compare */
	int (*registerCompare)(Array* pArray, func2 compare);
	/* register swap */
	int (*registerSwap)(Array* pArray, func2 swap);
	/* register write element */
	int (*registerWriteElement)(Array* pArray, funcIO writeElement);
	/* register read element */
	int (*registerReadElement)(Array* pArray, funcIO readElement);
	/* register callBack */
	int (*registerCallBack)(Array* pArray, func2 callBack);
	/* free element */
	int (*free)(Array* pArray);
	/* create */
	int (*create)(Array *pArray, int size);
	/* delete */
	int (*delete)(Array* pArray);
	/* resize */
	int (*resize)(Array* pArray, int newSize);
	/* shift left */
	int (*shiftLeft)(Array* pArray, int begin, int end, int steps);
	/* shift right */
	int (*shiftRight)(Array* pArray, int begin, int end, int steps);
	/* push back */
	int (*push_back)(Array* pArray, void* element);
	/* push front */
	int (*push_front)(Array* pArray, void* element);
	/* pop back */
	int (*pop_back)(Array* pArray);
	/* pop front */
	int (*pop_front)(Array* pArray);
	/* search return index */
	int (*search)(const Array* pArray, void* element);
	/* insert by index */
	int (*insert1)(Array* pArray, void* element, int index);
	/* insert by element */
	int (*insert2)(Array* pArray, void* element, void* frontElement);
	/* delete by index */
	int (*remove1)(Array* pArray, int index);
	/* delete */
	int (*remove2)(Array* pArray, void* element);
	/* traverse */
	int (*traverse)(Array* pArray, void* item);
	/* sort */
	int (*sort)(Array* pArray);
	/* write to file */
	int (*save)(const Array* pArray, const char* fileName);
	/* read from file */
	int (*load)(Array* pArray, const char* fileName);
};

/* register new type */
int array_registerCreateElement(Array* pArray, func createElement);
/* register delete type */
int array_registerFreeElement(Array* pArray, func1 freeElement);
/* register write element */
int array_registerWriteElement(Array* pArray, funcIO writeElement);
/* register read element */
int array_registerReadElement(Array* pArray, funcIO readElement);
/* register callBack */
int array_registerCallBack(Array* pArray, func2 callBack);
/* register compare */
int array_registerCompare(Array* pArray, func2 compare);
/* register swap */
int array_registerSwap(Array* pArray, func2 swap);
/* init */
void array_init(Array *pArray);
/* new array */
Array* array_new();
/* create element */
int array_create(Array *pArray, int size);
/* free element */
int array_free(Array* pArray);
/* delete */
int array_delete(Array* pArray);
/* resize */
int array_resize(Array* pArray, int newSize);
/* shift left */
int array_shiftLeft(Array* pArray, int begin, int end, int steps);
/* shift right */
int array_shiftRight(Array* pArray, int begin, int end, int steps);
/* push back */
int array_push_back(Array* pArray, void* element);
/* push front */
int array_push_front(Array* pArray, void* element);
/* pop back */
int array_pop_back(Array* pArray);
/* pop front */
int array_pop_front(Array* pArray);
/* search return index */
int array_search(const Array* pArray, void* element);
/* insert by index */
int array_insertByIndex(Array* pArray, void* element, int index);
/* insert by element */
int array_insertByElement(Array* pArray, void* element, void* frontElement);
/* delete by index */
int array_deleteByIndex(Array* pArray, int index);
/* delete by element */
int array_deleteByElement(Array* pArray, void* element);
/* traverse */
int array_traverse(Array* pArray, void* item);
/* sort */
int array_sort(Array* pArray);
/* write to file */
int array_writeToFile(const Array* pArray, const char* fileName);
/* read from file */
int array_readFromFile(Array* pArray, const char* fileName);
#ifdef __cplusplus
}
#endif // __cplusplus
#endif // ARRAY_H

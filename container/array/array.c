#include "array.h"

/* register new type */
int array_registerCreateElement(Array* pArray, func createElement)
{
	if (pArray == NULL || createElement == NULL) {
		DEBUG_MESSAGE("empty pointer ");
		return ARRAY_EMPTY_POINTER;
	}
	pArray->createElement = createElement;
	return ARRAY_OK;
}

/* register delete type */
int array_registerFreeElement(Array* pArray, func1 freeElement)
{
	if (pArray == NULL || freeElement == NULL) {
		DEBUG_MESSAGE("empty pointer ");
		return ARRAY_EMPTY_POINTER;
	}
	pArray->freeElement = freeElement;
	return ARRAY_OK;
}

/* register compare */
int array_registerCompare(Array* pArray, func2 compare)
{
	if (pArray == NULL || compare == NULL) {
		DEBUG_MESSAGE("empty pointer ");
		return ARRAY_EMPTY_POINTER;
	}
	pArray->compare = compare;
	return ARRAY_OK;
}

/* register swap */
int array_registerSwap(Array* pArray, func2 swap)
{
	if (pArray == NULL || swap == NULL) {
		DEBUG_MESSAGE("empty pointer ");
		return ARRAY_EMPTY_POINTER;
	}
	pArray->swap = swap;
	return ARRAY_OK;
}

/* register read element */
int array_registerReadElement(Array* pArray, funcIO readElement)
{
	if (pArray == NULL || readElement == NULL) {
		DEBUG_MESSAGE("empty pointer ");
		return ARRAY_EMPTY_POINTER;
	}
	pArray->readElement = readElement;
	return ARRAY_OK;
}

/* register write element */
int array_registerWriteElement(Array* pArray, funcIO writeElement)
{
	if (pArray == NULL || writeElement == NULL) {
		DEBUG_MESSAGE("empty pointer ");
		return ARRAY_EMPTY_POINTER;
	}
	pArray->writeElement = writeElement;
	return ARRAY_OK;
}

/* register callBack */
int array_registerCallBack(Array* pArray, func2 callBack)
{
	if (pArray == NULL || callBack == NULL) {
		DEBUG_MESSAGE("empty pointer ");
		return ARRAY_EMPTY_POINTER;
	}
	pArray->callBack = callBack;
	return ARRAY_OK;
}
/* init */
void array_init(Array* pArray)
{
	/* register compare */
	pArray->registerCompare = array_registerCompare;
	/* register swap */
	pArray->registerSwap = array_registerSwap;
	/* register new type */
	pArray->registerCreateElement = array_registerCreateElement;
	/* register delete type */
	pArray->registerFreeElement = array_registerFreeElement;
	/* register write element */
	pArray->registerWriteElement = array_registerWriteElement;
	/* register read element */
	pArray->registerReadElement = array_registerReadElement;
	/* register call back */
	pArray->registerCallBack = array_registerCallBack;
	/* create element */
	pArray->create = array_create;
	/* free element */
	pArray->free = array_free;
	/* delete array */
	pArray->delete = array_delete;
	/* resize */
	pArray->resize = array_resize;
	/* shift left */
	pArray->shiftLeft = array_shiftLeft;
	/* shift right */
	pArray->shiftRight = array_shiftRight;
	/* push back */
	pArray->push_back = array_push_back;
	/* push front */
	pArray->push_front = array_push_front;
	/* pop back */
	pArray->pop_back = array_pop_back;
	/* pop front */
	pArray->pop_front = array_pop_front;
	/* search return index */
	pArray->search = array_search;
	/* insert by index */
	pArray->insert1 = array_insertByIndex;
	/* insert by element */
	pArray->insert2 = array_insertByElement;
	/* remove by index */
	pArray->remove1 = array_deleteByIndex;
	/* remove */
	pArray->remove2 = array_deleteByElement;
	/* traverse */
	pArray->traverse = array_traverse;
	/* sort */
	pArray->sort = array_sort;
	/* write to file */
	pArray->save = array_writeToFile;
	/* read from file */
	pArray->load = array_readFromFile;
	return;
}

/* new array */
Array* array_new(int size)
{
	struct Array *pArray = NULL;
	do {
		pArray = (Array*)malloc(sizeof(Array));
		if (pArray == NULL)	{
			DEBUG_MESSAGE("pArray malloc failed");
			break;
		}
		void** pElements = (void*)malloc(sizeof(void*) * size);
		if (pElements == NULL) {
			DEBUG_MESSAGE("pElements malloc failed");
			break;
		}
		int i = 0;
		for (i = 0; i < size; i++) {
			pElements[i] = NULL;
		}
		pArray->pElements = pElements;
		pArray->maxSize = size;
		pArray->currentSize = 0;
		array_init(pArray);
		return pArray;
	} while (0);
	if (pArray != NULL) {
		free(pArray);
	}
	return NULL;
}

/* create element */
int array_create(Array *pArray, int size)
{
	int i = 0;
	if (pArray == NULL || pArray->pElements == NULL || pArray->createElement == NULL) {
		DEBUG_MESSAGE("pArray or pElements or createElement is null");
		return ARRAY_EMPTY_POINTER;
	}
	if (size > pArray->maxSize) {
		return ARRAY_ERR;
	}
	for (i = 0; i < size; i++) {
		pArray->pElements[i] = pArray->createElement();
		if (pArray->pElements[i] == NULL) {
			DEBUG_MESSAGE("create element fail");
			return ARRAY_MEM_ERR;
		}
	}
	return ARRAY_OK;
}

/* free element */
int array_free(Array* pArray)
{
	int i = 0;
	if (pArray == NULL || pArray->pElements == NULL) {
		DEBUG_MESSAGE("pArray or pElements is null");
		return ARRAY_EMPTY_POINTER;
	}
	if (pArray->freeElement != NULL) {
		for(i = 0; i < pArray->maxSize; i++) {
			if (pArray->pElements[i] != NULL) {
				pArray->freeElement(pArray->pElements[i]);
				pArray->pElements[i] = NULL;
			}
		}
	}
	pArray->currentSize = 0;
	return ARRAY_OK;
}

/* delete */
int array_delete(Array* pArray)
{
	if (pArray== NULL) {
		DEBUG_MESSAGE("pArray is null");
		return ARRAY_EMPTY_POINTER;
	}
	if (pArray->pElements != NULL) {
		free(pArray->pElements);
	}
	free(pArray);
	pArray = NULL;
	return ARRAY_OK;
}

/* resize */
int array_resize(Array* pArray, int newSize)
{
	if (pArray == NULL || pArray->pElements == NULL) {
		DEBUG_MESSAGE("pArray or pElements is null");
		return ARRAY_EMPTY_POINTER;
	}
	if (pArray->maxSize >= newSize) {
		DEBUG_MESSAGE("maxSize >= newSize");
		return ARRAY_SIZE_ERR;
	}
	void** pNewElements = NULL;
	int i = 0;
	pNewElements = (void*)malloc(sizeof(void*) * newSize);
	if (pNewElements == NULL) {
		DEBUG_MESSAGE("pNewElements malloc failed");
		return ARRAY_MEM_ERR;
	}
	for (i = 0; i < newSize; i++) {
		if (i < pArray->currentSize) {
			pNewElements[i] = pArray->pElements[i]; 
		} else {
			pNewElements[i] = NULL;
		}
	}
	free(pArray->pElements);
	pArray->pElements = pNewElements;
	pArray->maxSize = newSize;
	return ARRAY_OK;
}

/* shift left */
int array_shiftLeft(Array* pArray, int begin, int end, int steps)
{
	if (pArray == NULL || pArray->pElements == NULL) {
		DEBUG_MESSAGE("pArray or pElements is null");
		return ARRAY_EMPTY_POINTER;
	}
	if (begin > end || end > pArray->maxSize || (begin - steps) < 0) {
		DEBUG_MESSAGE("begin, end border error");
		return ARRAY_ERR;
	}
	int i = 0;
	for (i = begin; i < end + 1; i++) {
		pArray->pElements[i - steps] = pArray->pElements[i];
	}
	return ARRAY_OK;
}

/* shift right */
int array_shiftRight(Array* pArray, int begin, int end, int steps)
{
	if (pArray == NULL || pArray->pElements == NULL) {
		DEBUG_MESSAGE("pArray or pElements is null");
		return ARRAY_EMPTY_POINTER;
	}
	if (begin > end || end > pArray->maxSize || (end + steps) > pArray->maxSize) {
		DEBUG_MESSAGE("begin ,end border error");
		return ARRAY_ERR;
	}
	int i = 0;
	for (i = end; i >= begin; i--) {
		pArray->pElements[i + steps] = pArray->pElements[i];
	}
	return ARRAY_OK;
}

/* push back */
int array_push_back(Array* pArray, void* element)
{
	if (pArray == NULL || pArray->pElements == NULL) {
		DEBUG_MESSAGE("pArray or pElements is null");
		return ARRAY_EMPTY_POINTER;
	}
	if (element == NULL) {
		DEBUG_MESSAGE("element is null");
		return ARRAY_EMPTY_POINTER;
	}
	int ret = 0;
	if (pArray->currentSize + 1 > pArray->maxSize) {
		ret = array_resize(pArray, pArray->maxSize * 2);
		if (ret != ARRAY_OK) {
			DEBUG_MESSAGE("resize failed");
			return ARRAY_ERR;
		}
	}
	int index = pArray->currentSize;
	pArray->pElements[index++] = element;
	pArray->currentSize = index;
	return ARRAY_OK;
}

/* push front */
int array_push_front(Array* pArray, void* element)
{
	int ret = ARRAY_OK;
	if (pArray == NULL || pArray->pElements == NULL) {
		DEBUG_MESSAGE("pArray or pElements is null");
		return ARRAY_EMPTY_POINTER;
	}
	if (element == NULL) {
		DEBUG_MESSAGE("element is null");
		return ARRAY_EMPTY_POINTER;
	}
	if (pArray->currentSize + 1 > pArray->maxSize) {
		ret = array_resize(pArray, pArray->maxSize * 2);
		if (ret != ARRAY_OK) {
			DEBUG_MESSAGE("resize fail");
			return ARRAY_ERR;
		}
	}
	int i = 0;
	int end = pArray->currentSize - 1;
	for (i = end; i >= 0; i--) {
		pArray->pElements[i + 1] = pArray->pElements[i];
	}
	pArray->pElements[0] = element;
	pArray->currentSize++;
	return ARRAY_OK;
}

/* pop back */
int array_pop_back(Array* pArray)
{
	if (pArray == NULL || pArray->pElements == NULL) {
		DEBUG_MESSAGE("pArray is null");
		return ARRAY_EMPTY_POINTER;
	}
	if (pArray->currentSize == 0) {
		DEBUG_MESSAGE("size error");
		return ARRAY_SIZE_ERR;
	}
	int index = pArray->currentSize - 1;
	if (pArray->freeElement != NULL) {
		pArray->freeElement(pArray->pElements[index]);
	}
	pArray->pElements[index] = NULL;
	pArray->currentSize--;
	return ARRAY_OK;
}

/* pop front */
int array_pop_front(Array* pArray)
{
	if (pArray == NULL || pArray->pElements == NULL) {
		DEBUG_MESSAGE("pArray is null");
		return ARRAY_EMPTY_POINTER;
	}
	if (pArray->currentSize == 0) {
		DEBUG_MESSAGE("size error");
		return ARRAY_SIZE_ERR;
	}
	if (pArray->freeElement != NULL) {
		pArray->freeElement(pArray->pElements[0]);
	}
	int i = 0;
	for (i = 0; i < pArray->currentSize - 1; i++) {
		pArray->pElements[i] = pArray->pElements[i + 1]; 
	}
	pArray->pElements[i] = NULL;
	pArray->currentSize--;
	return ARRAY_OK;
}

/* search return index */
int array_search(const Array* pArray, void* element)
{
	if (pArray == NULL || pArray->pElements == NULL || element == NULL) {
		DEBUG_MESSAGE("pArray is null");
		return ARRAY_EMPTY_POINTER;
	}
	if (pArray->compare == NULL) {
		DEBUG_MESSAGE("compare is null");
		return ARRAY_EMPTY_POINTER;
	}
	int i = 0;
	for (i = 0; i < pArray->currentSize; i++) {
		if (pArray->compare(pArray->pElements[i], element) == 0) {
			return i;
		}
	}
	return -1;
}

/* insert by index */
int array_insertByIndex(Array* pArray, void* element, int index)
{  
	if (pArray == NULL || pArray->pElements == NULL || element == NULL) {
		DEBUG_MESSAGE("pArray is null");
		return ARRAY_EMPTY_POINTER;
	}
	if (index < 0 || index > pArray->currentSize) {
		DEBUG_MESSAGE("index is out of border");
		return ARRAY_ERR;
	}
	if (pArray->currentSize + 1 > pArray->maxSize) {
		int ret = array_resize(pArray, pArray->maxSize * 2);
		if (ret != ARRAY_OK) {
			DEBUG_MESSAGE("resize fail");
			return ARRAY_ERR;
		}
	}
	int i = 0;
	int end = pArray->currentSize;
	for (i = end - 1; i >= index; i--) {
		pArray->pElements[i + 1] = pArray->pElements[i];
	}
	pArray->pElements[index] = element;
	pArray->currentSize++;
	return ARRAY_OK;
}

/* insert by element */
int array_insertByElement(Array* pArray, void* element, void* frontElement)
{
	if (pArray == NULL || pArray->pElements == NULL || element == NULL || frontElement == NULL) {
		DEBUG_MESSAGE("empty pointer ");
		return ARRAY_EMPTY_POINTER;
	}
	if (pArray->currentSize + 1 > pArray->maxSize) {
		int ret = array_resize(pArray, pArray->maxSize * 2);
		if (ret != ARRAY_OK) {
			DEBUG_MESSAGE("resize fail");
			return ARRAY_ERR;
		}
	}
	int index = -1;
	int i = 0;
	int end = pArray->currentSize;
	for (i = 0; i < end; i++) {
		if (frontElement == pArray->pElements[i]) {
			index = i;
		}
	}
	if (index == -1) {
		DEBUG_MESSAGE("element not exist");
		return ARRAY_ERR;
	}
	for (i = end - 1; i >= index; i--) {
		pArray->pElements[i + 1] = pArray->pElements[i];
	}
	pArray->pElements[index] = element;
	pArray->currentSize++;
	return ARRAY_OK;
}

/* delete by index */
int array_deleteByIndex(Array* pArray, int index)
{
	if (pArray == NULL || pArray->pElements == NULL) {
		DEBUG_MESSAGE("empty pointer ");
		return ARRAY_EMPTY_POINTER;
	}
	if (index < 0 || index >= pArray->currentSize) {
		DEBUG_MESSAGE("index is out of border");
		return ARRAY_ERR;
	}
	if (pArray->freeElement != NULL) {
		pArray->freeElement(pArray->pElements[index]);
	}
	int i = 0;
	for (i = index; i < pArray->currentSize - 1; i++) {
		pArray->pElements[i] = pArray->pElements[i + 1];
	}
	pArray->pElements[i] = NULL;
	pArray->currentSize--;
	return ARRAY_OK;
}

/* delete by element */
int array_deleteByElement(Array* pArray, void* element)
{
	if (pArray == NULL || pArray->pElements == NULL || element == NULL) {
		DEBUG_MESSAGE("empty pointer ");
		return ARRAY_EMPTY_POINTER;
	}
	int index = -1;
	int i = 0;
	for (i = 0; i < pArray->currentSize; i++) {
		if (element == pArray->pElements[i]) {
			index = i;
		}
	}
	if (index == -1) {
		return ARRAY_ERR;
	}
	if (pArray->freeElement != NULL) {
		pArray->freeElement(pArray->pElements[index]);
	}
	for (i = index; i < pArray->currentSize - 1; i++) {
		pArray->pElements[i] = pArray->pElements[i + 1];
	}
	pArray->pElements[i] = NULL;
	pArray->currentSize--;
	return ARRAY_OK;
}

int array_traverse(Array* pArray, void* item)
{
	if (pArray == NULL || pArray->pElements == NULL ) {
		DEBUG_MESSAGE("pArray or pElement is null");
		return ARRAY_EMPTY_POINTER;
	}
	if (pArray->callBack == NULL) {
		DEBUG_MESSAGE("call back fuction is not registered");
		return ARRAY_EMPTY_POINTER;
	}
	int i = 0;
	for (i = 0; i < pArray->currentSize; i++) {
		pArray->callBack(pArray->pElements[i], item);
	}
	return ARRAY_OK;
}

/* quickSort */
static void quickSort(int first, int last, void* *pElements, func2 compareRule) 
{
	if (first > last) {
		return;
	}
	int i = first;
	int j = last;
	void* pRef = pElements[first];
	while (i < j) {
		while (i < j && (compareRule(pElements[j], pRef) > 0)) {
			j--;
		}
		pElements[i] = pElements[j];
		while (i < j && (compareRule(pElements[i], pRef) < 0)) {
			i++;
		}
		pElements[j] = pElements[i];
	}
	pElements[i] = pRef;
	quickSort(first, i -1 , pElements, compareRule);
	quickSort(i + 1, last, pElements, compareRule);
	return;
}
/* sort */
int array_sort(Array* pArray)
{
	if (pArray == NULL || pArray->pElements == NULL) {
		DEBUG_MESSAGE("pArray or pElements is NULL");
		return ARRAY_EMPTY_POINTER;
	}
	if (pArray->compare == NULL) {
		DEBUG_MESSAGE("compare fuction is not registered");
		return ARRAY_EMPTY_POINTER;
	}
	quickSort(0, pArray->currentSize - 1, pArray->pElements, pArray->compare);
	return ARRAY_OK;
}

/* write to file */
int array_writeToFile(const Array* pArray, const char* fileName)
{
	if (pArray == NULL || pArray->pElements == NULL) {
		DEBUG_MESSAGE("pArray or pElements is null");
		return ARRAY_EMPTY_POINTER;
	}
	if (fileName == NULL) {
		DEBUG_MESSAGE("fileName is null");
		return ARRAY_EMPTY_POINTER;
	}
	if (pArray->writeElement == NULL) {
		DEBUG_MESSAGE("write element is not registered");
		return ARRAY_EMPTY_POINTER;
	}
	int i = 0;
	FILE *fp = NULL;
	fp = fopen(fileName, "w+");
	if (fp == NULL) {
		DEBUG_MESSAGE("fp is NULL ");
		return ARRAY_EMPTY_POINTER;
	}
	for (i = 0; i < pArray->currentSize; i++) {
		pArray->writeElement(fp, pArray->pElements[i]);
	}
	fclose(fp);
	return ARRAY_OK;
}

/* read from file */
int array_readFromFile(Array* pArray, const char* fileName)
{
	if (pArray == NULL || pArray->pElements == NULL) {
		DEBUG_MESSAGE("pArray or pElements is null");
		return ARRAY_EMPTY_POINTER;
	}
	if (fileName == NULL) {
		DEBUG_MESSAGE("fileName is null");
		return ARRAY_EMPTY_POINTER;
	}
	if (pArray->readElement == NULL) {
		DEBUG_MESSAGE("read element is not registered");
		return ARRAY_EMPTY_POINTER;
	}
	int i = 0;
	FILE *fp = NULL;
	fp = fopen(fileName, "r+");
	if (fp == NULL) {
		DEBUG_MESSAGE("fp is NULL ");
		return ARRAY_EMPTY_POINTER;
	}
	for (i = 0; i < pArray->currentSize; i++) {
		pArray->readElement(fp, pArray->pElements[i]);
	}
	fclose(fp);
	return ARRAY_OK;
}


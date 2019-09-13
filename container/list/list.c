#include "list.h"
/* init list */
void list_init(list *pList)
{
	/* register function */
	pList->registerCreateElement = list_registerCreateElement;
	pList->registerFreeElement = list_registerFreeElement;
	pList->registerCompare = list_registerCompare;
	pList->registerCallBack = list_registerCallBack;
	pList->registerWriteElement = list_registerWriteElement;
	pList->registerReadElement = list_registerReadElement;
	/* free */
	pList->free = list_free;
	/* delete */
	pList->delete = list_delete;
	/* search */
	pList->search = list_search;
	/* push back */
	pList->push_back = list_push_back;
	/* pop back */
	pList->pop_back = list_pop_back;
	/* push front */
	pList->push_front = list_push_front;
	/* pop front */
	pList->pop_front = list_pop_front;
	/* insert by position */
	pList->insert1 = list_insertByPosition;
	/* delete by position */
	pList->remove1 = list_deleteByPosition;
	/* insert by element */
	pList->insert2 = list_insertByElement;
	/* delete by element */
	pList->remove2 = list_deleteByElement;
	/* sort */
	pList->sort = list_sort;
	/* reverse */
	pList->reverse = list_reverse;
	/* traverse */
	pList->traverse = list_traverse;
	/* write to file */
	pList->save = list_writeToFile;
	/* read from file */
	pList->load = list_readFromFile;
	return;
}
/* list_register function */
int list_registerCreateElement(list *pList, func createElement)
{
	if (pList == NULL || createElement == NULL) {
		DEBUG_MESSAGE("plist or new type is null");
		return LIST_EMPTY_POINTER;
	}
	pList->createElement = createElement;
	return LIST_OK;
}
int list_registerFreeElement(list *pList, func1 freeElement)
{
	if (pList == NULL) {
		DEBUG_MESSAGE("plist or delete type is null");
		return LIST_EMPTY_POINTER;
	}
	pList->freeElement = freeElement;
	return LIST_OK;
}
int list_registerCompare(list *pList, func2 compare)
{
	if (pList == NULL || compare == NULL) {
		DEBUG_MESSAGE("plist or compare is null");
		return LIST_EMPTY_POINTER;
	}
	pList->compare = compare;
	return LIST_OK;
}
int list_registerCallBack(list *pList, func2 callBack)
{
	if (pList == NULL || callBack == NULL) {
		DEBUG_MESSAGE("plist or callBack is null");
		return LIST_EMPTY_POINTER;
	}
	pList->callBack = callBack;
	return LIST_OK;
}
int list_registerWriteElement(list *pList, funcIO writeElement)
{
	if (pList == NULL || writeElement == NULL) {
		DEBUG_MESSAGE("plist or writeElement is null");
		return LIST_EMPTY_POINTER;
	}
	pList->writeElement = writeElement;
	return LIST_OK;
}
int list_registerReadElement(list *pList, funcIO readElement)
{
	if (pList == NULL || readElement == NULL) {
		DEBUG_MESSAGE("plist or readElement is null");
		return LIST_EMPTY_POINTER;
	}
	pList->readElement = readElement;
	return LIST_OK;
}

/* new */
list* list_new(int maxNum)
{
	list *pList = NULL;
	pList = (list*)malloc(sizeof(list));
	if (pList == NULL) {
		DEBUG_MESSAGE("list alloc failed");
		return NULL;
	}
	pList->head = NULL;
	pList->tail = NULL;
	pList->currentNum = 0;
	pList->maxNum = maxNum;
	list_init(pList);
	return pList;
}

/* free */
int list_free(list *pList)
{
	if (pList == NULL || pList->head == NULL) {
		DEBUG_MESSAGE("empty pointer");
		return LIST_EMPTY_POINTER;
	}
	Node *pNode = pList->head;
	Node *tmpNode = NULL;
	while (pNode != NULL) {
		tmpNode = pNode->next;
		if (pList->freeElement != NULL) {
			pList->freeElement(pNode->element);
		}
		free(pNode);
		pNode = tmpNode;
	}
	pList->head = NULL;
	pList->tail = NULL;
	pList->currentNum = 0;
	return LIST_OK;
}

/* delete */
int list_delete(list *pList) 
{
	if (pList == NULL) {
		DEBUG_MESSAGE("empty pointer");
		return LIST_EMPTY_POINTER;
	}
	if (pList->head == NULL) {
		free(pList);
	}
	return LIST_OK;
}
/* search */
Node *list_search(const list *pList, void *element)
{
	if (pList == NULL || pList->head == NULL || element == NULL) {
		DEBUG_MESSAGE("empty pointer");
		return NULL;
	}
	if (pList->compare == NULL) {
		DEBUG_MESSAGE("compare function is not registered");
		return NULL;
	}
	Node *pNode = pList->head;
	while (pNode != NULL) {
		if (pList->compare(pNode->element, element) == 0) {
			break;
		}
		pNode = pNode->next;
	}
	return pNode;
}

/* push back */
int list_push_back(list *pList, void* element)
{
	if (pList == NULL || element == NULL) {
		DEBUG_MESSAGE("empty pointer");
		return LIST_EMPTY_POINTER;
	}
	Node *pNode = NULL;
	pNode = (Node*)malloc(sizeof(Node));
	if (pNode == NULL) {
		DEBUG_MESSAGE("alloc failed");
		return LIST_MEM_ERR;
	}
	pNode->element = element;
	pNode->next = NULL;
	pNode->pre = NULL;
	if (pList->currentNum == 0) {
		pList->head = pNode;
		pList->tail = pList->head;
	} else {
		pList->tail->next = pNode;
		pNode->pre = pList->tail;
		pList->tail = pNode;
	}
	pList->currentNum++;
	return LIST_OK;
}

/* pop back */
int list_pop_back(list *pList)
{
	if (pList == NULL || pList->tail == NULL) {
		DEBUG_MESSAGE("empty pointer");
		return LIST_EMPTY_POINTER;
	}
	if (pList->currentNum == 0) {
		DEBUG_MESSAGE("size error");
		return LIST_SIZE_ERR;
	}
	Node *pNode = pList->tail;
	pList->tail = pNode->pre;
	pList->tail->next = NULL;
	pList->currentNum--;
	if (pList->freeElement != NULL) {
		pList->freeElement(pNode->element);
	}
	free(pNode);
	return LIST_OK;
}

/* push front */
int list_push_front(list *pList, void* element)
{
	if (pList == NULL || element == NULL) {
		DEBUG_MESSAGE("empty pointer");
		return LIST_EMPTY_POINTER;
	}
	Node *pNode = NULL;
	pNode = (Node*)malloc(sizeof(Node));
	if (pNode == NULL) {
		DEBUG_MESSAGE("alloc failed");
		return LIST_MEM_ERR;
	}
	pNode->element = element;
	pNode->next = NULL;
	pNode->pre = NULL;
	if (pList->currentNum == 0) {
		pList->head = pNode;
		pList->tail = pList->head;
	} else {
		pList->head->pre = pNode;
		pNode->next = pList->head;
		pList->head = pNode;
	}
	pList->currentNum++;
	return LIST_OK;
}

/* pop front */
int list_pop_front(list *pList)
{
	if (pList == NULL || pList->head == NULL) {
		DEBUG_MESSAGE("empty pointer");
		return LIST_EMPTY_POINTER;
	}
	if (pList->currentNum == 0) {
		DEBUG_MESSAGE("size error");
		return LIST_SIZE_ERR;
	}
	Node *pNode = pList->head;
	pList->head = pNode->next;
	pList->head->pre = NULL;
	pList->currentNum--;
	if (pList->freeElement != NULL) {
		pList->freeElement(pNode->element);
	}
	free(pNode);
	return LIST_OK;
}

/* insert by position */
int list_insertByPosition(list *pList, void* element, int position)
{
	if (pList == NULL) {
		DEBUG_MESSAGE("empty list");
		return LIST_EMPTY_POINTER;
	}
	if (element == NULL) {
		DEBUG_MESSAGE("element is null");
		return LIST_EMPTY_POINTER;
	}
	if (position > pList->currentNum) {
		DEBUG_MESSAGE("position is out of border");
		return LIST_ERR;
	}
	int i = 0;
	Node *pNode = NULL;
	Node *preNode = NULL;
	Node *nextNode = NULL; 
	pNode = (Node*)malloc(sizeof(Node));
	if (pNode == NULL) {
		DEBUG_MESSAGE("alloc failed");
		return LIST_MEM_ERR;
	}
	pNode->element = element;
	pNode->next = NULL;
	pNode->pre = NULL;
	if (pList->currentNum != 0) {
		if (position == 0) {
			nextNode = pList->head->next;
			pList->head = pNode;
			pNode->next = nextNode;
		} else if (position == pList->currentNum) {
			preNode = pList->tail;
			preNode->next = pNode;
			pNode->pre = preNode;
			pList->tail = pNode;
		} else {
			preNode = pList->head;
			for (i = 0; i < position; i++) {
				preNode = preNode->next;
			}
			nextNode = preNode->next;
			preNode->next = pNode;
			pNode->pre = preNode;
			pNode->next = nextNode;
			nextNode->pre = pNode;
		}
	} else {
		pList->head = pNode;
		pList->tail = pList->head;
	}
	pList->currentNum++;
	return LIST_OK;
}

/* delete by position */
int list_deleteByPosition(list *pList, int position)
{
	if (pList == NULL || pList->head == NULL) {
		DEBUG_MESSAGE("empty pointer");
		return LIST_EMPTY_POINTER;
	}
	if (pList->currentNum == 0) {
		DEBUG_MESSAGE("0 element");
		return LIST_SIZE_ERR;
	}
	if (position >= pList->currentNum) {
		DEBUG_MESSAGE("position is out of border");
		return LIST_ERR;
	}
	int i = 0;
	Node *pNode = pList->head;
	Node *preNode = NULL;
	Node *nextNode = NULL; 
	if (position == 0) {
		pList->head = pNode->next;
		pList->head->pre = NULL;
	} else if (position == pList->currentNum - 1) {
		pNode = pList->tail;
		pList->tail = pNode->pre;
		pList->tail->next = NULL;
	} else {
		for (i = 0; i < position; i++) {
			pNode = pNode->next;
		}
		nextNode = pNode->next;
		preNode = pNode->pre;
		preNode->next = nextNode;
		nextNode->pre = preNode;
	}
	pList->currentNum--;
	if (pList->freeElement != NULL) {
		pList->freeElement(pNode->element);
	}
	free(pNode);
	return LIST_OK;
}

/* insert by element */
int list_insertByElement(list *pList, void* preElement, void* element)
{
	if (pList == NULL || pList->head == NULL || element == NULL) {
		DEBUG_MESSAGE("empty pointer");
		return LIST_EMPTY_POINTER;
	}
	if (pList->compare == NULL) {
		DEBUG_MESSAGE("compare function is not registered");
		return LIST_EMPTY_POINTER;
	}
	if (pList->currentNum == 0) {
		DEBUG_MESSAGE("0 element");
		return LIST_EMPTY_POINTER;
	}
	Node *pNode = NULL;
	Node *preNode = pList->head;
	Node *nextNode = NULL; 
	while (preNode->next != NULL) {
		if (pList->compare(preNode->element, element) == 0) {
			break;
		}
		preNode = preNode->next;
	}
	if (preNode == NULL) {
		DEBUG_MESSAGE("element not found");
		return LIST_EMPTY_POINTER;
	}
	nextNode = preNode->next;
	pNode = (Node*)malloc(sizeof(Node));
	if (pNode == NULL) {
		DEBUG_MESSAGE("alloc failed");
		return LIST_MEM_ERR;
	}
	pNode->element = element;
	pNode->next = NULL;
	pNode->pre = NULL;
	preNode->next = pNode;
	pNode->pre = preNode;
	pNode->next = nextNode;
	if (nextNode != NULL) {
		nextNode->pre = pNode;
	}
	pList->currentNum++;
	return LIST_OK;
}

/* delete by element */
int list_deleteByElement(list *pList, void* element)
{
	if (pList == NULL || pList->head == NULL || element == NULL) {
		DEBUG_MESSAGE("empty pointer");
		return LIST_EMPTY_POINTER;
	}
	if (pList->currentNum == 0) {
		DEBUG_MESSAGE("0 element");
		return LIST_SIZE_ERR;
	}
	if (pList->compare == NULL) {
		DEBUG_MESSAGE("compare function is not registered");
		return LIST_EMPTY_POINTER;
	}
	Node *pNode = pList->head;
	Node *preNode = NULL;
	Node *nextNode = NULL; 
	while (pNode->next != NULL) {
		if (pList->compare(pNode->element, element) == 0) {
			break;
		}
		pNode = pNode->next;
	}
	if (pNode == NULL) {
		DEBUG_MESSAGE("element is not found");
		return LIST_EMPTY_POINTER;
	}
	nextNode = pNode->next;
	preNode = pNode->pre;
	preNode->next = nextNode;
	nextNode->pre = preNode;
	pList->currentNum--;
	if (pList->freeElement != NULL) {
		pList->freeElement(pNode->element);
	}
	free(pNode);
	return LIST_OK;
}
static int list_quickSort(Node *first, Node *last, list *pList)
{
	if (first == last) {
		return 0;
	}
	Node *pi = first;
	Node *pj = last;
	void *ref = first->element;
	while (pi != NULL && pj != NULL) {
		while (pj != NULL && pList->compare(pj->element, ref) > 0) {
			pj = pj->pre;
		}
		pi->element = pj->element;

		while (pi != NULL && pList->compare(pi->element, ref) < 0) {
			pi = pi->next;
		}
		pj->element = pi->element;
	}
	pi->element = ref;
	list_quickSort(first, pi, pList);
	list_quickSort(pi->next, last, pList);
	return 0;
}
static void list_bubbleSort(list *pList)
{
	Node *pNode1 = NULL;
	Node *pNode2 = NULL;
	void* tmp = NULL;
	pNode1 = pList->head;
	while (pNode1->next != NULL) {
		pNode2 = pNode1->next;
		while (pNode2->next != NULL) {
			if (pList->compare(pNode1->element, pNode2->element) < 0) {
				tmp = pNode1->element;
				pNode1->element = pNode2->element;
				pNode2->element = tmp;
			}
			pNode2 = pNode2->next;
		}
		pNode1 = pNode1->next;
	}
	return;
}
/* sort */
int list_sort(list *pList)
{
	if (pList == NULL || pList->head == NULL || pList->tail == NULL) {
		DEBUG_MESSAGE("empty pointer");
		return LIST_EMPTY_POINTER;
	}
	if (pList->currentNum <= 1) {
		DEBUG_MESSAGE("0 or 1 element");
		return LIST_SIZE_ERR;
	}
	if (pList->compare == NULL) {
		DEBUG_MESSAGE("compare is not registered");
		return LIST_EMPTY_POINTER;
	}
	list_bubbleSort(pList);
	return LIST_OK;
}

/* reverse */
int list_reverse(list *pList)
{
	if (pList == NULL || pList->head == NULL || pList->tail == NULL) {
		DEBUG_MESSAGE("empty pointer");
		return LIST_EMPTY_POINTER;
	}
	if (pList->currentNum <= 1) {
		DEBUG_MESSAGE("0 or 1 element");
		return LIST_SIZE_ERR;
	}
	pList->tail = pList->head;
	Node *pNode0 = NULL;
	Node *pNode1 = pList->head;
	Node *pNode2 = NULL;
	while (pNode1 != NULL) {
		pNode2 = pNode1->next;
		pNode1->next = pNode0;
		pNode1->pre = pNode2;
		pNode0 = pNode1;
		pNode1 = pNode2;
	}
	pList->head = pNode0;
	return LIST_OK;
}

/* traverse */
int list_traverse(const list *pList, void* item)
{
	if (pList == NULL || pList->head == NULL) {
		DEBUG_MESSAGE("empty pointer");
		return LIST_EMPTY_POINTER;
	}
	if (pList->callBack == NULL) {
		DEBUG_MESSAGE("call back function is not register");
		return LIST_EMPTY_POINTER;
	}
	Node *pNode = pList->head;
	while (pNode != NULL) {
		pList->callBack(pNode->element, item);
		pNode = pNode->next;
	}
	return LIST_OK;
}

/* write to file */
int list_writeToFile(list *pList, const char* fileName)
{
	if (pList == NULL || pList->head == NULL) {
		DEBUG_MESSAGE("pList or pList head is null");
		return LIST_EMPTY_POINTER;
	}
	if (fileName == NULL) {
		DEBUG_MESSAGE("fileName is null");
		return LIST_EMPTY_POINTER;
	}
	if (pList->writeElement == NULL) {
		DEBUG_MESSAGE("writeElement is null");
		return LIST_EMPTY_POINTER;
	}
	FILE *fp = NULL;
	fp = fopen(fileName, "w+");
	if (fp == NULL) {
		DEBUG_MESSAGE("open file failed");
		return LIST_EMPTY_POINTER;
	}
	Node *pNode = pList->head;
	while (pNode != NULL) {
		pList->writeElement(fp, pNode->element);
		pNode = pNode->next;
	}
	fclose(fp);
	return LIST_OK;
}

/* read from file */
int list_readFromFile(list *pList, const char* fileName)
{
	if (pList == NULL || pList->head == NULL) {
		DEBUG_MESSAGE("pList or pList head is null");
		return LIST_EMPTY_POINTER;
	}
	if (fileName == NULL) {
		DEBUG_MESSAGE("fileName is null");
		return LIST_EMPTY_POINTER;
	}
	if (pList->readElement == NULL) {
		DEBUG_MESSAGE("readElement is null");
		return LIST_EMPTY_POINTER;
	}
	FILE *fp = NULL;
	fp = fopen(fileName, "r");
	if (fp == NULL) {
		DEBUG_MESSAGE("open file failed");
		return LIST_EMPTY_POINTER;
	}
	Node *pNode = pList->head;
	while (pNode != NULL) {
		pList->readElement(fp, pNode->element);
		pNode = pNode->next;
	}
	fclose(fp);
	return LIST_OK;
}


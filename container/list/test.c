#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "list.h"
#include "../student.h"
#include "../../basic.h"
extern void student_showAdapter(void *pStu);
extern int student_writeAdapter(FILE *fp,void *pStu);
extern int student_readAdapter(FILE *fp, void *pStu);
extern int student_compareAdapter(void *pStu1, void  *pStu2);
extern void* student_newAdapter();
extern int student_deleteAdapter(void* pStu);
int list_printElement(void* element1, void* element2) 
{
	student_showAdapter(element1);
	return LIST_OK; 
}
int main()
{
	int ret = 0;;
	list *plist = NULL;
	/* create */
	plist = list_new(10);
	if (plist == NULL) {
		DEBUG_MESSAGE("new list failed");
		return 0;
	}
	/* register function */
	ret = plist->registerCreateElement(plist, student_newAdapter);
	DEBUG_ASSERT(ret == LIST_OK, 0);
	ret = plist->registerFreeElement(plist, student_deleteAdapter);
	DEBUG_ASSERT(ret == LIST_OK, 0);
	ret = plist->registerCompare(plist, student_compareAdapter);
	DEBUG_ASSERT(ret == LIST_OK, 0);
	ret = plist->registerWriteElement(plist, student_writeAdapter);
	DEBUG_ASSERT(ret == LIST_OK, 0);
	ret = plist->registerReadElement(plist, student_readAdapter);
	DEBUG_ASSERT(ret == LIST_OK, 0);
	plist->registerCallBack(plist, list_printElement);
	/* new instance */
	student *stu1 = student_new("google", 10, 20);
	student *stu2 = student_new("microsoft", 20, 30);
	student *stu3 = student_new("apple", 30, 30);
	student *stu4 = student_new("ibm", 40, 40);
	student *stu5 = student_new("aws", 50, 20);
	student *stu6 = student_new("ali", 60, 20);
	student *stu7 = student_new("huawei", 70, 30);
	student *stu8 = student_new("tecent", 80, 20);
	/* insert by index */
	ret = plist->insert1(plist, (void*)stu1, 0);
	DEBUG_ASSERT(ret == LIST_OK, 0);
	ret = plist->insert1(plist, (void*)stu2, 1);
	DEBUG_ASSERT(ret == LIST_OK, 0);
	/* insert by element */
	ret = plist->insert2(plist, (void*)stu2, (void*)stu3);
	DEBUG_ASSERT(ret == LIST_OK, 0);
	ret = plist->insert2(plist, (void*)stu3, (void*)stu4);
	DEBUG_ASSERT(ret == LIST_OK, 0);
	/* push back */
	ret = plist->push_back(plist, (void*)stu5);
	DEBUG_ASSERT(ret == LIST_OK, 0);
	ret = plist->push_back(plist, (void*)stu6);
	DEBUG_ASSERT(ret == LIST_OK, 0);
	ret = plist->push_back(plist, (void*)stu7);
	DEBUG_ASSERT(ret == LIST_OK, 0);
	/* push front */
	ret = plist->push_front(plist, (void*)stu8);
	DEBUG_ASSERT(ret == LIST_OK, 0);
	/* print element */
	printf("%s\n", "------------add----------------------");
	ret = plist->traverse(plist, NULL);
	DEBUG_ASSERT(ret == LIST_OK, 0);
	/* reverse */
	ret = plist->reverse(plist);
	DEBUG_ASSERT(ret == LIST_OK, 0);
	printf("%s\n", "------------reverse----------------------");
	plist->traverse(plist, NULL);
	/* search return index */
	Node* pNode = plist->search(plist, (void*)stu1);
	DEBUG_ASSERT(pNode != NULL, 0);
	/* write to file */
	ret = plist->save(plist, "companie01.txt");
	DEBUG_ASSERT(ret == LIST_OK, 0);
	/* delete by index */
	ret = plist->remove1(plist, 0);
	DEBUG_ASSERT(ret == LIST_OK, 0);
	/* delete by element */
	ret = plist->remove2(plist, (void*)stu2);
	DEBUG_ASSERT(ret == LIST_OK, 0);
	/* pop back */
	ret = plist->pop_back(plist);
	DEBUG_ASSERT(ret == LIST_OK, 0);
	/* pop front */
	ret = plist->pop_front(plist);
	DEBUG_ASSERT(ret == LIST_OK, 0);
	/* print element */
	printf("%s\n", "-------------delete ------------------");
	ret = plist->traverse(plist, NULL);
	DEBUG_ASSERT(ret == LIST_OK, 0);
	/* write to file */
	ret = plist->save(plist, "companie02.txt");
	DEBUG_ASSERT(ret == LIST_OK, 0);
	/* free */
	ret = plist->free(plist);
	DEBUG_ASSERT(ret == LIST_OK, 0);
	/* read from file */
	ret = plist->registerFreeElement(plist, NULL);
	DEBUG_ASSERT(ret == LIST_OK, 0);
	student stu[6];
	int i = 0;
	for (i = 0; i < 6; i++) {
		plist->push_back(plist, (void*)&stu[i]);
	}
	ret = plist->load(plist, "companie01.txt");
	DEBUG_ASSERT(ret == LIST_OK, 0);
	/* print element */
	printf("%s\n", "-------------load ------------------");
	ret = plist->traverse(plist, NULL);
	DEBUG_ASSERT(ret == LIST_OK, 0);
	/* sort */
	ret = plist->sort(plist);
	DEBUG_ASSERT(ret == LIST_OK, 0);
	/* print element */
	printf("%s\n", "-------------sort ------------------");
	ret = plist->traverse(plist, NULL);
	DEBUG_ASSERT(ret == LIST_OK, 0);
	/* delete */
	ret = plist->delete(plist);
	DEBUG_ASSERT(ret == LIST_OK, 0);
	return 0;
}

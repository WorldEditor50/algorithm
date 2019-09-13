#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "array.h"
#include "../student.h"
#include "../../basic.h"
extern void student_showAdapter(void *pStu);
extern int student_writeAdapter(FILE *fp,void *pStu);
extern int student_readAdapter(FILE *fp, void *pStu);
extern int student_compareAdapter(void *pStu1, void  *pStu2);
extern void* student_newAdapter();
extern int student_deleteAdapter(void* pStu);
int array_printElement(void* element1, void* element2) 
{
	student_showAdapter(element1);
	return ARRAY_OK; 
}
int main()
{
	int ret = 0;
	Array *pArray = NULL;
	/* create */
	pArray = array_new(10);
	if (pArray == NULL) {
		DEBUG_MESSAGE("new array failed");
		return 0;
	}
	/* register function */
	ret = pArray->registerCreateElement(pArray, student_newAdapter);
	DEBUG_ASSERT(ret == ARRAY_OK, 0);
	ret = pArray->registerFreeElement(pArray, student_deleteAdapter);
	DEBUG_ASSERT(ret == ARRAY_OK, 0);
	ret = pArray->registerCompare(pArray, student_compareAdapter);
	DEBUG_ASSERT(ret == ARRAY_OK, 0);
	ret = pArray->registerWriteElement(pArray, student_writeAdapter);
	DEBUG_ASSERT(ret == ARRAY_OK, 0);
	ret = pArray->registerReadElement(pArray, student_readAdapter);
	DEBUG_ASSERT(ret == ARRAY_OK, 0);
	/* new instance */
	student *stu1 = student_new("google", 10, 20);
	student *stu2 = student_new("microsoft", 20, 30);
	student *stu3 = student_new("apple", 30, 30);
	student *stu4 = student_new("ibm", 40, 40);
	student *stu5 = student_new("aws", 50, 20);
	student *stu6 = student_new("ali", 60, 20);
	student *stu7 = student_new("huawei", 70, 30);
	student *stu8 = student_new("tecent", 80, 20);
	/* shift left */
	ret = pArray->shiftLeft(pArray, 2, 4, 2);
	DEBUG_ASSERT(ret == ARRAY_OK, 0);
	/* shift right */
	ret = pArray->shiftRight(pArray, 0, 2, 2);
	DEBUG_ASSERT(ret == ARRAY_OK, 0);
	/* insert by index */
	ret = pArray->insert1(pArray, (void*)stu1, 0);
	DEBUG_ASSERT(ret == ARRAY_OK, 0);
	ret = pArray->insert1(pArray, (void*)stu2, 1);
	DEBUG_ASSERT(ret == ARRAY_OK, 0);
	/* insert by element */
	ret = pArray->insert2(pArray, (void*)stu3, (void*)stu2);
	DEBUG_ASSERT(ret == ARRAY_OK, 0);
	ret = pArray->insert2(pArray, (void*)stu4, (void*)stu3);
	DEBUG_ASSERT(ret == ARRAY_OK, 0);
	/* push back */
	ret = pArray->push_back(pArray, (void*)stu5);
	DEBUG_ASSERT(ret == ARRAY_OK, 0);
	ret = pArray->push_back(pArray, (void*)stu6);
	DEBUG_ASSERT(ret == ARRAY_OK, 0);
	ret = pArray->push_back(pArray, (void*)stu7);
	DEBUG_ASSERT(ret == ARRAY_OK, 0);
	/* push front */
	ret = pArray->push_front(pArray, (void*)stu8);
	DEBUG_ASSERT(ret == ARRAY_OK, 0);
	/* search return index */
	ret = pArray->search(pArray, (void*)stu1);
	DEBUG_ASSERT(ret == 1, 0);
	/* sort */
	ret = pArray->sort(pArray);
	DEBUG_ASSERT(ret == ARRAY_OK, 0);
	/* print element */
	printf("%s\n", "------------add----------------------");
	pArray->registerCallBack(pArray, array_printElement);
	ret = pArray->traverse(pArray, NULL);
	DEBUG_ASSERT(ret == ARRAY_OK, 0);
	/* write to file */
	ret = pArray->save(pArray, "companies.txt");
	DEBUG_ASSERT(ret == ARRAY_OK, 0);
	/* delete by index */
	ret = pArray->remove1(pArray, 0);
	DEBUG_ASSERT(ret == ARRAY_OK, 0);
	/* delete by element */
	ret = pArray->remove2(pArray, (void*)stu2);
	DEBUG_ASSERT(ret == ARRAY_OK, 0);
	/* pop back */
	ret = pArray->pop_back(pArray);
	DEBUG_ASSERT(ret == ARRAY_OK, 0);
	/* pop front */
	ret = pArray->pop_front(pArray);
	DEBUG_ASSERT(ret == ARRAY_OK, 0);
	/* print element */
	printf("%s\n", "-------------delete ------------------");
	ret = pArray->traverse(pArray, NULL);
	DEBUG_ASSERT(ret == ARRAY_OK, 0);
	/* write to file */
	ret = pArray->save(pArray, "companies_02.txt");
	DEBUG_ASSERT(ret == ARRAY_OK, 0);
	/* resize */
	ret = pArray->resize(pArray, 20);
	DEBUG_ASSERT(ret == ARRAY_OK, 0);
	DEBUG_ASSERT(pArray->maxSize == 20, 0);
	/* free element */
	ret = pArray->free(pArray);
	DEBUG_ASSERT(ret == ARRAY_OK, 0);
	/* read from file */
	student stu[8];
	int i = 0;
	for (i = 0; i < 8; i++) {
		pArray->push_back(pArray, (void*)&stu[i]);
	}
	ret = pArray->load(pArray, "companies.txt");
	DEBUG_ASSERT(ret == ARRAY_OK, 0);
	/* print element */
	printf("%s\n", "-------------load ------------------");
	ret = pArray->traverse(pArray, NULL);
	DEBUG_ASSERT(ret == ARRAY_OK, 0);
	/* delete */
	ret = pArray->delete(pArray);
	DEBUG_ASSERT(ret == ARRAY_OK, 0);
	return 0;
}

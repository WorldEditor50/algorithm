#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "btree.h"
#include "../student.h"
#include "../../basic.h"
extern void student_showAdapter(void *pStu);
extern int student_writeAdapter(FILE *fp,void *pStu);
extern int student_readAdapter(FILE *fp, void *pStu);
extern int student_compareAdapter(void *pStu1, void  *pStu2);
extern void* student_newAdapter();
extern int student_deleteAdapter(void* pStu);
int tree_printElement(void* element1, void* element2) 
{
	student_showAdapter(element1);
	return 0; 
}
int main()
{
	int ret = 0;
	BTree *ptree = NULL;
	/* create */
	ptree = BTree_new(student_compareAdapter);
	if (ptree == NULL) {
		DEBUG_MESSAGE("new tree failed");
		return 0;
	}
	/* register function */
	ret = ptree->registerCreateElement(ptree, student_newAdapter);
	DEBUG_ASSERT(ret == 0, 0);
	ret = ptree->registerFreeElement(ptree, student_deleteAdapter);
	DEBUG_ASSERT(ret == 0, 0);
	ret = ptree->registerWriteElement(ptree, student_writeAdapter);
	DEBUG_ASSERT(ret == 0, 0);
	ret = ptree->registerReadElement(ptree, student_readAdapter);
	DEBUG_ASSERT(ret == 0, 0);
	ptree->registerCallBack(ptree, tree_printElement);
	/* new instance */
	student *stu1 = student_new("google", 40, 20);
	student *stu2 = student_new("microsoft", 20, 30);
	student *stu3 = student_new("apple", 50, 30);
	student *stu4 = student_new("ibm", 30, 40);
	student *stu5 = student_new("aws", 45, 20);
	student *stu6 = student_new("ali", 10, 20);
	student *stu7 = student_new("huawei", 70, 30);
	student *stu8 = student_new("tecent", 25, 20);
	/* insert */
	ret = ptree->insert(ptree, (void*)stu1);
	DEBUG_ASSERT(ret == 0, 0);
	ret = ptree->insert(ptree, (void*)stu2);
	DEBUG_ASSERT(ret == 0, 0);
	ret = ptree->insert(ptree, (void*)stu3);
	DEBUG_ASSERT(ret == 0, 0);
	ret = ptree->insert(ptree, (void*)stu4);
	DEBUG_ASSERT(ret == 0, 0);
	ret = ptree->insert(ptree, (void*)stu5);
	DEBUG_ASSERT(ret == 0, 0);
	ret = ptree->insert(ptree, (void*)stu6);
	DEBUG_ASSERT(ret == 0, 0);
	ret = ptree->insert(ptree, (void*)stu7);
	DEBUG_ASSERT(ret == 0, 0);
	ret = ptree->insert(ptree, (void*)stu8);
	DEBUG_ASSERT(ret == 0, 0);
	/* print element */
	printf("%s\n", "------------add----------------------");
	ret = ptree->traverse(ptree, NULL);
	DEBUG_ASSERT(ret == 0, 0);
	/* search */
	ret = ptree->search(ptree, (void*)stu5);
	DEBUG_ASSERT(ret == 0, 0);
	/* write to file */
	ret = ptree->save(ptree, "companie01.txt");
	DEBUG_ASSERT(ret == 0, 0);
	/* remove element */
	ret = ptree->remove(ptree, (void*)stu2);
	DEBUG_ASSERT(ret == 0, 0);
	ret = ptree->remove(ptree, (void*)stu7);
	DEBUG_ASSERT(ret == 0, 0);
	/* print element */
	printf("%s\n", "-------------delete ------------------");
	ret = ptree->traverse(ptree, NULL);
	DEBUG_ASSERT(ret == 0, 0);
	/* write to file */
	ret = ptree->save(ptree, "companie02.txt");
	DEBUG_ASSERT(ret == 0, 0);
	/* free */
	ret = ptree->free(ptree);
	DEBUG_ASSERT(ret == 0, 0);
	/* read from file */
	ret = ptree->load(ptree, "companie03.txt", 6);
	DEBUG_ASSERT(ret == 0, 0);
	/* print element */
	printf("%s\n", "-------------load ------------------");
	ret = ptree->traverse(ptree, NULL);
	DEBUG_ASSERT(ret == 0, 0);
	/* free */
	ret = ptree->free(ptree);
	DEBUG_ASSERT(ret == 0, 0);
	/* delete */
	ret = ptree->delete(ptree);
	DEBUG_ASSERT(ret == 0, 0);
	return 0;
}

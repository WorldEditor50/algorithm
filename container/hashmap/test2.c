#include "hashmap.h"

#define TEST_ASSERT(condition, message) do { \
	if ((condition)) { \
		HASHMAP_MESSAGE(message); \
	} \
} while (0)

typedef struct Student {
	char pcName[64];
	int iAge;
	int iScore;
} Student;

void* Student_New(const char* pcName, int iAge, int iScore)
{
	Student* pstStudent = (Student*)malloc(sizeof(Student));
	if (pstStudent == NULL) {
		return NULL;
	}
	strcpy(pstStudent->pcName, pcName);
	pstStudent->iAge = iAge;
	pstStudent->iScore = iScore;
	return (void*)pstStudent;
}
void* Student_NewAdapter()
{
	Student* pstStudent = (Student*)malloc(sizeof(Student));
	if (pstStudent == NULL) {
		return NULL;
	}
	pstStudent->iAge = 0;
	pstStudent->iScore = 0;
	return (void*)pstStudent;
}

void Student_Delete(void* pvStudent)
{
	free(pvStudent);
	return;
}
int Student_Show(HashNode* pstNode, void* pvArg)
{
	Student* pstStudent = (Student*)pstNode->pValue;
	printf("%s  %s  %d  %d\n", pstNode->pcKey, pstStudent->pcName, pstStudent->iAge, pstStudent->iScore);
	return 0;
}

void Student_Write(void* pvStudent, FILE* pstFile)
{
	char acBuffer[256] = {0};
	Student* pstStudent = (Student*)pvStudent;
	sprintf(acBuffer, "%s,%d,%d,\n", pstStudent->pcName, pstStudent->iAge, pstStudent->iScore);
	fputs(acBuffer, pstFile);
	return;
}
void Student_Read(void** ppvStudent, FILE* pstFile)
{
	char acBuffer[256] = {0};
	char* pcName = NULL;
	char* pcAge = NULL;
	char* pcScore = NULL;
	Student* pstStudent = (Student*)malloc(sizeof(Student));
	if (pstStudent == NULL) {
		return;
	}
	/* read */
	fgets(acBuffer, 256, pstFile);
	pcName = strtok(acBuffer, ",");
	pcAge = strtok(acBuffer + strlen(pcName) + 1, ",");
	pcScore = strtok(acBuffer + strlen(pcName) + strlen(pcAge) + 2, ",");
	/* assign */
	strcpy(pstStudent->pcName, pcName);
	pstStudent->iAge = atoi(pcAge);
	pstStudent->iScore = atoi(pcScore);
	*ppvStudent = (void*)pstStudent;
	return;
}

void test_student()
{
	int iRet = HASHMAP_OK;
	HashMap* pstMap = NULL;
	/* create hashmap */
	pstMap = HashMap_Create(10);
	if (pstMap == NULL) {
		HASHMAP_MESSAGE("failed to create hashmap");
		return;
	}
	/* register object */
	iRet = HashMap_RegisterObject(pstMap, Student_Delete, Student_NewAdapter, Student_Write, Student_Read);
	TEST_ASSERT(iRet != HASHMAP_OK, "failed to insert");
	/* insert */
	void* pvStu = NULL;
	pvStu = Student_New("sauron", 1000, 100);
	iRet = HashMap_Insert(pstMap, "modor", pvStu);
	TEST_ASSERT(iRet != HASHMAP_OK, "failed to insert");
	pvStu = Student_New("gandalf", 800, 30);
	iRet = HashMap_Insert(pstMap, "valinor", pvStu);
	TEST_ASSERT(iRet != HASHMAP_OK, "failed to insert");
	pvStu = Student_New("frodo", 80, 9);
	iRet = HashMap_Insert(pstMap, "middle_earth", pvStu);
	TEST_ASSERT(iRet != HASHMAP_OK, "failed to insert");
	pvStu = Student_New("legolas", 200, 15);
	iRet = HashMap_Insert(pstMap, "mirkwood", pvStu);
	TEST_ASSERT(iRet != HASHMAP_OK, "failed to insert");
	pvStu = Student_New("melkor", 10000, 1000);
	iRet = HashMap_Insert(pstMap, "Arda", pvStu);
	TEST_ASSERT(iRet != HASHMAP_OK, "failed to insert");
	pvStu = Student_New("aragorn", 100, 10);
	iRet = HashMap_Insert(pstMap, "gondor", pvStu);
	TEST_ASSERT(iRet != HASHMAP_OK, "failed to insert");
	/* delete */
	pvStu = Student_New("aragorn", 100, 10);
	iRet = HashMap_Insert(pstMap, "gondor", pvStu);
	TEST_ASSERT(iRet != HASHMAP_OK, "failed to insert");
	iRet = HashMap_Delete(pstMap, "gondor");
	TEST_ASSERT(iRet != HASHMAP_OK, "failed to delete");
	iRet = HashMap_Delete(pstMap, "gondor");
	TEST_ASSERT(iRet != HASHMAP_OK, "failed to delete");
	/* search */
	void* pValue = NULL;
	iRet = HashMap_Search(pstMap, "modor", &pValue);
	TEST_ASSERT(iRet != HASHMAP_OK, "failed to search");
	if (pValue != NULL) {
		Student* pstStudent = (Student*)pValue;
		printf("search:  %s  %d  %d\n", pstStudent->pcName, pstStudent->iAge, pstStudent->iScore);
	}
	/* print */
	iRet = HashMap_Traverse(pstMap, Student_Show, NULL);
	TEST_ASSERT(iRet != HASHMAP_OK, "failed to traverse");
	/* save */
	iRet = HashMap_Save(pstMap, "./test2.txt");
	TEST_ASSERT(iRet != HASHMAP_OK, "failed to save");
	/* destroy hashmap */
	HashMap_Destroy(pstMap);
	return;
}
void test_load()
{
	int iRet = HASHMAP_OK;
	HashMap* pstMap = NULL;
	/* create hashmap */
	pstMap = HashMap_Create(10);
	if (pstMap == NULL) {
		HASHMAP_MESSAGE("failed to create hashmap");
		return;
	}
	/* register object */
	iRet = HashMap_RegisterObject(pstMap, Student_Delete, Student_NewAdapter, Student_Write, Student_Read);
	TEST_ASSERT(iRet != HASHMAP_OK, "failed to insert");
	/* load */
	iRet = HashMap_Load(pstMap, "./test2.txt");
	TEST_ASSERT(iRet != HASHMAP_OK, "failed to save");
	/* print */
	iRet = HashMap_Traverse(pstMap, Student_Show, NULL);
	TEST_ASSERT(iRet != HASHMAP_OK, "failed to traverse");
	/* destroy hashmap */
	HashMap_Destroy(pstMap);
	return;
}
int main()
{
	//test_student();
	test_load();
	return 0;
}

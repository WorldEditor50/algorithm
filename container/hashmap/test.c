#include "hashmap.h"
#define TEST_ASSERT(condition, message) do { \
	if ((condition)) { \
		HASHMAP_MESSAGE(message); \
	} \
} while (0)
void freeValue(void* pValue)
{
	free((char*)pValue);
	return;
}
int printHashNode(HashNode* pstNode, void* pArg)
{
	printf("%s\t%s\n", pstNode->pcKey, (char*)pstNode->pValue);
	return 0;
}
void test_HashMap()
{
	int iRet = HASHMAP_OK;
	HashMap* pstMap = NULL;
	/* create hashmap */
	pstMap = HashMap_Create(10, freeValue);
	if (pstMap == NULL) {
		HASHMAP_MESSAGE("failed to create hashmap");
		return;
	}
	/* insert */
	iRet = HashMap_Insert(pstMap, "china", strdup("beijing"));
	TEST_ASSERT(iRet != HASHMAP_OK, "failed to insert");
	iRet = HashMap_Insert(pstMap, "japan", strdup("tokyo"));
	TEST_ASSERT(iRet != HASHMAP_OK, "failed to insert");
	iRet = HashMap_Insert(pstMap, "america", strdup("washington"));
	TEST_ASSERT(iRet != HASHMAP_OK, "failed to insert");
	iRet = HashMap_Insert(pstMap, "british", strdup("london"));
	TEST_ASSERT(iRet != HASHMAP_OK, "failed to insert");
	iRet = HashMap_Insert(pstMap, "russian", strdup("moscow"));
	TEST_ASSERT(iRet != HASHMAP_OK, "failed to insert");
	iRet = HashMap_Insert(pstMap, "Afghanistan", strdup("Kabul"));
	TEST_ASSERT(iRet != HASHMAP_OK, "failed to insert");
	iRet = HashMap_Insert(pstMap, "Brazil", strdup("Brasilia"));
	TEST_ASSERT(iRet != HASHMAP_OK, "failed to insert");
	iRet = HashMap_Insert(pstMap, "Canada", strdup("Ottawa"));
	TEST_ASSERT(iRet != HASHMAP_OK, "failed to insert");
	iRet = HashMap_Insert(pstMap, "Denmark", strdup("Copenhagen"));
	TEST_ASSERT(iRet != HASHMAP_OK, "failed to insert");
	iRet = HashMap_Insert(pstMap, "Egypt", strdup("Cairo"));
	TEST_ASSERT(iRet != HASHMAP_OK, "failed to insert");
	iRet = HashMap_Insert(pstMap, "France", strdup("Paris"));
	TEST_ASSERT(iRet != HASHMAP_OK, "failed to insert");
	iRet = HashMap_Insert(pstMap, "Germany", strdup("Berlin"));
	TEST_ASSERT(iRet != HASHMAP_OK, "failed to insert");
	iRet = HashMap_Insert(pstMap, "Hungary", strdup("Budapest"));
	TEST_ASSERT(iRet != HASHMAP_OK, "failed to insert");
	iRet = HashMap_Insert(pstMap, "Iran", strdup("Tehran"));
	TEST_ASSERT(iRet != HASHMAP_OK, "failed to insert");
	iRet = HashMap_Insert(pstMap, "Jordan", strdup("Amman"));
	TEST_ASSERT(iRet != HASHMAP_OK, "failed to insert");
	iRet = HashMap_Insert(pstMap, "Kenya", strdup("Nairobi"));
	TEST_ASSERT(iRet != HASHMAP_OK, "failed to insert");
	iRet = HashMap_Insert(pstMap, "Libya", strdup("Tripoli"));
	TEST_ASSERT(iRet != HASHMAP_OK, "failed to insert");
	iRet = HashMap_Insert(pstMap, "Mexico", strdup("Mexico City"));
	TEST_ASSERT(iRet != HASHMAP_OK, "failed to insert");
	iRet = HashMap_Insert(pstMap, "Niger", strdup("Niamey"));
	TEST_ASSERT(iRet != HASHMAP_OK, "failed to insert");
	iRet = HashMap_Insert(pstMap, "Oman", strdup("Muscat"));
	TEST_ASSERT(iRet != HASHMAP_OK, "failed to insert");
	iRet = HashMap_Insert(pstMap, "Pakistan", strdup("Islamabad"));
	TEST_ASSERT(iRet != HASHMAP_OK, "failed to insert");
	iRet = HashMap_Insert(pstMap, "Qatar", strdup("Doha"));
	TEST_ASSERT(iRet != HASHMAP_OK, "failed to insert");
	iRet = HashMap_Insert(pstMap, "Romania", strdup("Bucharest"));
	TEST_ASSERT(iRet != HASHMAP_OK, "failed to insert");
	iRet = HashMap_Insert(pstMap, "Serbia", strdup("Belgrade"));
	TEST_ASSERT(iRet != HASHMAP_OK, "failed to insert");
	iRet = HashMap_Insert(pstMap, "Thailand", strdup("Bangkok"));
	TEST_ASSERT(iRet != HASHMAP_OK, "failed to insert");
	iRet = HashMap_Insert(pstMap, "Ukraine", strdup("Kyiv"));
	TEST_ASSERT(iRet != HASHMAP_OK, "failed to insert");
	iRet = HashMap_Insert(pstMap, "Vietnam", strdup("Hanoi"));
	TEST_ASSERT(iRet != HASHMAP_OK, "failed to insert");
	iRet = HashMap_Insert(pstMap, "Yemen", strdup("Sana"));
	TEST_ASSERT(iRet != HASHMAP_OK, "failed to insert");
	iRet = HashMap_Insert(pstMap, "Zambia", strdup("Lusaka"));
	TEST_ASSERT(iRet != HASHMAP_OK, "failed to insert");
	iRet = HashMap_Insert(pstMap, "X-place", strdup("heart"));
	TEST_ASSERT(iRet != HASHMAP_OK, "failed to insert");
	/* delete */
	iRet = HashMap_Insert(pstMap, "Ukraine", strdup("Kyiv"));
	TEST_ASSERT(iRet != HASHMAP_OK, "failed to insert");
	iRet = HashMap_Insert(pstMap, "Ukraine", strdup("Kyiv"));
	TEST_ASSERT(iRet != HASHMAP_OK, "failed to insert");
	iRet = HashMap_Delete(pstMap, "Ukraine");
	TEST_ASSERT(iRet != HASHMAP_OK, "failed to delete");
	iRet = HashMap_Delete(pstMap, "X-place");
	TEST_ASSERT(iRet != HASHMAP_OK, "failed to delete");
	iRet = HashMap_Delete(pstMap, "Ukraine");
	TEST_ASSERT(iRet != HASHMAP_OK, "failed to delete");
	iRet = HashMap_Delete(pstMap, "Ukraine");
	TEST_ASSERT(iRet != HASHMAP_OK, "failed to delete");
	/* search */
	char* pcValue = NULL;
	iRet = HashMap_Search(pstMap, "china", (void**)&pcValue);
	TEST_ASSERT(iRet != HASHMAP_OK, "failed to search");
	if (pcValue != NULL) {
		printf("value = %s\n", pcValue);
	}
	/* print */
	iRet = HashMap_Traverse(pstMap, printHashNode, NULL);
	TEST_ASSERT(iRet != HASHMAP_OK, "failed to traverse");
	/* destroy hashmap */
	HashMap_Destroy(pstMap);
	return;
}
void test_HashNode()
{
	HashNode* pstNode = NULL;
	pstNode = HashMap_CreateNode("china", strdup("beijing"));
	if (pstNode == NULL) {
		HASHMAP_MESSAGE("failed to ");
		return;
	}
	printHashNode(pstNode, NULL);
	HashMap_DestroyNode(pstNode, freeValue);
	return;
}
int main()
{
	test_HashMap();
	return 0;
}

#ifndef HASHMAP_H
#define HASHMAP_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
enum HASHMAP_ERROR {
	HASHMAP_OK,
	HASHMAP_NULL,
	HASHMAP_SIZE_ERR,
	HASHMAP_MEM_ERR,
	HASHMAP_NOT_FOUND,
	HASHMAP_NO_FILE
};
#define HASHMAP_BUFFER_LEN 128
#define HASHMAP_MESSAGE(message) do { \
	printf("file : %s    line : %d    message : %s", __FILE__, __LINE__, (message)); \
} while (0)
typedef struct HashNode {
	char* pcKey;
	void* pValue;
	struct HashNode *pstNext;
} HashNode;

typedef struct HashMap {
	HashNode* *ppstHashTable;
	int nodeNum;
	int maxListNum;
	void* (*pfObject_New)();
	void (*pfObject_Delete)(void* pObject);
	void (*pfObject_Write)(void* pObject, FILE* pstFile);
	void (*pfObject_Read)(void** ppObject, FILE* pstFile);
} HashMap;
HashNode* HashMap_CreateNode(const char* pcKey, void* pValue);
void HashMap_DestroyNode(HashNode* pstHashNode, void (*pfObject_Delete)(void* pObject));
unsigned int HashMap_Func(const char* pcKey);
HashMap* HashMap_Create(int maxListNum);
void HashMap_Destroy(HashMap* pstHashMap);
int HashMap_RegisterObject(
		HashMap* pstHashMap,
		void (*pfObject_Delete)(void* pObject),
		void* (*pfObject_New)(),
		void (*pfObject_Write)(void* pObject, FILE* pstFile),
		void (*pfObject_Read)(void** ppObject, FILE* pstFile));
int HashMap_Insert(HashMap* pstHashMap, const char* pcKey, void* pValue);
int HashMap_Delete(HashMap* pstHashMap, const char* pcKey);
int HashMap_Search(HashMap* pstHashMap, const char* pcKey, void** ppValue);
int HashMap_Traverse(HashMap* pstHashMap, int (*pfCallBack)(HashNode* pstNode, void* pArg), void* pArg);
int HashMap_Resize(HashMap* pstHashMap, int iNewSize);
int HashMap_Load(HashMap* pstHashMap, const char* pcFileName);
int HashMap_Save(HashMap* pstHashMap, const char* pcFileName);
#endif // HASHMAP

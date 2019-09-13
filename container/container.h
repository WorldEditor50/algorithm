#ifndef __CONTAINER_H
#define __CONTAINER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../basic.h"
#include "./array/array.h"
#include "./list/list.h"
#include "./binarytree/btree.h"
#ifdef __clusplus
extern "C" {
#endif
typedef struct container container;
struct container {
	array *pArray;
	list *pList;
	BTree *pBTree;
};
#ifdef __clusplus
}
#endif
#endif// __CONTAINER_H

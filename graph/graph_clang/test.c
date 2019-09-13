#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
int main()
{
	Graph *pstGraph = NULL;
	pstGraph = Graph_New(10);
	if (pstGraph == NULL) {
		GRAPH_MESSAGE("fail to allocted graph");
		return 0;
	}
	Graph_AddNode(pstGraph, 8);
	Graph_AddNode(pstGraph, 4);
	Graph_AddNode(pstGraph, 5);
	Graph_AddNode(pstGraph, 9);
	Graph_AddNode(pstGraph, 11);
	Graph_AddNode(pstGraph, 0);
	Graph_AddConnect(pstGraph, 0, 1, 1);
	Graph_AddConnect(pstGraph, 1, 2, 1);
	Graph_AddConnect(pstGraph, 1, 3, 1);
	Graph_AddConnect(pstGraph, 1, 5, 1);
	Graph_AddConnect(pstGraph, 2, 4, 1);
	Graph_AddConnect(pstGraph, 3, 4, 1);
	Graph_AddConnect(pstGraph, 4, 5, 1);
	Graph_AddConnect(pstGraph, 5, 0, 1);
	printf("connect num = %d\n", pstGraph->connectNum);
	Graph_DepthFirstSearch(pstGraph, 0);
	return 0;
}

#ifndef GRAPH_H
#define GRAPH_H
#include <stdio.h>
#include <stdlib.h>
#define GRAPH_OK 0
#define GRAPH_ERR 1
#define GRAPH_NULL 2
#define GRAPH_OVERFLOW 3
#define GRAPH_NOT_EXIST 4
#define GRAPH_MAX_ID_NUM 20
#define GRAPH_MAX_NODE_NUM 5
#define GRAPH_MESSAGE(message) do { \
	printf("function :%s line: %d message: %s\n", __FUNCTION__, __LINE__, (message)); \
} while (0)
typedef struct Connect {
	int from;
	int to;
	int activate;
	double weight;
} Connect;
typedef struct Node {
	int visited;
	int alive;
	double value;
} Node;

typedef struct Graph {
	int nodeNum;
	int disableNodeNum;
	int connectNum;
	int disableConnectNum;
	int maxNodeNum;
	int maxConnectNum;
	Node* pstNodes;
	Connect* pstConnects;
} Graph;
Graph* Graph_New(int maxNodeNum);
void Graph_Delete(Graph* pstGraph);
void Graph_CleanVisit(Graph* pstGraph);
int Graph_AddNode(Graph* pstGraph, double value);
int Graph_AddConnect(Graph* pstGraph, int from, int to, double weight);
int Graph_DelNode(Graph* pstGraph, double value);
int Graph_setConnect(Graph* pstGraph, int from, int to, int flag);
int Graph_BreadthFirstSearch(Graph* pstGraph, int id);
int Graph_DepthFirstSearch(Graph* pstGraph, int id);
int Graph_DepthFirstSearchNonRecurrent(Graph* pstGraph, int id);
#endif// GRAPH_H

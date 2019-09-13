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
	int id;
	int visited;
	int *pNextId;
	int *pPreId;
	int nextIdNum;
	int preIdNum;
	int maxNextIdNum;
	int maxPreIdNum;
	double value;
} Node;

typedef struct Graph {
	int nodeNum;
	int connectNum;
	int maxNodeNum;
	int maxConnectNum;
	Node* *pstNodes;
	Connect* *pstConnects;
} Graph;
Connect* Connect_New(int from, int to, double weight);
void Connect_Delete(Connect* pstConnect);
Node* Node_New(int id, double value);
void Node_Delete(Node* pstNode);
Graph* Graph_New(int maxNodeNum);
void Graph_Delete(Graph* pstGraph);
int Graph_AddNode(Graph* pstGraph, double value);
int Graph_AddConnect(Graph* pstGraph, int from, int to, double weight);
int Graph_BreadthFirstSearch(Graph* pstGraph, int id);
int Graph_DepthFirstSearch(Graph* pstGraph, int id);
#endif// GRAPH_H

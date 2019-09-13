#include "graph.h"

Connect* Connect_New(int from, int to, double weight)
{
	Connect *pstConnect = NULL;
	pstConnect = (Connect *)malloc(sizeof(Connect));
	if (pstConnect == NULL) {
		GRAPH_MESSAGE("failed to allocated connect");
		return NULL;
	}
	pstConnect->from = from;
	pstConnect->to = to;
	pstConnect->weight = weight;
	pstConnect->activate = 1;
	return pstConnect;
}

void Connect_Delete(Connect* pstConnect)
{
	if (pstConnect == NULL) {
		return;
	}
	free(pstConnect);
	return;
}

void Node_Delete(Node* pstNode)
{
	if (pstNode == NULL) {
		return;
	}
	if (pstNode->pNextId != NULL) {
		free(pstNode->pNextId);
	}
	if (pstNode->pPreId != NULL) {
		free(pstNode->pPreId);
	}
	if (pstNode != NULL) {
		free(pstNode);
	}
	return;
}

Node* Node_New(int id, double value)
{
	Node* pstNode = NULL;
	do {
		pstNode = (Node *)malloc(sizeof(Node));
		if (pstNode == NULL) {
			GRAPH_MESSAGE("failed to allocated node");
			break;
		}
		pstNode->id = id;
		pstNode->value = value;
		pstNode->visited = 0;
		pstNode->nextIdNum = 0;
		pstNode->preIdNum = 0;
		pstNode->maxNextIdNum = GRAPH_MAX_ID_NUM;
		pstNode->maxPreIdNum = GRAPH_MAX_ID_NUM;
		pstNode->pNextId = (int *)malloc(sizeof(int) * GRAPH_MAX_ID_NUM);
		if (pstNode->pNextId == NULL) {
			GRAPH_MESSAGE("failed to allocated next node id");
			break;
		}
		pstNode->pPreId = (int *)malloc(sizeof(int) * GRAPH_MAX_ID_NUM);
		if (pstNode->pPreId == NULL) {
			GRAPH_MESSAGE("failed to allocated next node id");
			break;
		}
		return pstNode;
	} while (0);
	Node_Delete(pstNode);
	return NULL;
}
int Node_Check(Node* pstNode)
{
	if (pstNode == NULL) {
		return GRAPH_ERR;
	}
	if (pstNode->pNextId == NULL) {
		return GRAPH_ERR;
	}
	if (pstNode->pPreId == NULL) {
		return GRAPH_ERR;
	}
	return GRAPH_OK;
}
int Node_IdResize(int **ppId, int *pMaxIdNum)
{
	int *pId = *ppId;
	int *pNewId = NULL;
	int maxNum = *pMaxIdNum;
	int len = 2 * maxNum;
	int i = 0;
	pNewId = (int *)malloc(sizeof(int) * len);
	if (pNewId == NULL) {
		return GRAPH_NULL;
	}
	for (i = 0; i < maxNum; i++) {
		pNewId[i] = pId[i];
	}
	free(pId);
	*ppId = pNewId;
	*pMaxIdNum = len;
	return GRAPH_OK;
}
int Node_AddNextNodeId(Node* pstNode, int nextId)
{
	int ret = 0;
	ret = Node_Check(pstNode);
	if (ret != GRAPH_OK) {
		return GRAPH_NULL;
	}
	if (pstNode->nextIdNum + 1 >= pstNode->maxNextIdNum) {
		ret = Node_IdResize(&(pstNode->pNextId), &(pstNode->maxNextIdNum));
		if (ret != GRAPH_OK) {
			return GRAPH_ERR;
		}
	}
	int pos = pstNode->nextIdNum;
	pstNode->pNextId[pos] = nextId;
	pstNode->nextIdNum++;
	return GRAPH_OK;
}

int Node_AddPreNodeId(Node* pstNode, int preId)
{
	int ret = 0;
	ret = Node_Check(pstNode);
	if (ret != GRAPH_OK) {
		return GRAPH_NULL;
	}
	if (pstNode->preIdNum + 1 >= pstNode->maxPreIdNum) {
		ret = Node_IdResize(&(pstNode->pPreId), &(pstNode->maxPreIdNum));
		if (ret != GRAPH_OK) {
			return GRAPH_ERR;
		}
	}
	int pos = pstNode->preIdNum;
	pstNode->pPreId[pos] = preId;
	pstNode->preIdNum++;
	return GRAPH_OK;
}

void Graph_Delete(Graph* pstGraph)
{
	if (pstGraph == NULL) {
		return;
	}
	int i = 0;
	if (pstGraph->pstNodes != NULL) {
		for (i = 0; i < pstGraph->nodeNum; i++) {
			if (pstGraph->pstNodes[i] != NULL) {
				Node_Delete(pstGraph->pstNodes[i]);
			}
		}
		free(pstGraph->pstNodes);
	}
	if (pstGraph->pstConnects != NULL) {
		free(pstGraph->pstConnects);
	}
	free(pstGraph);
	return;
}

Graph* Graph_New(int maxNodeNum)
{
	Graph *pstGraph = NULL;
	do {
		pstGraph = (Graph *)malloc(sizeof(Graph));
		if (pstGraph == NULL) {
			break;
		}
		pstGraph->nodeNum = 0;
		pstGraph->connectNum = 0;
		pstGraph->maxNodeNum = maxNodeNum;
		pstGraph->maxConnectNum = maxNodeNum * (maxNodeNum - 1);
		pstGraph->pstNodes = NULL;
		pstGraph->pstConnects = NULL;
		pstGraph->pstNodes = (Node* *)malloc(sizeof(Node*) * maxNodeNum);
		if (pstGraph->pstNodes == NULL) {
			break;
		}
		pstGraph->pstConnects = (Connect* *)malloc(sizeof(Connect*) * pstGraph->maxConnectNum);
		if (pstGraph->pstConnects == NULL) {
			break;
		}
		return pstGraph;	
	} while (0);
	Graph_Delete(pstGraph);
	return NULL;
}
int Graph_Check(Graph* pstGraph)
{
	if (pstGraph == NULL) {
		return GRAPH_NULL;
	}
	if (pstGraph->pstNodes == NULL) {
		return GRAPH_NULL;
	}
	if (pstGraph->pstConnects == NULL) {
		return GRAPH_NULL;
	}
	return GRAPH_OK;
}
int Graph_AddNode(Graph* pstGraph, double value)
{
	int ret = 0;
	int len = 0;
	int i = 0;
	Node** pstNewNodes = NULL;
	ret = Graph_Check(pstGraph);
	if (ret != GRAPH_OK) {
		return GRAPH_NULL;
	}
	if (pstGraph->nodeNum + 1 >= pstGraph->maxNodeNum) {
		len = 2 * pstGraph->maxNodeNum;
		pstNewNodes = (Node* *)malloc(sizeof(Node*) * len);
		if (pstNewNodes == NULL) {
			return GRAPH_NULL;
		}
		for (i = 0; i < pstGraph->maxNodeNum; i++) {
			pstNewNodes[i] = pstGraph->pstNodes[i]; 
		}
		free(pstGraph->pstNodes);
		pstGraph->pstNodes = pstNewNodes;
		pstGraph->maxNodeNum = len;
	}
	i = pstGraph->nodeNum;
	pstGraph->pstNodes[i] = Node_New(i, value);
	pstGraph->nodeNum++;
	return GRAPH_OK;
}

int Graph_AddConnect(Graph* pstGraph, int from, int to, double weight)
{
	int ret = 0;
	int len = 0;
	int i = 0;
	Node* pstNode = NULL;
	Connect** pstNewConnects = NULL;
	ret = Graph_Check(pstGraph);
	if (ret != GRAPH_OK) {
		return GRAPH_NULL;
	}
	if (from > pstGraph->nodeNum || to > pstGraph->nodeNum) {
		return GRAPH_OVERFLOW;
	}
	if (pstGraph->pstNodes[from] == NULL || pstGraph->pstNodes[to] == NULL) {
		GRAPH_MESSAGE("node doesn't exist");
		return GRAPH_NOT_EXIST;
	}
	if (pstGraph->connectNum + 1 >= pstGraph->maxConnectNum) {
		len = 2 * pstGraph->maxConnectNum;
		pstNewConnects = (Connect* *)malloc(sizeof(Connect*) * len);
		if (pstNewConnects == NULL) {
			return GRAPH_NULL;
		}
		for (i = 0; i < pstGraph->maxConnectNum; i++) {
			pstNewConnects[i] = pstGraph->pstConnects[i]; 
		}
		free(pstGraph->pstConnects);
		pstGraph->pstConnects = pstNewConnects;
		pstGraph->maxConnectNum = len;
	}
	i = pstGraph->connectNum;
	pstGraph->pstConnects[i] = Connect_New(from, to, weight);
	if (pstGraph->pstConnects[i] == NULL) {
		GRAPH_MESSAGE("failed to add connect");
		return GRAPH_NULL;	
	}
	pstGraph->connectNum++;
	ret = Node_AddNextNodeId(pstGraph->pstNodes[from], to);
	if (ret != GRAPH_OK) {
		GRAPH_MESSAGE("failed to add next id");
	}
	ret = Node_AddPreNodeId(pstGraph->pstNodes[to], from);
	if (ret != GRAPH_OK) {
		GRAPH_MESSAGE("failed to add pre id");
	}
	return GRAPH_OK;
}

int Graph_BreadthFirstSearch(Graph* pstGraph, int id)
{
	return GRAPH_OK;
}

int Graph_DepthFirstSearch1(Graph* pstGraph, int id)
{
	int i = 0;
	int index = 0;
	Node* pstNode = pstGraph->pstNodes[id];
	int *pNextId= pstNode->pNextId;
	printf("id = %d \t value = %lf\n", pstNode->id, pstNode->value);
	pstNode->visited = 1;
	for (i = 0; i < pstNode->nextIdNum; i++) {
		index = pNextId[i];
		pstNode = pstGraph->pstNodes[index];
		if (pstNode->visited == 0) {
			Graph_DepthFirstSearch(pstGraph, index);
		}
	}
	return GRAPH_OK;
}
int Graph_DepthFirstSearch(Graph* pstGraph, int id)
{
	int i = 0;
	int to = 0;
	Node* pstNode = pstGraph->pstNodes[id];
	printf("id = %d \t value = %lf\n", pstNode->id, pstNode->value);
	pstNode->visited = 1;
	for (i = 0; i < pstGraph->connectNum; i++) {
		if (pstGraph->pstConnects[i]->from == id) {
			to = pstGraph->pstConnects[i]->to;
			pstNode = pstGraph->pstNodes[to];
			if (pstNode->visited == 0) {
				Graph_DepthFirstSearch(pstGraph, to);
			}
		}
	}
	return 0;
}

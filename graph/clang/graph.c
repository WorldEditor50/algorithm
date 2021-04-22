#include "graph.h"

void Graph_Delete(Graph* pstGraph)
{
	if (pstGraph == NULL) {
		return;
	}
	if (pstGraph->pstNodes != NULL) {
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
	int i = 0;
	Graph *pstGraph = NULL;
	do {
		pstGraph = (Graph *)malloc(sizeof(Graph));
		if (pstGraph == NULL) {
			break;
		}
		pstGraph->nodeNum = 0;
		pstGraph->connectNum = 0;
		pstGraph->disableNodeNum = 0;
		pstGraph->disableConnectNum = 0;
		pstGraph->maxNodeNum = maxNodeNum;
		pstGraph->maxConnectNum = maxNodeNum * (maxNodeNum - 1);
		pstGraph->pstNodes = NULL;
		pstGraph->pstConnects = NULL;
		pstGraph->pstNodes = (Node *)malloc(sizeof(Node) * maxNodeNum);
		if (pstGraph->pstNodes == NULL) {
			break;
		}
		pstGraph->pstConnects = (Connect *)malloc(sizeof(Connect) * pstGraph->maxConnectNum);
		if (pstGraph->pstConnects == NULL) {
			break;
		}

		for (i = 0; i < pstGraph->maxNodeNum; i++) {
			pstGraph->pstNodes[i].alive = 0;
			pstGraph->pstNodes[i].visited = 0;
			pstGraph->pstNodes[i].value = 0;
		}
		for (i = 0; i < pstGraph->maxConnectNum; i++) {
			pstGraph->pstConnects[i].from = 0;
			pstGraph->pstConnects[i].to = 0;
			pstGraph->pstConnects[i].activate = 0;
			pstGraph->pstConnects[i].weight = 0;
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
void Graph_CleanVisit(Graph* pstGraph)
{
	int i = 0;
	int ret = 0;
	ret = Graph_Check(pstGraph);
	if (ret != GRAPH_OK) {
		return;
	}
	for (i = 0; i < pstGraph->nodeNum; i++) {
		pstGraph->pstNodes[i].visited = 0;
	}
	return;
}
int Graph_AddNode(Graph* pstGraph, double value)
{
	int ret = 0;
	int len = 0;
	int i = 0;
	Node* pstNewNodes = NULL;
	ret = Graph_Check(pstGraph);
	if (ret != GRAPH_OK) {
		return GRAPH_NULL;
	}
	if (pstGraph->disableNodeNum != 0) {
		for (i = 0; i < pstGraph->nodeNum; i++) {
			if (pstGraph->pstNodes[i].alive == 0) {
				pstGraph->pstNodes[i].alive = 1;
				pstGraph->pstNodes[i].visited = 0;
				pstGraph->pstNodes[i].value = value;
				break;
			}	
		}
		pstGraph->disableNodeNum--;
		return GRAPH_OK;
	}
	if (pstGraph->nodeNum + 1 >= pstGraph->maxNodeNum) {
		len = 2 * pstGraph->maxNodeNum;
		pstNewNodes = (Node *)malloc(sizeof(Node) * len);
		if (pstNewNodes == NULL) {
			return GRAPH_NULL;
		}
		for (i = 0; i < pstGraph->maxNodeNum; i++) {
			pstNewNodes[i].visited = pstGraph->pstNodes[i].visited; 
			pstNewNodes[i].value = pstGraph->pstNodes[i].value;
		}
		free(pstGraph->pstNodes);
		pstGraph->pstNodes = pstNewNodes;
		pstGraph->maxNodeNum = len;
	}
	i = pstGraph->nodeNum;
	pstGraph->pstNodes[i].alive = 1;
	pstGraph->pstNodes[i].value = value;
	pstGraph->nodeNum++;
	return GRAPH_OK;
}

int Graph_AddConnect(Graph* pstGraph, int from, int to, double weight)
{
	int ret = 0;
	int len = 0;
	int i = 0;
	Node* pstNode = NULL;
	Connect* pstNewConnects = NULL;
	Connect* pstConnects = NULL;
	ret = Graph_Check(pstGraph);
	if (ret != GRAPH_OK) {
		return GRAPH_NULL;
	}
	if (from > pstGraph->nodeNum || to > pstGraph->nodeNum) {
		return GRAPH_OVERFLOW;
	}
	if (pstGraph->pstNodes[from].alive == 0 || pstGraph->pstNodes[to].alive == 0) {
		GRAPH_MESSAGE("node doesn't exist");
		return GRAPH_NOT_EXIST;
	}
	/* connection already exist */
	pstConnects = pstGraph->pstConnects;
	for (i = 0; i < pstGraph->connectNum; i++) {
		if (pstConnects[i].from == from && pstConnects[i].to == to && pstConnects[i].activate == 1) {
			return GRAPH_OK;
		}
	}
	/* reuse disable space */
	if (pstGraph->disableConnectNum != 0) {
		for (i = 0; i < pstGraph->connectNum; i++) {
			if (pstConnects[i].activate == 0) {
				pstConnects[i].activate = 1;
				pstConnects[i].from = from;
				pstConnects[i].to = to;
				pstConnects[i].weight = weight;
				break;
			}	
		}
		pstGraph->disableConnectNum--;
		return GRAPH_OK;
	}
	/* array is full */
	if (pstGraph->connectNum + 1 >= pstGraph->maxConnectNum) {
		len = 2 * pstGraph->maxConnectNum;
		pstNewConnects = (Connect *)malloc(sizeof(Connect) * len);
		if (pstNewConnects == NULL) {
			return GRAPH_NULL;
		}
		for (i = 0; i < pstGraph->maxConnectNum; i++) {
			pstNewConnects[i].from = pstConnects[i].from; 
			pstNewConnects[i].to = pstConnects[i].to; 
			pstNewConnects[i].activate = pstConnects[i].activate; 
			pstNewConnects[i].weight = pstConnects[i].weight; 
		}
		free(pstGraph->pstConnects);
		pstGraph->pstConnects = pstNewConnects;
		pstGraph->maxConnectNum = len;
	}
	/* add new connection */
	i = pstGraph->connectNum;
	pstGraph->pstConnects[i].from = from;
	pstGraph->pstConnects[i].to = to;
	pstGraph->pstConnects[i].activate = 1;
	pstGraph->pstConnects[i].weight = weight;
	pstGraph->connectNum++;
	return GRAPH_OK;
}
int Graph_DelNode(Graph* pstGraph, double value)
{
	int i = 0;
	int index =0;
	int ret = 0;
	Node* pstNodes = NULL;
	ret = Graph_Check(pstGraph);
	if (ret != GRAPH_OK) {
		return GRAPH_NULL;
	}
	pstNodes = pstGraph->pstNodes;
	for (i = 0; i < pstGraph->nodeNum; i++) {
		if (pstNodes[i].value == value) {
			pstNodes[i].alive = 0;
			index = i;
			pstGraph->disableNodeNum++;
			break;
		}
	}
	for (i = 0; i < pstGraph->connectNum; i++) {
		if (pstGraph->pstConnects[i].from == index || pstGraph->pstConnects[i].to == index) {
			pstGraph->pstConnects[i].activate = 0;
			pstGraph->disableConnectNum++;
		}
	}
	return GRAPH_OK;
}
int Graph_setConnect(Graph* pstGraph, int from, int to, int flag)
{
	int i = 0;
	int ret = 0;
	Connect* pstConnect = NULL;
	ret = Graph_Check(pstGraph);
	if (ret != GRAPH_OK) {
		return GRAPH_NULL;
	}
	for (i = 0; i < pstGraph->connectNum; i++) {
		pstConnect = &(pstGraph->pstConnects[i]);
		if (pstConnect->from == from && pstConnect->to == to) {
			pstConnect->activate = flag;
			break;
		}
	}
	if (flag == 0) {
		pstGraph->disableNodeNum++;
	}
	return GRAPH_OK;
}

int Graph_BreadthFirstSearch(Graph* pstGraph, int id)
{
	int i = 0;
	int from = 0;
	int to = 0;
	int in = 0;
	int out = 0;
	int indexNum = 0;
	Node* pstNode = NULL; 
	int* pstQueue = NULL;
	int ret = 0;
	ret = Graph_Check(pstGraph);
	if (ret != GRAPH_OK) {
		return GRAPH_NULL;
	}
	if (id > pstGraph->nodeNum) {
		return GRAPH_OVERFLOW;
	}
	if (pstGraph->pstNodes[id].alive == 0) {
		return GRAPH_ERR;
	}
	Graph_CleanVisit(pstGraph);
	pstQueue = (int *)malloc(sizeof(int) * pstGraph->nodeNum);
	if (pstQueue == NULL) {
		return GRAPH_NULL;
	}
	pstNode = &(pstGraph->pstNodes[id]);
	printf("id = %d \t value = %lf\n", id, pstNode->value);
	pstNode->visited = 1;
	pstQueue[in % pstGraph->nodeNum] = id;
	in++;
	indexNum++;
	while (indexNum > 0) {
		from = pstQueue[out % pstGraph->nodeNum];
		out++;
		indexNum--;
		for (i = 0; i < pstGraph->connectNum; i++) {
			if (pstGraph->pstConnects[i].from == from && pstGraph->pstConnects[i].activate == 1) {
				to = pstGraph->pstConnects[i].to;
				pstNode = &(pstGraph->pstNodes[to]);
				if (pstNode->visited == 0 && pstNode->alive == 1) {
					printf("id = %d \t value = %lf\n", to, pstNode->value);
					pstNode->visited = 1;
					pstQueue[in % pstGraph->nodeNum] = to;
					in++;
					indexNum++;
				}
			}
		}
	}
	free(pstQueue);
	return GRAPH_OK;
}

void Graph_DFS(Graph* pstGraph, int id)
{
	int i = 0;
	int to = 0;
	Node* pstNode = &(pstGraph->pstNodes[id]);
	printf("id = %d \t value = %lf\n", id, pstNode->value);
	pstNode->visited = 1;
	for (i = 0; i < pstGraph->connectNum; i++) {
		if (pstGraph->pstConnects[i].from == id && pstGraph->pstConnects[i].activate == 1) {
			to = pstGraph->pstConnects[i].to;
			pstNode = &(pstGraph->pstNodes[to]);
			if (pstNode->visited == 0 && pstNode->alive == 1) {
				Graph_DFS(pstGraph, to);
			}
		}
	}
	return;
}
int Graph_DepthFirstSearch(Graph* pstGraph, int id)
{
	int ret = 0;
	ret = Graph_Check(pstGraph);
	if (ret != GRAPH_OK) {
		return GRAPH_NULL;
	}
	if (id > pstGraph->nodeNum) {
		return GRAPH_OVERFLOW;
	}
	if (pstGraph->pstNodes[id].alive == 0) {
		return GRAPH_ERR;
	}
	Graph_CleanVisit(pstGraph);
	Graph_DFS(pstGraph, id);
	return GRAPH_OK;
}

int Graph_DepthFirstSearchNonRecurrent(Graph* pstGraph, int id)
{
	int ret = 0;
	ret = Graph_Check(pstGraph);
	if (ret != GRAPH_OK) {
		return GRAPH_NULL;
	}
	if (id > pstGraph->nodeNum) {
		return GRAPH_OVERFLOW;
	}
	if (pstGraph->pstNodes[id].alive == 0) {
		return GRAPH_ERR;
	}
	Graph_CleanVisit(pstGraph);
	Node* pstNodes = pstGraph->pstNodes;;
	Connect* pstConnects = pstGraph->pstConnects;
	printf("id = %d \t value = %lf\n", id, pstNodes[id].value);
	pstNodes[id].visited = 1;
	int i = 0;
	int index = 0;
	int to = 0;
	/* create a stack */
	int *pstStack = NULL;
	int top = 0;
	int stackSize = pstGraph->nodeNum;
	pstStack = (int *)malloc(sizeof(int) * stackSize);
	pstStack[top] = id;
	top++;
	while (top > 0) {
		index = pstStack[top];
		top--;
		for (i = 0; i < pstGraph->connectNum; i++) {
			if (pstConnects[i].from == index && pstConnects[i].activate == 1) {
				to = pstConnects[i].to;
				if (pstNodes[to].visited == 0) {
					printf("id = %d \t value = %lf\n", to, pstNodes[to].value);
					pstNodes[to].visited = 1;
					/* psuh visied node into stack */
					top++;
					pstStack[top] = to;
					/* search next node */
					index = to;
					/* search from the begining of table */
					i = -1;
				}
			}
		}
	}
	free(pstStack);
	return GRAPH_OK;
}

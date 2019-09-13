#include "graph.h"

Graph::Graph() : nodeNum(0)
{

}

Graph::~Graph()
{

}

int Graph::addNode(double value)
{
	Node node;
	node.value = value;
	node.visited = false;
	node.alive = true;
	this->nodes.push_back(node);
	return 0;
}

int Graph::addConnect(int from, int to, double weight)
{
	Connect connect;
	connect.from = from;
	connect.to = to;
	connect.weight = weight;
	connect.activate = true;
	this->connects.push_back(connect);
	return 0;
}

void Graph::breadthFirstSearch(int id)
{
	if (id > nodes.size()) {
		return;
	}
	queue<int> indexQueue;
	int index = 0;
	for (int i = 0; i < nodes.size(); i++) {
		nodes[i].visited = false;
	}
	cout<<nodes[id].value<<endl;
	nodes[id].visited = true;
	indexQueue.push(id);
	while (!indexQueue.empty()) {
		index = indexQueue.front();
		indexQueue.pop();
		vector<Connect>::iterator it;
		for (it = connects.begin(); it != connects.end(); it++) {
			if (it->from == index) {
				if (nodes[it->to].visited == false) {
					cout<<nodes[it->to].value<<endl;
					nodes[it->to].visited = true;
					indexQueue.push(it->to);
				}
			}
		}
	}
	return;
}

void Graph::depthFirstSearch(int id)
{
	cout<<nodes[id].value<<endl;
	nodes[id].visited = true;
	vector<Connect>::iterator it;
	for (it = connects.begin(); it != connects.end(); it++) {
		if (it->from == id) {
			if (nodes[it->to].visited == false) {
				depthFirstSearch(it->to);
			}
		}
	}
	return;
}
void Graph::depthFirstSearchNonRecurrent(int id)
{
	int index = 0;
	stack<int> indexStack;
	for (int i = 0; i < nodes.size(); i++) {
		nodes[i].visited = false;
	}
	cout<<nodes[id].value<<endl;
	nodes[id].visited = true;
	indexStack.push(id);
	indexStack.push(id);
	while (!indexStack.empty()) {
		index = indexStack.top();
		indexStack.pop();
		vector<Connect>::iterator it;
		for (it = connects.begin(); it != connects.end(); it++) {
			if (it->from == index && nodes[it->to].visited == false) {
				cout<<nodes[it->to].value<<endl;
				nodes[it->to].visited = true;
				indexStack.push(it->to);
				index = it->to;
				it = connects.begin();
			}
		}
	}
	return;
}

bool Graph::topologicalSort(int id)
{
	return true;
}



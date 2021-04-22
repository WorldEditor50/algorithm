#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

struct Connect {
	int from;
	int to;
	double weight;
	bool activate;
};
struct Node {
	bool alive;
	double value;
	bool visited;
};
class Graph {
	public:
		Graph();
		~Graph();
		int addNode(double value);
		int addConnect(int from, int to, double weight);
		void breadthFirstSearch(int id);
		void depthFirstSearch(int id);
		void depthFirstSearchNonRecurrent(int id);
		bool topologicalSort(int id);
		int nodeNum;
		vector<Node> nodes;
		vector<Connect> connects;
};
#endif// GRAPH_H

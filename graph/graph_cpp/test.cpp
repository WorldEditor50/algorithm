#include <iostream>
#include "graph.h"
using namespace std;

int main()
{
	Graph g;
	g.addNode(8);
	g.addNode(4);
	g.addNode(5);
	g.addNode(9);
	g.addNode(11);
	g.addNode(0);
	g.addNode(13);
	g.addConnect(0, 1, 1);
	g.addConnect(1, 2, 1);
	g.addConnect(1, 3, 1);
	g.addConnect(1, 5, 1);
	g.addConnect(2, 4, 1);
	g.addConnect(3, 4, 1);
	g.addConnect(4, 5, 1);
	g.addConnect(5, 0, 1);
	g.addConnect(3, 6, 1);
	cout<<"recurrent : "<<endl;
	g.depthFirstSearch(0);
	cout<<"bfs : "<<endl;
	g.breadthFirstSearch(0);
	cout<<"non recurrent : "<<endl;
	g.depthFirstSearchNonRecurrent(0);

	return 0;
}

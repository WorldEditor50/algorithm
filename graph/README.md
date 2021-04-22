# 图的数据结构

## 1. 图的定义

#### 1.1顶点

#### 1.2边

#### 1.3 有向边

#### 1.4无向图

#### 1.5 有向图

## 2. 图的实现方法

### 2.1 邻接矩阵

#### 2.1.1 原理

```
1. graph
      +-----<-----+
      |           |
A --> B --> C --> E 
|     |           |
|     +--> D ---->+
|     |
+---->+--> F

2. adjacency matrix
    A  B  C  D  E  F
 A  0  1  0  0  0  1
 B  0  0  1  1  0  1
 C  0  0  0  0  1  0
 D  0  0  0  0  1  0
 E  0  1  0  0  0  0
 F  0  0  0  0  0  0
horizontal：to
vertical: from
1: connect
0: disconnect
```

#### 2.1.2 数据结构

```c++
struct Node {
    bool visited;
    double value;
};
class Graph {
    public:
    	Graph();
    	~Graph();
    private:
    	vector<Node> m_nodes;
    	vector<vector<double> > m_adjacencyMatrix;
};
```

### 2.2 邻接表

```
1. graph
      +-----<-----+
      |           |
A --> B --> C --> E 
|     |           |
|     +--> D ---->+
|     |
+---->+--> F
2. adjacency table

+---+     +---+     +---+
| A | --> | B | --> | F |
+---+     +---+     +---+
  |
+---+     +---+     +---+     +---+
| B | --> | C | --> | D | --> | F |
+---+     +---+     +---+     +---+
  |
+---+     +---+    
| C | --> | E | 
+---+     +---+    
  |
+---+     +---+   
| D | --> | E | 
+---+     +---+  
  |
+---+     +---+   
| E | --> | B | 
+---+     +---+  
  |
+---+    
| F |
+---+ 

```

#### 2.2.2数据结构

```c++
struct Node {
  	double value;
    bool visited;
    list<Node> m_nextNode;
};
class Graph {
    public:
    	Graph();
    	~Graph();
    private:
    	list<Node> m_nodes;
};
```



### 2.3 映射表

```
1. graph
      +-----<-----+
      |           |
A --> B --> C --> E 
|     |           |
|     +--> D ---->+
|     |
+---->+--> F
2. mapping table
+--------+---+---+---+---+---+---+---+---+
| from   | A | A | B | B | B | C | D | E |
+--------+---+---+---+---+---+---+---+---+
| to     | B | F | C | D | F | E | E | B |
+--------+---+---+---+---+---+---+---+---+
| weight | 1 | 3 | 2 | 8 | 9 | 2 | 4 | 6 |
+--------+---+---+---+---+---+---+---+---+
| status | 1 | 0 | 1 | 0 | 0 | 1 | 1 | 0 |
+--------+---+---+---+---+---+---+---+---+

```

#### 2.3.2数据结构

```c++
struct Node {
    bool visited;
    double value;
}; 
struct Connect {
    int from;
    int to;
    double weight;
    bool status;
};
class Graph {
    public:
    	Graph();
    	~Graph();
    private:
    	vector<Node> m_nodes;
    	vector<Connect> m_connects;
};
```

 

## 3. 图的遍历方法

### 3.1 深度优先遍历

#### 3.1.1方法描述

```
1. graph
      +-----<-----+
      |           |
A --> B --> C --> E 
|     |           |
|     +--> D ---->+
|     |
+---->+--> F
2. depth first search
A: A --> B --> C --> E --> D --> F
B: B --> C --> E --> A --> D --> F
C: C --> E --> B --> D --> F
D: D --> E --> B --> C --> F
E: E --> B --> C --> D --> F
F: F
```



​	深度优先遍历类似于树的前序遍历，假设初始状态图中所有的顶点都未曾访问过，则可以从图中任意选取一个顶点作为起点，首先访问起点，并将访问标记更新为已访问；然后访问起点的其中的一个邻接点，若邻接点未被访问过，则以邻接点作为新的起点开始遍历，直到图中所有与路径相通的顶点都被访问到；若此时图中仍有顶点未被访问，则另选一个未曾访问的顶点作为起点，重复上述过程，直到图中所有顶点都被访问到。

#### 3.1.2 递归方法

以映射表方法为例

```c++
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
```



#### 3.1.3非递归方法

```c++
void Graph::depthFirstSearchNonRecurrent(int id)
{
    int index = 0;
    /* create stack to store visited node */
    stack<int> indexStack;
    for (int i = 0; i < nodes.size(); i++) {
        nodes[i].visited = false;
    }
    cout<<nodes[id].value<<endl;
    nodes[id].visited = true;
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
                /* switch to next node */
                index = it->to;
                /* start over */
                it = connects.begin();
            }
        }
    }
    return;
}                   
```



### 3.2 广度优先遍历

```
1. graph
      +-----<-----+
      |           |
A --> B --> C --> E 
|     |           |
|     +--> D ---->+
|     |
+---->+--> F
2. depth first search
A: A --> B --> C --> D --> F --> E
B: B --> C --> D --> F --> E
C: C --> E --> B --> D --> F
D: D --> E --> B --> C --> F
E: E --> B --> C --> D --> F
F: F
```



​	广度优先遍历类似于树的按层次遍历，首先从图中任选取一个顶点作为起点，访问起点，将其访问标记更新为已访问；然后优先访问起点的所有的邻近点，更新访问标记，依次以邻接点作为新的起点开始遍历，重复上述过程，直到图中所有的顶点访问完毕

```c++
void Graph::breadthFirstSearch(int id)                                                                                                {
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
```



## 4. 图的生成树



## 5. 拓扑排序



## 6. 最短路径算法

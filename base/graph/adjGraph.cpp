#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include "adjGraph.h"
using namespace std;

struct minSpanTree {
	char ver;
	int weight;
	minSpanTree() {}
};

void printGraph(adjMGraph<char>*& mG, const int n) {
	adjG<char>* graph = mG->getGraph();
	cout << "顶点集合:" << endl;
	for (int i = 0; i < n; ++i)
		cout << graph->vertices[i] << ", ";
	cout << endl;
	cout << "邻接矩阵:" << endl;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j)
			cout << graph->edges[i][j] << " ";
		cout << endl;
	}
}

//图的深度优先遍历
void depthFSearch(adjMGraph<char>*& mG, int v, vector<int>& visit) {
	adjG<char>* graph = mG->getGraph();
	cout << v << "---" << graph->vertices[v] << endl;
	visit[v] = 1;
	//遍历下一个邻接结点
	int w = mG->getFirstVex(v);
	while (w != -1) {
		//下一个邻接结点存在且未被访问
		if (!visit[w])
			depthFSearch(mG, w, visit);
		//继续访问下一个邻接结点
		w = mG->getNextVex(v, w);
	}
}
//图的深度优先遍历非递归
void depthFSearchCur(adjMGraph<char>*& mG, int v, vector<int>& visit) {
	adjG<char>* graph = mG->getGraph();
	stack<int> s;
	//标记为已访问后入栈
	visit[v] = 1;
	s.push(v);
	int u, w;
	while (!s.empty()) {
		//访问并出栈
		u = s.top();
		cout << u << "---" << graph->vertices[u] << endl;
		s.pop();
		//获得u的下一个邻接点
		w = mG->getFirstVex(u);
		while (w != -1) {
			//结点w存在且未被访问
			if (!visit[w]) {
				//标记为已访问后入栈
				visit[w] = 1;
				s.push(w);
			}
			w = mG->getNextVex(u, w);
		}
	}
}

//图的广度优先遍历
void broadFSearch(adjMGraph<char>*& mG, int v, vector<int>& visit) {
	//访问完后入队
	queue<int> q;
	adjG<char>* graph = mG->getGraph();
	cout << v << "---" << graph->vertices[v] << endl;
	visit[v] = 1;
	q.push(v);
	int u, w;
	while (!q.empty()) {
		u = q.front();
		q.pop();
		//访问u的下一个邻接结点
		w = mG->getFirstVex(u);
		while (w != -1) {
			if (!visit[w]) {
				cout << w << "---" << graph->vertices[w] << endl;
				visit[w] = 1;
				q.push(w);
			}
			w = mG->getNextVex(u, w);
		}
	}
}

//最小生成树，prim算法
void prim(adjMGraph<char>*& mG, vector<minSpanTree*>& closeVexs) {
	adjG<char>* graph = mG->getGraph();
	int n = graph->vertices.size();
	//lowCost存储集合U（最小生成树结点）与集合V-U的所有边的最小值，-1表示加入到U中
	vector<int> lowCost(n, INT_MAX);
	closeVexs[0]->ver = graph->vertices[0];	//保存顶点
	closeVexs[0]->weight = INT_MAX;
	lowCost[0] = -1;						//标记顶点加入到集合U中
	//初始化lowCost为结点0（集合U内初始时只有一个结点0）到集合V-U的边权值
	for (int i = 1; i < n; ++i)
		lowCost[i] = graph->edges[0][i];
	//遍历n-1轮，每次将一个结点从集合V-U中移到集合U中
	for (int i = 1; i < n; ++i) {
		//寻找当前权值最小的弧头结点k
		int k, minCost = INT_MAX;
		for (int j = 1; j < n; ++j) {			
			if (lowCost[j] > 0 && lowCost[j] < minCost) {
				minCost = lowCost[j];
				k = j;
			}
		}
		//将结点k加入到集合U中
		closeVexs[i]->ver = graph->vertices[k];
		closeVexs[i]->weight = minCost;
		lowCost[k] = -1;
		//更新lowCost
		for (int m = 1; m < n; ++m) {
			//graph->edges[k][k]=0 < -1 不更新
			if (graph->edges[k][m] < lowCost[m])
				lowCost[m] = graph->edges[k][m];
		}
	}
}

//最短路径，Dijkastra算法，按路径长度递增顺序；
//集合U为已找到最短路径的点集，集合V-U为剩余结点，每次从V-U中移动一个结点到U后
//都要更新distance[]（v0到集合V-U的最短距离）
//path[i]存放(v0,i)最短路径上的i的前一个结点
void dijkastra(adjMGraph<char>*& mG, int v, vector<long long>& distance, vector<int>& path) {
	adjG<char>* graph = mG->getGraph();
	int n = graph->vertices.size(), i, j, k, minDis;
	//标记结点是否加入到集合U中(1)
	vector<int> flag(n, 0); 
	flag[v] = 1;
	//初始化distance与path
	for (i = 0; i < n; ++i) {
		distance[i] = graph->edges[v][i];
		if(i != v && distance[i] < INT_MAX && distance[i] > 0)
			path[i] = v;
	}
	//遍历n-1轮，每轮移动一个V-U集合的结点到U
	for (i = 1; i < n; ++i) {
		minDis = INT_MAX;
		//找到v到集合V-U最短的路径的结点k
		for (j = 0; j < n; ++j) {
			if (flag[j] == 0 && distance[j] < minDis) {
				k = j;
				minDis = distance[j];
			}
		}
		//将结点k添加到集合U中
		flag[k] = 1;
		//更新distance和path
		for (int m = 0; m < n; ++m) {
			if (flag[m] == 0 && distance[k] + graph->edges[k][m] < distance[m]) {
				distance[m] = distance[k] + graph->edges[k][m];
				path[m] = k;
			}
		}
	}
}

int main() {
	//prime test
	/*vector<char> Vexs{ 'A', 'B', 'C', 'D', 'E', 'F', 'G' };
	vector<rowColWeight*> edges{ new rowColWeight(0,1,50), new rowColWeight(1,0,50),
		new rowColWeight(0,2,60), new rowColWeight(2,0,60), new rowColWeight(1,3,65),
		new rowColWeight(3,1,65), new rowColWeight(1,4,40), new rowColWeight(4,1,40),
		new rowColWeight(2,3,52), new rowColWeight(3,2,52), new rowColWeight(2,6,45),
		new rowColWeight(6,2,45), new rowColWeight(3,4,50), new rowColWeight(4,3,50),
		new rowColWeight(3,5,30), new rowColWeight(5,3,30), new rowColWeight(3,6,42),
		new rowColWeight(6,3,42), new rowColWeight(4,5,70), new rowColWeight(5,4,70)
	};
	vector<minSpanTree*> mst;
	for (int i = 0; i < n; ++i)
		mst.push_back(new minSpanTree());
	prim(mG, mst);
	cout << "初始顶点为: " << mst[0]->ver << " 的最小生成树顶点序列和权值" << endl;
	for (int i = 1; i < n; ++i)
		cout << "顶点：" << mst[i]->ver << "---权值：" << mst[i]->weight << endl;*/

	//dijkastra test
	vector<char> Vexs{ 'A', 'B', 'C', 'D', 'E', 'F' };
	vector<rowColWeight*> edges{ new rowColWeight(0,2,5), new rowColWeight(0,3,30),
		new rowColWeight(1,0,2), new rowColWeight(1,4,8), new rowColWeight(2,1,15),
		new rowColWeight(2,5,7), new rowColWeight(4,3,4), new rowColWeight(5,3,10),
		new rowColWeight(5,4,18)
	};
	int n = 6, e = 9;
	adjMGraph<char>* mG = new adjMGraph<char>(Vexs, n, edges, e);
	printGraph(mG, n);
	vector<long long> distance(n, INT_MAX);
	vector<int> path(n, -1);
	int v = 0;
	dijkastra(mG, v, distance, path);
	cout << "Dijkastra算法，从顶点：" << v  << endl;
	for (int i = 0; i < n; ++i) {
		cout << "到顶点：" << mG->getGraph()->vertices[i] << "的最短路径为："
			<< distance[i] << "---上一结点为：" << path[i];
		if (path[i] != -1) cout << "---" << mG->getGraph()->vertices[path[i]];
		cout << endl;
	}

	vector<int> visit(n, 0);
	cout << "深度优先遍历：" << endl;
	depthFSearchCur(mG, 0, visit);

	//cout << "广度优先遍历：" << endl;
	//broadFSearch(mG, 0, visit);

	system("pause");
	return 0;
}
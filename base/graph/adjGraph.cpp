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
	cout << "���㼯��:" << endl;
	for (int i = 0; i < n; ++i)
		cout << graph->vertices[i] << ", ";
	cout << endl;
	cout << "�ڽӾ���:" << endl;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j)
			cout << graph->edges[i][j] << " ";
		cout << endl;
	}
}

//ͼ��������ȱ���
void depthFSearch(adjMGraph<char>*& mG, int v, vector<int>& visit) {
	adjG<char>* graph = mG->getGraph();
	cout << v << "---" << graph->vertices[v] << endl;
	visit[v] = 1;
	//������һ���ڽӽ��
	int w = mG->getFirstVex(v);
	while (w != -1) {
		//��һ���ڽӽ�������δ������
		if (!visit[w])
			depthFSearch(mG, w, visit);
		//����������һ���ڽӽ��
		w = mG->getNextVex(v, w);
	}
}
//ͼ��������ȱ����ǵݹ�
void depthFSearchCur(adjMGraph<char>*& mG, int v, vector<int>& visit) {
	adjG<char>* graph = mG->getGraph();
	stack<int> s;
	//���Ϊ�ѷ��ʺ���ջ
	visit[v] = 1;
	s.push(v);
	int u, w;
	while (!s.empty()) {
		//���ʲ���ջ
		u = s.top();
		cout << u << "---" << graph->vertices[u] << endl;
		s.pop();
		//���u����һ���ڽӵ�
		w = mG->getFirstVex(u);
		while (w != -1) {
			//���w������δ������
			if (!visit[w]) {
				//���Ϊ�ѷ��ʺ���ջ
				visit[w] = 1;
				s.push(w);
			}
			w = mG->getNextVex(u, w);
		}
	}
}

//ͼ�Ĺ�����ȱ���
void broadFSearch(adjMGraph<char>*& mG, int v, vector<int>& visit) {
	//����������
	queue<int> q;
	adjG<char>* graph = mG->getGraph();
	cout << v << "---" << graph->vertices[v] << endl;
	visit[v] = 1;
	q.push(v);
	int u, w;
	while (!q.empty()) {
		u = q.front();
		q.pop();
		//����u����һ���ڽӽ��
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

//��С��������prim�㷨
void prim(adjMGraph<char>*& mG, vector<minSpanTree*>& closeVexs) {
	adjG<char>* graph = mG->getGraph();
	int n = graph->vertices.size();
	//lowCost�洢����U����С��������㣩�뼯��V-U�����бߵ���Сֵ��-1��ʾ���뵽U��
	vector<int> lowCost(n, INT_MAX);
	closeVexs[0]->ver = graph->vertices[0];	//���涥��
	closeVexs[0]->weight = INT_MAX;
	lowCost[0] = -1;						//��Ƕ�����뵽����U��
	//��ʼ��lowCostΪ���0������U�ڳ�ʼʱֻ��һ�����0��������V-U�ı�Ȩֵ
	for (int i = 1; i < n; ++i)
		lowCost[i] = graph->edges[0][i];
	//����n-1�֣�ÿ�ν�һ�����Ӽ���V-U���Ƶ�����U��
	for (int i = 1; i < n; ++i) {
		//Ѱ�ҵ�ǰȨֵ��С�Ļ�ͷ���k
		int k, minCost = INT_MAX;
		for (int j = 1; j < n; ++j) {			
			if (lowCost[j] > 0 && lowCost[j] < minCost) {
				minCost = lowCost[j];
				k = j;
			}
		}
		//�����k���뵽����U��
		closeVexs[i]->ver = graph->vertices[k];
		closeVexs[i]->weight = minCost;
		lowCost[k] = -1;
		//����lowCost
		for (int m = 1; m < n; ++m) {
			//graph->edges[k][k]=0 < -1 ������
			if (graph->edges[k][m] < lowCost[m])
				lowCost[m] = graph->edges[k][m];
		}
	}
}

//���·����Dijkastra�㷨����·�����ȵ���˳��
//����UΪ���ҵ����·���ĵ㼯������V-UΪʣ���㣬ÿ�δ�V-U���ƶ�һ����㵽U��
//��Ҫ����distance[]��v0������V-U����̾��룩
//path[i]���(v0,i)���·���ϵ�i��ǰһ�����
void dijkastra(adjMGraph<char>*& mG, int v, vector<long long>& distance, vector<int>& path) {
	adjG<char>* graph = mG->getGraph();
	int n = graph->vertices.size(), i, j, k, minDis;
	//��ǽ���Ƿ���뵽����U��(1)
	vector<int> flag(n, 0); 
	flag[v] = 1;
	//��ʼ��distance��path
	for (i = 0; i < n; ++i) {
		distance[i] = graph->edges[v][i];
		if(i != v && distance[i] < INT_MAX && distance[i] > 0)
			path[i] = v;
	}
	//����n-1�֣�ÿ���ƶ�һ��V-U���ϵĽ�㵽U
	for (i = 1; i < n; ++i) {
		minDis = INT_MAX;
		//�ҵ�v������V-U��̵�·���Ľ��k
		for (j = 0; j < n; ++j) {
			if (flag[j] == 0 && distance[j] < minDis) {
				k = j;
				minDis = distance[j];
			}
		}
		//�����k��ӵ�����U��
		flag[k] = 1;
		//����distance��path
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
	cout << "��ʼ����Ϊ: " << mst[0]->ver << " ����С�������������к�Ȩֵ" << endl;
	for (int i = 1; i < n; ++i)
		cout << "���㣺" << mst[i]->ver << "---Ȩֵ��" << mst[i]->weight << endl;*/

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
	cout << "Dijkastra�㷨���Ӷ��㣺" << v  << endl;
	for (int i = 0; i < n; ++i) {
		cout << "�����㣺" << mG->getGraph()->vertices[i] << "�����·��Ϊ��"
			<< distance[i] << "---��һ���Ϊ��" << path[i];
		if (path[i] != -1) cout << "---" << mG->getGraph()->vertices[path[i]];
		cout << endl;
	}

	vector<int> visit(n, 0);
	cout << "������ȱ�����" << endl;
	depthFSearchCur(mG, 0, visit);

	//cout << "������ȱ�����" << endl;
	//broadFSearch(mG, 0, visit);

	system("pause");
	return 0;
}
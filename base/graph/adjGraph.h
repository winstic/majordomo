#pragma once
#include <iostream>
#include <vector>
using namespace std;

template <typename T>
struct adjG {
	vector<T> vertices;
	vector<vector<int>> edges;
	int edgesNum;
};

struct rowColWeight {
	int row;
	int col;
	int weight;
	rowColWeight(const int x, const int y, const int w) : row(x), col(y), weight(w){}
};

template <typename T>
class adjMGraph {
public:
	adjMGraph(const vector<T>& Vexs, const int vexn, const vector<rowColWeight*>& Edgs, const int e);
	int getFirstVex(const int v);
	int getNextVex(const int v, const int w);
	adjG<T>* getGraph() const { return G; }
	~adjMGraph();
private:
	void createEdge(const vector<rowColWeight*>& Edgs, const int e);
	void insertEdge(const int v1, const int v2, const int weight);
	void deleteEdge(const int v1, const int v2);

	adjG<T>* G;
	vector<rowColWeight*> Edgs;
	int verticesNum;
	int edgesNum;
};

template<typename T>
adjMGraph<T>::adjMGraph(const vector<T>& Vexs, const int vexn,
	const vector<rowColWeight*>& rcwEdgs, const int e) : verticesNum(vexn), edgesNum(0) {
	G = new adjG<T>();
	int i;
	for (i = 0; i < verticesNum; ++i) {
		G->vertices.push_back(Vexs[i]);
		vector<int> temp(verticesNum, INT_MAX);
		temp[i] = 0;
		G->edges.push_back(temp);
	}
	for (i = 0; i < e; ++ i)
		Edgs.push_back(rcwEdgs[i]);
	createEdge(Edgs, e);
}

template<typename T>
int adjMGraph<T>::getFirstVex(const int v) {
	if (v < 0 || v >= verticesNum) return -1;
	int currWeight;
	for (int i = 0; i < verticesNum; ++i) {
		currWeight = G->edges[v][i];
		if (currWeight > 0 && currWeight < INT_MAX) return i;
	}
	return -1;
}

template<typename T>
int adjMGraph<T>::getNextVex(const int v, const int w) {
	if (v < 0 || v >= verticesNum || w < 0 || w >= verticesNum) return -1;
	int currWeight;
	for (int i = w + 1; i < verticesNum; ++i) {
		currWeight = G->edges[v][i];
		if (currWeight > 0 && currWeight < INT_MAX) return i;
	}
	return -1;
}

template<typename T>
void adjMGraph<T>::createEdge(const vector<rowColWeight*>& Edgs, const int e) {
	if (e < 0) return;
	for (int i = 0; i < e; ++i) {
		insertEdge(Edgs[i]->row, Edgs[i]->col, Edgs[i]->weight);
	}
}

template<typename T>
void adjMGraph<T>::insertEdge(const int v1, const int v2, const int weight) {
	if (v1 < 0 || v1 >= verticesNum || v2 < 0 || v2 >= verticesNum) return;
	G->edges[v1][v2] = weight;
	++G->edgesNum;
}

template<typename T>
void adjMGraph<T>::deleteEdge(const int v1, const int v2) {
	if (v1 < 0 || v1 >= verticesNum || v2 < 0 || v2 >= verticesNum) return;
	//±ß²»´æÔÚ
	if (G->edges[v1][v2] == INT_MAX || v1 == v2) return;
	//É¾³ý±ß
	G->edges[v1][v2] = INT_MAX;
	--G->edgesNum;
}

template<typename T>
adjMGraph<T>::~adjMGraph() {}

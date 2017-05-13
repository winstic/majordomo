#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;

template<typename K, typename T>
struct cacheNode {
	K key;
	T data;
	cacheNode<K, T>* pre;
	cacheNode<K, T>* next;
};

template<typename K, typename T>
class LRU {
public:
	LRU(int tsize);
	~LRU();
	cacheNode<K, T>* getNode(K key);
	void putNode(K key, T data);
	void printNode();

private:
	void detach(cacheNode<K, T>* node);
	void attach(cacheNode<K, T>* node);
	cacheNode<K, T>* head;
	cacheNode<K, T>* ccNode;
	const int size;
	vector<cacheNode<K, T>*> adds;
	map<K, cacheNode<K, T>*> mapNodes;
};

template<typename K, typename T>
LRU<K, T>::LRU(int tsize) : size(tsize) {
	head = new cacheNode<K, T>;
	head->pre = head;
	head->next = head;
	ccNode = new cacheNode<K, T>[size];
	for (int i = 0; i < size; ++i)
		adds.push_back(ccNode + i);
}

template<typename K, typename T>
LRU<K, T>::~LRU() {
	cacheNode<K, T>* pNode = head->next;
	cacheNode<K, T>* pTemp;
	while (pNode != head) {
		pTemp = pNode->next;
		delete pNode;
		pNode = pTemp;
	}
	delete head;
	delete[] ccNode;
}

template<typename K, typename T>
void LRU<K, T>::printNode() {
	auto iter = mapNodes.begin();
	for (; iter != mapNodes.end(); ++iter)
		cout << iter->first << " -> " << iter->second->data << endl;
}

template<typename K, typename T>
cacheNode<K, T>* LRU<K, T>::getNode(K key) {
	cacheNode<K, T>* node = mapNodes[key];
	if (node) {
		//在cache中找到结点
		detach(node);
		attach(node);
	}
	return node;
}

template<typename K, typename T>
void LRU<K, T>::putNode(K key, T data) {
	cacheNode<K, T>* node = mapNodes[key];
	if (node) {
		//数据已在缓存中则更新数据
		node->data = data;
		detach(node);
		attach(node);
	}
	else {
		//数据不在缓存中，则添加到缓存
		node = new cacheNode<K, T>;
		node->key = key;
		node->data = data;
		node->pre = nullptr;
		node->next = nullptr;
		if (adds.empty()) {
			//缓存已满,替换链表尾的结点
			cacheNode<K, T>* backNode = head->pre;
			detach(backNode);
			mapNodes.erase(backNode->key);
			delete backNode;
		}
		else {
			//拿出一个地址给新数据
			adds.pop_back();
		}
		attach(node);
		mapNodes[key] = node;
	}
}

template<typename K, typename T>
void LRU<K, T>::detach(cacheNode<K, T>* node) {
	if (node) {
		node->next->pre = node->pre;
		node->pre->next = node->next;
	}
}

template<typename K, typename T>
void LRU<K, T>::attach(cacheNode<K, T>* node) {
	if (node) {
		node->next = head->next;
		head->next->pre = node;
		head->next = node;
		node->pre = head;
	}
}

template<typename K, typename T>
void printN(cacheNode<K, T>* node) {
	if (node)
		cout << node->data << endl;
	else
		cout << "cannot get node" << endl;
}

int main() {
	const int tsize = 10;
	LRU<int, string> lrucache(tsize);
	lrucache.putNode(1, "one");
	cacheNode<int, string>* node = lrucache.getNode(1);
	printN(node);

	node = lrucache.getNode(2);
	printN(node);

	for (int i = 0; i < tsize; ++i) {
		lrucache.putNode(i + 1, to_string(i + tsize));
	}
	lrucache.printNode();
	lrucache.putNode(11, "1455");
	node = lrucache.getNode(11);
	printN(node);
	lrucache.printNode();



	system("pause");
	return 0;
}
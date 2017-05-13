#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <set>
using namespace std;

typedef int DataType;
struct treeNode {
	DataType data;
	struct treeNode *pLeft;
	struct treeNode *pRight;
	treeNode(DataType x) : data(x), pLeft(nullptr), pRight(nullptr){}
};

void initTree(treeNode **root, DataType x) {
	(*root) = new treeNode(x);
}

treeNode* insertLeft(treeNode *pNode, DataType x) {
	if (pNode == nullptr) return nullptr;
	treeNode *ptrLfet = pNode->pLeft;
	treeNode *ptrInsert = new treeNode(x);
	ptrInsert->pLeft = ptrLfet;
	pNode->pLeft = ptrInsert;
	return pNode->pLeft;
}

treeNode* insertRight(treeNode *pNode, DataType x) {
	if (pNode == nullptr) return nullptr;
	treeNode *ptrRight = pNode->pRight;
	treeNode *ptrInsert = new treeNode(x);
	ptrInsert->pRight = ptrRight;
	pNode->pRight = ptrInsert;
	return pNode->pRight;
}

//recursive function
void preOrderRecursive(treeNode *root) {
	if (root == nullptr) return;
	cout << root->data << " ";
	preOrderRecursive(root->pLeft);
	preOrderRecursive(root->pRight);
}

void inOrderRecursive(treeNode *root) {
	if (root == nullptr) return;
	inOrderRecursive(root->pLeft);
	cout << root->data << " ";
	inOrderRecursive(root->pRight);
}

void postOrderRecursive(treeNode *root) {
	if (root == nullptr) return;
	postOrderRecursive(root->pLeft);
	postOrderRecursive(root->pRight);
	cout << root->data << " ";
}

//unrecursive function
void preOrderUnRecursive(treeNode *root) {
	if (root == nullptr) return;
	stack<treeNode*> stn;
	treeNode *pNode = root;
	stn.push(pNode);
	while (!stn.empty()) {
		pNode = stn.top();
		cout << pNode->data << " ";
		stn.pop();
		if (pNode->pRight)
			stn.push(pNode->pRight);
		if (pNode->pLeft)
			stn.push(pNode->pLeft);
	}
}

void inOrderUnRecursive(treeNode *root) {
	if (root == nullptr) return;
	stack<treeNode*> stn;
	treeNode *pNode = root;
	while ((pNode != nullptr) || !stn.empty()) {
		if (pNode) {
			stn.push(pNode);
			pNode = pNode->pLeft;
		}
		else {
			pNode = stn.top();
			cout << pNode->data << " ";
			stn.pop();
			pNode = pNode->pRight;
		}
	}
}

void postOrderUnRecursive(treeNode *root) {
	if (root == nullptr) return;
	stack<treeNode*> stn;
	treeNode* pNode = root, *rn = nullptr;
	while ((pNode != nullptr) || !stn.empty()) {
		if (pNode) {
			stn.push(pNode);
			pNode = pNode->pLeft;
		}
		else {
			pNode = stn.top();
			if (pNode->pRight == nullptr || pNode->pRight == rn) {
				cout << pNode->data << " ";
				stn.pop();
				rn = pNode;
				pNode = nullptr;
			}
			else
				pNode = pNode->pRight;
		}
	}
}

void layerOrderUnRecursive(treeNode *root) {
	if (root == nullptr) return;
	queue<treeNode*> qtn;
	treeNode *pNode = nullptr;
	qtn.push(root);
	while (!qtn.empty()) {
		pNode = qtn.front();
		cout << pNode->data << " ";
		qtn.pop();
		if (pNode->pLeft)
			qtn.push(pNode->pLeft);
		if (pNode->pRight)
			qtn.push(pNode->pRight);
	}
}

void DestroySubTree(treeNode **pNode) {
	if ((*pNode) != nullptr && (*pNode)->pLeft != nullptr)
		DestroySubTree(&(*pNode)->pLeft);
	if ((*pNode) != nullptr && (*pNode)->pRight != nullptr)
		DestroySubTree(&(*pNode)->pRight);
	delete(*pNode);
}

//maximun depth of binary tree
int maxDepth(treeNode *root) {
	if (root == nullptr) return 0;
	int leftDepth = maxDepth(root->pLeft);
	int rightDepth = maxDepth(root->pRight);
	return (leftDepth > rightDepth) ? leftDepth + 1 : rightDepth + 1;
}

//invert binary tree
treeNode* invertTree(treeNode* root) {
	if (root == nullptr) return nullptr;
	if (root->pLeft == nullptr && root->pRight == nullptr) return root;
	treeNode* pNode = root->pLeft;
	root->pLeft = root->pRight;
	root->pRight = pNode;
	if (root->pLeft) root->pLeft = invertTree(root->pLeft);
	if (root->pRight) root->pRight = invertTree(root->pRight);
	return root;
}

//minimum absolute difference in BST
auto min_diff = INT_MAX, val = -1;
int getMinimumDifference(treeNode* root) {
	if (root->pLeft) getMinimumDifference(root->pLeft);
	if (val >= 0) min_diff = min(min_diff, root->data - val);
	val = root->data;
	if (root->pRight) getMinimumDifference(root->pRight);
	return min_diff;
}

//sum of left leaves
auto sumLeftLeaves = 0;
int sumOfLeftLeaves(treeNode* root) {
	if (root != nullptr) {
		if (root->pLeft) {
			if(root->pLeft->pLeft == nullptr && root->pLeft->pRight == nullptr)
				sumLeftLeaves += root->pLeft->data;
			sumOfLeftLeaves(root->pLeft);			
		}
		if (root->pRight)
			sumOfLeftLeaves(root->pRight);
	}
	return sumLeftLeaves;
}
int sumOfLeftLeaves2(treeNode* root) {
	if (!root) return 0;
	if (root->pLeft && !root->pLeft->pLeft && !root->pLeft->pRight)
		return root->pLeft->data + sumOfLeftLeaves2(root->pRight);
	else
		return sumOfLeftLeaves2(root->pLeft) + sumOfLeftLeaves2(root->pRight);
}

//same tree
bool isSameTree(treeNode* p, treeNode* q) {
	if (p == nullptr && q == nullptr) return true;
	if (p == nullptr || q == nullptr) return false;
	return (p->data == q->data) &&
		isSameTree(p->pLeft, q->pLeft) &&
		isSameTree(p->pRight, q->pRight);
}

//is balance tree
int treeDepth(treeNode* root) {
	if (root == nullptr) return 0;
	int leftDepth = treeDepth(root->pLeft);
	int rightDepth = treeDepth(root->pRight);
	return (leftDepth > rightDepth) ? (leftDepth + 1) : (rightDepth + 1);
}
bool isBalanceTree(treeNode* root) {
	if (root == nullptr) return true;
	int leftDepth = treeDepth(root->pLeft);
	int rightDepth = treeDepth(root->pRight);
	int diff = leftDepth - rightDepth;
	if (diff < -1 || diff > 1)
		return false;
	return isBalanceTree(root->pLeft) && isBalanceTree(root->pRight);
}
//check for balance tree by post traverse
bool checkBalance(treeNode* root, int& blDepth) {
	if (root == nullptr) {
		blDepth = 0;
		return true;
	}
	int leftDepth, rightDepth;
	if (checkBalance(root->pLeft, leftDepth) && checkBalance(root->pRight, rightDepth)) {
		blDepth = (leftDepth > rightDepth) ? (leftDepth + 1) : (rightDepth + 1);
		int diff = leftDepth - rightDepth;
		if (diff >= -1 && diff <= 1) 
			return true;		
	}
	return false;
}
bool isBalancedTree2(treeNode* root) {
	if (root == nullptr) return true;
	int blDepath = 0;
	return checkBalance(root, blDepath);
}

//二叉树的下一个结点（含有父指针）

//对称的二叉树，自定义遍历方式

//按行打印二叉树
vector<vector<int> > printByLine(treeNode* pRoot) {
	if (pRoot == nullptr) return vector<vector<int> >{};
	vector<vector<int> > printVec;
	queue<treeNode*> queueTree;
	treeNode* pNode = pRoot, *tempNode = nullptr;
	queueTree.push(pNode);
	int currNumber = 1, nextLayerNumber = 0;
	while (!queueTree.empty()) {
		vector<int> layerVec;
		while (currNumber > 0) {
			tempNode = queueTree.front();			
			if (tempNode->pLeft) {
				queueTree.push(tempNode->pLeft);
				++nextLayerNumber;
			}
			if (tempNode->pRight) {
				queueTree.push(tempNode->pRight);
				++nextLayerNumber;
			}
			layerVec.push_back(tempNode->data);
			queueTree.pop();
			--currNumber;
		}
		printVec.push_back(layerVec);
		currNumber = nextLayerNumber;
		nextLayerNumber = 0;
	}
	return printVec;
}

//之字形打印二叉树（S形）
vector<vector<int> > printByLineS(treeNode* pRoot) {
	if (pRoot == nullptr) return vector<vector<int> >{};
	vector<vector<int> > printVec;
	vector<stack<treeNode*> > stackTree(2);
	treeNode* pNode = pRoot, *pTemp = nullptr;
	int currNumber = 1, nextNumber = 0;
	int flag = 0;
	stackTree[flag].push(pNode);
	while (!stackTree[flag].empty() || !stackTree[1-flag].empty()) {
		vector<int> tempVec;
		while (currNumber > 0) {
			pTemp = stackTree[flag].top();
			if (flag == 0) {
				if (pTemp->pLeft) {
					stackTree[1 - flag].push(pTemp->pLeft);
					++nextNumber;
				}
				if (pTemp->pRight) {
					stackTree[1 - flag].push(pTemp->pRight);
					++nextNumber;
				}
			}
			else if (flag == 1) {
				if (pTemp->pRight) {
					stackTree[1 - flag].push(pTemp->pRight);
					++nextNumber;
				}
				if (pTemp->pLeft) {
					stackTree[1 - flag].push(pTemp->pLeft);
					++nextNumber;
				}
			}
			tempVec.push_back(pTemp->data);
			stackTree[flag].pop();
			--currNumber;
		}		
		printVec.push_back(tempVec);
		currNumber = nextNumber;
		nextNumber = 0;
		flag = 1 - flag;
	}
	return printVec;
}

//序列化与反序列化二叉树
//序列化过程，将空结点以'#'补全，前序遍历完全二叉树
char* serialize(treeNode* root) {
	if (root == nullptr) return "#,";
	string s = to_string(root->data);
	s.push_back(',');
	char* cLeft = serialize(root->pLeft);
	char* cRight = serialize(root->pRight);
	unsigned int length = strlen(cLeft) + strlen(cRight) + s.size();
	char* ret = new char[length+1];
	strcpy_s(ret, length + 1, s.c_str());
	strcat_s(ret, length + 1, cLeft);
	strcat_s(ret, length + 1, cRight);
	return ret;
}
treeNode* deSerializeCore(char *&str) {
	if (str == nullptr) return nullptr;
	if (*str == '#') {
		str += 2;
		return nullptr;
	}
	int num = 0;
	while (*str != ',') {
		num *= 10;
		num += (*(str++) - '0');
	}
	treeNode* root = new treeNode(num);
	++str;		//step ','
	root->pLeft = deSerializeCore(str);
	root->pRight = deSerializeCore(str);
	return root;
}
treeNode* deSerialize(char* str) {
	if (str == nullptr) return nullptr;
	return deSerializeCore(str);
}

//求二叉搜索树的第K大的结点
treeNode* KthNodeCore(treeNode* pRoot, int& k) {
	treeNode* target = nullptr;
	if (pRoot->pLeft)
		target = KthNodeCore(pRoot->pLeft, k);
	if (target == nullptr) {
		if (k == 1) target = pRoot;
		--k;
	}
	if (!target && pRoot->pRight)
		target = KthNodeCore(pRoot->pRight, k);
	return target;
}
treeNode* KthNode(treeNode* pRoot, int k) {
	if (pRoot == nullptr || k <= 0) return nullptr;
	return KthNodeCore(pRoot, k);
}

//字符串全排列
void permutationCore(char* pstr, char* pBegin, vector<string>& stringVec) {
	if (*pBegin == '\0') {
		stringVec.push_back(pstr);
	}
	else {
		char temp;
		for (char* ch = pBegin; *ch != '\0'; ++ch) {
			if (ch != pBegin && *ch == *pBegin) continue;
			temp = *ch;
			*ch = *pBegin;
			*pBegin = temp;
			permutationCore(pstr, pBegin + 1, stringVec);
			temp = *ch;
			*ch = *pBegin;
			*pBegin = temp;
		}
	}
}
vector<string> Permutation(string str) {
	if (str.size() <= 0) return vector<string>{};
	vector<string> stringVec;
	permutationCore(const_cast<char*>(str.c_str()), const_cast<char*>(str.c_str()), stringVec);
	return stringVec;
}


int main() {
	treeNode* root = nullptr, *p = nullptr;
	//initTree(&root, 'A');
	//p = insertLeft(root, 'B');
	//p = insertLeft(p, 'D');
	//insertRight(p, 'G');
	//p = insertRight(root, 'C');
	//insertLeft(p, 'E');
	//insertRight(p, 'F');
	initTree(&root, 3);
	p = insertLeft(root, 9);
	p = insertRight(root, 20);
	insertRight(p, 7);
	insertLeft(p, 15);

	//treeNode* rootTemp = nullptr;
	//initTree(&rootTemp, 3);
	//p = insertLeft(rootTemp, 9);
	//p = insertRight(rootTemp, 20);
	//insertRight(p, 7);
	//insertLeft(p, 15);

	////recursive function
	//cout << "preOrder by Recursive: ";
	//preOrderRecursive(root);
	//cout << endl;
	//cout << "inOrder by Recursive: ";
	//inOrderRecursive(root);
	//cout << endl;
	//cout << "postOrder by Recursive: ";
	//postOrderRecursive(root);
	//cout << endl;
	////unrecursive function
	//cout << "UnRecursive:" << endl;
	//cout << "preOrder by UnRecursive: ";
	//preOrderUnRecursive(root);
	//cout << endl;
	//cout << "inOrder by UnRecursive: ";
	//inOrderUnRecursive(root);
	//cout << endl;
	//cout << "postOrder by UnRecursive: ";
	//postOrderUnRecursive(root);
	//cout << endl;
	//cout << "layerOrder by UnRecursive: ";
	//layerOrderUnRecursive(root);
	//cout << endl;

	//cout << "max depth of tree: " << maxDepth(root) << endl;

	//treeNode* vtroot = invertTree(root);
	//cout << "layerOrder by UnRecursive after invert tree: ";
	//layerOrderUnRecursive(vtroot);
	//cout << endl;
	//cout << "postOrder by UnRecursive after invert tree: ";
	//postOrderUnRecursive(vtroot);
	//cout << endl;

	//cout << "minimum absolute difference: " << getMinimumDifference(root) << endl;

	//cout << sumOfLeftLeaves2(root) << endl;
	//cout << isSameTree(root, rootTemp) << endl;

	//vector<vector<int> > printV = printByLineS(root);
	//for (auto item : printV) {
	//	for (auto x : item)
	//		cout << x << " ";
	//	cout << endl;
	//}

	//char* serCh = serialize(root);
	//cout << serCh << endl;
	//treeNode* newRoot = deSerialize(serCh);
	//cout << "preOrder by UnRecursive: ";
	//preOrderUnRecursive(newRoot);
	//cout << endl;

	vector<string> strVec = Permutation("aa");
	for (auto item : strVec)
		cout << item << " ";
	cout << endl;

	DestroySubTree(&root);
	//getchar();
	system("pause");
	return 0;
}
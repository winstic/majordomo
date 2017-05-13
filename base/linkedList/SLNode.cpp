#include <iostream>
using namespace std;

typedef int dataType;
struct slNode {
	dataType data;
	struct slNode *next;
};

void initSList(slNode **head) {
	(*head) = (slNode*)malloc(sizeof(slNode));
	(*head)->next = nullptr;
}

int listLength(slNode *head) {
	slNode *pNode = head;
	int size = 0;
	while (pNode->next) {
		++size;
		pNode = pNode->next;
	}
	return size;
}

bool insertNode(slNode *head, int i, dataType x) {
	slNode *pNode = head, *iNode = nullptr;
	int j = -1;
	while (pNode->next && j < i - 1) {
		pNode = pNode->next;
		++j;
	}
	if (j != i - 1) return false;
	iNode = (slNode*)malloc(sizeof(slNode));
	iNode->data = x;
	iNode->next = pNode->next;
	pNode->next = iNode;
	return true;
}

bool deleteNode(slNode *head, int i, dataType *x) {
	slNode *preNode = nullptr, *currNode = nullptr;
	int j = -1;
	currNode = head;
	while (currNode->next && j < i) {
		preNode = currNode;
		currNode = currNode->next;
		++j;
	}
	if (j != i) return false;
	*x = currNode->data;
	preNode->next = currNode->next;
	free(currNode);
	return true;
}

//back kth node
bool backKthNode(slNode *head, int k, dataType *x) {
	//cout << "k=" << k << " length=" << listLength(head) << endl;
	if (k > listLength(head)) return false;
	slNode *pFirst = head, *pSecond = head;
	int i = 0;
	while (pFirst && i < k - 1) {
		pFirst = pFirst->next;
		++i;
	}
	if (i != k - 1) return false;
	while (pFirst->next) {
		pSecond = pSecond->next;
		pFirst = pFirst->next;
	}
	*x = pSecond->data;
	return true;
}

//first common node
bool firstCommonNode(slNode *lhead1, slNode *lhead2, dataType *x) {
	if (lhead1->next == nullptr || lhead2->next == nullptr) return false;
	int longLength = listLength(lhead1), shortLength = listLength(lhead2);
	slNode *longNode = lhead1->next, *shortNode = lhead2->next;
	int distance = longLength - shortLength, i = 0;
	if (distance < 0) {
		longNode = lhead2->next;
		shortNode = lhead1->next;
		distance = -distance;
	}
	while (longNode && i < distance) {
		longNode = longNode->next;
		++i;
	}
	while (longNode && shortNode) {
		if (longNode->data == shortNode->data) {
			*x = longNode->data;
			return true;
		}
		longNode = longNode->next;
		shortNode = shortNode->next;
	}
	return false;
}
slNode* findFirstCommomNode(slNode* pHead1, slNode* pHead2) {
	if (pHead1 == nullptr || pHead2 == nullptr) return nullptr;
	slNode *longPHead = pHead1->next,	*shortPHead = pHead2->next;
	int longLength = listLength(pHead1), shortLength = listLength(pHead2);
	int diff = longLength - shortLength, i = 0;
	if (diff < 0) {
		diff = -diff;
		longPHead = pHead2;
		shortPHead = pHead1;
	}
	while (longPHead && i++ < diff)
		longPHead = longPHead->next;
	while (longPHead && shortPHead) {
		if (longPHead->data == shortPHead->data) return shortPHead;
		longPHead = longPHead->next;
		shortPHead = shortPHead->next;
	}
	return nullptr;
}

//delete node in a linked list
void deleteNodeo1(slNode* node) {
	if (node == nullptr || node->next == nullptr) return;
	slNode *pNode = node->next;
	node->data = pNode->data;
	node->next = pNode->next;
	free(pNode);
}

//reverse linked list
slNode* reverseListRecursion(slNode* head) {
	if (head == nullptr || head->next == nullptr) return head;
	slNode* newHead = reverseListRecursion(head->next);
	head->next->next = head;
	head->next = nullptr;
	return newHead;
}
slNode* reverseListUnRecursion(slNode* head) {
	if (head == nullptr || head->next == nullptr) return head;
	slNode *preNode = nullptr, *currNode = head, *nextNode = head->next;
	while (currNode) {		
		nextNode = currNode->next;
		currNode->next = preNode;
		preNode = currNode;
		currNode = nextNode;
	}
	return preNode;
}

//链表中环的入口
//1.快慢指针找到相遇点（在环内）；
//2.慢指针回到起点，快慢指针以相同的步长继续走，第一个相遇的点即为环入口
slNode* entryNodeOfLoop(slNode* pHead) {
	if (pHead == nullptr) return nullptr;
	//find meeting node
	slNode* slowPt = pHead;
	slNode* fastPt = pHead;
	slNode* meetNode = nullptr;
	while (slowPt != nullptr && fastPt != nullptr && fastPt->next != nullptr) {
		slowPt = slowPt->next;
		fastPt = fastPt->next->next;
		if (slowPt == fastPt) {
			meetNode = slowPt;
			break;
		}
	}
	if (!meetNode) return nullptr;
	slowPt = pHead;
	while (slowPt != nullptr && fastPt != nullptr) {
		if (slowPt == fastPt) {
			meetNode = slowPt;
			break;
		}
		slowPt = slowPt->next;
		fastPt = fastPt->next;
	}
	return meetNode;
}

//删除链表中重复的结点
slNode* deleteDuplication(slNode* pHead) {
	if (pHead == nullptr) return nullptr;
	slNode* preNode = nullptr;
	slNode* currNode = pHead;
	slNode* nextNode = currNode->next;
	slNode* newHead = nullptr;
	int currVal;
	bool isUpdatePre = true;
	while (currNode != nullptr && nextNode != nullptr) {
		currVal = currNode->data;
		isUpdatePre = true;
		while (nextNode != nullptr && currVal == nextNode->data) {
			currNode = nextNode;
			nextNode = nextNode->next;
			isUpdatePre = false;
		}
		if (isUpdatePre) {
			preNode = currNode;
			if (!newHead) newHead = preNode;
		}
		currNode = nextNode;
		if(currNode)
			nextNode = currNode->next;
		if(preNode)
			preNode->next = currNode;		
	}
	if (!newHead && currNode) newHead = currNode;
	return newHead;
}

void printList(slNode *head) {
	slNode *pNode = head->next;
	while (pNode) {
		cout << pNode->data << " ";
		pNode = pNode->next;
	}
	cout << endl;
}

void destroyList(slNode **head) {
	slNode *pNode = *head, *pTemp = nullptr;
	while (pNode) {
		pTemp = pNode;
		pNode = pNode->next;
		free(pTemp);
	}
	*head = nullptr;
}


int main() {
	slNode *head = nullptr;
	int i;
	//dataType x;
	initSList(&head);
	for (i = 0; i < 10; ++i) {
		insertNode(head, i, i + 1);
	}

	slNode *head2 = nullptr;
	initSList(&head2);
	for (i = 0; i < 5; ++i) {
		insertNode(head2, i, i + 10);
	}
	for (i = 5; i < 10; ++i) {
		insertNode(head2, i, i + 1);
	}
	printList(head);
	printList(head2);
	slNode *commNode = findFirstCommomNode(head, head2);
	cout << commNode->data << endl;
	//if (firstCommonNode(head, head2, &x))
	//	cout << x << endl;

	//printList(head);
	//deleteNode(head, 4, &x);
	//cout << x << endl;
	//for (i = 0; i < listLength(head); ++i) {
	//	backKthNode(head, i+2, &x);
	//	cout << x << endl;
	//}
	printList(head);

	//deleteNodeo1(head->next->next->next);
	//printList(head);

	destroyList(&head);
	//destroyList(&head2);
	system("pause");
	return 0;
}
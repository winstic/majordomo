#include <iostream>
using namespace std;

typedef int DataType;

//bubble sort
void bubbleSort(DataType A[], int length) {
	int i, j;
	DataType temp;
	bool flag = 1;
	for (i = 0; i < length && flag == 1; ++i) {
		flag = 0;
		for (j = 0; j < length - 1 - i; ++j) {
			if (A[j] > A[j+1]) {
				temp = A[j];
				A[j] = A[j+1];
				A[j+1] = temp;
				flag = 1;
			}
		}
	}
}

//heap sort
void adjustHeap(DataType A[], int length, int k) {
	int i, j;
	DataType temp;
	i = k;	
	temp = A[i];
	j = 2 * i + 1;
	while (j < length) {		
		if (j + 1 < length && A[j] < A[j + 1]) j = j + 1;
		if (temp < A[j]) {
			A[i] = A[j];
			i = j;
			j = 2 * i + 1;
		}
		else
			break;
	}
	A[i] = temp;
}

void createHeap(DataType A[], int length) {
	int i;
	for (i = (length - 2) / 2; i >= 0; --i) {
		adjustHeap(A, length, i);
	}
}

void heapSort(DataType A[], int length) {
	DataType temp;
	int i;
	createHeap(A, length);
	for (i = length - 1; i > 0; --i) {
		temp = A[0];
		A[0] = A[i];
		A[i] = temp;
		adjustHeap(A, i, 0);
	}
}

//quick Sort
void quickRecursive(DataType A[], int start, int finish) {
	DataType pivot = A[start];
	int i = start, j = finish;
	while (i < j) {
		while (i < j && A[j] > pivot) --j;
		if (i < j) A[i++] = A[j];
		while (i < j && A[i] < pivot) ++i;
		if (i < j) A[j--] = A[i];
	}
	A[i] = pivot;
	if(start < i-1)
		quickRecursive(A, start, i - 1);
	if(finish > i+1)
		quickRecursive(A, i + 1, finish);
}

void quickSort(DataType A[], int length) {
	int start = 0, finish = length - 1;
	quickRecursive(A, start, finish);
}

int main() {
	DataType A[] = { 4, 2, 6, 5, 9, 10, 8 };
	int i;
	quickSort(A, 7);
	for (i = 0; i < 7; ++i)
		cout << A[i] << " ";
	cout << endl;
	getchar();
	return 0;
}
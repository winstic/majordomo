#include <iostream>
#include <vector>
using namespace std;

void getNext(string pattern, int length, vector<int>& next) {
	if (length <= 0) return;
	int k = -1, index = 0;	//k是前缀，index是后缀
	next[0] = -1;
	while (index < length - 1) {
		if (k == -1 || pattern[k] == pattern[index]) {
			++k;
			++index;
			next[index] = k;
		}
		else
			k = next[k];
	}
}

int kmpSearch(string str, string pattern) {
	int strLength = str.size();
	int patternLength = pattern.size();
	if (strLength <= 0 || strLength < patternLength) return -1;
	int strIndex = 0, patIndex = -1;
	vector<int> next(patternLength, -1);
	getNext(pattern, patternLength, next);
	while (strIndex < strLength && patIndex < patternLength) {
		if (patIndex == -1 || str[strIndex] == pattern[patIndex]) {
			++strIndex;
			++patIndex;
		}
		else {
			patIndex = next[patIndex];
		}
	}
	if (patIndex == patternLength) return strIndex - patternLength;
	else return -1;
}

/*int main() {
	string str = "ABCDABACABCDABCEAC";
	string pattern = "ABCDABCEAC";
	int index = kmpSearch(str, pattern);
	cout << index << endl;
	system("pause");
	return 0;
}*/
#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

void fillVector(vector<int>& vi) {
	static int value = 1;
	generate(vi.begin(),
		vi.end(),
		[] {return value++; });
}

void sortBylambda(vector<int>& vi) {
	sort(vi.begin(),
		vi.end(),
		[](int a, int b) {return a < b; });
}

vector<int> fibonacciLambda(const int nums) {
	vector<int> vi(nums, 1);
	int fib1 = 1, fib2 = 1;
	generate_n(vi.begin()+2,
		nums-2,
		[=]()mutable -> int {
		int n = fib1 + fib2;
		fib1 = fib2;
		fib2 = n;
		return n;
	});
	return vi;
}

template <typename T>
void printData(const T& data) {
	for (const auto& e : data)
		cout << e << " ";
	cout << endl;
}

void testLambda() {
	int a = 1;
	//declaration lambda function and call it by parameter 2
	cout << [](int b) {return b; }(2) << endl;
	//capture by value
	cout << [=](int b) {return a + b; }(2) << endl; //same with [a]
	cout << [=](int b) mutable {return a += b; }(2) << " a=" << a << endl;
	//capture by reference
	cout << [&](int b) {return a += b; }(2); // or[&a]
	cout << " a=" << a << endl;
	//cout function instack from right to left,so if using below statement a will be 1;
	//cout << [&](int b) {return a += b; }(2) << " a=" << a << endl;

	//save lambda function
	auto lf = [](int b) {return b; };
	cout << lf(2) << endl;
	//function<int(int)> means int parameter and return int
	function<int(int)> lff = [](int b) {return b; };
	cout << lff(4) << endl;
}

int main() {
	//testLambda();
	vector<int> v = fibonacciLambda(11);
	printData(v);
	fillVector(v);
	printData(v);
	fillVector(v);
	printData(v);

	int A[] = { 4,5,3,1,9,2,5,7 };
	vector<int> v2(A, A + 8);
	sortBylambda(v2);
	printData(v2);
	system("pause");
	return 0;
}
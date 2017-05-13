#include <iostream>
using namespace std;

class singleTon {

private:
	singleTon(){}
	singleTon(const singleTon&){}
	singleTon& operator = (const singleTon&){}
	~singleTon(){}

	static singleTon* instance;	

public:	
	static singleTon* getInstance();
};

//懒汉模式
/*singleTon* singleTon::instance = nullptr;
singleTon* singleTon::getInstance() {
	if (nullptr == instance)
		instance = new singleTon;
	return instance;
}*/

//饿汉模式
singleTon* singleTon::instance = new singleTon;
singleTon* singleTon::getInstance() {
	return instance;
}

int main() {
	singleTon* obj1 = singleTon::getInstance();
	singleTon* obj2 = singleTon::getInstance();
	if (obj1 == obj2)
		cout << "single object" << endl;
	else
		cout << "error" << endl;
	system("pause");
	return 0;
}
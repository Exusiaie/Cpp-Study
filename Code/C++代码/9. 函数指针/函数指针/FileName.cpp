#include <iostream>
#include <string>
using namespace std;
#if 0
int add(int a, int b) {
	return a + b;
}
int sub(int a, int b) {
	return a - b;
}
int multiply(int a, int b) {
	return a * b;
}

int divide(int a, int b) {
	return a / b;
}
int cal(int a, int b, string operation) {
	//int (*pFunc)(int, int);
	typedef int (*FunctionPointer)(int, int);
	FunctionPointer fp;
	if (operation == "+") {
		fp = add;
	}
	else if (operation == "-") {
		fp = sub;
	}
	else if (operation == "*") {
		fp = multiply;
	}
	else if (operation == "/") {
		fp = divide;
	}
	else {
		return 0;
	}
	return *fp;
}
#endif


#if 0
class MyCin {
public:
	MyCin(int good,int fail,int bad, int eof) 
		:_good(good),
		_fail(fail),
		_bad(bad),
		_eof(eof)

	{

	}

	operator bool() {
		return _fail != 1;
	}
private:
	int _good;
	int _fail;
	int _bad;
	int _eof;
};

void test() {
	MyCin cin(0, 1, 0, 0);
	if (cin) {
		cout << "True" << endl;
	}
	else {
		cout << "Fail" << endl;
	}
}
#endif
// 类型转换函数要写在USD中, 赋值函数要写在CNY中
class USD {
public:
	USD(double value)
		:_value(value)
	{

	}
	friend ostream& operator<<(ostream& ost, const USD& usd);

private:
	double _value;
};

class CNY {
public:
	CNY (double value)
		:_value(value)
	{

	}
	friend ostream& operator<<(ostream& ost, const CNY& cny);

private:
	double _value;
};

ostream& operator<<(ostream& ost, const USD& usd) {
	ost << "$" << usd._value;
	return ost;
}

ostream& operator<<(ostream& ost, const CNY& cny) {
	ost << "¥" << cny._value;
	return ost;
}

void test() {

}

int main() {
	test();
	return 0;
}

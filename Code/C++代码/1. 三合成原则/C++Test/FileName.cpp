#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <string>
using namespace std;

class Person {
public:
	// 1. 构造函数, 调用时机是一般创建对象的时候
	Person(const char* name, int age = 0) // 给出了默认参数
		:_name(new char[strlen(name) + 1]()), // 不能这样写name(new char(strlen(name) + 1))
		_age(age)		// 给数据成员赋初值
	{
		strcpy(_name, name);
		cout << this << "调用构造函数" << endl;
	}

	// 2. 拷贝构造函数, 调用时机有三种...最常见的是用已经存在的other对象给新创建的对象赋值
	Person(const Person& other) // 一般情况下这里的参数是创建时给出的, 但这是拷贝构造, 所以参数就变成了已有的那个对象 
								// other指的是另一个对象, 一般是已有的那个对象(拷贝构造的Source)
		:_name(new char[strlen(other._name) + 1]()), // 使用堆空间申请一个自己的内存,避免浅拷贝问题. 
		_age(other._age) // 用已有对象赋值自己的_age
	{
		strcpy(_name, other._name); // 用已有对象赋值自己的_name
		cout << this << "调用拷贝构造函数" << endl;
	}

	// 3. 赋值运算符函数, 调用时机只有一种, 对象已经存在, 用同样已经存在的other对象给它重新赋值
	/* 赋值运算符函数书写的四步:
		1. 考虑自赋值问题
		2. 清理左操作数的数据成员原本申请的堆空间
		3. 深拷贝（以及其他的数据成员的赋值）
		4. 返回*this（本对象）
	*/
	Person &operator = (const Person& other) 
	{
		if (this != &other) { // if(this == &other) 就表示对象和other对象, 他两是同一个对象, 属于自赋值, 需要规避掉, 直接返回指向本对象的指针
			delete[] _name; // 清理左操作数原来的堆空间
			_name = new char[strlen(other._name) + 1](); // 申请新的堆空间
			strcpy(_name, other._name); // 接收右操作数传值
			_age = other._age;
		}
		cout << this << "调用赋值运算符函数" << endl;
		return *this;
	}

	void PrintInfo() {
		cout << "name:" << _name << endl;
		cout << "age:" << _age << endl;
		cout << this << ":-----------" << endl;
	}

	// 4. 析构函数, 调用时机是在对象被销毁时自动调用
	~Person() {
		if (_name != nullptr) {
			delete[] _name;
			_name = nullptr;
		}
		cout << this << "调用析构函数" << endl;
	}

private:
	char* _name;
	int _age;
};

void test1() {
	Person p1("小明", 60);
	Person p2("小洙", 70);
	p1.PrintInfo();
	p2.PrintInfo();
}


int main() {
	test1();
	return 0;
}

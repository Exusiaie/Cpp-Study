#if 0
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "string.h"
using namespace std;

// 实现拷贝构造, 赋值运算符重载
class String {
public:
	// 构造函数
	String(const char* pstr) 
		:_pstr(new char[strlen(pstr) + 1]())
	{
		strcpy(_pstr, pstr);
	}
	
	// 拷贝构造函数
	String(const String & rhs) 
		:_pstr(new char[strlen(rhs._pstr) + 1]())
	{
		strcpy(_pstr, rhs._pstr);
	}

	// 赋值运算符重载
	String& operator=(const String& rhs)
		
	{
		// 自赋值判断
		if (this != &rhs) {
			//this->_pstr = rhs._pstr; // 浅拷贝
			delete[] _pstr; // 删除左值原本的数据避免脏数据
			_pstr = new char[strlen(rhs._pstr) + 1](); // 深拷贝
			strcpy(_pstr, rhs._pstr);
		}
		return *this;
	}

	// 移动构造函数
	String(String &&rhs) noexcept//不报异常
		: _pstr(rhs._pstr) // "窃取"右值对象的成员, 拿来赋值
	{
		rhs._pstr = nullptr; // 需要主动的让临时对象的指针从堆空间断开
	}

	//移动赋值函数
	String& operator=(String&& rhs) noexcept {
		if (this != &rhs) {
			delete[] _pstr; 
			this->_pstr = rhs._pstr; // 浅拷贝
			rhs._pstr = nullptr;
		}
		return *this;
	}

	// 析构函数
	~String() {
		if (_pstr) { 
			delete[] _pstr;
			_pstr = nullptr;
		}
	}

	friend ostream& operator<<(ostream& os, const String& rhs);

private:
	char* _pstr;
};

// 使用友元函数重载<<输出流运算符
ostream& operator<<(ostream& os, const String& rhs) { 
	if (rhs._pstr) {	 // 要求指针不为空
		os << rhs._pstr; // 将指针塞到输出流中
	}
	return os;
}



void test() {
	String mystr1("faker"); // 构造
	cout << "mystr1: " << mystr1 << endl;
	String mystr2 = mystr1; // 拷贝构造
	cout << "mystr2: " << mystr2 << endl;
	String mystr3("chovy"); // 赋值运算符重载
	cout << "mystr3: " << mystr3 << endl;
	mystr3 = mystr1;
	cout << "mystr3: " << mystr3 << endl;

	String mystr4 = String("showmaker"); // 使用右值初始化String
	cout << "mystr4: " << mystr4 << endl;

}


int main() {
	test();
	return 0;
}
#endif

#include <iostream>

// 重载两种情况：接收左值引用 vs 右值引用
void overload(int& x) {
	std::cout << "overload(int&): lvalue 左值引用 被调用\n";
}
void overload(int&& x) {
	std::cout << "overload(int&&): rvalue 右值引用 被调用\n";
}

void test(int&& x) {
	// 虽然 x 的类型是 int&&，但是这里的 “x” 是一个左值表达式
	overload(x);               

	// 用 std::move 把 x 转换成右值后才会匹配右值引用函数
	overload(std::move(x));    
}

int main() {
	test(42);
	return 0;
}


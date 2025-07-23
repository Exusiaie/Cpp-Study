#include <iostream>
using namespace std;
// 核心目标: 确保一个类只有一个对象

// 第一种方法: 在全局/静态区创建单例对象
#if 0
class GraphicCard {
public:
	// 2. 直接在类里用静态成员函数和静态数据成员
	//    定义了一个唯一的对象gc, 这样就确保了GraphicCard只拥有一个对象
	static GraphicCard& getObject() {
		static GraphicCard gc("RTX 5080", 10000);
		return gc;
	}

private:
	// 1. 将构造函数私有化, 使得外界不能通过构造函数创建对象
	GraphicCard(string name, int price) 
		:_name(name)
		,_price(price)
	{
		cout << "构造函数已被私有化" << endl;
	}

	string _name;
	int _price;
};

void test1() {
	// 使用类名+作用域限定符的形式, 调用单例对象(引用)
	GraphicCard& gc1 = GraphicCard::getObject();
	GraphicCard& gc2 = GraphicCard::getObject();
	GraphicCard& gc3 = GraphicCard::getObject();
	// 使用取地址&打印这三个单例对象的地址, 发现这三个对象都是一个东西
	cout << &gc1 << endl;
	cout << &gc2 << endl;
	cout << &gc3 << endl;
}

int main() {
	test1();

	return 0;
}
// 那么问题又来了. 单例对象此时被创建在内存中的全局/静态区, 这个地方大小有限, 一个好的办法就是把它创建在堆区
#endif

// 第二种方法: 在堆区创建单例对象

class GraphicCard {
public:
	// 3. 直接在类里用静态成员函数和静态数据成员定义了一个唯一的对象gc, 这样就确保了GraphicCard只拥有一个对象
	// 这个静态成员函数返回值类型是对象指针, 指向了堆空间里被创建的那个单例对象
	static GraphicCard *getObject() {
		if (p_gc == nullptr) { // 只有在对象没被创建的时候才创建对象
			p_gc = new GraphicCard("RTX 5080", 10000);
		}
		return p_gc;
	}

	// 4. 使用静态成员函数自定义了一个析构函数
	// 外界想要进行析构的时候, 只能调用这个函数
	static void destroyObject() {
		if (p_gc != nullptr) {
			delete p_gc;
			p_gc = nullptr;
		}
	}


private:
	// 1. 将构造函数私有化, 使得外界不能通过构造函数创建对象
	GraphicCard(string name, int price)
		:_name(name)
		, _price(price)
	{
		cout << "构造函数已被私有化" << endl;
	}

	// 2. 将析构函数私有化, 使得外界不能调用析构函数
	~GraphicCard() {

	}

	static GraphicCard* p_gc;
	string _name;
	int _price;
};
// 静态数据成员要类外初始化
GraphicCard * GraphicCard::p_gc  = nullptr;


void test1() {
	// 使用类名+作用域限定符的形式, 调用单例对象(指针)
	GraphicCard * gc1 = GraphicCard::getObject();
	GraphicCard * gc2 = GraphicCard::getObject();
	GraphicCard * gc3 = GraphicCard::getObject();
	// 先解引用取得单例对象, 再使用取地址&打印这三个单例对象的地址, 发现这三个对象都是一个东西
	cout << &(*gc1) << endl;
	cout << &(*gc2) << endl;
	cout << &(*gc3) << endl;

	GraphicCard::destroyObject();
}

int main() {
	test1();

	return 0;
}
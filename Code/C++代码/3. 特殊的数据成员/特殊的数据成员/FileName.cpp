#include <iostream>
#include <string>
using namespace std;


// 常量数组成员
#if 0
class Car {
public:
	Car(const string brand, int price) 
		:_brand(brand), // 常量数据成员必须使用初始化列表进行初始化操作
		_price(price)
	{
		cout << "调用构造函数" << endl;
	}

	void Print() {
		cout << "car name: " << _brand << endl;
		cout << "price: " << _price << endl;
	}

#if 0
	void Change() {
		string newbrand = "BYD";
		_brand = newbrand; // ERROR 表达式必须是可修改的左值
	}
#endif
private:
	const string _brand; // 常量数据成员
	int _price;
};

void test() {
	char temp[15] = "Porsche 911";
	Car c1(temp, 128);
	c1.Print();
}
# endif


// 引用数据成员
#if 0
class Point {
public:
	Point(int ix, int iy)
		: _ix(ix)
		, _iy(iy)
		, _iz(_ix) //注意这里面的写法，绑定_ix
	{
	}

	void Print() {
		cout << "_ix: " << _ix << endl;
		cout << "_iy: " << _iy << endl;
		cout << "_iz: " << _iz << endl;
	}


	// 注意: 引用成员需要绑定一个已经存在的、且在这个引用成员的生命内始终有效的变量（对象）。
	// 下面这种绑定参数的写法, 因为参数并不在这个引用成员的生命内始终有效, 因此不能这样写
#if 0
	class Point2
	{
	public:
		Point2(int x, int y, int z)
			: _ix(x)
			, _iy(y)
			, _iz(z) //这样绑定可行吗
		{
		}

	private:
		int _ix;
		int _iy;
		int& _iz;
	};
#endif

private:
	int _ix;
	int _iy;
	int& _iz; // 用_iz绑定了数据成员_ix
};

void test() {
	Point p(777,666);
	p.Print();
}
# endif

// 对象数据成员 
#if 0
class Point {
public:
	Point() {}

	Point(int ix, int iy)
		:_ix(ix)
		, _iy(iy)
	{
	}

private:
	int _ix;
	int _iy;
};

class Line {
public:
	Line(int x1, int y1, int x2, int y2)
		//如果没有在Line的构造函数的初始化列表中
		//显示调用Point的构造函数
		//那么会自动调用Point的无参构造
		: _pt1(x1, y1) //相当于Point _pt1(x1,y1)
		, _pt2(x2, y2)
	{
		cout << "Line(int,int,int,int)" << endl;
	}

private:
	Point _pt1;
	Point _pt2;
};

void test() {
	Line L(1, 1, 2, 2);
}
# endif

// 引用对象数据成员

class Point {
private:
	int _x;
	int _y;

public:
	Point(int x, int y)
		:_x(x)
		, _y(y)
	{
		cout << "Point构造函数" << endl;
	}

	~Point() {
		cout << "Point析构函数" << endl;
	}
	Point(const Point& other)
		:_x(other._x)
		, _y(other._y)
	{
		cout << "Point拷贝构造函数" << endl;
	}
};


class Line {
private:
	//如果不用&引用的方式, 这里面会有拷贝构造函数调用, 造成更多的消耗
	//如果想要避免，这里面直接写引用
	Point& _pt1;
	Point& _pt2;

public:
	//这里面也需要引用，满足拷贝构造函数的调用时机2
	Line(Point& pt, Point& pt2)
		:_pt1(pt)
		, _pt2(pt2)
	{
		cout << "Line构造函数" << endl;
	}

	~Line() {
		cout << "Line析构函数" << endl;
	}
};

void test() {
	Point pt1(1, 2), pt2(3, 5);
	Line line(pt1, pt2);
}



int main() {
	test();

	return 0;
}

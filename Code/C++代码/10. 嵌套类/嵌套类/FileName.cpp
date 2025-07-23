#include <iostream>
using namespace std;
#if 0 // 11.
// 为了让内部类的私有只给外部类使用
class Line {
public:
	Line(int x1, int y1, int x2, int y2)
		:_pt1(x1, y1),
		_pt2(x2, y2)
	{
		cout << "here" << endl;
	}

	void Print() {
		_pt1.Print();
		_pt2.Print();
	}

	class Point {
	public:
		Point(int x, int y)
			:_x(x),
			_y(y)
		{
			cout << "(" << _x << "," << _y << ")" << endl;
		}

		void Print() {
			cout << "(" << _x << "," << _y << ")" << endl;
		}
	private:
		int _x;
		int _y;
	};

private:
	Point _pt1;
	Point _pt2;

};


// 输出流运算符重载
ostream& operator<<(ostream& os, const Line& rhs) {
	
}



void test() {
	// 使用输出流运算符对Line和Point进行输出
	Line line(1, 2, 3, 4);
	cout << line << endl;
	Line::Point pt(1, 2); // 再定义一个点
	cout << pt << endl;
}
# endif

class Line {
public:
	Line(int x1, int y1, int x2, int y2)
		:_p1(x1, y1)
		, _p2(x2, y2)
	{
	}


private:
	class Point {
	public:
		Point(int x, int y)
			:_x(x)
			, _y(y)
		{
		}

		friend ostream& operator<<(ostream& os, const Line::Point& rhs);


	private:
		int _x;
		int _y;
	};

	friend ostream& operator<<(ostream& os, const Line& rhs);

	friend ostream& operator<<(ostream& os, const Line::Point& rhs);


private:
	Point _p1;
	Point _p2;
};

// 为了用<<输出Line对象, 将Line对象中的两个Point对象放到<<输出流中
// 这样就产生了两个问题:
// 1. << 也同样要输出Point对象, 于是要加一个针对Point对象的运算符重载
// 2. 针对Line对象的运算符重载函数要用到私有成员Point, 针对Point对象的运算符重载函数要用到私有成员_x_y, 于是要加上它两的友元函数
ostream& operator<<(ostream& os, const Line& rhs) {
	os << rhs._p1 << "------>" << rhs._p2;
	return os;
}

ostream& operator<<(ostream& os, const Line::Point& rhs) {
	os << "(" << rhs._x << "," << rhs._y << ")";
	return os;
}


void test() {

	Line L(0, 0, 3, 4);

	cout << "l1: " << L << endl;
}


int main() {
	test();
	return 0;
}
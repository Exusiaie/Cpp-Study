#include <iostream>
using namespace std;
#if 0 // 11.
// Ϊ�����ڲ����˽��ֻ���ⲿ��ʹ��
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


// ��������������
ostream& operator<<(ostream& os, const Line& rhs) {
	
}



void test() {
	// ʹ��������������Line��Point�������
	Line line(1, 2, 3, 4);
	cout << line << endl;
	Line::Point pt(1, 2); // �ٶ���һ����
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

// Ϊ����<<���Line����, ��Line�����е�����Point����ŵ�<<�������
// �����Ͳ�������������:
// 1. << Ҳͬ��Ҫ���Point����, ����Ҫ��һ�����Point��������������
// 2. ���Line�������������غ���Ҫ�õ�˽�г�ԱPoint, ���Point�������������غ���Ҫ�õ�˽�г�Ա_x_y, ����Ҫ������������Ԫ����
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
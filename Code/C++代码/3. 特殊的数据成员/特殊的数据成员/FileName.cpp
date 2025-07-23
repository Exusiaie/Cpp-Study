#include <iostream>
#include <string>
using namespace std;


// ���������Ա
#if 0
class Car {
public:
	Car(const string brand, int price) 
		:_brand(brand), // �������ݳ�Ա����ʹ�ó�ʼ���б���г�ʼ������
		_price(price)
	{
		cout << "���ù��캯��" << endl;
	}

	void Print() {
		cout << "car name: " << _brand << endl;
		cout << "price: " << _price << endl;
	}

#if 0
	void Change() {
		string newbrand = "BYD";
		_brand = newbrand; // ERROR ���ʽ�����ǿ��޸ĵ���ֵ
	}
#endif
private:
	const string _brand; // �������ݳ�Ա
	int _price;
};

void test() {
	char temp[15] = "Porsche 911";
	Car c1(temp, 128);
	c1.Print();
}
# endif


// �������ݳ�Ա
#if 0
class Point {
public:
	Point(int ix, int iy)
		: _ix(ix)
		, _iy(iy)
		, _iz(_ix) //ע���������д������_ix
	{
	}

	void Print() {
		cout << "_ix: " << _ix << endl;
		cout << "_iy: " << _iy << endl;
		cout << "_iz: " << _iz << endl;
	}


	// ע��: ���ó�Ա��Ҫ��һ���Ѿ����ڵġ�����������ó�Ա��������ʼ����Ч�ı��������󣩡�
	// �������ְ󶨲�����д��, ��Ϊ����������������ó�Ա��������ʼ����Ч, ��˲�������д
#if 0
	class Point2
	{
	public:
		Point2(int x, int y, int z)
			: _ix(x)
			, _iy(y)
			, _iz(z) //�����󶨿�����
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
	int& _iz; // ��_iz�������ݳ�Ա_ix
};

void test() {
	Point p(777,666);
	p.Print();
}
# endif

// �������ݳ�Ա 
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
		//���û����Line�Ĺ��캯���ĳ�ʼ���б���
		//��ʾ����Point�Ĺ��캯��
		//��ô���Զ�����Point���޲ι���
		: _pt1(x1, y1) //�൱��Point _pt1(x1,y1)
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

// ���ö������ݳ�Ա

class Point {
private:
	int _x;
	int _y;

public:
	Point(int x, int y)
		:_x(x)
		, _y(y)
	{
		cout << "Point���캯��" << endl;
	}

	~Point() {
		cout << "Point��������" << endl;
	}
	Point(const Point& other)
		:_x(other._x)
		, _y(other._y)
	{
		cout << "Point�������캯��" << endl;
	}
};


class Line {
private:
	//�������&���õķ�ʽ, ��������п������캯������, ��ɸ��������
	//�����Ҫ���⣬������ֱ��д����
	Point& _pt1;
	Point& _pt2;

public:
	//������Ҳ��Ҫ���ã����㿽�����캯���ĵ���ʱ��2
	Line(Point& pt, Point& pt2)
		:_pt1(pt)
		, _pt2(pt2)
	{
		cout << "Line���캯��" << endl;
	}

	~Line() {
		cout << "Line��������" << endl;
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

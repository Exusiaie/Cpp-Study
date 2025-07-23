#include <iostream>
using namespace std;
// ����Ŀ��: ȷ��һ����ֻ��һ������

// ��һ�ַ���: ��ȫ��/��̬��������������
#if 0
class GraphicCard {
public:
	// 2. ֱ���������þ�̬��Ա�����;�̬���ݳ�Ա
	//    ������һ��Ψһ�Ķ���gc, ������ȷ����GraphicCardֻӵ��һ������
	static GraphicCard& getObject() {
		static GraphicCard gc("RTX 5080", 10000);
		return gc;
	}

private:
	// 1. �����캯��˽�л�, ʹ����粻��ͨ�����캯����������
	GraphicCard(string name, int price) 
		:_name(name)
		,_price(price)
	{
		cout << "���캯���ѱ�˽�л�" << endl;
	}

	string _name;
	int _price;
};

void test1() {
	// ʹ������+�������޶�������ʽ, ���õ�������(����)
	GraphicCard& gc1 = GraphicCard::getObject();
	GraphicCard& gc2 = GraphicCard::getObject();
	GraphicCard& gc3 = GraphicCard::getObject();
	// ʹ��ȡ��ַ&��ӡ��������������ĵ�ַ, ����������������һ������
	cout << &gc1 << endl;
	cout << &gc2 << endl;
	cout << &gc3 << endl;
}

int main() {
	test1();

	return 0;
}
// ��ô����������. ���������ʱ���������ڴ��е�ȫ��/��̬��, ����ط���С����, һ���õİ취���ǰ��������ڶ���
#endif

// �ڶ��ַ���: �ڶ���������������

class GraphicCard {
public:
	// 3. ֱ���������þ�̬��Ա�����;�̬���ݳ�Ա������һ��Ψһ�Ķ���gc, ������ȷ����GraphicCardֻӵ��һ������
	// �����̬��Ա��������ֵ�����Ƕ���ָ��, ָ���˶ѿռ��ﱻ�������Ǹ���������
	static GraphicCard *getObject() {
		if (p_gc == nullptr) { // ֻ���ڶ���û��������ʱ��Ŵ�������
			p_gc = new GraphicCard("RTX 5080", 10000);
		}
		return p_gc;
	}

	// 4. ʹ�þ�̬��Ա�����Զ�����һ����������
	// �����Ҫ����������ʱ��, ֻ�ܵ����������
	static void destroyObject() {
		if (p_gc != nullptr) {
			delete p_gc;
			p_gc = nullptr;
		}
	}


private:
	// 1. �����캯��˽�л�, ʹ����粻��ͨ�����캯����������
	GraphicCard(string name, int price)
		:_name(name)
		, _price(price)
	{
		cout << "���캯���ѱ�˽�л�" << endl;
	}

	// 2. ����������˽�л�, ʹ����粻�ܵ�����������
	~GraphicCard() {

	}

	static GraphicCard* p_gc;
	string _name;
	int _price;
};
// ��̬���ݳ�ԱҪ�����ʼ��
GraphicCard * GraphicCard::p_gc  = nullptr;


void test1() {
	// ʹ������+�������޶�������ʽ, ���õ�������(ָ��)
	GraphicCard * gc1 = GraphicCard::getObject();
	GraphicCard * gc2 = GraphicCard::getObject();
	GraphicCard * gc3 = GraphicCard::getObject();
	// �Ƚ�����ȡ�õ�������, ��ʹ��ȡ��ַ&��ӡ��������������ĵ�ַ, ����������������һ������
	cout << &(*gc1) << endl;
	cout << &(*gc2) << endl;
	cout << &(*gc3) << endl;

	GraphicCard::destroyObject();
}

int main() {
	test1();

	return 0;
}
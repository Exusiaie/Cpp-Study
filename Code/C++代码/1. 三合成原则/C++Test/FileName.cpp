#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <string>
using namespace std;

class Person {
public:
	// 1. ���캯��, ����ʱ����һ�㴴�������ʱ��
	Person(const char* name, int age = 0) // ������Ĭ�ϲ���
		:_name(new char[strlen(name) + 1]()), // ��������дname(new char(strlen(name) + 1))
		_age(age)		// �����ݳ�Ա����ֵ
	{
		strcpy(_name, name);
		cout << this << "���ù��캯��" << endl;
	}

	// 2. �������캯��, ����ʱ��������...����������Ѿ����ڵ�other������´����Ķ���ֵ
	Person(const Person& other) // һ�����������Ĳ����Ǵ���ʱ������, �����ǿ�������, ���Բ����ͱ�������е��Ǹ����� 
								// otherָ������һ������, һ�������е��Ǹ�����(���������Source)
		:_name(new char[strlen(other._name) + 1]()), // ʹ�öѿռ�����һ���Լ����ڴ�,����ǳ��������. 
		_age(other._age) // �����ж���ֵ�Լ���_age
	{
		strcpy(_name, other._name); // �����ж���ֵ�Լ���_name
		cout << this << "���ÿ������캯��" << endl;
	}

	// 3. ��ֵ���������, ����ʱ��ֻ��һ��, �����Ѿ�����, ��ͬ���Ѿ����ڵ�other����������¸�ֵ
	/* ��ֵ�����������д���Ĳ�:
		1. �����Ը�ֵ����
		2. ����������������ݳ�Աԭ������Ķѿռ�
		3. ������Լ����������ݳ�Ա�ĸ�ֵ��
		4. ����*this��������
	*/
	Person &operator = (const Person& other) 
	{
		if (this != &other) { // if(this == &other) �ͱ�ʾ�����other����, ������ͬһ������, �����Ը�ֵ, ��Ҫ��ܵ�, ֱ�ӷ���ָ�򱾶����ָ��
			delete[] _name; // �����������ԭ���Ķѿռ�
			_name = new char[strlen(other._name) + 1](); // �����µĶѿռ�
			strcpy(_name, other._name); // �����Ҳ�������ֵ
			_age = other._age;
		}
		cout << this << "���ø�ֵ���������" << endl;
		return *this;
	}

	void PrintInfo() {
		cout << "name:" << _name << endl;
		cout << "age:" << _age << endl;
		cout << this << ":-----------" << endl;
	}

	// 4. ��������, ����ʱ�����ڶ�������ʱ�Զ�����
	~Person() {
		if (_name != nullptr) {
			delete[] _name;
			_name = nullptr;
		}
		cout << this << "������������" << endl;
	}

private:
	char* _name;
	int _age;
};

void test1() {
	Person p1("С��", 60);
	Person p2("С�", 70);
	p1.PrintInfo();
	p2.PrintInfo();
}


int main() {
	test1();
	return 0;
}

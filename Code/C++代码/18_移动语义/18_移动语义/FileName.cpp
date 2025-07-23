#if 0
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "string.h"
using namespace std;

// ʵ�ֿ�������, ��ֵ���������
class String {
public:
	// ���캯��
	String(const char* pstr) 
		:_pstr(new char[strlen(pstr) + 1]())
	{
		strcpy(_pstr, pstr);
	}
	
	// �������캯��
	String(const String & rhs) 
		:_pstr(new char[strlen(rhs._pstr) + 1]())
	{
		strcpy(_pstr, rhs._pstr);
	}

	// ��ֵ���������
	String& operator=(const String& rhs)
		
	{
		// �Ը�ֵ�ж�
		if (this != &rhs) {
			//this->_pstr = rhs._pstr; // ǳ����
			delete[] _pstr; // ɾ����ֵԭ�������ݱ���������
			_pstr = new char[strlen(rhs._pstr) + 1](); // ���
			strcpy(_pstr, rhs._pstr);
		}
		return *this;
	}

	// �ƶ����캯��
	String(String &&rhs) noexcept//�����쳣
		: _pstr(rhs._pstr) // "��ȡ"��ֵ����ĳ�Ա, ������ֵ
	{
		rhs._pstr = nullptr; // ��Ҫ����������ʱ�����ָ��Ӷѿռ�Ͽ�
	}

	//�ƶ���ֵ����
	String& operator=(String&& rhs) noexcept {
		if (this != &rhs) {
			delete[] _pstr; 
			this->_pstr = rhs._pstr; // ǳ����
			rhs._pstr = nullptr;
		}
		return *this;
	}

	// ��������
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

// ʹ����Ԫ��������<<����������
ostream& operator<<(ostream& os, const String& rhs) { 
	if (rhs._pstr) {	 // Ҫ��ָ�벻Ϊ��
		os << rhs._pstr; // ��ָ�������������
	}
	return os;
}



void test() {
	String mystr1("faker"); // ����
	cout << "mystr1: " << mystr1 << endl;
	String mystr2 = mystr1; // ��������
	cout << "mystr2: " << mystr2 << endl;
	String mystr3("chovy"); // ��ֵ���������
	cout << "mystr3: " << mystr3 << endl;
	mystr3 = mystr1;
	cout << "mystr3: " << mystr3 << endl;

	String mystr4 = String("showmaker"); // ʹ����ֵ��ʼ��String
	cout << "mystr4: " << mystr4 << endl;

}


int main() {
	test();
	return 0;
}
#endif

#include <iostream>

// �������������������ֵ���� vs ��ֵ����
void overload(int& x) {
	std::cout << "overload(int&): lvalue ��ֵ���� ������\n";
}
void overload(int&& x) {
	std::cout << "overload(int&&): rvalue ��ֵ���� ������\n";
}

void test(int&& x) {
	// ��Ȼ x �������� int&&����������� ��x�� ��һ����ֵ���ʽ
	overload(x);               

	// �� std::move �� x ת������ֵ��Ż�ƥ����ֵ���ú���
	overload(std::move(x));    
}

int main() {
	test(42);
	return 0;
}


#include <iostream>
using namespace std;

// ȫ��ֻ��һ��ʾ������
// ��Ҫһ����̬�ĺ���, �������Ķ���¶�����
// ���⿽��

class Singleton {
public:
	static Singleton* getInstance(){
		if (_pInstance == nullptr) {

		}
	}


private:
	Singleton() {}
	static Singleton * _pInstance
};

void test() {

}

int main() {
	test();
}

#include <iostream>
using namespace std;

// 全局只有一个示例对象
// 需要一个静态的函数, 将创建的对象暴露给外界
// 避免拷贝

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

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class FunctionObject {
public:
    // 重载运算符(), 不接收参数
    int operator()() {
        cout << "FunctionObject operator()()" << endl;
        ++_count;
        return _count;
    }

    // 接收两个参数
    int operator()(int x, int y) {
        cout << "operator()(int,int)" << endl;
        ++_count;
        return x + y;
    }

    int _count = 0;//用这个数据成员来记录这个函数对象被调用的次数
};


void test0() {
    FunctionObject fo;

    cout << fo() << endl;
    cout << fo.operator()() << endl;//本质是这样写的

    cout << fo(5, 6) << endl;
    cout << fo.operator()(5, 6) << endl;//本质

    cout << "fo._count:" << fo._count << endl;//打印函数对象被调用的次数
}

int main() {
    test0();
    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class FunctionObject {
public:
    // ���������(), �����ղ���
    int operator()() {
        cout << "FunctionObject operator()()" << endl;
        ++_count;
        return _count;
    }

    // ������������
    int operator()(int x, int y) {
        cout << "operator()(int,int)" << endl;
        ++_count;
        return x + y;
    }

    int _count = 0;//��������ݳ�Ա����¼����������󱻵��õĴ���
};


void test0() {
    FunctionObject fo;

    cout << fo() << endl;
    cout << fo.operator()() << endl;//����������д��

    cout << fo(5, 6) << endl;
    cout << fo.operator()(5, 6) << endl;//����

    cout << "fo._count:" << fo._count << endl;//��ӡ�������󱻵��õĴ���
}

int main() {
    test0();
    return 0;
}

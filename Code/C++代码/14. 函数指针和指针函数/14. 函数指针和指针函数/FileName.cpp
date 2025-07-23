#include <iostream>
using namespace std;

// 普通函数
float add(int a, float b) {
    return a + b;
}

void test() {

    // 定义一个函数指针pf, 指针的类型需要和函数的返回值类型完全一致, 指针定义的参数类型也要与函数一致
    float (*pf)(int, float) = nullptr;
    // 将pf指向函数add, 与一般指针操作方法相同
    pf = &add;
    // 用指针调用函数add
    cout << pf(1, 2.9) << endl;

}


// 返回 int* 的函数：在堆上分配一个 int 并返回其地址
int* createInt(int value) {
    int* p = new int(value);
    return p;
}

void test1() {
    // 调用指针函数，得到一个指向 int 的指针
    int* pValue = createInt(42);

    cout << "*pValue = " << *pValue << endl;  // 解引用

    delete pValue;  // 别忘了释放内存
}

int main() {
    test1();
    return 0;
}
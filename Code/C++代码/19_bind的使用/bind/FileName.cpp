#include <iostream>
#include <functional>

using std::cout;
using std::endl;
using std::bind;
using namespace std;


#if 0
int add(int x, int y)
{
    cout << "int add(int, int)" << endl;
    return x + y;
}

int multiply(int x, int y, int z)
{
    cout << "int multiply(int, int, int)" << endl;
    return x * y * z;
}

class Example
{
public:
    //Example * this
    int add(int x, int y) // 非静态成员函数
    {
        cout << "int Example::add(int, int)" << endl;
        return x + y;
    }
};

void test()
{
    //在C语言中，函数名是函数的入口地址；数组名是数组的入口地址
    //但是在C++中，成员函数名与函数地址是两码事，函数名就是函数名，函数入口
    //地址就是函数的入口地址
    auto f = bind(add, 10, 20); // 普通函数名在表达式中会自动衰减为函数指针（类似数组名衰减为指针）
    cout << "f() = " << f() << endl;

    cout << endl;
    auto f2 = bind(&multiply, 3, 4, 5);
    cout << "f2() = " << f2() << endl;

    cout << endl;
    Example ex;
    auto f3 = bind(&Example::add, &ex, 11, 22); // 非静态成员函数必须使用引用绑定&
    cout << "f3() = " << f3() << endl;

    cout << endl;
    //占位符
    /* using namespace std::placeholders; */
    auto f4 = bind(add, 100, std::placeholders::_2);
    cout << "f4(200) = " << f4(200, 300, 400) << endl;
}

int main(int argc, char* argv[])
{
    test();
    printf("&main = %p\n", &main);  // 这里可以看到用不用&, 在传递函数名时函数名都会退化为函数指针
    printf("main = %p\n", main);
    return 0;
}
#endif

#if 0
int add(int x, int y)
{
    cout << "int add(int, int)" << endl;
    return x + y;
}

int multiply(int x, int y, int z)
{
    cout << "int multiply(int, int, int)" << endl;
    return x * y * z;
}

class Example
{
public:
    int add(int x, int y)
    {
        cout << "int Example::add(int, int)" << endl;
        return x + y;
    }
};

void func(int x, string y)
{
    cout << "x = " << x << endl;
    cout << "y = " << y << endl;
}

void test()
{
    //函数的类型(函数的标签、函数的形态):函数的返回类型与函数的参数列表(
    //参数的个数、参数的类型、参数顺序)
    //add函数的形态：int(int, int)
    //返回值f的形态：int()
    function<int()> f = bind(add, 10, 20);
    cout << "f() = " << f() << endl;

    cout << endl;
    //multiply的函数类型:int(int, int, int)
    //f2的形态:int()
    /* function<int()> f2 = bind(&multiply, 3, 4, 5); */
    /* cout << "f2() = " << f2() << endl; */
    f = bind(&multiply, 3, 4, 5);
    cout << "f() = " << f() << endl;

    cout << endl;
    Example ex;
    //成员函数add:int(Example *, int, int)
    //f3的形态：int()
    /* function<int()> f3 = bind(&Example::add, &ex, 11, 22); */
    /* cout << "f3() = " << f3() << endl; */
    f = bind(&Example::add, &ex, 11, 22);
    cout << "f() = " << f() << endl;

    cout << endl;
    //占位符
    //add函数的形态：int(int, int)
    //f4的形态：int(int)
    function<int(int)> f4 = bind(add, 100, std::placeholders::_1);
    cout << "f4(200) = " << f4(200) << endl;

    using namespace std::placeholders;
    //add的形态：int(int, int)
    function<int(int, int)> f5 = bind(add, _1, _2);

    //func的形态：void(int, string)
    function<void(int, string)> f6 = bind(func, 100, _2);
}

int main(int argc, char* argv[])
{
    test();
    return 0;
}
#endif

#if 0
class Example
{
public:
    int add(int x, int y)
    {
        cout << "int Example::add(int, int)" << endl;
        return x + y;
    }

    /* int _data() */
    /* { */
    /*     return 1234; */
    /* } */

    int _data = 1234;//C++11的写法，在声明的时候初始化
};

void test()
{
    Example ex;
    function<int()> f = bind(&Example::add, &ex, 11, 22);
    cout << "f() = " << f() << endl;

    cout << endl;
    function<int()> f2 = bind(&Example::_data, &ex);
    cout << "f2() = " << f2() << endl;
}

int main(int argc, char* argv[])
{
    test();
    return 0;
}
#endif



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
    int add(int x, int y) // �Ǿ�̬��Ա����
    {
        cout << "int Example::add(int, int)" << endl;
        return x + y;
    }
};

void test()
{
    //��C�����У��������Ǻ�������ڵ�ַ�����������������ڵ�ַ
    //������C++�У���Ա�������뺯����ַ�������£����������Ǻ��������������
    //��ַ���Ǻ�������ڵ�ַ
    auto f = bind(add, 10, 20); // ��ͨ�������ڱ��ʽ�л��Զ�˥��Ϊ����ָ�루����������˥��Ϊָ�룩
    cout << "f() = " << f() << endl;

    cout << endl;
    auto f2 = bind(&multiply, 3, 4, 5);
    cout << "f2() = " << f2() << endl;

    cout << endl;
    Example ex;
    auto f3 = bind(&Example::add, &ex, 11, 22); // �Ǿ�̬��Ա��������ʹ�����ð�&
    cout << "f3() = " << f3() << endl;

    cout << endl;
    //ռλ��
    /* using namespace std::placeholders; */
    auto f4 = bind(add, 100, std::placeholders::_2);
    cout << "f4(200) = " << f4(200, 300, 400) << endl;
}

int main(int argc, char* argv[])
{
    test();
    printf("&main = %p\n", &main);  // ������Կ����ò���&, �ڴ��ݺ�����ʱ�����������˻�Ϊ����ָ��
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
    //����������(�����ı�ǩ����������̬):�����ķ��������뺯���Ĳ����б�(
    //�����ĸ��������������͡�����˳��)
    //add��������̬��int(int, int)
    //����ֵf����̬��int()
    function<int()> f = bind(add, 10, 20);
    cout << "f() = " << f() << endl;

    cout << endl;
    //multiply�ĺ�������:int(int, int, int)
    //f2����̬:int()
    /* function<int()> f2 = bind(&multiply, 3, 4, 5); */
    /* cout << "f2() = " << f2() << endl; */
    f = bind(&multiply, 3, 4, 5);
    cout << "f() = " << f() << endl;

    cout << endl;
    Example ex;
    //��Ա����add:int(Example *, int, int)
    //f3����̬��int()
    /* function<int()> f3 = bind(&Example::add, &ex, 11, 22); */
    /* cout << "f3() = " << f3() << endl; */
    f = bind(&Example::add, &ex, 11, 22);
    cout << "f() = " << f() << endl;

    cout << endl;
    //ռλ��
    //add��������̬��int(int, int)
    //f4����̬��int(int)
    function<int(int)> f4 = bind(add, 100, std::placeholders::_1);
    cout << "f4(200) = " << f4(200) << endl;

    using namespace std::placeholders;
    //add����̬��int(int, int)
    function<int(int, int)> f5 = bind(add, _1, _2);

    //func����̬��void(int, string)
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

    int _data = 1234;//C++11��д������������ʱ���ʼ��
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



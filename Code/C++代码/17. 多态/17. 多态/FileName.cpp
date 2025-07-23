#include <iostream>
using std::cout;
using std::endl;

// ����ʱ��̬ʾ��
#if 0
class Base {
public:

    virtual void show() { // ��virtual���ε��麯��
        cout << "Base::show()" << endl;
    }

private:
    long _base = 10;
};

class Derived : public Base {
public:// ��Ȼûд virtual��������ͬǩ����д�ĺ���, �̳��˻������, ��Ȼ���麯��
    void show() override {//override ���߱������Ͷ��ߣ��� ȷ�� ����������дһ��������麯��

        cout << "Derived::show()" << endl;
    }

private:
   long _derived = 20;
};


void test1() {
    Base* p = new Derived; // ����ָ��p ָ����Derived����. ��������е�����ָ��vfptrָ��Derived������
                            // ��ʱp -> vfptrָ����vtabele����ʼ��ַ
    p->show(); // ����vfptr�ҵ���Derived��vtable, Ȼ����ת���麯�� Derived::show ִ��
    cout << sizeof(Base) << endl;
    cout << sizeof(Derived) << endl;
}

int main()
{
    test1();
    // ��� Derived::show()
    return 0;
}
#endif

// �麯���ڲ�ͬ�����µ���
#if 0
class Grandpa
{
public:
    Grandpa() { cout << "Grandpa()" << endl; }
    ~Grandpa() { cout << "~Grandpa()" << endl; }

    virtual void func1() {
        cout << "Grandpa::func1()" << endl;
    }

    virtual void func2() {
        cout << "Grandpa::func2()" << endl;
    }

};

class Parent
    : public Grandpa
{
public:
    Parent() {
        cout << "Parent()" << endl;
        func1();//���캯���е����麯��
    }

    ~Parent() {
        cout << "~Parent()" << endl;
        func2();//���������е����麯��
    }

    // ֻ������func2() ,û��func1()
    virtual void func2() override {
        cout << "Parent::func2()" << endl;
    }
};

class Son
    : public Parent
{
public:
    Son() { cout << "Son()" << endl; }
    ~Son() { cout << "~Son()" << endl; }

    virtual void func1() override {
        cout << "Son::func1()" << endl;
    }

    virtual void func2() override {
        cout << "Son::func2()" << endl;
    }
};

void test0() {
    Son ss;
    Parent pp;
    Grandpa* p = &pp;
    p->func1();
    p->func2();
}

int main() {
    test0();
    return 0;
}
#endif

// ���麯��
#if 0
class A
{
public: // �����������麯��
    virtual void print() = 0;
    virtual void display() = 0;
};

class B
    : public A
{
public:
    virtual void print() override {
        cout << "B::print()" << endl;
    }
};

class C
    : public B
{
public:
    virtual void display() override {
        cout << "C::display()" << endl;
    }
};

void test0() {
    //A�ඨ���˴��麯����A���ǳ�����
    //�������޷���������
    //A a;//error
    //B b;//error
    C c;
    A* pa2 = &c;
    pa2->print();
    pa2->display();
}

int main() {
    test0();
    return 0;
}
#endif

//�õ�ַ�������
#if 0
class Base {

    virtual
        void print() {
        cout << "Base::print()" << endl;
    }

    virtual
        void display() {
        cout << "Base::display()" << endl;
    }

    virtual
        void show() {
        cout << "Base::show()" << endl;
    }

private:
    long _base = 10;
};

class Derived : public Base
{
    void print() {
        cout << "Derived::print()" << endl;
    }

    void display() {
        cout << "Derived::display()" << endl;
    }

    void show() {
        cout << "Derived::show()" << endl;
    }

private:
    long _derived = 100;
};

void test() {
    Base base;
    Derived derived;
    cout << "sizeof(base)= " << sizeof(base) << endl; //16
    cout << "sizeof(derived)= " << sizeof(derived) << endl; //16 + 8(long) = 24
    
    
    long* pbase = (long*)&base;
    long* pderived = (long*)&derived;
    //pbase���Կ����ǵ�base������׵�ַ���׵�ַ��ŵ���ָ��vfptr, ƫ��һ��ָ���С����base����
    long* base_vfptr = (long*)*pbase;
    long base_number = *(pbase + 1);
    cout << "base_vfptr=" << base_vfptr << endl;
    cout << "base_number=" << base_number << endl;


    //pderived���Կ����ǵ�derived������׵�ַ,ƫ��һ��ָ���С����base��derived����
    long* derived_vfptr = (long*)*pderived;
    long derived_base_number = *(pderived + 1);
    long derived_number = *(pderived + 2);
    cout << "derived_vfptr=" << derived_vfptr << endl;
    cout << "derived_base_number=" << derived_base_number << endl;
    cout << "derived_number=" << derived_number << endl;


    //�麯����ĵ�һ������������ַ
    cout << "base��һ���麯����ַ=" << base_vfptr << endl;
    cout << "base�ڶ����麯����ַ=" << base_vfptr + 1 << endl;
    cout << "base�������麯����ַ=" << base_vfptr + 2 << endl;
    cout << "derived��һ���麯����ַ=" << derived_vfptr << endl;
    cout << "derived�ڶ����麯����ַ=" << derived_vfptr + 1 << endl;
    cout << "derived�������麯����ַ=" << derived_vfptr + 2 << endl;

    
    //�ٴζ��麯����ַ���н����ã�Ȼ����һ������ָ�룬���ú���
    typedef void (*pFunc)();
    pFunc base_print = (pFunc)*base_vfptr;
    pFunc base_display = (pFunc) * (base_vfptr + 1);
    pFunc base_show = (pFunc) * (base_vfptr + 2);
    base_print();
    base_display();
    base_show();
    pFunc derived_print = (pFunc)*derived_vfptr;
    pFunc derived_display = (pFunc) * (derived_vfptr + 1);
    pFunc derived_show = (pFunc) * (derived_vfptr + 2);
    derived_print();
    derived_display();
    derived_show();
}

int main()
{
    test();
    return 0;
}
#endif

class Base1 {
public:
    Base1()
        :_iBase1(10)
    {
        cout << "Base1()" << endl;
    }

    virtual void f() {
        cout << "Base1::f()" << endl;
    }

    virtual void g() {
        cout << "Base1::g()" << endl;
    }

    virtual void h() {
        cout << "Base1::h()" << endl;
    }

    virtual ~Base1() {
        cout << "~Base1()" << endl;
    }

private:
    double _iBase1;
};

class Base2 {
public:
    Base2()
        :_iBase2(20)
    {
        cout << "Base2()" << endl;
    }

    virtual void f() {
        cout << "Base2::f()" << endl;
    }

    virtual void g() {
        cout << "Base2::g()" << endl;
    }

    virtual void h() {
        cout << "Base2::h()" << endl;
    }

    virtual ~Base2() {
        cout << "~Base2()" << endl;
    }

private:
    double _iBase2;
};

class Base3 {
public:
    Base3()
        :_iBase3(30)
    {
        cout << "Base3()" << endl;
    }

    virtual void f() {
        cout << "Base3::f()" << endl;
    }

    virtual void g() {
        cout << "Base3::g()" << endl;
    }

    virtual void h() {
        cout << "Base3::h()" << endl;
    }

    virtual ~Base3() {
        cout << "~Base3()" << endl;
    }

private:
    double _iBase3;
};

class Derived
    : public Base1
    , public Base2
    , public Base3
{
public:
    Derived()
        : _iDerived(10000)
    {
        cout << "Derived()" << endl;
    }

    void f() override
    {
        cout << "Derived::f()" << endl;
    }

    void g1()
    {
        cout << "Derived::g1()" << endl;
    }
private:
    double _iDerived;
};

int main(void)
{
    cout << sizeof(Derived) << endl;

    Derived d;
    Base1* pBase1 = &d;
    Base2* pBase2 = &d;
    Base3* pBase3 = &d;

    cout << "&Derived = " << &d << endl;
    cout << "pBase1 = " << pBase1 << endl;
    cout << "pBase2 = " << pBase2 << endl;
    cout << "pBase3 = " << pBase3 << endl;

    return 0;
}

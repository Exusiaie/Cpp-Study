#include <iostream>
using std::cout;
using std::endl;

// 运行时多态示例
#if 0
class Base {
public:

    virtual void show() { // 用virtual修饰的虚函数
        cout << "Base::show()" << endl;
    }

private:
    long _base = 10;
};

class Derived : public Base {
public:// 虽然没写 virtual，但这是同签名重写的函数, 继承了基类的虚, 依然是虚函数
    void show() override {//override 告诉编译器和读者：我 确认 这里是在重写一个基类的虚函数

        cout << "Derived::show()" << endl;
    }

private:
   long _derived = 20;
};


void test1() {
    Base* p = new Derived; // 基类指针p 指向了Derived对象. 这个对象中的隐藏指针vfptr指向Derived类的虚表
                            // 此时p -> vfptr指向了vtabele的起始地址
    p->show(); // 根据vfptr找到了Derived的vtable, 然后跳转到虚函数 Derived::show 执行
    cout << sizeof(Base) << endl;
    cout << sizeof(Derived) << endl;
}

int main()
{
    test1();
    // 输出 Derived::show()
    return 0;
}
#endif

// 虚函数在不同条件下调用
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
        func1();//构造函数中调用虚函数
    }

    ~Parent() {
        cout << "~Parent()" << endl;
        func2();//析构函数中调用虚函数
    }

    // 只覆盖了func2() ,没动func1()
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

// 纯虚函数
#if 0
class A
{
public: // 定义两个纯虚函数
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
    //A类定义了纯虚函数，A类是抽象类
    //抽象类无法创建对象
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

//用地址访问虚表
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
    //pbase可以看做是当base对象的首地址，首地址存放的是指针vfptr, 偏移一个指针大小便是base变量
    long* base_vfptr = (long*)*pbase;
    long base_number = *(pbase + 1);
    cout << "base_vfptr=" << base_vfptr << endl;
    cout << "base_number=" << base_number << endl;


    //pderived可以看做是当derived对象的首地址,偏移一个指针大小便是base和derived变量
    long* derived_vfptr = (long*)*pderived;
    long derived_base_number = *(pderived + 1);
    long derived_number = *(pderived + 2);
    cout << "derived_vfptr=" << derived_vfptr << endl;
    cout << "derived_base_number=" << derived_base_number << endl;
    cout << "derived_number=" << derived_number << endl;


    //虚函数表的第一二三个函数地址
    cout << "base第一个虚函数地址=" << base_vfptr << endl;
    cout << "base第二个虚函数地址=" << base_vfptr + 1 << endl;
    cout << "base第三个虚函数地址=" << base_vfptr + 2 << endl;
    cout << "derived第一个虚函数地址=" << derived_vfptr << endl;
    cout << "derived第二个虚函数地址=" << derived_vfptr + 1 << endl;
    cout << "derived第三个虚函数地址=" << derived_vfptr + 2 << endl;

    
    //再次对虚函数地址进行解引用，然后定义一个函数指针，调用函数
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

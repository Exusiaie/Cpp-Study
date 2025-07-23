#include <iostream>
#include <string>
using namespace std;

// 使用成员函数对+进行重载
#if 0 
class Complex {
public:
    Complex(int real, int image)
        :_real(real)
        , _image(image)
    {
        cout << "------Complex(int, int)------" << endl;
    }

    // 运算符重载函数, 第一个参数是this指针 第二个参数是＋的右操作数
    Complex operator+(const Complex& rhs) {
        return Complex(_real + rhs._real, _image + rhs._image);
    }

    void print() {
        cout << _real << " + " << _image << "i" << endl;
    }

private:
    int _real;
    int _image;
};

void test() {
    Complex cx1(1, 2);
    Complex cx2(3, 4);
    //上下两种方式完全等价
    Complex cx3 = cx1 + cx2;
    //  Complex cx4 = cx1.operator+(cx2);//本质等价
    cx3.print();
    //  cx4.print();
}
#endif

// 使用友元函数进行+运算符进行重载
#if 0 
class Complex {
public:
    Complex(int real, int image)
        :_real(real)
        , _image(image)
    {
        cout << "------Complex(int, int)------" << endl;
    }

    void print() {
        cout << _real << " + " << _image << "i" << endl;
    }

    friend Complex operator+(const Complex& lhs, const Complex& rhs);

private:
    int _real;
    int _image;
};

Complex operator+(const Complex& lhs, const Complex& rhs) {
        return Complex(lhs._real + rhs._real, lhs._image + rhs._image);
}

void test0() {
    Complex cx1(1, 2);
    Complex cx2(3, 4);
    Complex cx3 = cx1 + cx2;
    cx3.print();
}

int main() {
    test0();
    return 0;
}
#endif



 // +=这种修改操作数值的运算符, 一般使用成员函数
 // ++这种运算符只有一个操作数, 仅靠this指针就能完成
#if 0
class Complex {
public:
    Complex(int real, int image)
        :_real(real)
        , _image(image)
    {
        cout << "------Complex(int, int)------" << endl;
    }

    // 运算符重载函数, 第一个参数是this指针 第二个参数是 ＋= 的右操作数, 返回值是对象的引用可以增加性能
    Complex& operator+=(const Complex& rhs) {
        // return Complex(this->_real + rhs._real, this->_image + rhs._image);
        // 这样写会构造一个临时的变量并且返回, 但是主函数中并没有相应的参数来接收它, 这个临时变量就被抛弃了
        // 因此我们需要通过this指针直接对调用这个重载函数的cx2本身进行操作
        this->_real = this->_real + rhs._real;
        this->_image += rhs._image; // 两个基本数据类型+=不需要调用重载函数
        return *this;
    }

    // 前置++
    Complex& operator++() {
        ++_real;
        ++_image;
        return *this;
    }

    // 后置++
    Complex& operator++(int) {
        _real++;
        _image++;
        return *this;
    }

    void print() {
        cout << _real << " + " << _image << "i" << endl;
    }

private:
    int _real;
    int _image;
};

void test() {
    Complex cx1(1, 2);
    Complex cx2(3, 4);

    cx1.print();
    cx1 += cx2;
    cx1.print();
    ++cx1;
    cx1.print();
}
#endif

 // 用成员函数对[]运算符重载
#if 0
class Array {
public:
    Array(const char* arr) // test函数传来的参数为数组的首元素地址
        :_capacity(sizeof(arr)),
        _data(new char[_capacity]())
    { 
        for (size_t i = 0; i <= _capacity; ++i) {
            _data[i] = arr[i]; // 为什么参数类型为char* 还可以用下标运算符?
                                // 相当于*(arr + i)只使用首元素指针和地址偏移计算
        }
    }

    ~Array() {
        if (_data) {
            return;
        }
        delete _data;
        _data = nullptr;
        return;
    }
    //数组arr调用, capacity为8
    char& operator[](size_t idx) { // 调用[]时传来的参数自然是size_t类型的下标
        if (idx < _capacity) {
            return _data[idx];
        }
        else {
            cout << "out of range" << endl;
            static char nullchar = '\0'; // 静态成员变量在程序开始时被分配，直到程序结束才释放, 是一个可以被使用的左值
            return nullchar; // 必须返回左值, 否则会造成悬空引用
        }
    }

    void print() const {
        cout << _data << endl;
    }
private:
    size_t _capacity; // 数组大小
    char* _data; // 
};

void test() {
    char arr[10] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', };
    Array AAA(arr);
    for (int i = 0; i < 10; ++i) {
        cout << AAA[i] << endl;
    }
}
#endif


 // 用友元函数对<<输出流运算符进行重载
#if 0
class Complex{
public:
    Complex(int real, int image)
        :_real(real)
        , _image(image)
    {
        cout << "------Complex(int, int)------" << endl;
    }
    friend ostream& operator<<(ostream &os, const Complex& rhs);

    void print() {
        cout << _real << " + " << _image << "i" << endl;
    }

private:
    int _real;
    int _image;
};

// 输出流重载有两个操作数, 一个是左边的输出流ostream, 一个是右边的对象, 这适合使用友元函数重载. (如果使用成员函数重载, 第一个参数必然是this指针)
ostream& operator<<(ostream &os, const Complex& rhs) {
    os << rhs._real << endl;
    os << rhs._image << endl; 
    os << "(" << rhs._real << "," << rhs._image <<")";
    return os;
}

void test() {
    Complex cx1(666, 777);
    cout << cx1 << endl; //本质形式： operator<<(cout,cx) << endl;

}
#endif


// 用友元函数对>>输入流运算符进行重载
#if 0
class Complex {
public:
    Complex(int real = 0, int image = 0)
        :_real(real)
        , _image(image)
    {
        cout << "------Complex(int, int)------" << endl;
    }
    friend ostream& operator<<(ostream& os, const Complex& rhs);
    friend istream& operator>>(istream& is,  Complex& rhs);

    void print() {
        cout << _real << " + " << _image << "i" << endl;
    }

private:
    int _real;
    int _image;
};

ostream& operator<<(ostream& os, const Complex& rhs) {
    os << rhs._real << endl;
    os << rhs._image << endl;
    os << "(" << rhs._real << "," << rhs._image << ")";
    return os;
}

// 对于输入流运算符, 因为要修改右操作数, 所以不能再使用const
istream& operator>>(istream& is,  Complex& rhs) {
    is >> rhs._real;
    is >> rhs._image;

    return is;
}

void test() {
    Complex cx1;
    cin >> cx1; //本质形式： operator>>(cin,cx)
    cout << cx1 << endl;
}

int main() {
    test();

    return 0;
}
#endif

// 两层 MiddleLayer -> Data
#if 0
class Data
{
public:
    Data() {}
    ~Data() {}

    int getData() const { // const表示保证不修改成员
        return _data; 
    }
private:
    int _data = 10;
};

class MiddleLayer
{
public:
    MiddleLayer(Data* p)
        : _pdata(p)
    {
    }

    ~MiddleLayer() {
        if (_pdata) {
            delete _pdata;
            _pdata = nullptr;
        }
    }
private:
    Data* _pdata; // 双层结构, MiddleLayer含有一个Data*型的数据成员
};

// 传统形式使用指针, 需要对Data实例进行手动释放内存 
void test1() {
    Data* pdata = new Data();
    /*双层结构”：
        第一层 —— 指针 Data* p，存放地址。p指向了存在堆上的类Data
        第二层 —— 堆上 Data 对象实例，存放成员变量 _data。
    */
    pdata->getData();
    (*pdata).getData(); // *p得到Data实例,  .调用Data的成员函数
    delete pdata;
    pdata = nullptr;
}

void test2() {
//....后续正常使用
// delete pdata;不需要手动delete, 在MiddleLayer结束调用析构函数时会执行delete逻辑
// 当MiddleLayer栈空间被销毁时Data实例就被释放
    Data* pdata = new Data();
    MiddleLayer ml(pdata);

    // 这反而会造成double free
    // delete pdata;
    // pdata = nullptr;
}
#endif

// 使用成员函数对->运算符进行重载
#if 0
class Data
{
public:
    Data() {}
    ~Data() {}

    int getData() const { // const表示保证不修改成员
        return _data;
    }
private:
    int _data = 10;
};

class MiddleLayer
{
public:
    MiddleLayer(Data* p)
        : _pdata(p)
    {
    }

    // 对->进行重载, 需要将指向Data的指针_pdata返回, 这样才能正常访问Data类
    Data* operator->() {
        return _pdata;
    }

    ~MiddleLayer() {
        if (_pdata) {
            delete _pdata;
            _pdata = nullptr;
        }
    }
private:
    Data* _pdata; // 双层结构, MiddleLayer含有一个Data*型的数据成员
};

void test() {
    Data* pdata = new Data; // 在堆上创建一个Data实例
    MiddleLayer ml(pdata);

    cout << ml->getData(); // *(ml).getData
}
#endif



class Data {

public:
    Data() {
        cout << "Data()" << endl;
    }

    ~Data() {
        cout << "~Data()" << endl;
    }
    int getData() {
        return _data;
    }

private:
    int _data = 10;
};

class MiddleLayer {
public:
    MiddleLayer(Data* p)
        :_pdata(p)
    {
        cout << "MiddleLayer(Data *)" << endl;
    }

    ~MiddleLayer() {
        cout << "~MiddleLayer()" << endl;
        if (_pdata) {
            delete _pdata;
            _pdata = nullptr;
        }
    }
    Data* operator->() {
        return _pdata;
    }
    //对象能够进行解引用，只有一个原因
    //实现了解引用运算符的重载
    Data& operator*() {
        return *_pdata;
    }

private:
    Data* _pdata;
};

class ThirdLayer {
public:
    ThirdLayer(MiddleLayer* p)
        :_pml(p)
    {
        cout << "ThirdLayer(MiddleLayer*)" << endl;
    }
    ~ThirdLayer() {
        cout << "~ThirdLayer()" << endl;
        if (_pml) {
            delete _pml;
            _pml = nullptr;
        }
    }
    //箭头访问运算符
    MiddleLayer& operator->() {
        return *_pml;
    }
    Data& operator*() {
        return *(*_pml);
    }

private:
    MiddleLayer* _pml;
};


void test() {
    ThirdLayer tl(new MiddleLayer(new Data()));
    //目前的代码满足不了这个功能
    cout << (*tl).getData() << endl;
}

int main() {
    test();
    return 0;
}



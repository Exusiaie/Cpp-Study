#include <iostream>
#include <string>
using namespace std;

// ʹ�ó�Ա������+��������
#if 0 
class Complex {
public:
    Complex(int real, int image)
        :_real(real)
        , _image(image)
    {
        cout << "------Complex(int, int)------" << endl;
    }

    // ��������غ���, ��һ��������thisָ�� �ڶ��������ǣ����Ҳ�����
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
    //�������ַ�ʽ��ȫ�ȼ�
    Complex cx3 = cx1 + cx2;
    //  Complex cx4 = cx1.operator+(cx2);//���ʵȼ�
    cx3.print();
    //  cx4.print();
}
#endif

// ʹ����Ԫ��������+�������������
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



 // +=�����޸Ĳ�����ֵ�������, һ��ʹ�ó�Ա����
 // ++���������ֻ��һ��������, ����thisָ��������
#if 0
class Complex {
public:
    Complex(int real, int image)
        :_real(real)
        , _image(image)
    {
        cout << "------Complex(int, int)------" << endl;
    }

    // ��������غ���, ��һ��������thisָ�� �ڶ��������� ��= ���Ҳ�����, ����ֵ�Ƕ�������ÿ�����������
    Complex& operator+=(const Complex& rhs) {
        // return Complex(this->_real + rhs._real, this->_image + rhs._image);
        // ����д�ṹ��һ����ʱ�ı������ҷ���, �����������в�û����Ӧ�Ĳ�����������, �����ʱ�����ͱ�������
        // ���������Ҫͨ��thisָ��ֱ�ӶԵ���������غ�����cx2������в���
        this->_real = this->_real + rhs._real;
        this->_image += rhs._image; // ����������������+=����Ҫ�������غ���
        return *this;
    }

    // ǰ��++
    Complex& operator++() {
        ++_real;
        ++_image;
        return *this;
    }

    // ����++
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

 // �ó�Ա������[]���������
#if 0
class Array {
public:
    Array(const char* arr) // test���������Ĳ���Ϊ�������Ԫ�ص�ַ
        :_capacity(sizeof(arr)),
        _data(new char[_capacity]())
    { 
        for (size_t i = 0; i <= _capacity; ++i) {
            _data[i] = arr[i]; // Ϊʲô��������Ϊchar* ���������±������?
                                // �൱��*(arr + i)ֻʹ����Ԫ��ָ��͵�ַƫ�Ƽ���
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
    //����arr����, capacityΪ8
    char& operator[](size_t idx) { // ����[]ʱ�����Ĳ�����Ȼ��size_t���͵��±�
        if (idx < _capacity) {
            return _data[idx];
        }
        else {
            cout << "out of range" << endl;
            static char nullchar = '\0'; // ��̬��Ա�����ڳ���ʼʱ�����䣬ֱ������������ͷ�, ��һ�����Ա�ʹ�õ���ֵ
            return nullchar; // ���뷵����ֵ, ����������������
        }
    }

    void print() const {
        cout << _data << endl;
    }
private:
    size_t _capacity; // �����С
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


 // ����Ԫ������<<������������������
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

// ���������������������, һ������ߵ������ostream, һ�����ұߵĶ���, ���ʺ�ʹ����Ԫ��������. (���ʹ�ó�Ա��������, ��һ��������Ȼ��thisָ��)
ostream& operator<<(ostream &os, const Complex& rhs) {
    os << rhs._real << endl;
    os << rhs._image << endl; 
    os << "(" << rhs._real << "," << rhs._image <<")";
    return os;
}

void test() {
    Complex cx1(666, 777);
    cout << cx1 << endl; //������ʽ�� operator<<(cout,cx) << endl;

}
#endif


// ����Ԫ������>>�������������������
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

// ���������������, ��ΪҪ�޸��Ҳ�����, ���Բ�����ʹ��const
istream& operator>>(istream& is,  Complex& rhs) {
    is >> rhs._real;
    is >> rhs._image;

    return is;
}

void test() {
    Complex cx1;
    cin >> cx1; //������ʽ�� operator>>(cin,cx)
    cout << cx1 << endl;
}

int main() {
    test();

    return 0;
}
#endif

// ���� MiddleLayer -> Data
#if 0
class Data
{
public:
    Data() {}
    ~Data() {}

    int getData() const { // const��ʾ��֤���޸ĳ�Ա
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
    Data* _pdata; // ˫��ṹ, MiddleLayer����һ��Data*�͵����ݳ�Ա
};

// ��ͳ��ʽʹ��ָ��, ��Ҫ��Dataʵ�������ֶ��ͷ��ڴ� 
void test1() {
    Data* pdata = new Data();
    /*˫��ṹ����
        ��һ�� ���� ָ�� Data* p����ŵ�ַ��pָ���˴��ڶ��ϵ���Data
        �ڶ��� ���� ���� Data ����ʵ������ų�Ա���� _data��
    */
    pdata->getData();
    (*pdata).getData(); // *p�õ�Dataʵ��,  .����Data�ĳ�Ա����
    delete pdata;
    pdata = nullptr;
}

void test2() {
//....��������ʹ��
// delete pdata;����Ҫ�ֶ�delete, ��MiddleLayer����������������ʱ��ִ��delete�߼�
// ��MiddleLayerջ�ռ䱻����ʱDataʵ���ͱ��ͷ�
    Data* pdata = new Data();
    MiddleLayer ml(pdata);

    // �ⷴ�������double free
    // delete pdata;
    // pdata = nullptr;
}
#endif

// ʹ�ó�Ա������->�������������
#if 0
class Data
{
public:
    Data() {}
    ~Data() {}

    int getData() const { // const��ʾ��֤���޸ĳ�Ա
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

    // ��->��������, ��Ҫ��ָ��Data��ָ��_pdata����, ����������������Data��
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
    Data* _pdata; // ˫��ṹ, MiddleLayer����һ��Data*�͵����ݳ�Ա
};

void test() {
    Data* pdata = new Data; // �ڶ��ϴ���һ��Dataʵ��
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
    //�����ܹ����н����ã�ֻ��һ��ԭ��
    //ʵ���˽����������������
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
    //��ͷ���������
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
    //Ŀǰ�Ĵ������㲻���������
    cout << (*tl).getData() << endl;
}

int main() {
    test();
    return 0;
}



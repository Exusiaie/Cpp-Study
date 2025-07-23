#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;

class My_String {
public:
    // 默认构造函数
    My_String()
        : _pstr(new char[1]())  // 初始化为一个空字符
    {
        cout << "默认构造函数: " << endl;
    }

    // 接受 C 字符串构造函数
    explicit My_String(const char* pstr)
        : _pstr(new char[strlen(pstr) + 1]())  // 分配内存
    {
        strcpy(_pstr, pstr);  // 复制字符串
        cout << "构造函数: " << endl;
    }

    // 复制构造函数
    My_String(const My_String& rhs)
        : _pstr(new char[strlen(rhs._pstr) + 1]())  // 重新分配内存
    {
        strcpy(_pstr, rhs._pstr);  // 复制字符串
        cout << "拷贝构造函数: " << endl;
    }

    // 赋值运算符重载
    My_String& operator=(const My_String& rhs) {
        if (this == &rhs)  // 处理自赋值
            return *this;

        delete[] _pstr;  // 删除旧内存

        _pstr = new char[strlen(rhs._pstr) + 1]();  // 重新分配内存
        strcpy(_pstr, rhs._pstr);  // 复制内容
        cout << "赋值运算符函数: " << endl;

        return *this;
    }

    // 返回是否为空
    bool empty() const {
        return strlen(_pstr) == 0;
    }

    // 返回字符串的大小
    int size() const {
        return strlen(_pstr);
    }

    // 返回 C 风格的字符串
    const char* c_str() const {
        return _pstr;
    }

    // 析构函数
    ~My_String() {
        delete[] _pstr;  // 删除动态分配的内存
        cout << "~String()" << endl;
    }

    // 追加字符串 (另一个 String)
    My_String& append(const My_String& rhs) {
        char* temp = new char[size() + rhs.size() + 1]();  // 重新分配更大的内存
        strcpy(temp, _pstr);  // 复制原始字符串
        strcat(temp, rhs._pstr);  // 追加 rhs 的字符串

        delete[] _pstr;  // 删除原来的内存
        _pstr = temp;  // 更新指针
        return *this;
    }

    // 追加字符串 (C 风格字符串)
    My_String& append(const char* pstr) {
        char* temp = new char[size() + strlen(pstr) + 1]();  // 重新分配更大的内存
        strcpy(temp, _pstr);  // 复制原始字符串
        strcat(temp, pstr);  // 追加 C 字符串

        delete[] _pstr;  // 删除原来的内存
        _pstr = temp;  // 更新指针
        return *this;
    }

private:
    char* _pstr;  // 存储字符串的指针
};

int main() {
    // 测试字符串构造和操作
    My_String str1("WCSDSLMTBDSL");
    cout << "str1: " << str1.c_str() << ", size: " << str1.size() << endl;

    My_String str2(" MTZMBQS");
    str1.append(str2);
    cout << "str1 after append: " << str1.c_str() << ", size: " << str1.size() << endl;

    My_String str3;
    str3.append(" WCMTZKSY");
    str3.append(" WCYZLA").append(" BBRDSB");
    cout << "str3: " << str3.c_str() << ", size: " << str3.size() << endl;

    return 0;
}

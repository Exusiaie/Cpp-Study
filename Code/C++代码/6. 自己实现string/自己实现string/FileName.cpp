#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;

class My_String {
public:
    // Ĭ�Ϲ��캯��
    My_String()
        : _pstr(new char[1]())  // ��ʼ��Ϊһ�����ַ�
    {
        cout << "Ĭ�Ϲ��캯��: " << endl;
    }

    // ���� C �ַ������캯��
    explicit My_String(const char* pstr)
        : _pstr(new char[strlen(pstr) + 1]())  // �����ڴ�
    {
        strcpy(_pstr, pstr);  // �����ַ���
        cout << "���캯��: " << endl;
    }

    // ���ƹ��캯��
    My_String(const My_String& rhs)
        : _pstr(new char[strlen(rhs._pstr) + 1]())  // ���·����ڴ�
    {
        strcpy(_pstr, rhs._pstr);  // �����ַ���
        cout << "�������캯��: " << endl;
    }

    // ��ֵ���������
    My_String& operator=(const My_String& rhs) {
        if (this == &rhs)  // �����Ը�ֵ
            return *this;

        delete[] _pstr;  // ɾ�����ڴ�

        _pstr = new char[strlen(rhs._pstr) + 1]();  // ���·����ڴ�
        strcpy(_pstr, rhs._pstr);  // ��������
        cout << "��ֵ���������: " << endl;

        return *this;
    }

    // �����Ƿ�Ϊ��
    bool empty() const {
        return strlen(_pstr) == 0;
    }

    // �����ַ����Ĵ�С
    int size() const {
        return strlen(_pstr);
    }

    // ���� C �����ַ���
    const char* c_str() const {
        return _pstr;
    }

    // ��������
    ~My_String() {
        delete[] _pstr;  // ɾ����̬������ڴ�
        cout << "~String()" << endl;
    }

    // ׷���ַ��� (��һ�� String)
    My_String& append(const My_String& rhs) {
        char* temp = new char[size() + rhs.size() + 1]();  // ���·��������ڴ�
        strcpy(temp, _pstr);  // ����ԭʼ�ַ���
        strcat(temp, rhs._pstr);  // ׷�� rhs ���ַ���

        delete[] _pstr;  // ɾ��ԭ�����ڴ�
        _pstr = temp;  // ����ָ��
        return *this;
    }

    // ׷���ַ��� (C ����ַ���)
    My_String& append(const char* pstr) {
        char* temp = new char[size() + strlen(pstr) + 1]();  // ���·��������ڴ�
        strcpy(temp, _pstr);  // ����ԭʼ�ַ���
        strcat(temp, pstr);  // ׷�� C �ַ���

        delete[] _pstr;  // ɾ��ԭ�����ڴ�
        _pstr = temp;  // ����ָ��
        return *this;
    }

private:
    char* _pstr;  // �洢�ַ�����ָ��
};

int main() {
    // �����ַ�������Ͳ���
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

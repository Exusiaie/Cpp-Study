#include <iostream>
using namespace std;

// ��ͨ����
float add(int a, float b) {
    return a + b;
}

void test() {

    // ����һ������ָ��pf, ָ���������Ҫ�ͺ����ķ���ֵ������ȫһ��, ָ�붨��Ĳ�������ҲҪ�뺯��һ��
    float (*pf)(int, float) = nullptr;
    // ��pfָ����add, ��һ��ָ�����������ͬ
    pf = &add;
    // ��ָ����ú���add
    cout << pf(1, 2.9) << endl;

}


// ���� int* �ĺ������ڶ��Ϸ���һ�� int ���������ַ
int* createInt(int value) {
    int* p = new int(value);
    return p;
}

void test1() {
    // ����ָ�뺯�����õ�һ��ָ�� int ��ָ��
    int* pValue = createInt(42);

    cout << "*pValue = " << *pValue << endl;  // ������

    delete pValue;  // �������ͷ��ڴ�
}

int main() {
    test1();
    return 0;
}
#include <iostream>
//ע�⣺��Ҫinclude
#include <limits>
#include <cstring>
#include <fstream>
#include <string>

using namespace std;

void check_stream_status() {
    cout << "cin goodbit:" << cin.good() << endl; // ����״̬
    cout << "cin badbit:" << cin.bad() << endl; // ���ɻָ�����
    cout << "cin failbit:" << cin.fail() << endl; // �ɻָ�����
    cout << "cin eofbit:" << cin.eof() << endl; // ������β

}

// ��׼���������, ʹ����״̬�����߼�
void test1() {
    cout << "����������" << endl;
    int number;
    while (1) {
        cin >> number;
        if (cin.eof() || cin.bad()) {
            check_stream_status();
            cout << "�����Ѿ�����" << endl;
            break;
        }
        else if (cin.fail()) {
            check_stream_status();
            cout << "��ջ�����" << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            check_stream_status();
            cout << "������һ������" << endl;
        }
        else {
            //good
            cout << "number=" << number << endl;
            check_stream_status();
        }
    }
}

// ��׼�������������ķ���ֵ�Ƕ����Լ�, ���ֱ�ӽ�number����if�ж�������, �������ʽ����ת��Ϊtrue����false, 
void test2() {
    cout << "����������" << endl;
    int number;
    while (1) {
        cin >> number;
        if (!number) {
            check_stream_status();
            cout << "��ջ�����" << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            check_stream_status();
            cout << "������һ������" << endl;
        }
        else if(number){
            //good
            cout << "number=" << number << endl;
            check_stream_status();
        }
    }
}


// �ļ�������
void test3() {
    ifstream ifs;
    ifs.open("test1.cc"); // ʹ��open��������һ���ļ�������

    ifstream ifs2("test2.cc"); // ʹ�ò�������һ���ļ�������

    string filename = "test3.cc"; // ���������һ���ַ���
    ifstream ifs3(filename);
}

void test4() {
    ifstream ifs("temp.txt");
    if (!ifs.good()) { // ����ļ�����������good״̬��ֹͣ��
        cerr << "ifstream is not good" << endl;
        return;
    }

    string word;
    while (ifs >> word) { // ��ifs״̬Ϊgoodʱ, һֱ����ļ����뻺�����е�����, ֪������״̬Ϊeof����������
        cout << word;
    }
    cout << endl;
    ifs.close(); // �ǵùر���
}

void test5() {

        ifstream ifs("temp.txt");
        if (!ifs.good()) { // ����ļ�����������goodbit״̬��ֹͣ��
            cerr << "ifstream is not good" << endl;
            return;
        }

        string word;
        while (getline(ifs, word, '-')) { // ��һ���������ļ���, �ڶ�����������������Ļ�����, ��������ָ���ķָ���Ĭ���ǻ���, ����ֵ������Ķ���
            cout << word << endl;
        }
        cout << endl;
        ifs.close();
}

// �ļ������
void test6() {
    ofstream ofs1("temp1.txt"); // Ĭ�ϴ�ģʽ��outģʽ, ÿ���������
    string line("MTZC!\n");
    ofs1 << line;
    ofs1.close();

    ofstream ofs2("temp1.txt", std::ios::app); // app׷��ģʽ, ÿ�δ򿪲��������
    string buf("MTNB!\n");
    ofs2 << buf; // ���ַ�����������������<<�����ݴ��ݸ��ļ����������, ������write�������д���
    ofs2.close();

    ofstream ofs3("temp1.txt", std::ios::app);
    const char * buf2 = "WBSJS\n"; // �Ƚϼ���
    ofs3.write(buf2, strlen(buf2));
}

void test7() {
    fstream fs("num.txt");
    if (!fs.good()) {
        cerr << "fs is not good" << endl;
        return;
    }
    //д�����ݵ��ļ���
    int number;
    for (size_t i = 0; i < 5; i++) {
        cin >> number;
        fs << number << " ";
    }

    //��ȡ����
    int number2;
    for (size_t i = 0; i < 5; i++) {
        fs >> number2;
        cout << number2 << " ";
    }
}

void test8() {
    fstream fs("num.txt");
    if (!fs.good()) {
        cerr << "fs is not good" << endl;
        return;
    }
    //д�����ݵ��ļ���
    int number;
    for (size_t i = 0; i < 5; i++) {
        cin >> number;
        fs << number << " ";
    }
    //��ȡ����
    int index = fs.tellg();
    cout << index << endl;

    //fs.seekg(0);
    fs.seekg(0, std::ios::beg);
    int index2 = fs.tellg();
    cout << index2 << endl;

    string word;
    for (size_t i = 0; i < 5; i++) {
        fs >> word;
        cout << word << " ";
    }
}

int main()
{
    test4();
    return 0;
}
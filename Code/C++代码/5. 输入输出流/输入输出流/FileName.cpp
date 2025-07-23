#include <iostream>
//注意：需要include
#include <limits>
#include <cstring>
#include <fstream>
#include <string>

using namespace std;

void check_stream_status() {
    cout << "cin goodbit:" << cin.good() << endl; // 正常状态
    cout << "cin badbit:" << cin.bad() << endl; // 不可恢复错误
    cout << "cin failbit:" << cin.fail() << endl; // 可恢复错误
    cout << "cin eofbit:" << cin.eof() << endl; // 流到结尾

}

// 标准输入输出流, 使用流状态控制逻辑
void test1() {
    cout << "请输入数字" << endl;
    int number;
    while (1) {
        cin >> number;
        if (cin.eof() || cin.bad()) {
            check_stream_status();
            cout << "程序已经结束" << endl;
            break;
        }
        else if (cin.fail()) {
            check_stream_status();
            cout << "清空缓存区" << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            check_stream_status();
            cout << "请输入一个数字" << endl;
        }
        else {
            //good
            cout << "number=" << number << endl;
            check_stream_status();
        }
    }
}

// 标准输入流缓冲区的返回值是对象自己, 如果直接将number置于if判断条件中, 会进行隐式类型转化为true或者false, 
void test2() {
    cout << "请输入数字" << endl;
    int number;
    while (1) {
        cin >> number;
        if (!number) {
            check_stream_status();
            cout << "清空缓存区" << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            check_stream_status();
            cout << "请输入一个数字" << endl;
        }
        else if(number){
            //good
            cout << "number=" << number << endl;
            check_stream_status();
        }
    }
}


// 文件输入流
void test3() {
    ifstream ifs;
    ifs.open("test1.cc"); // 使用open函数创建一个文件输入流

    ifstream ifs2("test2.cc"); // 使用参数创建一个文件输入流

    string filename = "test3.cc"; // 这个参数是一个字符串
    ifstream ifs3(filename);
}

void test4() {
    ifstream ifs("temp.txt");
    if (!ifs.good()) { // 如果文件输入流不是good状态就停止读
        cerr << "ifstream is not good" << endl;
        return;
    }

    string word;
    while (ifs >> word) { // 当ifs状态为good时, 一直输出文件输入缓冲区中的内容, 知道它的状态为eof或其他两种
        cout << word;
    }
    cout << endl;
    ifs.close(); // 记得关闭流
}

void test5() {

        ifstream ifs("temp.txt");
        if (!ifs.good()) { // 如果文件输入流不是goodbit状态就停止读
            cerr << "ifstream is not good" << endl;
            return;
        }

        string word;
        while (getline(ifs, word, '-')) { // 第一个参数是文件流, 第二个参数是用来保存的缓冲区, 第三个是指定的分隔符默认是换行, 返回值是自身的对象
            cout << word << endl;
        }
        cout << endl;
        ifs.close();
}

// 文件输出流
void test6() {
    ofstream ofs1("temp1.txt"); // 默认打开模式是out模式, 每次清空内容
    string line("MTZC!\n");
    ofs1 << line;
    ofs1.close();

    ofstream ofs2("temp1.txt", std::ios::app); // app追加模式, 每次打开不清空内容
    string buf("MTNB!\n");
    ofs2 << buf; // 这种方法是用输出流运算符<<将内容传递给文件输出流对象, 下面用write函数进行传输
    ofs2.close();

    ofstream ofs3("temp1.txt", std::ios::app);
    const char * buf2 = "WBSJS\n"; // 比较鸡肋
    ofs3.write(buf2, strlen(buf2));
}

void test7() {
    fstream fs("num.txt");
    if (!fs.good()) {
        cerr << "fs is not good" << endl;
        return;
    }
    //写入数据到文件中
    int number;
    for (size_t i = 0; i < 5; i++) {
        cin >> number;
        fs << number << " ";
    }

    //读取数据
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
    //写入数据到文件中
    int number;
    for (size_t i = 0; i < 5; i++) {
        cin >> number;
        fs << number << " ";
    }
    //读取数据
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
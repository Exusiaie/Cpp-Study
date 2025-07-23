#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cctype> 
#include <algorithm>
using namespace std;

/*
	构造一个vector容器, 容器中的每个成员都是一个Record
	设置一个buf, 一个字符一个字符的读取, 只有判断是一个字母时才存入buf, 存到空格停止, 认为一个单词已经存入
	遍历vector, 用buf同容器中的每一个_word进行匹配, 匹配成功则_frequency+1, 匹配失败则创建一个新的Record存入vector中
*/

struct Record
{
	string _word = "0"; // 单词的名字
	int _frequency = 0; // 每个单词出现的频率
};

// vector 是对象D的成员
class Dictionary
{
public:
	// 读取文件, 并创建一个字典函数
	void create() {
		ifstream ifs("The_Holy_Bible.txt");
		if (!ifs.good()) {
			cerr << "ifstream is not good" << endl;
			return;
		}
		string buff;

# if 0
		ifs.seekg(0); 

		while (ifs >> buff) { 
			auto it = _dict.begin(); 
			while (it != _dict.end() ) {
				if (buff == it->_word) {
					it->_frequency++;
				}
				else {	// 问题一: 每对比失败一次就插入一次；而不是等全部比完都不匹配再插入；导致 “只匹配不到一部分就插入”，从而多次插入同一个单词。
					Record rec;
					rec._word = buff;
					rec._frequency = 1;
					_dict.push_back(rec); //问题二: 在遍历 _dict 的同时往它里面 push_back，导致迭代器失效, 进而出现未定义行为
				}
				it++;
			}
		}
# endif

		while (ifs >> buff) {
			// 只有是单词才录入
			if (isalpha(buff[0])) {

				bool found = false;
				// 每读到一个单词, 先在 _dict 中查找
				for (auto& rec : _dict) {
					if (rec._word == buff) {
						rec._frequency++;
						found = true;
						break;  // 找到就退出循环，不要再插入
					}
				}
				// 如果没找到，再插入新 Record
				if (!found) {
					Record rec;
					rec._word = buff;
					rec._frequency = 1;
					_dict.push_back(rec);
				}
			}
		}
		
		// 程序走到这里, 表示文件已经读完
		ifs.close();
	}

	// 读字典函数
	void read() {
		auto it = _dict.begin();
		while (it != _dict.end()) {
			cout << it->_word << " " << it->_frequency << endl;
			it++;
		}
		cout << "字典结束" << endl;
	}

	// 将vector中的内容全部保存到文件
	void store() {
		ofstream ofs("Dictionary.txt");

		auto it = _dict.begin();
		while (it != _dict.end()) {
			ofs << "->	" << it->_word << " " << it->_frequency << endl;
			it++;
		}
		cout << "写入结束" << endl;
		ofs.close();
	}

	// 出现频率从高到低排序
	void sort() {
		std::sort(_dict.begin(), _dict.end(), [](const Record& a, const Record& b) {
			return a._frequency > b._frequency;  // 频率大的排前面
			});
	}

private:
	vector<Record> _dict;
};



int main()
{
	Dictionary D;
	D.create();
	D.sort();
	//D.read();
	D.store();

	
    return 0;
}

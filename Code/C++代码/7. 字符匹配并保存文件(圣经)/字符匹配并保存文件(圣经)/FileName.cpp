#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cctype> 
#include <algorithm>
using namespace std;

/*
	����һ��vector����, �����е�ÿ����Ա����һ��Record
	����һ��buf, һ���ַ�һ���ַ��Ķ�ȡ, ֻ���ж���һ����ĸʱ�Ŵ���buf, �浽�ո�ֹͣ, ��Ϊһ�������Ѿ�����
	����vector, ��bufͬ�����е�ÿһ��_word����ƥ��, ƥ��ɹ���_frequency+1, ƥ��ʧ���򴴽�һ���µ�Record����vector��
*/

struct Record
{
	string _word = "0"; // ���ʵ�����
	int _frequency = 0; // ÿ�����ʳ��ֵ�Ƶ��
};

// vector �Ƕ���D�ĳ�Ա
class Dictionary
{
public:
	// ��ȡ�ļ�, ������һ���ֵ亯��
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
				else {	// ����һ: ÿ�Ա�ʧ��һ�ξͲ���һ�Σ������ǵ�ȫ�����궼��ƥ���ٲ��룻���� ��ֻƥ�䲻��һ���־Ͳ��롱���Ӷ���β���ͬһ�����ʡ�
					Record rec;
					rec._word = buff;
					rec._frequency = 1;
					_dict.push_back(rec); //�����: �ڱ��� _dict ��ͬʱ�������� push_back�����µ�����ʧЧ, ��������δ������Ϊ
				}
				it++;
			}
		}
# endif

		while (ifs >> buff) {
			// ֻ���ǵ��ʲ�¼��
			if (isalpha(buff[0])) {

				bool found = false;
				// ÿ����һ������, ���� _dict �в���
				for (auto& rec : _dict) {
					if (rec._word == buff) {
						rec._frequency++;
						found = true;
						break;  // �ҵ����˳�ѭ������Ҫ�ٲ���
					}
				}
				// ���û�ҵ����ٲ����� Record
				if (!found) {
					Record rec;
					rec._word = buff;
					rec._frequency = 1;
					_dict.push_back(rec);
				}
			}
		}
		
		// �����ߵ�����, ��ʾ�ļ��Ѿ�����
		ifs.close();
	}

	// ���ֵ亯��
	void read() {
		auto it = _dict.begin();
		while (it != _dict.end()) {
			cout << it->_word << " " << it->_frequency << endl;
			it++;
		}
		cout << "�ֵ����" << endl;
	}

	// ��vector�е�����ȫ�����浽�ļ�
	void store() {
		ofstream ofs("Dictionary.txt");

		auto it = _dict.begin();
		while (it != _dict.end()) {
			ofs << "->	" << it->_word << " " << it->_frequency << endl;
			it++;
		}
		cout << "д�����" << endl;
		ofs.close();
	}

	// ����Ƶ�ʴӸߵ�������
	void sort() {
		std::sort(_dict.begin(), _dict.end(), [](const Record& a, const Record& b) {
			return a._frequency > b._frequency;  // Ƶ�ʴ����ǰ��
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

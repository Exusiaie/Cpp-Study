#include <iostream>
#include <string>
using namespace std;

// ��8�ַ�ʽ�����ַ���:
void test1() {
	string str1; // 1. �޲ι��캯��, ����һ�����ַ���
	string str2("MTYDMTLL"); // 2. ����һ���ַ�������ʼ��ֵ
	string str3("WGNMSMTBJYDXZDYMTHYJMSI", 3); // 3. �õ�һ��������ǰ3��ֵ����һ���ַ���
	string str4(str2); // 4. ��������һ���ַ���
	string str5(str2, 4, 3); // 5. �õ�һ�������Ĳ��ֹ����ַ���(��ʼλ, ����), ��0��ʼ��
	string str6(5, 'a'); // 6. ����һ����N����ͬ�ַ����ַ���
	cout << "str1: " << str1 << endl;
	cout << "str2: " << str2 << endl;
	cout << "str3: " << str3 << endl;
	cout << "str4: " << str4 << endl;
	cout << "str5: " << str5 << endl;
	cout << "str6: " << str6 << endl;

	char arr[17] = "BLMGWDBLMTXLHHHH";	//����ͷβ����������Ŀǰ�׶ξͰѵ���������ָ��
	string str7(arr, arr + 3); // 7. ������[arr, arr+3)�ڵ��ַ�����һ��String����
	cout << "str7: " << str7 << endl;

	//begin()���ص����׵�����, end()���ص���β�������
	string str8(str2.begin(), str2.end()); // 8. ������[begin, end)�ڵ��ַ�����һ��String����
	cout << "str8: " << str8 << endl;

	cout << "----------------------------------" << endl;
}

// Ҳͬ����8�ַ�ʽ�����ַ���:
void test2() {
	string str("MTNB");
	string str2("WBSJS");

	cout << str.data() << endl; // 1. ��ȡָ���ַ�����ָ��
	cout << str.c_str() << endl; // 2. ����c�����ַ���, ����const char*
	cout << str.empty() << endl; // 3. �ж��Ƿ�Ϊ�� empty  �Ƿ���1�񷵻�0��ʾ��ֵ
	cout << str.size() << endl; // 4. ��ȡ�ַ���, ��������β��\0
	cout << str.length() << endl; // 5. ������һģһ��
	str.push_back('a'); // 6. �ַ�����β׷��һ���ַ�
	cout << str << endl;

	// 7. ������append����������
	cout << str.append(2, 'h') << endl; // ���ַ�����ĩβ���N���ַ�
	cout << str.append(str2) << endl; // ���ַ���ĩβ���str2
	cout << str.append(str2, 1, 3) << endl; // ���ַ���ĩβ���str2ָ����ֵ[1,3]
	cout << str.append("MTZC") << endl; // ���ַ���ĩβ��Ӳ���
	
	// 8. ������find����������
	cout << str.find(str2, 0) << endl; // ���ַ����ĵ�Nλ��ʼ�����ַ���str2, ����λ��
	cout << str.find('h', 0) << endl; // ���ַ����ĵ�Nλ��ʼ�����ַ�, ����λ��
	cout << str.find("BSJS", 0, 2) << endl; // ���ַ���ָ����ʼλ�ò����ַ�, ���ҵ�һ��������ǰ2��ֵ, ����λ��

	cout << "----------------------------------" << endl;
}

void test3() {
	string str1 = "MTNB";
	string str2 = "MTZC";
	string str3 = "MTNB";
	
	// �����ַ�������ֱ����Ƚ�, 1��0��
	cout << (str1 == str2) << endl;
	cout << (str1 == str3) << endl;
	cout << (str1 != str2) << endl;
	cout << (str1 < str2) << endl;
	cout << (str1 > str2) << endl;
	cout << (str1 <= str2) << endl;
	cout << (str1 >= str2) << endl;

	cout << "----------------------------------" << endl;
}

// ��3�б���string�ķ���:
// string ��һ�ִ洢char�����ݵ�����, ���ٴλ�������չ�˷ḻ���ַ����ӿ�
// ��˶��ַ����ı��������Ͷ������ı�������û��ʲô����
void test4() {
	string str = "WCSDSLMTBDSLMTZMBQSWCMTZKSYWCYZLABBRDSB";
	
	// 1. ʹ��ƽƽ�����forѭ���±����
	for (size_t i = 0; i < str.length(); i++) {
		cout << str[i];
	}
	cout << endl;

	// 2. ʹ����ǿ��ƽƽ�����forѭ������
	for (auto& ch : str) { // ����һ�����ñ���. ��������str�е�����, ���ٿ���
		if (ch == 'A') {
			ch = 'a'; // ����ֱ���޸�����, Ϊ�˱��������autoǰ����const
		}
		cout << ch;
	}
	cout << endl;

	// 3. ʹ�ÿ�����ţ�Ƶĵ���������
	// begin���������׵����� (ָ����Ԫ�ص�ָ��); end��������β�������(ָ��βԪ�صĺ�һλ��ָ��)
	auto head = str.begin();
	while (head != str.end()) {
		cout << *head;
		head++;
	}
	cout << endl;
}

int main() {
	test1();
	test2();
	test3();
	test4();

	return 0;
}

#include <iostream>
#include <string>
using namespace std;

// 有8种方式构建字符串:
void test1() {
	string str1; // 1. 无参构造函数, 生成一个空字符串
	string str2("MTYDMTLL"); // 2. 构造一个字符串并初始化值
	string str3("WGNMSMTBJYDXZDYMTHYJMSI", 3); // 3. 用第一个参数的前3个值构造一个字符串
	string str4(str2); // 4. 拷贝构造一个字符串
	string str5(str2, 4, 3); // 5. 用第一个参数的部分构造字符串(起始位, 长度), 从0开始的
	string str6(5, 'a'); // 6. 构造一个有N个相同字符的字符串
	cout << "str1: " << str1 << endl;
	cout << "str2: " << str2 << endl;
	cout << "str3: " << str3 << endl;
	cout << "str4: " << str4 << endl;
	cout << "str5: " << str5 << endl;
	cout << "str6: " << str6 << endl;

	char arr[17] = "BLMGWDBLMTXLHHHH";	//接收头尾部迭代器，目前阶段就把迭代器理解成指针
	string str7(arr, arr + 3); // 7. 以区间[arr, arr+3)内的字符创建一个String对象
	cout << "str7: " << str7 << endl;

	//begin()返回的是首迭代器, end()返回的是尾后迭代器
	string str8(str2.begin(), str2.end()); // 8. 以区间[begin, end)内的字符创建一个String对象
	cout << "str8: " << str8 << endl;

	cout << "----------------------------------" << endl;
}

// 也同样有8种方式操作字符串:
void test2() {
	string str("MTNB");
	string str2("WBSJS");

	cout << str.data() << endl; // 1. 获取指向字符串的指针
	cout << str.c_str() << endl; // 2. 返回c风格的字符串, 类型const char*
	cout << str.empty() << endl; // 3. 判断是否为空 empty  是返回1否返回0表示有值
	cout << str.size() << endl; // 4. 获取字符数, 不包含结尾的\0
	cout << str.length() << endl; // 5. 跟上面一模一样
	str.push_back('a'); // 6. 字符串结尾追加一个字符
	cout << str << endl;

	// 7. 下面是append函数的重载
	cout << str.append(2, 'h') << endl; // 在字符串的末尾添加N个字符
	cout << str.append(str2) << endl; // 在字符串末尾添加str2
	cout << str.append(str2, 1, 3) << endl; // 在字符串末尾添加str2指定的值[1,3]
	cout << str.append("MTZC") << endl; // 在字符串末尾添加参数
	
	// 8. 下面是find函数的重载
	cout << str.find(str2, 0) << endl; // 从字符串的第N位开始查找字符串str2, 返回位置
	cout << str.find('h', 0) << endl; // 从字符串的第N位开始查找字符, 返回位置
	cout << str.find("BSJS", 0, 2) << endl; // 从字符串指定起始位置查找字符, 查找第一个参数的前2个值, 返回位置

	cout << "----------------------------------" << endl;
}

void test3() {
	string str1 = "MTNB";
	string str2 = "MTZC";
	string str3 = "MTNB";
	
	// 两个字符串可以直接向比较, 1真0假
	cout << (str1 == str2) << endl;
	cout << (str1 == str3) << endl;
	cout << (str1 != str2) << endl;
	cout << (str1 < str2) << endl;
	cout << (str1 > str2) << endl;
	cout << (str1 <= str2) << endl;
	cout << (str1 >= str2) << endl;

	cout << "----------------------------------" << endl;
}

// 有3中遍历string的方法:
// string 是一种存储char型数据的容器, 并再次基础上拓展了丰富的字符串接口
// 因此对字符串的遍历方法和对容器的遍历方法没有什么区别
void test4() {
	string str = "WCSDSLMTBDSLMTZMBQSWCMTZKSYWCYZLABBRDSB";
	
	// 1. 使用平平无奇的for循环下标遍历
	for (size_t i = 0; i < str.length(); i++) {
		cout << str[i];
	}
	cout << endl;

	// 2. 使用增强的平平无奇的for循环遍历
	for (auto& ch : str) { // 定义一个引用变量. 用来接收str中的内容, 减少开销
		if (ch == 'A') {
			ch = 'a'; // 可以直接修改内容, 为了避免可以在auto前加上const
		}
		cout << ch;
	}
	cout << endl;

	// 3. 使用看起来牛逼的迭代器遍历
	// begin函数返回首迭代器 (指向首元素的指针); end函数返回尾后迭代器(指向尾元素的后一位的指针)
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

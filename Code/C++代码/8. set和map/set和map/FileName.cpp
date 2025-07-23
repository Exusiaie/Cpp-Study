#include <iostream>
#include <string>
#include <set>
#include <vector>
using namespace std;

#if 0
// set 的构造
set<int> test1() {
// 无参构造
	set<int> nums;
	// 拷贝构造
	set<int> nums1 = nums;
	// 迭代器构造
	vector<int> v{ 3, 1, 4, 1, 5, 9, 2, 6, 5 };	// 用 v 的所有元素（从 begin 到 end）来构造 set
	set<int> nums2(v.begin(), v.end());
	// 初始化列表构造
	set<int> nums3 = { 9,5,6,3,2,8,7,4, };

	return nums2;
}

// set的遍历是迭代器遍历和增强for循环遍历
void test2(class set<int> number) {
	// 增强for循环
	for (auto& temp : number) {
		cout << temp << endl;
	}
	// 迭代器遍历
	auto it = number.begin(); // 头部
	while (it != number.end()) { // 尾后
		cout << *it << endl;
		++it;
	}
}


int main() {
	set<int> num = test1(); // 拷贝构造
	test2(num); // 注意到nums2中的重复部分已经被去重了

	return 0;
}
#endif


#if 0
set<string> Create_Set() {
	vector<string> buff{ "zmx","lxc","csa","zmk" };
	set<string> namelist(buff.begin(), buff.end());

	return namelist;
}

void Count(set<string> namelist) {
	string target;
	cin >> target;
	if (namelist.count(target)) { // 找到count返回1
		cout << "找到了: " << namelist.count(target) << endl;
	}
	else { // 没找到返回0
		cout << "没找到: " << namelist.count(target) << endl;
	}
}

void Find(set<string> namelist) {
	string target;
	cin >> target;
	auto it = namelist.find(target); // 找到find返回目标对应的迭代器
	if (it != namelist.end()) {
		cout << "找到了: " << *it << endl;
	}
	else {
		// .end()这个迭代器并不指向任何有效元素，不能被解引用
		// cout << "没找到: " << *it << endl;
		cout << "没找到" << endl;
	}
}


int main(void) {
	set<string> namelist = Create_Set();
	Count(namelist);
	Find(namelist);
	return 0;
}
#endif


set<string> Create_Set() {
	vector<string> buff{ "facker","showmaker","chove","zues","MT",};
	set<string> namelist(buff.begin(), buff.end());

	return namelist;
}

void Inter(set<string> &namelist) {
	pair<set<string>::iterator, bool> ret = namelist.insert("bin");
	if (ret.second) {
		cout << "该元素插入成功:" << *(ret.first) << endl;
	}
	else {
		cout << "该元素插入失败，表明该元素已存在" << endl;
	}
}

void Print(set<string> namelist) {
	auto it = namelist.begin();
	while (it != namelist.end()) {
		cout << *it << endl;
		++it;
	}
}

void test() {
	set<int> number = { 1, 2, 3, 4, 5 }; // 列表初始化
	pair<set<int>::iterator, bool> result = number.insert(4); // 插入4这个元素
	if (result.second) {
		cout << "该元素插入成功: " << *(result.first) << endl;
	}
	else {
		cout << "该元素插入失败,原本就存在" << endl;
	}

	//插入一组元素
	int arr[6] = { 33, 5, 1, 4, 56 };
	number.insert(arr, arr + 6); // 插入一整个arr到number里
	for (auto& e : number) { // 打印全部的number
		cout << e << " ";
	}
	cout << endl;

	//大括号形式插入一组元素
	number.insert({ 100, 99, 87, 99 }); // 不用中转, 直接把大括号填到参数列表里
	for (auto& e : number) { // 打印
		cout << e << " ";
	}
	cout << endl;
}

int main(void) {
	set<string> namelist = Create_Set();
	Inter(namelist);
	Print(namelist);
	//test();
	return 0;
}
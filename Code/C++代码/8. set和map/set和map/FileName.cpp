#include <iostream>
#include <string>
#include <set>
#include <vector>
using namespace std;

#if 0
// set �Ĺ���
set<int> test1() {
// �޲ι���
	set<int> nums;
	// ��������
	set<int> nums1 = nums;
	// ����������
	vector<int> v{ 3, 1, 4, 1, 5, 9, 2, 6, 5 };	// �� v ������Ԫ�أ��� begin �� end�������� set
	set<int> nums2(v.begin(), v.end());
	// ��ʼ���б���
	set<int> nums3 = { 9,5,6,3,2,8,7,4, };

	return nums2;
}

// set�ı����ǵ�������������ǿforѭ������
void test2(class set<int> number) {
	// ��ǿforѭ��
	for (auto& temp : number) {
		cout << temp << endl;
	}
	// ����������
	auto it = number.begin(); // ͷ��
	while (it != number.end()) { // β��
		cout << *it << endl;
		++it;
	}
}


int main() {
	set<int> num = test1(); // ��������
	test2(num); // ע�⵽nums2�е��ظ������Ѿ���ȥ����

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
	if (namelist.count(target)) { // �ҵ�count����1
		cout << "�ҵ���: " << namelist.count(target) << endl;
	}
	else { // û�ҵ�����0
		cout << "û�ҵ�: " << namelist.count(target) << endl;
	}
}

void Find(set<string> namelist) {
	string target;
	cin >> target;
	auto it = namelist.find(target); // �ҵ�find����Ŀ���Ӧ�ĵ�����
	if (it != namelist.end()) {
		cout << "�ҵ���: " << *it << endl;
	}
	else {
		// .end()�������������ָ���κ���ЧԪ�أ����ܱ�������
		// cout << "û�ҵ�: " << *it << endl;
		cout << "û�ҵ�" << endl;
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
		cout << "��Ԫ�ز���ɹ�:" << *(ret.first) << endl;
	}
	else {
		cout << "��Ԫ�ز���ʧ�ܣ�������Ԫ���Ѵ���" << endl;
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
	set<int> number = { 1, 2, 3, 4, 5 }; // �б��ʼ��
	pair<set<int>::iterator, bool> result = number.insert(4); // ����4���Ԫ��
	if (result.second) {
		cout << "��Ԫ�ز���ɹ�: " << *(result.first) << endl;
	}
	else {
		cout << "��Ԫ�ز���ʧ��,ԭ���ʹ���" << endl;
	}

	//����һ��Ԫ��
	int arr[6] = { 33, 5, 1, 4, 56 };
	number.insert(arr, arr + 6); // ����һ����arr��number��
	for (auto& e : number) { // ��ӡȫ����number
		cout << e << " ";
	}
	cout << endl;

	//��������ʽ����һ��Ԫ��
	number.insert({ 100, 99, 87, 99 }); // ������ת, ֱ�ӰѴ�����������б���
	for (auto& e : number) { // ��ӡ
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
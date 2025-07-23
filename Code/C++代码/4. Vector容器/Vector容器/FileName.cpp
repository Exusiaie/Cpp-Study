#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Point {
public:
    Point(int x = 0, int y = 0) : _x(x), _y(y) {
        cout << "���캯��: Point(" << _x << ", " << _y << ")" << endl;
    }

    Point(const Point& other) : _x(other._x), _y(other._y) {
        cout << "�������캯��: Point(" << _x << ", " << _y << ")" << endl;
    }

    ~Point() {
        cout << "��������: Point(" << _x << ", " << _y << ")" << endl;
    }

private:
    int _x, _y;
};

void test1() {
	vector <int> nums1; // �޲ι���
	vector <char> nums2(10, 'x'); // �������ָ��Ԫ�����ͺ�����
	vector <string> nums3{ "In ", "the ", "beginning ", "hello ", "god ", "created ", "the ", "heaven ", "and ", "the ", "earth" }; // ���б���г�ʼ��
	vector <string> nums4(nums3.begin(), nums3.end()-2); // �õ��������г�ʼ��

    // һ�ֳ����ı���д��, ������Ԫ�ص�������β�������
    auto it1 = nums3.begin();
    auto it2 = nums3.end();
    while (it1 != it2) {
        cout << *it1;
        it1++;
    }
    cout << endl;
}

void test2() {
    vector<int> v{ 1, 2, 3, 4 };

    //������������д��������ȷ
    vector<int>::iterator it1 = v.begin(); // auto it1 = v.begin();
    auto it2 = v.end();

    while (it1 != it2) {
        cout << *it1 << " ";
        ++it1;
    }
    cout << endl;
    cout << "�п�`" << v.empty() << endl; //1.�п�
    cout << "���������д�ŵ�Ԫ�ظ���`" << v.size() << endl; //2.���������д�ŵ�Ԫ�ظ���
    cout << "������������`" << v.capacity() << endl; //3.�������������������Դ��Ԫ�صĸ�����
    v.push_back(5); //4.�����һ��Ԫ�صĺ����ٴ��Ԫ��
    cout << "���������д�ŵ�Ԫ�ظ���`" << v.size() << endl;
    cout << "������������`" << v.capacity() << endl; 
    v.pop_back(); //5.ɾ�����һ��Ԫ��
    cout << "���������д�ŵ�Ԫ�ظ���`" << v.size() << endl;
    cout << "������������`" << v.capacity() << endl;
    v.shrink_to_fit();  //6.�ͷŶ���Ŀռ�
    cout << "���������д�ŵ�Ԫ�ظ���`" << v.size() << endl;
    cout << "������������`" << v.capacity() << endl;
    cout << "�п�`" << v.empty() << endl; //�п�
    v.clear(); //7.�������Ԫ�أ������ͷſռ�
    cout << "���������д�ŵ�Ԫ�ظ���`" << v.size() << endl;
    cout << "������������`" << v.capacity() << endl;
    cout << "�п�`" << v.empty() << endl; //�п�
    v.shrink_to_fit();  //8.�ͷŶ���Ŀռ�
    cout << "���������д�ŵ�Ԫ�ظ���`" << v.size() << endl;
    cout << "������������`" << v.capacity() << endl;
    cout << "�п�`" << v.empty() << endl; //�п�
    v.reserve(10); //9.����ռ䣬�����Ԫ��
    cout << "���������д�ŵ�Ԫ�ظ���`" << v.size() << endl;
    cout << "������������`" << v.capacity() << endl;
    cout << "�п�`" << v.empty() << endl; //�п�
}

void test3() {

    vector<Point> nums;

    // nums.reserve(10); // ע�ͺ�۲������仯�뿽���������
    /*
        ������ reserve() ��ʱ��
        vector ������������ �Զ�������ͨ����2�����ݣ���
        ����������ʱ������� ���� + Ԫ�ؿ�����Ƶ�����ÿ������캯����

        ���� nums.reserve(10);��
        ��ǰ������㹻�Ŀռ䣨10�� Point����
        ���� push_back �����������ݣ�Ҳ���ᵼ������Ԫ�صĿ�����
        ���캯�����ô������٣����ܸ��ߡ�
    */

    nums.push_back(Point(1, 2));
    cout << "Size: " << nums.size() << ", Capacity: " << nums.capacity() << endl;

    nums.push_back(Point(3, 4));
    cout << "Size: " << nums.size() << ", Capacity: " << nums.capacity() << endl;

    nums.push_back(Point(5, 6));
    cout << "Size: " << nums.size() << ", Capacity: " << nums.capacity() << endl;

    nums.push_back(Point(7, 8));
    cout << "Size: " << nums.size() << ", Capacity: " << nums.capacity() << endl;

}

int main() {
    test3();
	return 0;
}
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Point {
public:
    Point(int x = 0, int y = 0) : _x(x), _y(y) {
        cout << "构造函数: Point(" << _x << ", " << _y << ")" << endl;
    }

    Point(const Point& other) : _x(other._x), _y(other._y) {
        cout << "拷贝构造函数: Point(" << _x << ", " << _y << ")" << endl;
    }

    ~Point() {
        cout << "析构函数: Point(" << _x << ", " << _y << ")" << endl;
    }

private:
    int _x, _y;
};

void test1() {
	vector <int> nums1; // 无参构造
	vector <char> nums2(10, 'x'); // 传入参数指明元素类型和数量
	vector <string> nums3{ "In ", "the ", "beginning ", "hello ", "god ", "created ", "the ", "heaven ", "and ", "the ", "earth" }; // 用列表进行初始化
	vector <string> nums4(nums3.begin(), nums3.end()-2); // 用迭代器进行初始化

    // 一种常见的遍历写法, 利用首元素迭代器和尾后迭代器
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

    //迭代器的两种写法，均正确
    vector<int>::iterator it1 = v.begin(); // auto it1 = v.begin();
    auto it2 = v.end();

    while (it1 != it2) {
        cout << *it1 << " ";
        ++it1;
    }
    cout << endl;
    cout << "判空`" << v.empty() << endl; //1.判空
    cout << "返回容器中存放的元素个数`" << v.size() << endl; //2.返回容器中存放的元素个数
    cout << "返回容器容量`" << v.capacity() << endl; //3.返回容器容量（最多可以存放元素的个数）
    v.push_back(5); //4.在最后一个元素的后面再存放元素
    cout << "返回容器中存放的元素个数`" << v.size() << endl;
    cout << "返回容器容量`" << v.capacity() << endl; 
    v.pop_back(); //5.删除最后一个元素
    cout << "返回容器中存放的元素个数`" << v.size() << endl;
    cout << "返回容器容量`" << v.capacity() << endl;
    v.shrink_to_fit();  //6.释放多余的空间
    cout << "返回容器中存放的元素个数`" << v.size() << endl;
    cout << "返回容器容量`" << v.capacity() << endl;
    cout << "判空`" << v.empty() << endl; //判空
    v.clear(); //7.清空所有元素，但不释放空间
    cout << "返回容器中存放的元素个数`" << v.size() << endl;
    cout << "返回容器容量`" << v.capacity() << endl;
    cout << "判空`" << v.empty() << endl; //判空
    v.shrink_to_fit();  //8.释放多余的空间
    cout << "返回容器中存放的元素个数`" << v.size() << endl;
    cout << "返回容器容量`" << v.capacity() << endl;
    cout << "判空`" << v.empty() << endl; //判空
    v.reserve(10); //9.申请空间，不存放元素
    cout << "返回容器中存放的元素个数`" << v.size() << endl;
    cout << "返回容器容量`" << v.capacity() << endl;
    cout << "判空`" << v.empty() << endl; //判空
}

void test3() {

    vector<Point> nums;

    // nums.reserve(10); // 注释后观察容量变化与拷贝构造次数
    /*
        不调用 reserve() 的时候：
        vector 容器的容量会 自动增长（通常是2倍扩容）。
        当容量不够时，会进行 扩容 + 元素拷贝，频繁调用拷贝构造函数。

        调用 nums.reserve(10);：
        提前分配好足够的空间（10个 Point）。
        后续 push_back 不再引起扩容，也不会导致已有元素的拷贝。
        构造函数调用次数变少，性能更高。
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
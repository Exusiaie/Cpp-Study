# 一:  标准模板库STL

  标准模板库，即Standard Template Library，简称STL，是一个具有工业强度的，高效的C++程序库。它被容纳于C++标准库中，是ANSI/ISO C++标准中最新的也是极具革命性的一部分。该库包含了诸多在计算机科学领域里所常用的基本数据结构和基本算法。为广大C++程序员们提供了一个可扩展的应用框架，高度体现了软件的可复用性。与之前学到的编程思想面向对象编程不一样，STL采用的是一种新的编程模式：<span style=color:red;background:yellow;font-size:20px>**泛型编程**</span>。它允许程序员编写通用的代码，即可适用于不同的数据类型，而不必为每种类型编写不同的代码。这种编程方法的基本思想是将数据类型抽象化，使用泛型来表示数据类型，并在编写代码时使用泛型来代替具体的数据类型。

虽然STL的内容繁多，但是可以总结为六大组件：容器、迭代器、算法、适配器、空间配置器、函数对象。下面对六大组件的功能做一个概述。

- <span style=color:red;background:yellow;font-size:20px>**容器**：</span>是用来存放数据的，即<font color = red>数据结构</font>。这里可以按照类别分为 1. 序列式容器（比如：vector、deque(双端队列) , list(双向循环链表)  2. 关联式容器（比如：set、map） 3. 无序关联式容器（比如：unordered_set、unordered_map）三类。
- <span style=color:red;background:yellow;font-size:20px>**迭代器**：</span>是一种抽象的数据类型，可用于访问容器中的元素，行为类似于C语言中的指针，这里可以将其称为<font color = red>泛型指针</font>。迭代器是容器和算法之间的桥梁
- <span style=color:red;background:yellow;font-size:20px>**算法**：</span>它是用于<font color = red>对容器中的元素进行操作</font>的函数模板。STL中提供了大量的常用算法，包括：查找、排序、合并、去重、集合操作、取最值、数值计算等。
- <span style=color:red;background:yellow;font-size:20px>**适配器**：</span>一种用来修饰容器或者仿函数或者迭代器接口的东西。是使一种事物的行为类似于另外一种事物行为的一种机制，类似于生活中的转接器功能。比如stack \ queue \ priority_queue优先级队列
- <span style=color:red;background:yellow;font-size:20px>**函数对象**：</span>也称为仿函数，可作为算法的某种策略, 做<font color = red>定制化操作</font>。是一种封装了函数或函数指针的对象，它可以像函数一样被调用，也可以像对象一样被赋值或传递给其他函数，STL中的函数对象是做定制化操作的。
- <span style=color:red;background:yellow;font-size:20px>**空间配置器**：</span>管理内存分配和释放。

------------------

容器(container)

<span style=color:red;background:yellow;font-size:20px>**容器就是用来存放数据的，也就是数据结构，这是STL中最基础、最重要的部分**。</span>STL中的容器可以分为三类：序列式容器、关联式容器、无序关联式容器

------

迭代器(iterator)

可以看做是两个指针, 一个指向容器的第一个元素, 一个指向容器最后一个元素的下一个位置

<img src="D:\MarkDown\Picture\image-20250625145837993.png" alt="image-20250625145837993" style="zoom:67%;" />

#  二: 序列式容器 vector, deque, list

## 1: vector

**静态数组array**中保存的是一个传统的c数组, 它的大小在创建时就确定, 后续不可更改

**动态数组vector**中保存着start, finish, end_of_storage三个指针, 指向堆上的一片连续空间, 分别指向容器的开头, 容器有效位置尾部, 和容器总空间的尾部的后一个位置. 

这使得动态数组可以在总空间不够时进行扩容. 扩容的大小在LINUX上是2倍扩容, 扩容时先在堆上申请2倍大小的新空间, 在将这三个指针指向相应位置, 让os自动回收旧空间. 

迭代器失效: 动态数组在进行插入删除时导致迭代器指向的元素位置失效, 进行扩容操作后会出现迭代器失效, 因此每次插入删除后都要更新迭代器的位置

![image-20250625144005441](D:\MarkDown\Picture\image-20250625144005441.png)

### 常用操作

**初始化**

>1.   无参对象
>2.   count个value
>3.   迭代器范围
>4.   大括号范围
>5.   拷贝构造, 移动构造

**遍历**

>1.   迭代器遍历
>2.   下标
>3.   增强for循环

**头插尾插**

>1.   push_back
>2.   emplace_back
>3.   push_front
>4.   emplace_front

**指定位置插入**

>1.   指定位置插入一个元素
>2.   指定位置插入count个相同元素
>3.   指定位置插入迭代器范围的元素

### <span style=color:red;background:yellow;font-size:30px>vector的迭代器失效</span>

以vector为例，如果使用insert插入元素，而每次插入元素的个数不确定，可能剩余空间不足以存放插入元素的个数，那么insert在插入的时候**底层就可能导致扩容，从而导致迭代器还指向老的空间，继续使用该迭代器会出现迭代器失效的问题**。

```c++
void test1() {
	vector<int> vec = { 11, 22, 33, 44, 55};
	vector<int> num = { 0, 1, 2, 3, 4, 5}; // num的初始capacity为6

	auto it = num.begin() + 2;
	cout << "*it = " << *it << endl;
    
#if 0
	num.insert(it, vec.begin(), vec.end());  // 此时num的capacity不足, 触发扩容, vector的三根指针指向了新的堆空间
											 // 扩容一旦发生，旧堆区被释放，但此时的迭代器it依然指向旧的堆空间, 这就是vector的迭代器失效
	Print(num);
	cout << "*it = " << *it << endl; // ERROR, 此时的it已经成为悬空指针
#endif
    
	// 解决方法: 在每次扩容后更新迭代器it
	it = num.insert(it, vec.begin(), vec.end()); // 此时迭代器it已经指向新的堆空间, 避免了失效
												 // insert 的返回值是一个 iterator
	Print(num);
	cout << "*it = " << *it << endl;
}

```

<img src="D:\MarkDown\Picture\image-20250625165541859.png" alt="image-20250625165541859" style="zoom:67%;" />

<font color = red>迭代器失效的本质是指针悬空</font>

**思考：insert插入数据导致容量不够，底层是不是也采用类似vector的push_back一样的两倍扩容呢？**

>因为vector的push_back操作每次只会插入一个元素，所以可以按照统一的形式2 * capacity()，但是insert的时候，插入的元素个数是不定的，所以就不能一概而论。这里可以分别讨论一下，我们设置capacity() = n, size() = m, insert插入的元素个数为t个：
>
>```
>capacity = n ---------
>size = m     ----
>```
>
>- 如果t < n - m，新插入元素的个数比剩余空间小，这个时候就无需扩容，所以直接插入;
>- 如果n - m < t < m，就按照m的2倍去进行扩容，新的空间就是2 * m；
>- 如果n - m< t < n 且t > m,就按照 t + m去进行扩容；
>- 如果t > n时，依旧按照t + m去进行扩容 ； 
>
>这就是vector进行insert扩容的原理（这个原理可以了解一下，主要是为了告诉大家不是两倍扩容）。

















## 2: deque

**双端队列deque**是一个逻辑上连贯, 物理上由一个个离散的片段组成的数据结构 , 每个片段的大小固定, deque中保存着一个中控器数组Map, 里面保存着所有片段的首地址

每个片段中拥有cur, first, last, node四个指针, 分别指向当前元素位置, 第一个元素位置, 最后元素位置的下一个位置, Map当前索引的位置. 

双端队列在进行Map扩容后会出现迭代器失效, 因此每次插入删除后都要更新迭代器位置.

![image-20250625144245906](D:\MarkDown\Picture\image-20250625144245906.png)





### deque的迭代器失效

deque的迭代器失效比vector的迭代器失效更加容易触发, C++ 标准对 deque 的迭代器失效有个非常清晰的规定：

 **对两端的插入/删除（`push_front`/`push_back`）和所有中间插入/删除操作，都会使所有现有迭代器失效**。

```c++
void test(){
	deque<int> dq = { 0, 1, 2 , 3};
	auto it = dq.begin() + 1;   // 指向元素 1
	int& ref = dq[1];           // 引用也指向元素 1
	int* ptr = &dq[1];          // 指针指向元素 1

	dq.push_back(77);            // 插入新元素，迭代器 it 失效
	Print(dq);
	it = dq.insert(it, 10, 99);       // it 早已失效，再用它插入会导致 未定义行为
	Print(dq);
 
	cout << *it << "\n"; //  it 现在是悬空的，再解引用是未定义行为：

	// 但下面两行仍然安全，因为引用和指针对应的元素并未搬迁
	cout << ref << "\n";  // 输出 1
	cout << *ptr << "\n"; // 输出 1
}
```

<span style=color:red;background:yellow;font-size:20px>vector和deque的迭代器失效的区别: </span>

vector的迭代器只出现在扩容时, 而deque的迭代器失效会发生在所有的两端插入/删除和中间插入删除时, 即使deque没有真的发生了扩容和内存搬迁, 这样规定的目的是提前规避bug



### deque的插入和删除时内存变化

![image-20250625144245906](D:\MarkDown\Picture\image-20250625144245906.png)

1. deque的减少移动时开销策略

deque在插入或删除元素时, 需要看操作位置与size()的一半的大小，根据这个判断是挪动前一半还是后一半, 以减少开销

2. deque的插入逻辑:

​	 如果在第一个位置插, 直接调用push_front(), 如果在最后一个位置插, 直接调用push_back(), 如果在中间插, 先用头位置-目标位置, 判断是在前一半插还是在后一半插, 前一半就前移元素再插入, 后一半就后移元素再插入

3. deque指针的变化

    1. 在一个block中移动

        ```c++
        ++it 时，只做 _M_cur++；
        --it 时，只做 _M_cur--；
        只要仍在 [ _M_first, _M_last ) 范围内，_M_node 不变。
        ```

    2. 跨block移动, 逻辑上deque是连续的, 实际上从一个缓冲区block跳到了另外一个

        ```c++
        if(++it 后 _M_cur == _M_last){
            _M_node++; // 偏移到Map的下一个成员
        	_M_first = *(_M_node); // 取地址得到下一个block的首地址, 让first指针指过去
        	_M_last  = _M_first + buffer_size; // 首地址 + 一个block的大小 = last
        	_M_cur   = _M_first; // 当前位置为block首位
        }
        
        if( --it 后 _M_cur < _M_first){
            _M_node--; // 偏移到Map的上一个成员
        	_M_first = *(_M_node); // 取地址
        	_M_last  = _M_first + buffer_size; // 得到last
        	_M_cur   = _M_last - 1; // 当前位置为block的最后一个位置
        }
        ```









































## 3: 双向循环链表list

**双向循环链表list**在第一个结点和最后一个结点之间存在一个空节点, 这使得list.end方便的实现, list.end == list.begin成为判空条件, 且统一了插入和删除操作

list是一个带尾部空节点的双向循环链表, 如果没有这个空节点, .begin和.end会用不了

![image-20250623210707324](D:\MarkDown\Picture\image-20250623210707324.png)



## 4: 相关操作



我们主要看vector, list, deque这三种数据结构

**5种初始化**

1. 无参对象

```c++
vector<int> number; 
deque<int>  number; 
list<int>  number;
```

2. count个value

```c++
vector<int> number(10, 1); // 10个1
deque<int> number(10, 2); // 10个2
list<int> number(10, 3); // 10个3
```

3. 迭代器范围

```c++
int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
vector<int> number1(arr, arr + 10); //左闭右开区间 [arr, arr+10)
vector<int> number2(arr.begin(), arr.end()) // [begin(), arr.end())
//vector可以直接替换为deque与list
```

4. 拷贝或者移动

```c++
vector<int> number1 = {1, 2, 4, 6};
vector<int> number2(number1); // 拷贝构造
vector<int> number3(std::move(number1)); // 移动构造
//vector可以直接替换为deque与list
```

5. 大括号范围

```c++
vector<int> number = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//vector可以直接替换为deque与list
```



**2种遍历**

1. 使用下标遍历

```c++
// 使用下标进行遍历(要求容器必须是支持下标访问的，list不支持下标，所以就不适用)
for(size_t i = 0; i != number.size(); ++i)
{
    cout << number[i] << " ";
}
```

2. 迭代器

```c++
// 初始化迭代器代替 size_t i
vector<int>::iterator it = number.begin();
for(; it != number.end(); ++it)
{
    cout << *it << " ";
}
```

3. 迭代器+增强for循环

```c++
// 这里的auto的类型实际上是vector<int>::value_type , value也可以是deque与list
for(auto &elem : number){
    cout << elem << " ";
}
cout << endl;
```



**在尾部进行插入与删除**

```c++
// push_back会在容器的.end()位置调用元素自己的拷贝构造函数或者是移动构造函数
cout << "vector、deque、list均可在尾部进行插入删除" << endl;
number.push_back(111);
number.pop_back();
```

三种序列式vector、deque、list都支持在尾部进行插入与删除。



**在头部进行插入与删除**

```c++
cout << "deque和list均可以在头部插入删除" << endl;
number.push_front(111);
number.pop_front();
```

<span style=color:red;background:yellow;font-size:20px>注意：对于deque与list而言，都可以在头部进行插入与删除，但是vector没有提供这种方式</span>

为什么vector不支持在头部进行插入与删除

因为vector是动态连续数组，也就是元素是连续的，如果在第一个位置插入一个元素，那么后面的所有元素都会后移；如果删除第一个元素，那么后面的所有元素都会前移，这样会导致开销比较大，也就是时间复杂度O(N),出于效率考虑，就没有提供在头部进行插入的push_front与删除的pop_front函数。

对于deque和list在头部操作的时间复杂度只有O(1)



**在任意位置插入 / 3种insert**

三种序列式容器在任意位置进行插入的操作是insert函数，三种容器都适合

在 STL 容器（如 `vector`、`deque`、`list`）中，几乎所有的 `insert` 重载都是“在给定迭代器所指向的位置**之前**插入”一个或多个元素。

```c++
auto it = container.begin() + k;  // it 指向第 k+1 个元素
container.insert(it, value);
```

这条语句会把 `value` 插入到当前迭代器 `it` 所指向元素的**前面**，也就是成为第 k+1 个元素，原先的第 k+1、k+2…个元素依次往后移动一位。

如果 `it == container.begin()`，相当于在最前面插入；如果 `it == container.end()`，相当于在末尾插入（和 `push_back` 效果一致，但 `insert(end(), …)` 会返回新插入元素的迭代器）。

---------

1. 插入一个元素

```C++
// 在容器的某个位置前面插入一个元素
// pos		 要插入内容的迭代器位置。pos 可以是.end()迭代器
// value	 要插入的元素值
iterator insert( iterator pos, const T& value );
iterator insert( const_iterator pos, const T& value );

//示例：
auto it = number.begin();
number.insert(it, 22);
```

2. 插入count个相同元素

```C++
// count	相同元素的数量
void insert(iterator pos, size_type count, const T& value);
iterator insert(const_iterator pos, size_type count, const T& value);

//示例：
auto it = number.begin();
number.insert(it, 4, 44);
```

3. 插入迭代器范围元素

```C++
// 在容器的某个位置前面插入迭代器范围的元素
// first, last	 要插入的元素的范围
template<class InputIt> 
void insert(iterator pos, InputIt first, InputIt last);
template<class InputIt> 
iterator insert(const_iterator pos, InputIt first, InputIt last);

//示例：
auto it = number.begin();
vector<int> vec{51, 52, 53, 54, 55, 56, 57, 58, 59};
number.insert(it, vec.begin(), vec.end());
```

4. 插入大括号范围元素

```C++
//在容器的某个位置前面插入大括号范围的元素
iterator insert(const_iterator pos, std::initializer_list<T> ilist);

//示例：
number.insert(it, std::initialiser_list<int>{1, 2, 3});
//也可以直接如下操作(这种简单一些)
number.insert(it, {1, 2, 3});
```

**思考：上述代码中，三种容器在insert之后，迭代器it解引用之后的结果有什么区别**？

insert在任意位置进行插入，list使用起来很好，没有任何问题，但是deque与vector使用起来可能会出现问题，因为**vector是物理上连续的**，所以在中间插入元素会导致插入元素后面的所有元素向后移动，deque也有类似情况，<span style=color:red>**可能因为插入而引起底层容量不够而扩容，从而使得迭代器失效(申请了新的空间，但是迭代器还指向老的空间)**</span>，即使没有扩容，插入之后的迭代器也失效了(不再指向之前的元素了)。









**在任意位置删除元素**

三种序列式容器的删除操作是erase函数，函数接口如下

```C++
//删除指定迭代器位置的元素
iterator erase(iterator position);
//删除一个迭代器范围的元素
iterator erase(iterator first, iterator last); 
```

对于vector而言，会导致删除迭代器之后的所有元素前移，从而导致<font color = red>删除元素之后的所有迭代器失效</font>（迭代器的位置没有改变，但是因为元素的移动，导致迭代器指向的不是删除之前的元素，所以失效）；

解决方法:
```c++
// 这样的写法与解决insert时vector迭代器失效的方法相同
auto it = vec.begin() + 3;
it = vec.erase(it);
```

对于deque而言,  erase操作也会让被删除元素之后的元素向前“补位”，**实现上也可能导致元素的搬移（跨 block 或 block 内移动）**, 执行 erase 后，所有迭代器和引用都被视为失效。

解决方法与vector相同, 永远用it接收erase的返回值



**其他操作:    获取元素个数 \ 清空元素 \ 重置元素个数 \ 交换两个容器的内容\ 获取头部元素尾部元素**

三种序列式容器vector、deque、list都支持元素的清空clear函数 \ 获取元素个数的size函数 \ 重置元素个数的resize函数 \ 交换两个同类型容器元素的swap函数

对于vector与deque还支持回收多余空间的shrink_to_fit函数，特别的，对于vector而言，还支持获取容量的capacity函数

```c++
// vector vec
cout << "size(): " << vec.size() << endl; // 实际存储的元素个数
cout << "capacity(): " << vec.capacity() << endl; // 不扩容的前提下最大的存储空间
vec.clear(); // 清空元素
vec.shrink_to_fit(); // 回收多余的空间
vec.resize(42); // 将元素个数重置为42个, 多余的地方补0
vec.swap(other_vec); // 交换元素
vec.front(); // 首元素
vec.back(); // 尾元素

// deque dq
cout << "size(): " << dq.size() << endl; // 实际存储的元素个数
dq.clear(); // 清空元素
dq.shrink_to_fit(); // 回收多余的空间
dq.resize(42); // 将元素个数重置为42个, 多余的地方补0
dq.swap(other_dq); // 交换元素
dq.front(); // 首元素
dq.back(); // 尾元素

// list li
cout << "size(): " << li.size() << endl; // 实际存储的元素个数
li.clear(); // 清空元素
li.resize(42); // 将元素个数重置为42个, 多余的地方补0
li.swap(other_li); // 交换元素
li.front(); // 首元素
li.back(); // 尾元素
```

-------

重置元素个数的函数接口

```C++
// 如果 新 size > 当前 size：追加若干个值为 value 的元素(value 默认为 T()，即类型的默认值);	如果 新 size < 当前 size：删除末尾多余的元素。
void resize( size_type count, T value = T() );
std::vector<int> v = {1, 2};
v.resize(5, 9);  // v = {1, 2, 9, 9, 9}
// 使用默认值扩容
void resize( size_type count );
// 与第一种相同
void resize( size_type count, const value_type& value );
```

交换两个容器的内容

```C++
void swap( vector& other );
```

三种序列式容器都支持swap操作。

三种序列式容器都可以使用front与back获取首尾元素。



**emplace系列函数**

`emplace` 系列函数是 C++11 引入的，是对传统 `insert`/`push_back` 等函数的性能优化版本，广泛用于 STL 容器中（如 `vector`, `deque`, `list`, `map`, `set` 等）。

1. 核心概念：

> **在容器中原地构造对象，避免额外的拷贝或移动操作。**

 常见函数有：

| 函数名            | 用途描述                                        |
| ----------------- | ----------------------------------------------- |
| `emplace_back()`  | 在容器末尾原地构造元素（类似 `push_back`）      |
| `emplace_front()` | 在容器开头原地构造元素（类似 `push_front`）     |
| `emplace()`       | 在指定位置或规则下原地构造元素（类似 `insert`） |



2. 与 push / insert 的区别

`push_back(obj)` 做了什么？

```cpp
T obj(...);            // 构造一个临时对象
vec.push_back(obj);    // 拷贝或移动这个对象进 vector
```

 `emplace_back(args...)` 做了什么？

```cpp
vec.emplace_back(...); // 直接在 vector 的末尾原地构造对象
```

 **效率更高，因为省去了构造临时对象再拷贝/移动的步骤。**

![image-20250624112841124](D:\MarkDown\Picture\image-20250624112841124.png)



## 5: list的特殊操作

因为是链表, list有reverse()逆置, sort()排序, unique()去重, merge()合并, splice()移动 五个特有的操作

```c++
// list容器特有的5个操作
void test4() {
	// 初始列表
	list<int> li = { 3, 1, 4, 1, 5, 9, 2, 6, 5 };
	cout << "初始 li: ";
	Print(li);
	cout << '\n';

	// 1. reverse(): 原地逆置
	li.reverse();
	cout << "1. reverse(): ";
	Print(li);


	// 2. sort(): 原地排序, list不支持随机访问, 这里用的不是std::sort()而是std::list::sort()
	li.sort();
	cout << "2. sort(): ";
	Print(li);

	// 3. unique(): 删除相邻重复元素
	li.unique();
	cout << "3. unique(): ";
	Print(li);

	// 4. merge(): 合并另一个已排序的 list
	list<int> other = { 0, 2, 8, 8 };  // 必须已排序
	li.merge(other);
	cout << "4. merge(other): ";
	Print(li);
	// 合并后 other 为空
	cout << "other.size() " << other.size() << endl;

	// 5. splice(): 从 another 列表“搬”元素到 li
	list<int> another = { 7, 7, 7 };
	auto it = next(li.begin(), 3);    // 插入位置：第 4 个元素之前 // next()表示迭代器向后移动指定位置
	li.splice(it, another);           // 将 entire another 移到 li
	cout << "5. splice(it, another): ";
	Print(li);
	// splice 后 another 也为空
	cout << "another.size() " << another.size() << endl;
}
```

```c++
初始 li: 3 1 4 1 5 9 2 6 5

1. reverse(): 5 6 2 9 5 1 4 1 3
2. sort(): 1 1 2 3 4 5 5 6 9
3. unique(): 1 2 3 4 5 6 9
4. merge(other): 0 1 2 2 3 4 5 6 8 8 9
other.size() 0
5. splice(it, another): 0 1 2 7 7 7 2 3 4 5 6 8 8 9
another.size() 0
```

- merge()合并函数:

合并的链表必须是有序的，如果没有顺序，合并没有效果。merge函数只有在两个链表都是升序的时候, 合并后才是有序其他的方式(比如都是降序, 一个升序一个降序)不能保证最后的结果是有序的两个链表合并之后，并且另一个链表就为空了。

- splice函数可以用来调整元素位置

```c++
void test5() {
	// splice的other参数可以是它自己, 即把自己内部的数据调整位置
	// 但是插入位置不是范围本身的一部分
	std::list<int> li = { 1, 2, 3, 4, 5 };																					
	auto first = std::next(li.begin(), 1);  // 指向 2																		
	auto last = std::next(li.begin(), 4);   // 指向 5（不包含）
	auto pos = li.begin();  // 指向 1
	li.splice(pos, li, first, last);  // 把 2,3,4 移动到 1 前面
	Print(li); // 结果：2 3 4 1 5
}
```

<img src="D:\MarkDown\Picture\image-20250625215759847.png" alt="image-20250625215759847" style="zoom: 50%;" />

#### <span style=color:red;background:yellow;font-size:30px>sort函数自定义排序规则</span>

sort函数无参版本默认升序排序,  可以传入两个参数来控制升序还是降序

```c++
vec.sort(); // 默认升序
vec.sort(std::less<int>()); // 降序
vec.sort(std::greater<int>()); // 升序
```

可以自定义一个类, 重载函数调用运算符在里面自定义排序的方法

```c++
typedef struct Student {
	string name;
	int Chinese_sorce;
	int Math_sorce;
	int English_sorce;
	int Sum_sorce;
}student;

// 自定义类, 类的参数是参与比较的容器中的两个元素
struct CompareList {
	bool operator()(const student& lhs, const student& rhs) const { // debug 比较器的两个参数是容器的两个数据成员, 而不是两个容器
		if (lhs.Sum_sorce != rhs.Sum_sorce) {
			return lhs.Sum_sorce > rhs.Sum_sorce;
		}
		else if (lhs.Sum_sorce == rhs.Sum_sorce) {
			return (lhs.Chinese_sorce > rhs.Chinese_sorce);
		}
	}
};

void homework3() {
	student s1 = { "Tom", 90, 95, 88, 90 + 95 + 88 };
	student s2 = { "Jack", 91, 95, 87, 91 + 95 + 87 };
	student s3 = { "EW", 90, 99, 99, 90 + 99 + 99 };
	student s4 = { "Man!", 24, 24, 24, 24 + 24 + 24 };
	list<student> L = {s1, s2, s3, s4};
	Print(L);

	cout << "按照总成绩sum进行降序，如果总成绩sum相同按照语文成绩进行降序:" << endl;
	L.sort(CompareList());
	Print(L);
}
```

<img src="D:\MarkDown\Picture\image-20250625220815440.png" alt="image-20250625220815440" style="zoom: 50%;" />















## 序列式容器总结

5种初始化,

 2种遍历,

头插尾插, 

头删尾删(list没有)(push_back拷贝操作), 

insert(一定在一个迭代器前面进行插入)(底层扩容导致容器失效), 

删除(一个/ 迭代器范围)(Vector, deque, list在删除连续重复元素要注意漏删元素)(解决办法: 每次删除都要把删除结果返回迭代器指针), 

vector和deque的迭代器失效有什么区别? 

清空(clear), 

获取元素个数, 

回收多余空间

, 重置容器元素个数

, 重置元素个数,

获取第一个元素

, 获取最后一个元素,

 随机访问

, emplace系列可变参数函数

, list的特殊操作,

 sort自定义排序,

 merge函数的注意点()

, splice有什么特点







# 三: 关联式容器 set, multiset, map, multimap

## 1: pair模板结构

`std::pair` 用来把两个类型可能不同的值“打包”在一起，形成一个简单的二元组

```c++
template<typename T1, typename T2>
struct pair {
    T1 first;   // 第一个成员，通常表示“键”
    T2 second;  // 第二个成员，通常表示“值”

    // 还包含构造函数、比较运算符等
    // …拷贝/移动构造、赋值、析构…
    // 比较运算符 (<, >, ==, !=, <=, >=) 按字典序
};
```

```c++
// 三种构造方式
pair<int, string> p1;              		// 1. 默认构造：first、second 默认初始化
pair<int, string> p2(42, "hello"); 		// 2. 用指定值构造
auto p3 = make_pair(3.14, 'a');          // 3. 推荐：使用make_pair类型自动推导
:pair p4{1, 2.0};					   // C++17可以用大括号
```

```c++
// pair支持按字典的顺序的比较
pair<int,int> a{1, 5}, b{2, 3};
bool lt = (a < b);   // true，因为先比较 first：1 < 2
bool eq = (a == b);  // false
```

```c++
// 与关联容器结合 std::map<Key, T> 里面存放的元素类型就是 std::pair<const Key, T>
std::map<std::string,int> ages;
ages.insert({ "Alice", 30 });
```

计算除法的例子

```c++
pair<int, int> divmod(int a, int b) { // 一个函数, 返回值是一个pair二元组
        return { a / b, a % b }; // 返回的first是除的结果, second是除的余数
}

void test2() {
    // 2) 构造 pair
    pair<int, string> p1 = make_pair(1, "one"); // make_pair自动创建一个pair对象
    pair<int, string> p2(2, "two");  // 也可直接用构造函数
    cout << "p1: " << p1.first << " -> " << p1.second << "\n";
    cout << "p2: " << p2.first << " -> " << p2.second << "\n\n";

    // 3) 接收 divmod 的返回值，并取出 first/second
    pair<int, int> res = divmod(17, 5);
    int quotient = res.first;
    int remainder = res.second;
    cout << "17 / 5 = " << quotient << " 余 " << remainder << "\n\n";

    
    // 4) 在 map 中插入／遍历时也常用 pair
    map<int, string> m;
    // insert 接受 pair<key,value>
    m.insert(make_pair(3, "three")); // 使用makepair自动构造
    m.insert(pair<int, string>(4, "four")); // 手动构造pair
    // 遍历
    for (map<int, string>::iterator it = m.begin(); it != m.end(); ++it) {
        // *it 是 pair<const int, string>
        cout << it->first << " => " << it->second << "\n";
    }
}

打印结果:
p1: 1 -> one
p2: 2 -> two

17 / 5 = 3 余 2

3 => three
4 => four
```







## 2:    set

**set的基本特征:**

1. 存放的是key类型，key值是唯一的，不能重复
2. 默认情况下，会按照key值进行升序排列
3. 底层实现是红黑树
4. ![image-20250628155354817](D:\MarkDown\Picture\image-20250628155354817.png)

```c++
/* set<int, std::greater<int>> number ={4,5,2,35,5,2,1,7,5,43,2,9 };*/
set<int>number={4,5,2,35,5,2,1,7,5,43,2,9 };
Print(number); // 打印: 1 2 4 5 7 9 35 43 // 默认进行去重+升序排序
```

```c++
void test1() {           
    set<int> s = { 4,5,2,35,5,2,1,7,5,43,2,9  };
    
    // 1. count计数函数, 返回值出现的次数
    cout << "35出现了几次: " << s.count(35) << endl; // 因为set的Key不可重复, 因此只会输出0和1
    
    // 2. find查找函数, 返回指向值的位置的迭代器
    auto it = s.find(7); // set中的Key是只读的, 不可用迭代器修改
    if(it != s.end()){
         cout << "找到指定值" << endl;
    }else{
         cout << "未找到值" << endl;
     }
 }
```

insert函数有一个重载会返回一个 `std::pair<iterator, bool>`

```c++
// 3. insert插入函数
// insert插入
cout << endl << "set的insert操作" << endl;
pair<set<int>::iterator, bool> ret = number.insert(4); // 把set的迭代器和bool类型组合成了一个pair, 接收set.insert的返回值, insert 函数有一个重载就是会返回一个 std::pair<iterator, bool>
                                                           // 这个pair的first是指向被插入容器的迭代器(成功指向新插的元素, 失败指向已有的元素), second是插入是否成功
    
if (ret.second){
        cout << "插入成功了: " << *ret.first << endl;
}
else{
    cout << "插入失败了，该元素已经在set里了: " << *ret.first << endl;
}
Print(number);
 
输出:
set的insert操作
插入失败了，该元素已经在set里了: 4
1  3  4  7  8  9
```



#### set自定义类型的写法







除了key值可以重复其他的和set都基本一样



## 3:    multiset

multiple a.多种多样的   compare v.比较    Allocator 内存分配器

```c++
template<
    class Key, // 存储在multiset中的类型为Key
    class Compare = std::less<Key>, // 默认排序规则是less, 可调用对象来自定义排序规则
    class Allocator = std::allocator<Key> // 管理 multiset 在堆上分配和释放节点的方式
>
```

基本特性:

1. 存放Key类型, Key值不唯一, 可重复
2. 默认按Key值升序, <font color = red>不进行去重</font>
3. 底层实现是红黑树

功能:

1. multiset的查找（count、find）、插入（insert）、删除（erase）与set基本是一样的
2. 不支持下标操作，不支持使用迭代器修改值

bound函数

```c++
multiset<int> number = { 1,3,4,8,7,3,4,9 };
auto cit = number.lower_bound(3); // 返回第一个 >= 给定Key值的迭代器
auto cit2 = number.upper_bound(3); // 返回第一个 > 给定Key值的迭代器

pair < multiset<int>::iterator, multiset <int>::iterator> ret = number.equal_range(3); // 返回结果是一个pair, .first是一个指向"第一个大于等于 >= 给定Key值的迭代器", .second是一个指向"第一个大于 > 给定Key的迭代器"
cout << *ret.first << endl; // 输出3
cout << *ret.second << endl; // 输出4
```

记忆: >= 是第一个first, > 是第二个second



## 4:    map

基本特征:

1. 存放的是key-value类型, key值是唯一的, 不能重复 / 但是value值可以重复
2. 默认情况下, 会按key值进行升序排序
3. 底层是红黑树
4. 里面存放的类型是pair, 可以用pair的成员first和second访问Key和Value
5. ![image-20250628153657003](D:\MarkDown\Picture\image-20250628153657003.png)

```c++
map<int, string> number = {
    // 第一种构建方法: 大括号构建pair类型
    {1, "北京"},
    {3, "南京"},
    // 第二种构建方法: 用pair对象进行构建
    pair<int, string>(4, "武汉"), // Key不可重复, 但是value可以重复
    pair<int, string>(2, "武汉"), 
    // 第三种构建方法: 使用make_pair直接构建pair
    make_pair(5, "天津"),
    make_pair(3, "湖南"),
};
Print(number);
```

```c++
// 增强for循环遍历
void Print(const map<int, string>& con)
{
    for (const pair<int, string>& elem : con)
    {
        cout << "Key: " << elem.first << " " << "value: " << elem.second << endl; // first和second是pair的成员
    }
    cout << endl;
}


打印: 
Key: 1 value: 北京
Key: 2 value: 武汉
Key: 3 value: 南京
Key: 4 value: 武汉
Key: 5 value: 天津
```

map的插入: 利用make_pair创建一个pair, 再将pair插入

```c++
    // ret是一个pair, 将map的迭代器和表示插入成功与否的bool值绑定在了一块
    pair<map<int, string>::iterator, bool> ret = number.insert(make_pair(6, "东京"));
    // 当然也可以用auto来创建这个pair
    auto ret1 = number.insert(make_pair(7, "高天原"));

    if (ret.second) {
        cout << "插入成功" << ret.first->first << " " << ret.first->second << endl;
    } else {
        cout << " 插入失败, map中已有该元素" << endl;
    }
    if (ret1.second) {
        cout << "插入成功" << ret1.first->first << " " << ret1.first->second << endl;
    } else {
        cout << " 插入失败, map中已有该元素" << endl;
    }
```

map的下标: 带有const的map不可使用下标操作

```c++
    // 可以直接用下标进行增查改
    cout << endl << "map的下标操作" << endl;
    cout << "number[4]= " << number[4] << endl;//查找
    cout << "number[8]= " << number[8] << endl;//插入
    Print(number);
    cout << endl << endl;
    /* T &operator[](const Key &key) */
    number[8] = "重庆";//修改
    number[7] = "上海";
    /* number.operator[](7).operator=("上海");*/
    Print(number);
    //map的下标是没有重载const版本的，所以const的map是不能调用下标
    /* const map<int, string> mm ={ {1, "wangdao"} }; */
    /* mm[1];//error */
```

针对自定义类型

<img src="D:\MarkDown\Picture\image-20250626112112911.png" alt="image-20250626112112911" style="zoom:50%;" />

对于map针对于自定义类型而言，如果自定义类型中的Key是不能比较大小的，还是需要进行改写Comapre，改写的方式有三种：模板的特化、运算符重载、函数对象；但是如果Key类型可以比较大小，但是T类型不能比较大小，那么就不受影响，不用改变Compare的传参。



## 5:    multimap

1. 存放的是key-value类型, key值是不唯一的, key值和value值可以重复
2. 默认情况下, 会按key值进行升序排序
3. 底层是红黑树
4. 里面存放的类型是pair, 可以用pair的成员first和second访问Key和Value3

multimap的查找（count、find）、插入（insert）、删除（erase）与map基本是一样的。

不可以使用下标, 下标使用的前提是key的值唯一存在

<img src="D:\MarkDown\Picture\image-20250626112946748.png" alt="image-20250626112946748" style="zoom:50%;" />



## 6: 有序关联式容器总结

1、所有关联式容器中的元素是<span style=color:red;background:yellow;font-size:20px>有序的</span>, 即使存入的时候是无序的, 容器内也会变成有序；

2、底层使用的是<span style=color:red;background:yellow;font-size:20px>红黑树</span>；

3、不带multi开头的key值是唯一的，带multi开头的key值是可以重复的；

4、只有map具备下标，其他三种关联式容器都不具备下标，特别的，map的下标传递的是key类型。





# 四: 无序关联式容器 unordered_set, unordered_multiset, unordered_map, unordered_multimap

STL中无序关联式容器的底层实现都是哈希表, 解决哈希冲突的问题一般采用链地址法

<img src="D:\MarkDown\Picture\image-20250628160246676.png" alt="image-20250628160246676" style="zoom:67%;" />

## 1: unordered_set

基本特征:

1. 存放的是key, key值唯一, 不可重复
2. key值无序, 会自动进行去重操作
3. 底层是哈希表

unordered_set的查找（count、find）、插入（insert）、删除（erase）与set是完全一样，也不支持下标操作。

针对自定义类型







## 2: unordered_multiset

基本特征

1. 存放的是key, key值不唯一, 可重复
2. key值无序, 会自动进行去重操作
3. 底层是哈希表

unordered_multiset的查找（count、find）、插入（insert）、删除（erase）与multiset是完全一样，也不支持下标操作。

针对于自定义类型

<img src="C:/Users/18388/Desktop/3th/05_CppBase/STL笔记/嵌入式3期STL部分.assets/image-20250626160047067.png" alt="image-20250626160047067" style="zoom:67%;" />

unordered_multiset针对于自定义类型的写法与unordered_set是完全一样，也需要关注第二个模板参数Hash以及第三个模板参数KeyEqual。



## 3: unordered_map

基本特征

1. 存放的是key-value, key值是唯一的, 不可重复, 但value可重复
2. key值无序, 会自动进行去重操作, 但不会进行排序操作
3. 底层是哈希表

unordered_map的查找（count、find）、插入（insert）、删除（erase）与map是完全一样。

下标操作也与map相同





## 4: unordered_multimap

基本特征

1. 存放的是key-value, key值是不唯一的, 可重复, value可重复
2. key值无序, 会自动进行去重操作, 但不会进行排序操作
3. 底层是哈希表

unordered_multimap的查找（count、find）、插入（insert）、删除（erase）与multimap是完全一样，也不支持下标。



## 5: 无序关联式容器总结

1、所有无序关联式容器中的元素是<span style=color:red;background:yellow;font-size:20px>无序的</span>, 即使输入的时候是有序的, 存入容器中也会变的无序;

2、底层使用的是<span style=color:red;background:yellow;font-size:20px>哈希</span>；

3、不带multi开头的key值是唯一的，带multi开头的key值是可以重复的；

4、只有unordered_map具备下标，其他三种无序关联式容器都不具备下标，特别的，unordered_map的下标传递的是key类型。



# 五: <span style=color:red;background:yellow;font-size:30px>如何选择容器（重要）</span>

 1、元素是不是有序的

首先选择的是关联式容器，不应该选择的是无序关联式容器，其次，可以选择序列式容器，对于vector与deque可以使用sort算法，对于list而言，可以使用成员函数sort。

 2、有没有下标

序列式容器：vector、deque；

关联式容器：map；

无序关联式容器：unordered_map；

 3、查找时间复杂度

序列式容器：O(N);

关联式容器：O(logN);

无序关联式容器：O(1);

 4、迭代器类型

随机访问迭代器：vector、deque；

双向迭代器：list、关联式容器；

前向迭代器：无序关联式容器。



| 容器                 | 元素是否有序                  | 是否有下标               | 查找时间复杂度               | 迭代器类型     |
| -------------------- | ----------------------------- | ------------------------ | ---------------------------- | -------------- |
| `vector`             | 有序（插入顺序）              | 是                       | 查找元素 O(n)；随机访问 O(1) | 随机访问迭代器 |
| `list`               | 有序（插入顺序）              | 否    链表不支持随机访问 | O(n)                         | 双向迭代器     |
| `deque`              | 有序（插入顺序）              | 是                       | O(n)                         | 随机访问迭代器 |
| `set`                | 有序（按键排序）key值不重复   | 否    不是“键→值”映射    | O(log n)                     | 双向迭代器     |
| `multiset`           | 有序（按键排序）key值可重复   | 否    不是“键→值”映射    | O(log n)                     | 双向迭代器     |
| `map`                | 有序（按键排序）key值不重复   | 是                       | O(log n)                     | 双向迭代器     |
| `multimap`           | 有序（按键排序）key值可重复   | 否    键不唯一           | O(log n)                     | 双向迭代器     |
| `unordered_set`      | 无序    key值不重复(自动去重) | 否    不是“键→值”映射    | 平均 O(1)，最坏 O(n)         | 前向迭代器     |
| `unordered_multiset` | 无序    key值可重复           | 否    不是“键→值”映射    | 平均 O(1)，最坏 O(n)         | 前向迭代器     |
| `unordered_map`      | 无序    key值不重复(自动去重) | 是                       | 平均 O(1)，最坏 O(n)         | 前向迭代器     |
| `unordered_multimap` | 无序    key值可重复           | 否    键不唯一           | 平均 O(1)，最坏 O(n)         | 前向迭代器     |




写无参构造的时候不能带小括号, 带小括号()就是函数声明了

vec.at(0) 有范围检查, 不会越界

vec[0] 没有范围检查, 容易越界

copy函数用来打印







# 六:  算法

## 迭代器

迭代器行为类似于指针，但是又不完全等同是指针。但是在使用上与普通指针没有什么区别。将迭代器称为**泛型指针**。

<img src="D:\MarkDown\Picture\image-20250628162153352.png" alt="image-20250628162153352" style="zoom:67%;" />

### 流迭代器

可以把流迭代器看做是容器 流存在输入输出缓冲区, 缓冲区可以存放数据=>把迭代器当做容器看待

### 插入迭代器

| 插入器           | 作用                                       | 使用场景                                                     |
| ---------------- | ------------------------------------------ | ------------------------------------------------------------ |
| `back_inserter`  | 使用 `push_back` 插入到**容器尾部**        | `vector`、`deque`、`list`（支持 `push_back`）                |
| `front_inserter` | 使用 `push_front` 插入到**容器头部**       | `list`、`deque`（支持 `push_front`）                         |
| `inserter`       | 使用 `insert(pos, ...)` 插入到**指定位置** | 任意支持 `insert(iterator, value)` 的容器，如 `set`、`map`、`list` |

```c++
void test5() {
    vector<int> vec = { 1, 3, 4, 8, 7, 3, 4, 9 };
    Print(vec);
    list<int> lst = { 777, 777, 777 ,777 };

//back_inserter		push_back
    //将list中的所有元素插入到vector的尾部
    copy(lst.begin(), lst.end(), back_inserter(vec));
    copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));

//front_inserter	push_front
    //将vector中的所有元素插入到list的头部
    copy(vec.begin(), vec.end(), front_inserter(lst));
    copy(lst.begin(), lst.end(), ostream_iterator<int>(cout, " 我是空格 "));

//inserter			insert(pos, ...)
    //将vector中的所有元素插入到set的中间
    set<int> setNum = { 11,7,10,23 };
    auto it = setNum.begin();
    copy(vec.begin(), vec.end(), inserter(setNum, it));
    
    cout << " 用copy实现打印 : " << endl;
    copy(setNum.begin(), setNum.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}
```

```c++
copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
copy 会对 vec 的每个元素调用 *out = *first;      // out 是 ostream_iterator
// 将每个元素的起始迭代器赋值给输出流迭代器
这就触发了
cout << *first << " ";
// 对起始迭代器解引用得到值, 并将这个值放入输出流迭代器中
于是就“打印”出每个元素，并在后面写上一个空格。
```

>
>小辨析:
>| 名称     | 所属上下文                | 含义                                           |
>| -------- | ------------------------- | ---------------------------------------------- |
>| `first`  | 算法函数参数（如 `copy`） | 起始迭代器，定义处理区间的开始                 |
>| `last`   | 算法函数参数              | 结束迭代器，定义处理区间的末尾（不包含该位置） |
>| `first`  | `std::pair` 成员          | 对象的第一个值                                 |
>| `second` | `std::pair` 成员          | 对象的第二个值                                 |
>
>







使用的头文件: `#include <algorithm>`

STL中所有函数都不是成员函数(对象加点.), 都是普通函数(全局函数,  自由函数)

## 算法的类别

非修改的算法: count, find, for_each

修改的算法: copy, move, fill, remove, swap

排序: sort

二分搜索: lower_bound, upper_bound, equal_range

集合操作: 取交集, 取并集, 交集

堆操作: make_heap, push_heap

取最值: mac, min

数组操作: accumulate(累加)

未初始化的内存操作: uninitialzed_copy

> UnaryFunction一元函数: 函数的参数只有一个
> UnaryPre  一元断言\谓词函数, 一元函数, 且返回值是bool









## 一: copy

定义在头文件 `<algorithm>` 中。

------

  原型说明：

class InputIt -------> class OutputIt 

```cpp
template< class InputIt, class OutputIt >
OutputIt copy( InputIt first, InputIt last, OutputIt d_first );
```

这是一个**函数模板（template function）**

  1. `template< class InputIt, class OutputIt >`

- 说明 `std::copy` 是一个模板函数，接受两个**模板参数类型**。
- `InputIt`：输入迭代器类型（可以是指针、vector的iterator、list的iterator 等）。
- `OutputIt`：输出迭代器类型（也可以是插入器、指针、ostream_iterator 等）。

 2. 函数参数说明

```cpp
copy(InputIt first, InputIt last, OutputIt d_first);
```

- `first`：==输入区间的起始位置==。
- `last`：==输入区间的结束位置==（**不包含该位置的值**，是半开区间 `[first, last)`）。
- `d_first`：==目标输出的起始位置==。

------

  3. 返回值

- 返回一个 `OutputIt` 类型的迭代器，表示**输出序列的末尾**（也就是==上一次写入之后的位置==）。
- 在大多数使用场景中，这个返回值不是必须使用的（但你可以用它继续写入或判断）。

------

  4. 功能描述

> **将 `[first, last)` 范围内的元素按顺序复制到以 `d_first` 开始的目标范围中。**

例如：

```cpp
std::vector<int> v1 = {1, 2, 3};
std::vector<int> v2(3);
std::copy(v1.begin(), v1.end(), v2.begin());  // 把 v1 复制到 v2
```

或者把 `vector` 打印到屏幕上：

```cpp
std::copy(v1.begin(), v1.end(), std::ostream_iterator<int>(std::cout, " "));
```

 总结一句话：

> `std::copy` 是一个非常通用的“复制算法”，它接收**任意一对输入迭代器**和一个**输出迭代器**，将输入范围内的元素依次赋值给输出范围，并返回输出末尾迭代器位置。可用于复制、拼接、打印等场景。

例如:

```c++
void test6() {
    vector<int> src = { 1, 2, 3, 4, 5 };    // 原始容器
    vector<int> dest = { 7,7,7,7,7,7,7 };                 // 目标容器，提前存入
    Print(dest); // 打印: 7 7 7 7 7 7 7
    // 使用 std::copy 将 src 的元素复制到 dest
    copy(src.begin(), src.end(), dest.begin());

    Print(dest); // 打印内容: 1 2 3 4 5 7 7 // 发生了覆盖
}
```





## 二:    for_each

一元函数：函数的参数只有一个；二元函数：函数的参数是两个；

一元断言/谓词：函数的参数只有一个，并且返回类型是bool；二元断言/谓词：函数的参数只有两个，并且返回类型是bool；

```c++
template< class InputIt, class UnaryFunction >
UnaryFunction for_each( InputIt first, InputIt last, UnaryFunction f ); // 首迭代器, 尾迭代器, 一元函数
```

`std::for_each` 可以让你“对每个元素执行某个函数”，不需要手动写 `for` 循环。

格式: 

```c++
std::for_each(起始迭代器, 结束迭代器, 函数或函数对象);
// 起始迭代器：通常是 容器.begin()
// 结束迭代器：通常是 容器.end()
// 函数：对每个元素执行的操作，可以是：普通函数, Lambda 表达式,   函数对象
```



```c++
vector<int> v = {1, 2, 3, 4, 5};

for_each(v.begin(), v.end(), [](int x){
    std::cout << x << " ";
});
```







## 三:    lambda表达式

匿名函数

1. 基本语法



2. 值捕获和引用捕获

值捕获: 将外部局部变量拷贝到lambda中, 是值传递

引用捕获: 将外部局部变量的引用传递到lambda表达式中

=: 将外部所有的局部变量都进行值捕获

&: 将外部所有的局部变量都进行引用捕获

混合: 指定的局部变量成为引用捕获, 其他的局部变量是值捕获

this指针: 捕获当前类的this指针, 让lambda表达式拥有和当前类成员函数同样的访问权限(修改类的数据成员, 使用类的成员函数)

特别的: 全局变量的作用域包含了lambda表达式





本质是一个带operator( )的类, 即函数对象, 且是一个const类型的



1、基语法规则

<img src="D:\MarkDown\Picture\image-20250627171611815.png" alt="image-20250627171611815" style="zoom:67%;" />

 2、捕获方式

<img src="D:\MarkDown\Picture\image-20250627171931298.png" alt="image-20250627171931298" style="zoom: 50%;" />

3、混合捕获

可以在捕获列表中将部分外部局部变量进行值捕获，也可以将部分变量进行引用捕获，当然也可以全部值捕获或者全部引用捕获。

<img src="D:\MarkDown\Picture\image-20250627173022155.png" alt="image-20250627173022155" style="zoom:50%;" />

<img src="D:\MarkDown\Picture\image-20250627173036655.png" alt="image-20250627173036655" style="zoom:50%;" />

<span style=color:red;background:yellow;font-size:20px>[this] 捕获当前类中的this指针。让lambda表达式拥有和当前类成员函数同样的访问权限；可以修改类的成员变量，使用类的成员函数。如果已经使用了 & 或者 =, 默认添加此选项  </span>

<span style=color:red;background:yellow;font-size:20px>特别注意：全局变量是可以直接在lambda中进行使用，无需在捕获列表中进行捕获。</span>

 4、本质

lambda表达式的类型在C++11中会被看做是一个带operator()的类，即函数对象。按照C++标准，lambda表达式的operator()默认是const的，一个const成员函数是无法修改成员变量值的。mutable选项的作用就在于取消operator()的const属性。







bind

绑定函数的部分参数

```c++
void func(int x1, int x2, int x3, int &x4, int x5)


auto f = bind(&func, 10, _1, _2, number, number); // bind默认采用值传递, _1 _2 是占位符, 给 x2, x3 占个位置
number = 88888;
f(20, 30, 400, 500000, 1); // 多余的参数用完就丢掉


auto f = bind(&func, 10, _1, _2, std::ref(number), number); // 采用引用包装器, 将值传递变为引用传递
number = 88888;
f(20, 30, 400, 500000, 1); // 多余的参数用完就丢掉
```

引用折叠

```c++
&& && ----------> &&
& && -----------> &
&& & -----------> & 
& & ------------> &
```

在模板中, 如果右值引用遇到右值引用, 会折叠成右值引用, 只要有左值引用参与, 最后的结果就会折叠为左值引用



函数的形态

std::function 通用函数封装器





lambad表达式的使用误区:

不要捕获生命周期销毁的局部变量的引用





## 四:    回调函数

把某段逻辑(函数) “注册”给框架/对象，由框架/对象在合适的时机“回过头”去调用

回调函数就是一个可调用的对象, 比如: 函数指针, 函数对象, function, bind 产生的可调用对象, 还有lambda表达式. 这些对象先被保存起来, 等需要他们时再回过头来调用(回调函数)



回调函数三个步骤:

1. 定义回调函数 2. 注册回调函数 3. 执行回调函数

例子: 用bind, function实现Figure

步骤一: 在类中定义一个“回调函数成员变量”，通常用 `std::function` 来保存回调的接口

```c++
class Figure {
public:
    // 用using起别名
    using PrintName_Callback = std::function<void()>;
    using Area_Callback      = std::function<double()>;

    // 回调函数占位符（即：回调函数变量）
    PrintName_Callback _printName_Callback;
    Area_Callback      _area_Callback;
};
```

步骤二: 在子类中，将自己的成员函数绑定（bind）并赋值给回调变量，完成“注册”

```c++
class Rectangle : public Figure {
public:
    Rectangle(double len, double width)
      : _len(len), _width(width)
    {
        // 注册：绑定成员函数到回调, bind返回值是一个可调用的对象, 是一个匿名类, 被在步骤一中定义的function接收保存
        _printName_Callback = std::bind(&Rectangle::Print_Figure_Name, this); //  相当于this->Print_Figure_Name()
        _area_Callback      = std::bind(&Rectangle::Count_Area, this);
    }

    void Print_Figure_Name() const { /*...*/ }
    double Count_Area() const { /*...*/ }
};
```

步骤三: 在主程序中，通过调用回调变量，触发绑定的成员函数。

```c++
int main() {
    Rectangle rec(10, 20);

    // 执行回调：调用注册好的函数
    rec._printName_Callback(); // 执行这一句相当于, 底层自动调用了之前用 bind 注册的 rec.Print_Figure_Name()。
    
    rec._area_Callback();      // 输出并返回面积
}
```





## 五:    bind

### <span style=color:red;background:yellow;font-size:30px>bind的使用（非常重要）</span>

```c++
// 普通函数
int add(int x, int y)
{
    cout << "int add(int, int)" << endl;
    return x + y;
}

int multiply(int x, int y, int z)
{
    cout << "int multiply(int, int, int)" << endl;
    return x * y * z;
}

// 成员函数
class Example
{
public:
    //Example * this
    int add(int x, int y)
    {
        cout << "int Example::add(int, int)" << endl;
        return x + y;
    }
};
```





#### 1、绑定函数

<img src="D:\MarkDown\Picture\image-20250630111857521.png" alt="image-20250630111857521" style="zoom: 50%;" />

<span style=color:red;background:yellow;font-size:20px>注意：std::bind既可以绑定普通函数，也可以绑定成员函数，但是如果是成员函数，要注意取地址。</span>

#### 2、函数指针

<img src="D:\MarkDown\Picture\image-20250630115815231.png" alt="image-20250630115815231" style="zoom:50%;" />

<span style=color:red;background:yellow;font-size:20px>注意：函数指针的定义形式、与回调函数之间的关系以及调用步骤、延迟调用的思想、指向的类型。</span>

#### 3、占位符

顾名思义，就是占据函数的参数的位置。

<img src="D:\MarkDown\Picture\image-20250630145249893.png" alt="image-20250630145249893" style="zoom:50%;" />

<span style=color:red;background:yellow;font-size:20px>特别要注意：默认采用的是值传递的概念。</span>

bind绑定普通函数, 成员函数, 占位符, 数据成员

占位符

值传递引用传递





面向对象: 有继承 

基于对象: 没有继承  

(用function接收函数返回值, 用bind改变函数参数)

```c++
    //在C语言中，函数名是函数的入口地址；数组名是数组的入口地址
    //但是在C++中，成员函数名与函数地址是两码事，函数名就是函数名，函数入口
    //地址就是函数的入口地址
    auto f = bind(add, 10, 20); // 普通函数名在表达式中会自动衰减为函数指针（类似数组名衰减为指针）
    cout << "f() = " << f() << endl;

    cout << endl;
    auto f2 = bind(&multiply, 3, 4, 5);
    cout << "f2() = " << f2() << endl;

    cout << endl;
    Example ex;
    auto f3 = bind(&Example::add, &ex, 11, 22); // 非静态成员函数必须使用引用绑定&
    cout << "f3() = " << f3() << endl;
```



## bind的返回值到底是什么?

 **`std::bind` 返回的是一个可调用对象（callable object）**

**一个==匿名的函数对象==的实例。**



你可以把它理解成一个“包装器”，它内部保存了：

- 被绑定的函数或成员函数指针
- 被绑定的参数
- 以及可能的占位符 `_1`, `_2`, ...

这个类型其实非常复杂，不能直接书写出来，是一个类似下面这种形式的模板实例化：

```c++
std::_Bind<int (*(int, std::_Placeholder<1>))(int)>
```



------------

指针函数\函数指针, 指针常量\常量指针, 指针数组\数组指针

对于使用mem_fn进行适配时, 可以使用bind改变形态



alloctor 源码底层是malloc

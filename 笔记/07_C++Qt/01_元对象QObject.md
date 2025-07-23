# 一:    什么是元对象系统

## 1. MOS

元对象系统（Meta-Object System，MOS） 是Qt框架在C++基础上扩展的一套<span style=color:red;background:yellow;font-size:20px>运行时动态</span>特性机制。管理这些元信息的机制，使程序能在运行时动态操作对象。它的核心是通过预编译（moc工具）生成额外的元信息代码，使得原本静态的C++类具备动态能力，元对象系统具备以下功能：

- 信号（signal）与槽（slot）的跨对象通信

- 对象树 

- 属性系统动态添加、修改属性（Q_PROPERTY）

- 运行时类型信息

    

如果对象是一本书，元对象就是这本书的目录（记录章节、页码等元信息），元对象系统是存储和查询目录的规则（如通过目录快速翻到某一页） 



MOS把宏生成为moc_xxx.cpp文件

## 2. 三大核心组件

1. QObject

	任何使用了元对象系统的类都要直接或者间接继承QObject类

2. Q_OBJECT

	并且要在定义中包含Q_OBJECT宏

3. 元对象编译器

	MOC是指元对象编辑器, 用以处理包含了元对象QObject类的代码, 生成额外的元对象代码

	因为Qt并不是完全使用的标准的C++语法，所以需要将Qt的语法通过moc编译器进行编译，这样才可以使用标准的C++编译器进行编译



# 一.一: 作用域限定符+函数名

**静态成员或嵌套类型**： 当你访问一个类的==静态成员变量、静态成员函数或者其内部定义的嵌套类/枚举时==，也需要使用作用域限定符。

```c++
#include <QLineF>
#include <QPointF>

QPointF p1(0, 0); QPointF p2(10, 10);
QLineF line = QLineF::fromPoints(p1, p2); // fromPoints 是 QLineF 的静态成员函数
```

**枚举类型**： Qt中的许多枚举类型都是定义在它们的父类或命名空间内部的。因此，在使用这些枚举值时，你需要使用作用域限定符来访问它们。

```c++
#include <QLabel>
#include <Qt> // 包含Qt命名空间，或者具体的头文件如<QFlags>

QLabel *label = new QLabel("Hello World");
label->setAlignment(Qt::AlignCenter); // Qt::AlignCenter 是 Qt 命名空间下的枚举值
```



# 二:    信号与槽



<img src="D:\MarkDown\C++Qt\assets\image-20250710140636088.png" alt="image-20250710140636088" style="zoom: 67%;" />

**信号（Signal）**：是对象在发生某个**事件时自动发出的通知**。比如按钮被点击时，就会发出一个 `clicked()` 信号。

**槽（Slot）**：是一个**普通的成员函数**，用于响应信号。可以把槽函数看作是“信号触发后要做的事情”。

 核心思想是: " 一个对象发出信号, 另一个对象用槽函数响应 "



## 1. 连接信号与槽的函数: connect( )

用来把信号连接到槽, 等于是告诉程序 " 当某个事件发生时, 就自动调用某个槽函数来响应这个事件 " 

它是属于QObject中的静态成员函数

在调用connect函数连接信号与槽时，sender对象的信号并不会立即产生，因此receiver对象的method也不会被调用，==**实际的调用时机是在信号被触发之后**==，调用槽函数的操作由Qt框架负责的。

当然信号与槽连接后，可以使用disconnect函数断开连接，断开后信号触发时，槽函数将不再被调用。注意，断开连接时的参数必须与连接时完全一致。

>​								<已经很少使用>
>
>```c++
>// 1. 字符串形参
>QMetaObject::Connection QObject::connect(
>    const QObject *sender,			// 信号发送对象，必须是QObject类或其子类的对象
>    const char *signal,				// 信号的名字, 必须要用宏 `SIGNAL()`包裹
>    const QObject *receiver,		// 信号接收对象，必须是QObject类或其子类的对象
>    const char *method,				// 槽函数的名字, 必须要用宏 `SLOT()`包裹
>    Qt::ConnectionType type = Qt::AutoConnection);
>```
>
>示例:
>
>```c++
>connect(button, SIGNAL(clicked()), this, SLOT(onClicked()));
>```
>
>这个版本没有编译时检查，拼错了编译器不会报错，运行时才报错
>
>

----------------------

```c++
// 2. 没有接受者的版本
QMetaObject::Connection QObject::connect(
    const QObject *sender,			// 只有信号发送对象，必须是QObject类或其子类的对象
    PointerToMemberFunction signal,	// 指向发送信号的函数的指针
    Functor functor);

```

示例: 

```c++
connect(button, &QPushButton::clicked, []() {
    qDebug() << "Button clicked!";
});
```

不指定接收者对象（只有信号发出者 + 槽函数），槽是 lambda 或可调用对象。常用于临时函数响应（不需要 member function）。在槽函数中用 lambda 捕获外部变量非常方便。

-----------------------------

```c++
// 3. 函数指针形参
QMetaObject::Connection QObject::connect(
    const QObject *sender,			// 信号发送对象，必须是QObject类或其子类的对象
    PointerToMemberFunction signal,	// 指向信号成员函数的函数指针
    const QObject *receiver,		// 信号接收对象，必须是QObject类或其子类的对象
    PointerToMemberFunction method,	// 指向槽成员函数的函数指针
    Qt::ConnectionType type = Qt::AutoConnection); // 控制信号与槽之间的调用方式, 不写的话默认是Qt::AutoConnection

```

```c++
connect(button, &QPushButton::clicked, this, &MainWindow::handleClick);
```

这一版本是最推荐的现代写法

其他的连接方式:

>- Qt::AutoConnection（自动方式）：Qt的默认连接方式，如果信号的发出和接收这个信号的对象同属一个线程，那个工作方式与直连方式相同；否则工作方式与排队方式相同。
>- Qt::DirectConnection（直连方式）：当信号被发射时，槽函数会立即被调用，没有任何延迟（同步执行）槽函数不会切换到其他线程，而是在信号所在的线程中运行。
>- Qt::QueuedConnection（排队方式）：当信号发出后，排队到信号队列中，需等到接收对象所属线程的事件循环取得控制权时才取得该信号，调用相应的槽函数。（此时信号被塞到信号队列里了，信号与槽函数关系类似于消息通信，异步执行）
>- Qt::BlockingQueuedConnection（阻塞队列方式）：与Qt::QueuedConnection类似，但信号发送线程会阻塞，直到槽函数执行完毕。如果接收者对象与信号发送线程在同一个线程中，则绝对不要使用这种连接方式，否则程序会死锁。(信号和槽必须在不同的线程中，否则就产生死锁)这个是完全同步队列只有槽线程执行完成才会返回，否则发送线程也会一直等待，相当于是不同的线程可以同步起来执行。
>- Qt::UniqueConnection（唯一连接）：这是一个可以与上述任意一种连接类型通过位或（|）操作组合使用的标志。当设置Qt::UniqueConnection时，如果连接已存在（即相同的信号已经连接到相同对象的同一个槽），则 QObject::connect()会失败。该标志从 Qt4.6版本开始引入。





## 2. 自定义信号与槽

信号和槽的本质:	信号与槽其实都是独立的函数，但是可以通过connect将信号与槽连接在一起，但是连接之后并不能调用槽函数，<span style=color:red;background:yellow;font-size:20px>**只有当信号被触发时，连接的槽函数才会自动调用，并将信号中的参数传递到连接的槽函数中**</span>。

标准信号:	Qt提供了许多类来检测用户触发的特定事件。当这些事件被触发时，便会产生对应的信号，这些信号都是Qt类内部自带的，被称为标准信号

标准槽:	Qt的许多类内部还提供了多个功能函数，这些函数可以作为信号触发后的处理动作，称为标准槽函数

-----------------

**自定义信号: **

Qt框架提供的信号在某些特定场景下可能无法满足项目需求，因此可以设计自定义信号。
要使用自定义信号和槽，首先需要编写一个新的类，并让其继承Qt的某些标准类。==如果想在Qt中使用信号槽机制，必须满足以下条件==：1. 该类必须从QObject类或其子类派生	2. 在定义类的第一行头文件中加入Q_OBJECT宏

这些条件与使用元对象系统的要求当然相同

```c++
class MyWidget : public QWidget
{
    Q_OBJECT
public:
    ......
};
```



**自定义信号的规则：**

- ==信号使用signals关键字声明==，在其后面有一个冒号":"，在其前面不能有 public、private、protected 访问控制符，信号默认是public 的;

- ==信号只需像函数那样声明即可==，其中可以有参数，参数的主要作用是用于和槽的通信，这就像普通函数的参数传递规则一样；
- ==信号只需声明，不能对其进行定义==，信号是由moc自动生成的；
- ==信号的返回值只能是void 类型的==。

**发射信号需符合以下规则**：

- ==发射信号需要使用emit关键字==，注意，在emit后面不需要冒号；emit发射的信号使用的语法与调用普通函数相同，比如有一个信号为 void f(int)，则发送的语法为： emit f(3);
- ==当信号被发射时，与其相关联的槽函数会被调用==(注意：信号和槽需要使用QObject::connect 函数进行关联之后，发射信号后才会调用相关联的槽函数)。

<span style=color:red;background:yellow>注意：因为信号位于类之中，因此发射信号的位置需要位于该类的成员函数中或该类能见到信号的标识符的位置。</span>

```C++
emit mySignals();//发送信号
```

<span style=color:red;>emit是一个空宏，没有特殊含义，仅用来表示这个语句是发射一个信号。</span>

-------------------

**自定义槽: **

槽函数是信号的处理动作, 自定义槽函数和普通函数的写法相同

<span style=color:red;background:yellow;font-size:20px>声明槽函数必须遵守以下规则：</span>

- 声明槽需要使用slots关键字， 在其后面有一个冒号“:”，且槽需使用 public、 private、protected 访问控制符之一，但是在Qt5及以后的版本中，其实可以不再强制要求写slots关键字；
- 槽就是一个普通的函数，可以像使用普通函数一样进行使用，槽与普通函数的主要区别是，槽可以与信号关联;

- 槽函数的返回类型必须是void，不能是其它类型；
- 槽函数的参数数量必须小于或等于信号的参数数量。

槽函数类型：

- 成员函数（普通成员函数、静态成员函数）；
- 全局函数；
- 匿名函数（lambda表达式）。

# 三:    对象树























# 四:    属性系统























# 五:    运行时类型信息





































-------------

在qt中多建立堆对象

teacherstudent示例:40min

emit操作默认有一个, 只要调用一下信号函数就能触发信号, 不是必须选emit

qt中建议在数据成员前加上m_  m_number





自定义的类必须直接或者间接的继承自QObject类，并且在自定义类的头文件中包含Q_OBJECT宏。

```c++
#ifndef TEACHER_H
#define TEACHER_H

#include <QObject>

class Teacher : public QObject // 继承自QObject
{
    Q_OBJECT					// 包含Q_OBJECT宏
public:
    explicit Teacher(QObject *parent = nullptr);

signals:

};

#endif // TEACHER_H




#include "teacher.h"

Teacher::Teacher(QObject *parent) : QObject(parent)
{

}

```











# 六







```c++
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MainWindow : public QMainWindow // 继承自 QMainWindow，这是 Qt 提供的标准主窗口类，带有菜单栏、工具栏、状态栏、中心区域等
{
    Q_OBJECT // Q_OBJECT 宏：启用 Qt 的信号与槽机制

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H

-------------------------------------------------

#include "mainwindow.h"

#include <QToolBar>
#include <QAction>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("测试主窗口中的工具栏");
    resize(600, 480);

    QToolBar *tBar = new QToolBar("工具栏", this);
    tBar->resize(300, 100);
    tBar->addAction("AAA");
    tBar->addAction(QIcon("C:\\Users\\lili\\Desktop\\Image\\bee.jpg"), "BBB");
    tBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

}

MainWindow::~MainWindow()
{
}

-------------------------------------------------
    
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
```


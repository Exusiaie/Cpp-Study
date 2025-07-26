# 基本概念

对话框通常会是一个顶层窗口，出现在程序最上层，用于实现短期任务或者简洁的用户交互

对话框与窗口的明显区别在于对话框通常没有最大最小化按钮 

 **继承图:**

<img src="D:\MarkDown\C++Qt\assets\image-20250715110313203.png" alt="image-20250715110313203" style="zoom: 80%;" />  



## 1. 模态对话框

`模态对话框：`在同一个程序中，模态对话框会<span style=color:red;background:yellow;font-size:20px>**阻止**</span>用户与其它可见窗口的交互。而模态对话框有分为两种：

- 应用程序对话框(默认方式)：该模式会阻止用户与应用程序中的所有窗口的交互，直到关闭对话框
- 窗口模式对话框：只阻止与对话框的有亲缘关系的窗口的交互访问，允许用户在程序中继续使用其他窗口

<span style=color:red;background:yellow;font-size:20px>注意：模态对话框不会阻止与其子窗口的交互</span>  

**设置模态对话框的方式:**

- 第一种方式：直接调用exec函数，就可以创建模态对话框，这是一种常用方式。但是该模式会阻塞调用，直到关闭该对话框；
- 第二种方式：可以调用setModal函数或者QWidget::setWindowModality函数，然后调用show函数。

## 2. 非模态对话框

`非模态对话框：`在同一个程序中，非模态对话框<span style=color:red;background:yellow;font-size:20px>**允许**</span>用户与其它可见窗口的交互 



# 四种常用对话框

## 1. 消息对话框 QMessageBox

```c++
QPushButton *messBtn = new QPushButton("消息对话框", this);
messBtn->resize(300, 50);
messBtn->move(100, 200);

connect(messBtn, &QPushButton::clicked, [=](){
        // 四种消息对话框
QMessageBox::critical(this, "严重错误","///!!!///!!!////!!!////");
QMessageBox::information(this, "信息", "一段信息");
MessageBox::question(this, "问题", "出现了问题");
QMessageBox::warning(this, "警告", "警告信息");
```



![image-20250715200006688](D:\MarkDown\C++Qt\assets\image-20250715200006688.png)



## 2. 颜色对话框 QColorDialog

```c++
QPushButton *colorBtn = new QPushButton("颜色对话框", this);
colorBtn->resize(300, 50);
colorBtn->move(100, 300);

connect(colorBtn, &QPushButton::clicked, [=]{
QColor col = QColorDialog::getColor();// 类名调用静态成员函数
qDebug() << "R = " << col.red()
         << "G = " << col.green()
         << "B = " << col.blue();
    });
```

<img src="D:\MarkDown\C++Qt\assets\image-20250715200740652.png" alt="image-20250715200740652" style="zoom:67%;" />





## 3. 字体对话框 QFontDialog

```c++
    QPushButton *fontBtn = new QPushButton("字体对话框", this);
    fontBtn->resize(300, 50);
    fontBtn->move(100, 400);

    connect(fontBtn, &QPushButton::clicked, [=]{
        bool ok;
        QFont font = QFontDialog::getFont(&ok); // 类名调用静态成员函数
        qDebug() << "字体" << font.family()
                 << "字体风格" << font.style()
                 << "字号" << font.pointSize();
    });
```



<img src="D:\MarkDown\C++Qt\assets\image-20250715200837742.png" alt="image-20250715200837742" style="zoom:67%;" />



## 4. 文件对话框 QFileDialog

```c++
QPushButton *fileBtn = new QPushButton("文件对话框", this);
fileBtn->resize(300, 50);
fileBtn->move(100, 500);

QPlainTextEdit *pte = new QPlainTextEdit(this);
pte->move(450, 50);
pte->resize(500, 700);

connect(fileBtn, &QPushButton::clicked, [=]{
	QString path = QFileDialog::getOpenFileName(this, "xxx"						 // 标题
                                                	, "D:/MarkDown" 			  // 打开的文件夹
                                                	, "(*.png);;(*.md);;(*.txt)"); // 筛选显示的文件格式
    qDebug() << "Path = " << path;

    QFile file(path);   // 打开文件
    file.open(QIODevice::ReadOnly); // 指定打开模式
    QByteArray ba = file.readAll(); // 将文件中的数据一次性读完
        // (QByteArray)
    QString msg(ba); // 将ByteArray转为String
    pte->setPlainText(msg);
    file.close();
});
```

![image-20250715201220993](D:\MarkDown\C++Qt\assets\image-20250715201220993.png)

```c++
//函数的作用是：返回用户选择的文件名（路径），但是当用户选择文件时，若选择取消，则返回一个空串。
[static] QString QFileDialog::getOpenFileName(QWidget *parent = nullptr	//parent:标准文件对话框的父窗口;
                 , const QString &caption = QString()	//caption:文件对话框的标题名;
                 , const QString &dir = QString()		//dir:指定了默认的目录，若参数带有文件名，则文件将是默认选中的文件;
                 , const QString &filter = QString()	//filter:对文件类型进行过滤，只有匹配的文件类型才会显示，如果指定多种过滤方式，使用";;"隔开;
                 , QString *selectedFilter = nullptr	//selectedFilter:用户选择多的过滤器通过此参数返回;
                 , QFileDialog::Options options = Options()); //options:选择显示文件名的格式，默认是同时显示目录与文件名.
    
//指定读取文件的格式name
[static] QTextCodec *QTextCodec::codecForName(const char *name)

//将此编解码器的编码转换为Unicode，并以QString形式返回结果。
QString QTextCodec::toUnicode(const QByteArray &a) const
```




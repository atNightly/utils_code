## non-local static对象
什么是non-local?，non-local这个术语其实是我在effective c++这本书中学到的术语，这个术语指的是非函数局部局部用域内的．
那么non-local static对象有指的是什么呢？,其实说到static(不是指static关键字定义的对象)对象，至少可以排除那些内存是在堆中和栈中的对象了，
所谓static对象指的是内存在data段和bss段中的对象．这类对象在整个程序的生命周期内都是存在的，除非程序结束否则会一直存在，利用static关键字声明
的对象是static对象中的一种，但是如果是在函数内部定义的static对象，那么这种static对象被称为local static对象，除此之外的则是non-local static对象　
比如:global作用域内的static对象，namespace作用域内的static对象，类作用域内使用static关键字声明的对象，file作用域内的static对象等．
到此为止我相信我应该是把non-local static对象的含义解释清楚了吧．

## 为什么谈这个话题
其实我也是个C++的小白，自己在读书的过程中喜欢把自己不理解的，或者比较有意思的，很重要的知识点，通过实践和总结写成博客，其实这篇博客的主题就来自于
effective C++(from item 4)．为何这个话题我觉得重要呢，其实C++难学其中有一个原因我认为是C++中存在很多无明确定义的地方．本文就是其中一个．
在C++中对于定义在不同编译单元内的non-local static对象其初始化相对次序是无明确的定义的．主要原因是在于决定它们的初始化次序相当困难，非常困难，或者
说根本无解，至于为什么其实我也不清楚，这是那些搞编译器的人需要做的事情．占且我们认为这是一个未解决的bug吧．先来解释下编译单元这个术语的含义吧，编译
单元在这里指的的要进行编译的.cpp文件，一个.cpp文件就是一个编译单元． 如果在一个场景中，在两个不同的编译单元中存在两个static变量，并且其中一个static变量
利用另外一个进行了初始化．那么很显然这是未定义的．因为两个static对象的初始化顺序是未定义的．为了更加直观，下面例举一个例子，如下:

first.cpp文件
```
#include <iostream>
#include "common.h"
test1 t1;
```
second.cpp文件
```
#include <iostream>
#include "common.h"
test2 t2;
```

last.cpp文件
```
#include <iostream>
#include "common.h"
using namespace std;

int main()
{
    cout << "Hello World" << endl;
    return 0;
}
```
common.h头文件
```
#ifndef _LIB_H_
#define _LIB_H_

#include <iostream>

using namespace std;
class test2;
extern test2 t2;

class test2
{
    public:
        test2()
        {
	    value = 100;
            cout << "test2 construct" << endl;
        }

        void said()
        {
            cout << "I am test2 " << "value=" << value << endl;
        }
    private:
	int value;
};


class test1
{
    public:
        test1()
        {
            cout << "test1 construct" << endl;
            t2.said();
        }
};
#endif
```
定义了test1和test2两个类，在test1中调用了test2类的实例t2．first.cpp和second.cpp分别是t1和t2两个实例的初始化操作．因为两者的初始化顺序不明确，导致
执行的结果是未定义的．下面是执行的结果．

```
#g++ -c -o first.o first.cpp 
#g++ -c -o second.o second.cpp 
#g++ -c -o last.o last.cpp 
#g++ last.o first.o second.o 
#./a.out 
test1 construct
I am test2 value=0
test2 construct
Hello World
#g++ last.o second.o first.o 
#./a.out 
test2 construct
test1 construct
I am test2 value=100
Hello World
```
首先很明确的是t1和t2的初始化是在main函数之前完成的，其实你会发现first.o和second.o编译的顺序影响了最终的输出结果．fisrt.o在前会导致
t1先初始化，然后才到t2初始化，否则t2会先初始化，然后才到t1开始初始化，通过value的值很显而易见．通过上面的例子证实了non-local static对象
存在的这个初始化顺序未定义的问题．

## 解决这个问题
尽管对于C++来说定义在不同编译单元内的non-local static对象其初始化相对次序是无明确的定义没有解决，但是幸运的是只要程序员们稍微通过一个小小的设计就可以完全
消除这个bug，本文的最后一个部分就是来解决这个问题的．利用local static可以解决这个问题，这是因为local static对象会在函数被调用期间，首次遇到该对象的定义式
时被初始化．是不是读起来挺绕口的?好吧，用这个方法改造上面的例子来说明这个问题吧．
first.cpp不需要任何改动，把second.cpp修改成下面的样子:

```
//为了节省篇幅只列出部分代码，头文件部分去掉了
test2& gettest()
{
    static test2 t2;
    return t2;
}
```
common.h 修改成下面这个样子
```
#ifndef _LIB_H_
#define _LIB_H_

#include <iostream>

using namespace std;
class test2;
test2& gettest();  //变成函数声明了
class test2
{
    public:
        test2():value(100)
        {
            //value = 100;
            cout << "test2 construct" << endl;
        }

        void said()
        {
            cout << "I am test2 " << "value" << value << endl;
        }
    int value;
};


class test1
{
    public:
        test1()
        {
            cout << "test1 construct" << endl;
            gettest().said(); //改成通过返回来获取t2的引用
        }
};
#endif
```
原来的non-local static对象t2变成了local static对象，利用了local static对象的一个特性就是不会在编译的时候自动初始化，然后在调用函数的时候
碰到local static对象定义的时候才会对其进行初始化．写过单例的读者应该很清楚这种用法，单例的实现方式中有一种就是利用local static对象来完成的
可以加快程序启动速度，因为local static对象在程序启动的时候不会进行初始化，只有在用的时候才会初始化的．



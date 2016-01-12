## String
一个C++ String有什么好分析的呢，或许有的读者会发出这样的疑问，起初的我也是这么觉得的，但是随着知识的积累，以及实际编程过程中，发现String类
还是有很多的坑的，本文试图揭开一些我所知道的坑，但是我觉得我的能力可能无法全面的解剖,因此我把相关的文章会列出来，方便大家详细的学习，本文主要
来自与我实际编程过程的一些体会，还参考了<<Effecitive C++>>，<<C++编程思想>>下，<<C++ Primer>>，还有coolshell的几篇文章。文章的最后会详细的列出
参考文章的链接。

## 字符串的内部表示
在C语言中，字符串基本就是字符串数组，并且总是以二进制零(也就是空结束符)作为最末元素，C++ String与他们在C语言中的前身截然不同。

* C++ String隐藏了它所保护的字符序列的物理表示，程序设计人员不必关心数组的维数和空结束符方面的问题。
* C++ String对象知道自己在内存中的开始位置，包含的内容，包含的字符长度等信息。
* C++ String可以动态的增长。
因为C++ String有如上诸多的优点，因此，使用C++ String来编程可以极大的减少C语言编程过程中出现的最常见也是最具破坏性的错误。

* 数组越界(C语言中的可变数组的实现恰恰是利用了这个特点)
* 通过未被初始化或被赋以错误值的指针来访问数组
* 释放了数组原先分配的存储单元后仍保留了悬挂指针

## String COW
C++标准并没有规定String类的内存布局，允许不同的编译器厂商有不同的实现方式，有一种String类的实现方式就是基于引用计数来实现的，也就是当String类
发生拷贝的时候拷贝后的字符串和原字符串是共用同一段物理内存，无论使用何种实现方式，对于用户来说这应该都是透明的，所以如果是使用引用计数来实现，那么
当发生字符串修改的时候，就需要打破引用关系进行字符串的拷贝。这就是所谓的COW，将真正的拷贝推迟到字符串发生修改的时候，目的就是为了提供性能，减少不必要
的开销，下面的这段代码，说明了COW的存在。

```
#include <iostream>
#include <string>
#include <cstdio>
using namespace std;

int main()
{ 
   string s1 = "test";
   string s2 = s1;
   printf("s1:%p\n",s1.c_str());
   printf("s2:%p\n",s2.c_str());
}
```
上面的输出结果是相同的，也就是说s1和s2实际上指向的是同一块物理内存(使用的是g++编译器)，也就是说g++版本的编译器的String内部实现使用了引用计数机制，
也就是说在String发生赋值拷贝的时候并不分配内存来实际进行拷贝，而是直接使用内部的```char*```(String类内部维护了一个```char*```的指针指向字符串存储的物理内存)指针来指向目标内存即可，并设置引用计数。如果让你来实现这个功能，你该怎么做呢?，其实也不难想到，只要在string发生赋值或者是拷贝的时候建立引用计数机制，通过指针指向目标内存，因此只需要实现拷贝构造函数，还有重载赋值操作符，在其中实现引用技术机制即可，至于怎么实现引用技术机制，可以参考()[]

下面我们来看看String的COW的性能如何吧:

```
#include <string>
#include <iostream>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

static long getcurrenttick()
{
    long tick;
    struct timeval time_val;
    gettimeofday(&time_val, NULL);
    tick = time_val.tv_sec * 1000 + time_val.tv_usec / 1000;
    return tick;
}

int main()
{
    string the_base(1024 * 1024 * 10,'x');
    long begin = getcurrenttick();
    for(int i = 0; i < 100; ++i) {
        string the_copy = the_base;
    }
    fprintf(stdout,"耗时[%ld]\n",getcurrenttick() - begin);
}
```
上面的程序在我的机器上大概只需要１毫秒都不到，速度还是很可观的，现在我们来稍微修改下代码，再次执行一下。

```
int main()
{
    string the_base(1024 * 1024 * 10,'x');
    long begin = getcurrenttick();
    for(int i = 0; i < 100; ++i) {
        string the_copy = the_base;
        the_copy[0] = 'y'; //加了这一句，修改拷贝后的字符串，触发了实际的拷贝操作
    }
    fprintf(stdout,"耗时[%ld]\n",getcurrenttick() - begin);
}
```
拷贝完成后修改一下，这将导致COW发生实际的拷贝操作，因此上面的这段程序执行完在我的机器上执行了大约200毫秒，差距还真大啊。相信读者们看到这样的事实
会发现String的COW的实现效率真的是没话说的，所以我们在写程序的时候应该尽可能的利用COW，不去触发实际的拷贝操作，神码不去触发实际的拷贝操作，如果字符串拷贝
完成后实际业务需求决定了我一定会去修改字符串，这怎么去避免呢，NO NO NO~~~~，我不是这个意思，其实不修改String也会发生实际的拷贝动作，请看下面这段代码

```
int main()
{
    string the_base(1024 * 1024 * 10,'x');
    fprintf(stdout,"the_base's first char is [%c]/n",the_base[0] );//加了这一句关闭了COW机制
    long begin = getcurrenttick();
    for(int i = 0; i < 100; ++i) {
        string the_copy = the_base;
    }
    fprintf(stdout,"耗时[%ld]\n",getcurrenttick() - begin);
}
```
在我机器上同样大约需要200毫秒，因为fprintf那句话关闭了COW机制，此后的拷贝操作会发生实际的拷贝，不使用引用计数机制，为啥呢?，容我在这里浅析一下，
the_base[0]其实调用的是String类的[]操作运算符，这个操作运算符返回的是内部```char*```的某一个元素的引用，所以我们可以通过如下的表达式来修改String

```
the_base[2] = 'x';
```

假如有一天，有人写出了如下的代码
```
String the_base = "1234567";
char *p = &the_base[4];
String new_string = the_base;
```
请问现在如何保证new_string和the_base互相不影响，如果此时通过指针p修改了the_base中的某一个字符，那么new_string同样也会被修改，因为两者共同同一块
物理内存.这里我是利用p指针来修改String的字符的，所以String无法捕捉字符修改操作，那么因此就没办法进行实际的拷贝操作了，因此C++ String类在实现的
时候发现只要有[]操作运算符发生就会关闭COW机制。

关于COW就说到这里了，上面的代码都来自于这篇文章<<>>，更详细的内容可以阅读下这篇文章。这里我提一点就是多线程环境下，引用计数实现的String类是非线程安全的。
 
##　String的初始化
这个部分谈谈String的初始化吧，首先看看下面几个初始化的例子。

```
String s1;
String s2 = "test1";
String s3(s1);
String s4("test2");
String s5(s2,0,3); //拷贝String s2从第０个字符开始，拷贝3个字符
String s6 = s4 + "test6";
String s7(s6.begin(),s6.end());'
String s8(10,'c'); //初始化为10个字符c
```
看起来String的初始化还是很丰富的啊。这里我想额外谈一下String类，String类其实还是存在很多问题的，具体可以参考这篇文章(STL 的string类怎么啦？)，这里我引用两点
一个就是String类内部有太多的接口实现，代码可读性非常差，其目的就是为了性能，例如下面一组接口

```
bool operator==(const string& lhs, const string& rhs);
bool operator==(const string& lhs, const char* rhs);
bool operator==(const char* lhs, const string& rhs);
```
其目的就是避免在使用string类和char指针做==运算比较的时候，char指针会先隐式转换为String对象再进行比较，有了上面第二个和第三个就避免了隐式转换的开销了。
第二点就是内存碎片的问题，我们都知道String存储字符串是使用堆来存储的，因此这必然会带来大量的内存分配和释放，所以会加剧内存碎片化问题，幸好又补救办法，那就是
可以利用allocator来定制内存分配来避免内存碎片化问题。更详细的内容参见上面提到的这篇文章吧。

## String的操作
C++中的String提供了大量的字符串操作成员函数，几乎跟C库中的函数一样多，但是由于有重载，使String类的功能更加强大，更加易于使用。额外需要提到的一点就是，
使用String的话就不需要在意字符串某尾的空字符了，如果是C语言的话，就需要确保字符串某尾有空字符，否则C的一些标准库可能无法正常工作了。

### String基本操作

```
string s;
s.empty(); //s为空返回true，否则返回false
s.size();  //返回s中字符的个数 
s1 + s2	   //字符串连接
s1 = s2	   //字符串赋值
s1 == s2   //字符串比较
s1 != s2   //字符串比较h
```
这里提一点就是使用size()成员方法的时候返回的是string的大小，这个数值的类型是一个string的内部类型，是string::size_type类型，这是一个无符号类型的值,所以避免在表达式中混用带符号数和无符号,将可能产生意想不到的结果。

### String求子串

string的求子串操作
```
string s;
s.substr(start,end);  //从start开始到end结束这段字符
s.substr(start);      //从start开始到结束的这段字符
```

### string修改操作

```
string s;
s.insert(pos,args); //在pos之前插入args，pos在这里可以是迭代器，也可以是下标
s.append(args);     //字符串的追加
s.erase(pos,len)；  //删除从位置pos开始的len个字符
s.assign(args);	   //把s替换为args，并返回指向s的引用
s.replace(range,args); //删除s中range范围的字符，替换为args指定的字符，range可以是一个下标，也可以是一个长度，还可以是一个指向s的迭代器。
```
下面通过一段代码演示一下replace的使用。

```
#include <iostream>
#include <string>

using namespace std;

int main()
{
	string s = "teststring";
	cout << s.replace(s.begin(),s.begin()+3,"new") << endl;
	cout << s.replace(0,4,"zhang") << endl;
	
}
```
上面介绍到的几个操作还有很多重载方式，args可以有多种形式，可以是一个字符串，也可以是一个string字符串，还可以是一个string对的迭代器等等。这里不详细说了，可以参考<<C++ primer 5th>>中的323页


### String的搜索操作
这个部分提供了很多有关搜索的函数，每个函数都有很多重载版本。每一个搜索操作都返回一个string::size_type类型的值，表明找到的字符再string的下标位置，如果没有找到则会返回string::npos，让我们来看看都有哪些版本的搜索函数吧。

```
string s;
s.find(args);			//查找s中args第一次出现的位置
s.rfind(args);			//逆向查找args最后一次出现的位置
下面四个函数中查找的是args的子集
s.find_first_of(args);		//在s中查找args中任何一个字符第一次出现的位置
s.find_last_of(args);		//在s中查找args中任何一个字符最后一次出现的位置
s.find_first_not_of(args);	//在s中查找第一个不在args中的字符
s.find_last_not_of(args);	//在s中查找最后一个不在args中的字符
```
上面的args可以有多种形似，每一种形式就是一个函数重载，一般情况可以有如下几种形式:

```
c,pos		//pos可以省略默认是0，从s中的pos位置查找字符c
s2,pos		//pos同上，从s中的pos位置查找字符串s2
cp,pos		//pos同上,从s中的pos位置查找cp指针，指向的以空字符串结尾的C风格字符串
cp,pos,n	//pos同上，从s中pos位置查找cp指针指向的以空字符串结尾的C风格字符串
``` 
可见一个简单的搜索操作居然有如此之多的函数重载，可想而知string的内部实现该有多少代码啊。


## 小结
String对于程序员的我们应该知道COW，知道String的线程安全性，会利用String提供的成员函数实现一些功能，而不是重复造轮子。总的来说在C++中我们应该尽量去使用String替换char，毕竟String的优点是大于缺点的。本文主要参考了
C++ Primer，C++编程思想，和陈浩的几篇博文。

## 参考文献


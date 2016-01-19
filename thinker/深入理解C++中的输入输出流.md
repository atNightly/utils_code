## 为什么引入输入输出流?
因为C++兼容C，所以C中的输入输出函数依然可以在C++中使用，但是很显然如果直接把C的那套输入输出搬到C++中肯定无法满足C++的需求，第一点也是最重要的一点那就是C中的输入输出有类型要求，只支持基本类型，很显然这是没办法满足C++的需求的
，因此C++设计了易于使用的并且多种输入输出流接口统一的IO类库。并且还支持多种格式化操作。还可以自定义格式化操作。C++中总体来说有三种输入输出流，第一种就是标准的输入输出，第二种是文件的输入输出，第三种是基于字符串的输入输出流。
C++引入IO流，将这三种输入输出流接口统一起来，使用>>读取数据的时候，不用去官是从何处读取数据，使用<<写数据的时候也不需要管是写到哪里去。

## 标准输入输出流的
最常用的就是标准输出cout，标准输入cin，以及标准错误输出cerr，这三个其实就是istream，ostream这两个类的全局实例。标准的输入和输出流也是大多数情况下我们使用的最多的一种输入输出流了，前面说过，对于IO流来说可以支持自定义类型，
通过给自定义类型重载标准输入和输出流可以让自定义类型支持IO流，通常这也是很方便实现的。下面给出一个具体的例子:

自定义类型Date的实现:
```
class Date
{
  public:
    Date(int year,int month,int day)
         :m_day(day),m_month(month),m_year(year)
    {
    }
    ~Date()
    {
    }
    int getMonth()const {
        return m_month;
    }
    int getDay()const {
        return m_day;
    }
    int getYear()const {
        return m_year;
    }

  private:
    int m_day;
    int m_month;
    int m_year;
};

```
上面是一个自定义类型，如何让其支持输入和输出流？，需要对输出流进行重载，函数原型如下:

```
ostream& operator<<(ostream& os,const Date& d);
```
很显然这个函数不能是成员函数，因为第一个参数必须是输出流类ostream，为了让输出流支持链式表达式，所以函数返回ostream的引用，如果要输入的数据是Date类的私有成员，可以将这个函数设置为Date类的友元函数，本文没有这样做，
因为Date类已经将数据通过public接口输入了。下面是具体实现.
```
ostream& operator<<(ostream& os,const Date& d) {
    char fillc = os.fill('0');
    //设置填充字符,当输出长度小于指定的长度的时候用于进行填充
    os<<setw(2) << d.getMonth() << '-' //setw用来设置输出长度
      <<setw(2) << d.getDay() << '-' 
      <<setw(4) << setfill(fillc) << d.getYear();
      //setfill还原回原来的填充字符
    return os; 
}
```
上面使用了一些操作流的函数，下文会展开来讨论。到此为此为自定义类型添加对输出流的支持就完成了。接下来看看如何重载标准输入流吧，实现如下:

```
istream& operator>>(istream& is,Date& d) {
    is >> d.m_month;
    char dash;
    is >> dash;
    if (dash != '-')
        is.setstate(ios::failbit);
        //设置流错误状态,这使得下面的所有操作都会被忽略
    is >> d.m_day;
    is >> dash;
    if (dash != '-')
        is.setstate(ios::failbit);
    is >> d.m_year;
    return is;
}

```
输入流也很简单，同样它也不能是成员函数，但是在这输入流必须是友元函数，因为这里直接对Date类的私有成员进行了操作，所以需要在Date类的开始处添加友元声明，如下:

```
class Date
{
  public:
	friend istream& operator>>(istream& is,Date& d);
	.....
```

到此为此输入流重载也很简单的实现了，在输入流中用到了setstate这个函数，这是用来设置流的状态的，C++中给流设置了许多状态来，不同的状态效果不同的，在某些状态下将会导致输入输出流无效.这里通过
setstate将流设置为ios::failbit状态，这个状态将导致流不可用.因为这个输入流其实就是要求用户输入按照"-"分割的数字。例如下面是合法的:

```
08-10-2003
8-10-2003
```
因为m_month，m_day，m_year都是整型，所以如果你输入的不是整型那么同样也会导致流出现错误。导致流的状态发生改变。 下面就流的状态来谈谈对IO流操作的影响。

### 流的状态
C++中一共有四种流的状态，这些流状态标志位都是ios类的成员，如下:
```
badbit  发生了致命性错误，流无法继续使用
eofbit  输入结束，文件流物理上结束了，或者是用户按下ctrl+z或ctrl+d结束
failbit io操作失败，主要是操作了非法数据，流可以继续使用，输入结束后也将设置流为failbit
goodbit 一切正常，没有错误发生
```
C++同时也提供了一系列的函数用于测试这些状态位和操作状态位。

```
good() 判断流是否是goodbit状态
bad()  判断流是否是badbit状态
eof()  判断流是否是eofbit状态
fail() 判断流是否是badbit或failbit状态
clear() 清楚流的状态
这些都是io流类的成员函数，无论是标准输入输出流还是文件流还是字符串流，都是有这一系列的函数。
```
那么流的状态到底在什么情况下会发生改变呢，每一种状态会对io流操作产生什么影响呢?，这或许是我对流的状态这个知识点的疑问。下面来看一个例子。 
```
int main()
{
    int a = -1;
    cin >> a;
    cout << "state:"<<cin.fail() << endl;
    cout << a << endl;
}

```
代码很简单，就是从标准输入接收一个数值，然后打印流的状态 ,下面是在不同的输入情况下的输出结果。

```
$ ./a.out 
1
state:0
1
$ ./a.out
q
state:1
0
$./a.out 
state:1
-1
```
第一次是输入了一个数字，正确被接收了，所以状态肯定不是failbit了，第二次输入是一个字符，所以cin会发生错误，流的状态会变成failbit，所以流的状态测试结果是true。但是一个意想不到的效果是a的值居然变成了0。
当io流接收到一个错误的值的时候，io流会使用空值(0)来代替。第三次直接从键盘输入ctrl+d表示流结束，你会发现流的状态变成了failbit，正好对应上文。并且在这种情况下不会对接收变量做任何赋值操作。 

### 处理流错误
在大部分情况下流是很少会出现错误的，但是为了程序的健壮性程序员可能需要使用测试流状态的函数去检测io流是否正常，因为io流出现再C++引入异常之前，所以错误处理方式仍是像C那样去检查错误码或者状态等来判断，因此
C++一方面为了兼容早期的代码另一方面为了迎合异常错误处理，所以在io流错误处理这块可以通过抛出异常来进行错误处理。方法如下:

```
#include <stdexcept>
#include <ostream>
#include <istream>
#include <sstream>
#include <iomanip>

using namespace std;


/*
 *  流发生错误,需要手动查看其状态才能知道,这是早起c++不支持异常导致的,
 *  为了兼容,一致沿用,为了统一使用异常来处理错误,可以使用流的exception函数来设置当发生了指定流状态的时候,触发异常
 *
 */

int main()
{
    
    float a;
    cin.exceptions(ios::failbit);
    try {
        cin >> a; //接收了一个字符,触发了fail
    } catch(const std::ios_base::failure& fail) {
        cout <<"Get a error" << endl;    
        cout << fail.what() << endl;
    }
}
```
通过流的成员函数exceptions来设置当什么为某种状态的时候出发异常。到此为止标准输入输出流相关的内容基本结束了。


## 基于文件的的输入输出流
先看一段文件流使用的基本示列。

```
int main()
{

    ifstream in("in.txt");
    ostream out("out.txt");
    const int sz = 1024;
    char buf[SZ];
    while(in.getline(buf,SZ)) { //每读取一行，然后写到out.txt中
        out << cp << endl;
    }
}
```
所以对于文件输入输出流来说使用方式和标准输入输出流基本是一样的。就这么轻轻送送的操作文件了。getline是一个按行读取的函数，当读取到指定大小的数据还没有遇到换行符就返回。
到遇到eof则getline返回false。如果对C语言中的文件输入输出熟悉的人来说，可能会发现少了打开模式和定位的操作。其实不然，C++也是有的。下面分别介绍下文件流的打开模式和流的定位操作

### 文件流的打开模式

```
 ios::in     打开输入文件,使的现存的文件不会被截断
 ios::out    打开输出文件,意味值是ios::trunc模式
 ios::app    打开文件,进行追加
 ios::ate    打开文件,指向文件末尾
 ios::trunc  打开文件,文件存在就截断旧文件
 ios::binary 按照二进制方式打开文件,默认打开为文本方式

```
可以通过ifstream和ostream声明实例的时候添加第二个参数，这些打开模式还可以通过|操作符来进行组合。这个部分内容很简单在这里就不使用例子演示了。

### 文件流的定位
```
流指针定位
ios::beg    流的开始位置
ios::cur    流的当前位置
ios::end    流的末端位置
```
通过流的seekg成员函数并传入定位的长度和定位的模式来进行IO流的定位操作。下面是一个使用流定位的例子:
```
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
using namespace std;

/*
 *  流指针定位
 *  ios::beg    流的开始位置
 *  ios::cur    流的当前位置
 *  ios::end    流的末端位置
 */

int main()
{
    const int STR_NUM = 5,STR_LEN = 30;
    char origData[STR_NUM][STR_LEN]  = {
        "Hickory dickory dus....",
        "Are you tired of C++?",
        "Well,if you have,",
        "That's just too bad",
        "There's plenty more for us!"    
    };

    char readData[STR_NUM][STR_LEN] = {{ 0 }};
    //二进制输入模式打开
    ofstream out("poem.in",ios::out|ios::binary);
    for(int i = 0; i < STR_NUM;i++)
        out.write(origData[i],STR_LEN);  //可以使用read,write折这样的接口
    out.close();                       //流是可以显示关闭的。

    ifstream in("poen.bin",ios::in|ios::binaray);
    in.read(readData[0],STR_LEN);
    assert(strcmp(readData[0],"Hickory dickory dbus...") == 0);

    in.seekg(-STR_LEN,ios::end);
    in.read(readData[1],STR_LEN);

    assert(strcmp(readData[1],"There's plenty more for us!") == 0);
    //默认是ios::beg定位模式
    in.seekg(3 * STR_LEN);
    assert(strcmp(readData[2],"That's just too bad") == 0);
    //从流的当前位置开始定位
    in.seekg(-STR_LEN * 2,ios::cur);
    in.read(readData[3],STR_LEN);
    assert(strcmp(readData[3],"Well, if you have,") == 0)
}

```
到此为此文件流相关的内容也基本介绍完毕了.

## IO流缓冲
和fopen，fread系列函数一样，C++的输入输出流也是有缓冲机制的，为了避免每次去调用系统调用来获取磁盘的数据，输入输出流加入了缓冲机制，使用streambuf类进行了封装。streambuf内部维护了私有成员来保存缓冲数据
streambuf类提供了一个rdbuf成员函数可以用来读取内部用来保存缓冲数据的私有成员。有了这个rdbuf成员函数就可以简单的完成很多事情，比如可以一次性读取整个文件的内容，而不用使用getline一行一行的读取了。
一个使用rdbuf的例子.
```
#include <fstream>
#include <iostream>
#include <ostream>

using namespace std;


int main()
{
    ifstream in("1.txt");
    ofstream out("1.out");

    out << in.rdbuf(); //copy file 文件一行拷贝
    in.close();
    out.close();

    ifstream in2("1.out",ios::in|ios::out);
    ostream out2(in2.rdbuf()); //out2中的内容是对in2的引用,并不是拷贝

    out2.seekp(0,ios::end); //默认流是在开始处，如果直接往里面写东西会导致覆盖开始处的字符，所以这里将流定位到结束处。
    out2 << "Where does this end up?";
    out2 << "And what about this?";
    in2.seekg(0,ios::beg);
    cout << in2.rdbuf(); //因为out2是对in2的一个引用，in2也会输出上面的两行

}
```

## 基于字符串的输入输出流
字符串流是我感觉和C语言差别最大的一个地方吧，在C++中可以使用输入输出操作符来操作字符串，基于字符串流可以实现像C语言使用scanf那样来分解输入参数，还可以格式化输出，字符串和数字之间的转换等。总之来说字符串流
功能很强大，也是很多C++新手没有掌握的一把利器。先来看一段使用字符串流的代码来分割参数的例子。

利用字符串流实现参数分割，比fscanf好用多了。 同时也实现了字符串转数字的功能
```
#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

using namespace std;

int main()
{
    istringstream s("47 1.414 This is a test"); //用户的输入
    int i;
    double f;
    s >> i >> f; //空白字符为分隔符输入，对输入进行了分割，提取了前面的整型和浮点型
    assert(i == 47);
    //演示了浮点型比较的正规做法
    double relerr = (fabs(f) - 1.414)  / 1.414;
    //double数据进行比较的时候不能使用恒等,应该使用这个epsilon
    //是两个double数的机器最小误差
    assert(relerr <= numeric_limits<double>::epsilon());
    string buf2;
    s >> buf2; //提取this
    assert(buf2 == "This");
    cout << s.rdbuf();  //输入
    cout << endl;
}
```


利用字符串输出流实现了fprintf的效果
```
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main()
{
    cout << "type an in ,a float and a string: ";
    int i;
    float f;
    cin >> i >> f;
    string stuff;
    getline(cin,stuff);
    ostringstream os;
    os << "integer = " << i << endl;
    os << "float = " << f << endl;
    os << "string = " << stuff << endl;
    string result = os.str();
    cout << result << endl;
}

```

## 输出流的格式化
使用过printf的函数的人应该都知道printf可以根据传入格式化字符串来对输入进行格式化，那么C++的输入输出流也不例外同样也是可以对输出流进行格式化的，并且相比与printf来说更易于使用，下面会介绍一些常用的输出流格式化操作。

一些开关标志:
```
ios::skipws 跳过空格(输入流的默认情况，会跳过输入的空格)
ios::showbase 打印整型值时指出数字的基数，比如八进制输出的话就在前面加个0，十六进制输入就在前面加个0x
ios::showpoint 显示浮点值的小数点并阶段数字末尾的零
ios::uppercase 显示十六进制数值的时，使用大写A~F来代替
ios::showpos 显示整数前的加号
ios::unitbuf 单元缓冲区，每次插入后刷新流
```
上面这类是开关标志可以直接使用流的setf成员来设置，使用unsetf来取消。 下面给出一些使用的基本示列:

```
int main()
{
    int a = 14;
    cout.setf(ios::showbase);
    cout.setf(ios::oct,ios::basefield);//设置按照几进制输出
    cout << a << endl; //默认会按照十进制输出14，通过设置ios::oct，会按照八进制输出16，又因为开启了showbase，所以会输出016
}
```

ios::unitbuf是一个很值得探究的标志。如果这个标志没有开启，那么下面的代码在某些编译器上则可能只存入部分字符，

```
int main()
{

    ofstream out("log.txt");
    //当这个选项没有开启的时候,某些编译器仅写入一个字母'o'到文件log.txt
    //开启单元缓冲器后则不会丢失任何数据
    out.setf(ios::unitbuf);
    out << "one" << endl;
    out << "two" << endl;
    abort();
}

```
一些格式化操作:
```
ios::basefield类
//设置按照几进制输出 
ios::dec
ios::hex
ios::oct

ios::floatfield类
//浮点数显示相关
ios::scientific 按照科学计数显示浮点数
ios::fixed  按照固定格式显示浮点数， 

ios::adjustfield类
//数值对齐方式
ios::left   数值左对齐，使用填充字符右边填充
ios::right  数值右对齐 使用填充字符左边填充
ios::internal 数值中间对齐，左右填充
```
这类格式化操作通过setf成员函数来设置，不过需要在第二个参数处填入格式化操作所属于的类别列入cout.setf(ios::dec,ios::basefiled)
还有一类格式化操作，用于设置宽带，填充字符，精度设置等。
```
ios::width()
ios::width(int n)
ios::fill()
ios::fill(int n)
ios::precision()
ios::precision(int n)
```
不带参数的用于返回当前的宽带，填充字符，和精度，带参数的用于设置宽度，填充字符和精度，返回的都是设置之前的值。这个部分使用起来还是很简单的，就不再举例子了。
有的时候是不是感觉使用setf成员函数来设置这些标志位很麻烦，C++为了方便给我们提供了另外一种方式来设置输出格式化操作。如下:

```
比如cout.setf(ios::showbase)可以变成cout << showbase，看起来是不是清爽多了
```
上面的写法是不是清爽多了， C++同时也可以自定义输出格式化操作。鉴于使用的较少这里就不介绍了。可以参考<<C++编程思想 下>>


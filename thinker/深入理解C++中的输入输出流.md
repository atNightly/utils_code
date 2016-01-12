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
因为m_month，m_day，m_year都是整形，所以如果你输入的不是整形那么同样也会导致流出现错误。导致流的状态发生改变。 下面就流的状态来谈谈对IO流操作的影响。

### 流的状态
C++中一共有四种流的状态，这些流状态标志位都是ios类的成员，如下:
```
badbit  发生了致命性错误，流无法继续使用
eofbit  输入结束，文件流物理上结束了，或者是用户按下ctrl+z或ctrl+d结束
failbit io操作失败，主要是操作了非法数据，流可以继续使用，输入结束后也将设置流为failbit
goodbit 一切正常，没有错误发生
```
C++同时也提供了一系列的函数用于测试这些状态位和操作状态位。

## 基于文件的的输入输出流

## 基于字符串的输入输出流

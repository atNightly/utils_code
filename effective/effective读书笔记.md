
## 条款03 尽可能使用const
* 分清顶层const和底层const的区别

```
顶层const指的是const在*号的右边，表示指针本身是一个常量,无法修改对象本身.
底层const指的是const在*号的左边，表示的则是指针所指的对象是一个常量, 无法修改其指向的对象
对于内置数据类型来说const无所谓底层(基本类型没有指向某个对象的意思)的概念,引用本身不是对象
所以也无所谓顶层const，只有指针是比较特殊的。具有顶层const含义和底层const的含义

```
* 两个成员函数如果只是常量性不同，可以被重载
* 当const和non-const成员函数有着实质等价的实现时，令non-const版本调用const版本可以避免代码重复

```
class Test
{
  public:
    //至于为什么要有non-const和const两个版本这是因为bitwise constness 和 logical constness两个流行概念
    const char& operator[](std::size_t position)const {
        //some code 
        return data[position]
    }

    //non-const版本调用const版本,避免代码重复
    char& operatorp[](std::size_t position) {
        //some code
        return const_cast<char&>(
            static_cast<const Test&>(*this)[position]
        );
    }

  private:
    char data[MAX_SIZE];
};
```
* bitwise constness 和 logical constness

```
bitwise constness流派认为成员函数只有在不更改对象中的任何成员变量(static除外)时才可以说是const的
logical constness流派主张一个const成员函数可以修改它所处理的对象内的某些bits，但只有在客户端侦测不出来的情况下
通过给bitwise constness成员函数所要修改的变量加上mutable修饰，就变成了logical constness
```
* const可以在类内部初始化静态成员

```
class Test
{
    public:
    private:
        const static int data = 10; //可以初始化
        //static int data = 10; 错误的，无法在类内部初始化
};

```
## 条款04 确定对象被使用前已先被初始化
C++对于定义不同编译单元内的non-local static对象的初始化次序是未定义的，但是C++保证函数内的local static对象会在函数调用期间首次遇到该对象的定义式时被初始化，那么如果使用函数调用
(返回内部local static对象)替换直接访问non-local static对象就可以解决这个未定义的问题，具体细节详见[non-local static对象初始化顺序](http://blog.csdn.net/zhangyifei216/article/details/50549703)
对于构造函数最好使用成员初值列表，而不要再构造函数本体内使用赋值操作．处置列表列出的成员变量，其排列次序应该和它们在class中的声明次序相同

## 条款06 若不想使用编译器自动生成的函数，就该明确拒绝
* 将相应的成员函数声明为private并且不予实现
* 使用像Uncopyable这样的base class
```
class Uncopyable {
protected:
    Uncopyable() {}
    ~Uncopyable() {}
private:
    Uncopyable(const Uncopyable&);
    Uncopyable& operator=(const Uncopyable&);
};
通过继承Uncopyable就可以阻止编译器生成默认的拷贝赋值函数．
```
* 使用boost库提供的noncopyable

## 条款08 别让异常逃离析构函数
绝对不能在析构函数中抛出异常，为了避免这个问题可以有以下几个办法避免.
* 在析构函数中捕获异常，然后记录异常抛出事件，最后调用abort.
* 在析构函数中捕获异常，然后吞掉.
* 重新设计析构函数，让用户主动去调用可能会跑出异常的成员函数，而不是放在析构函数中调用，在用户没有调用的情况下才在析构函数中调用

## 条款09 绝不在构造和析构过程中调用virtual函数
因为在构造函数和析构函数调用virtual函数的时候，绝对不会下降到derived classes层.例如下面这个例子

```
class Base
{
public:
    Base()
    {
        string str("derived construct");
        log(str);
    }

    virtual void log(string &str)
    {
        cout << "I am base log:" << str << endl;
    }
};


class Derived : public Base
{
public:

    virtual void log(string &str)
    {
        cout << "I am derived log:" << str << endl;
    }
};

//Derived在构造期间会先对Base进行初始化，在初始化Base类的时候，调用虚函数log的时候调用的是Base类的，而不是Derived的．
```
对于这个问题的解决方法就是重新设计，避免使用虚函数，通过在derivied中调用base成员函数的时候传递一些信息来实现．

## 条款10 令operator= 返回一个`reference to *this`
为了让赋值操作可以连锁赋值，那么赋值操作符必须返回一个reference指向操作符的左侧实参,例如下面的例子:

```
class Widget
{
public:
    //.....
    Widget& operator=(const Widget& rhs)
    {
        //....
        return *this;  //返回左侧对象
    }
};
```
这是一个赋值操作符应该遵循的协议，并无强制性，同时还有+=,-=,*=等操作符都需要满足这个需求．

## 条款11 在operator=中处理　"自我赋值"

```
class Bitmap
{
    //....
};

class Widget {
  //....
    Widget& operator=(const Widget& rhs);
private:
    Bitmap *pb;
};
```

先来看一份不安全的operator=实现版本
```
Widget& Widget::operator=(const Widget& rhs)
{
    //证同测试: if(this == &rhs) return *this;
    delete pb;  //如果rhs就是this本身，那么这里将pb的内存释放会出现严重问题．这里需要加上证同测试
    pb = new Bitmap(*rhs.pb);
    return *this;
};
```

尽管加上了证同测试上面的这份代码依然存在很多问题，不具备异常安全性，如果`pb = new Bitmap(*rhs.pb);`出现了异常，那么Widget最终会持有一个被删除了的指针．因此有了第二版operator=的实现

```
Widget& Widget::operator=(const Widget& rhs)
{
    Bitmap *pOrig = pb;  //先记住原来的指针，等new成功了，才删除原来的
    pb = new Bitmap(*rhs.pb);
    delete pOrig;
    return *this;
};
```

通过精心的调整代码的排列顺序现在上面这份代码剧本了异常安全性了，除此之外还有另外一种技术可以实现异常安全性，也就是所谓的copy and swap技术．

```
Widget& Widget::operator=(const Widget& rhs)
{
    Widget temp(rhs);
    swap(temp);
    return *this;
};
```


## 条款13 以对象管理资源
把资源放进对象内，便可以依赖C++的析构函数自动调用机制，确保资源被释放．两个步骤:
* 获得资源后立刻放进管理对象
* 管理对象运用析构函数确保资源被释放

这种以对象管理资源的观念被资源获得世纪便是初始化时机也就是所谓的RAII机制．可以为资源专门创建一个类来管理，也可以把资源交由一些智能指针来管理．
下面是一个使用RAII机制管理的互斥锁资源:

```
#ifndef LIB_MUTEX_H_
#define LIB_MUTEX_H_

#include <iostream>
#include <pthread.h>
#include <boost/noncopyable.hpp>

//mutex资源
class Mutex:boost::noncopyable
{

public:
	Mutex():m_mutex(PTHREAD_MUTEX_INITIALIZER)
	{
			//do nothing
	}	

	~Mutex()
	{
		pthread_mutex_destroy(&m_mutex);
	}

	int Lock()
	{
		return pthread_mutex_lock(&m_mutex);
	}

	pthread_mutex_t *get_mutex()
	{
		return &m_mutex;
	}

	int Unlock()
	{
		return pthread_mutex_unlock(&m_mutex);
	}

private:
	pthread_mutex_t m_mutex;
};

//资源管理类 RAII class
class MutexLockGuard:boost::noncopyable
{
	public:	
		MutexLockGuard(Mutex &mutex):m_mutex(mutex) {
			m_mutex.Lock();
		}

		~MutexLockGuard() {
			m_mutex.Unlock();
		}
	private:
		Mutex& m_mutex;
};
#endif //end of LIB_MUTEX_H_

```
## 条款14 在资源管理类中小心copying行为
* 复制RAII对象，必须一并复制它所管理的资源，所以资源的copying行为决定了RAII对象的copying行为
* 普遍而常见的RAII class　copying行为是，抑制copying，施行引用技术法.

## 条款15 在资源管理类中提供对原始资源的访问
* 一些函数或者是API往往要求访问原始资源，所以每一个RAII class应该提供一个所管理之资源的办法.
* 对原始资源的访问可能经由显示转换或隐式转换，一般而言显式转换比较安全，但隐式转换对客户比较方便．

## 条款17 以独立语句将newed对象置入对象智能指针

```
int priority();
void processWidget(std::shared_ptr<Widget> pw,int priority);
```

对于上面两个函数接口来说，如果使用下面的方法来调用:

```
processWidget(new Widget,priority());
```
上面的调用存在问题，processWidget要求传入的是一个shared_ptr类型的参数，尽管一个Widget可以隐式转换为shared_ptr类型，但是shared_ptr的这个构造函数是explicit，因此上面的调用会失败．
把上面的调用改成下面的形式:

```
processWdget(std::shared_ptr<Widget>(new Widget),priority());
```
现在上面的调用不会出错了，表面上看起来是很好的．但是实际上这种调用方式会导致泄露资源．上面的调用会先计算好参数，然后将参数传递给函数再调用．因此,上面的调用分为以下几步:

* 执行`new Widget`表达式
* 调用std::shared_ptr构造函数
* 调用priority

那么C++会按照什么顺序来执行上面几个步骤呢?这是不定的，唯一可以确定的就是`new Widget`会在std::shared_ptr之前调用，但是priority什么时候调用，这是不一定的．如果priority在`new Widget`之后
在std::shared_ptr之前调用，此时如果priority发生了异常将会导致资源泄露．因此为了避免上述问题应该将上面的语句分离出来．

## 条款18 让接口容易被正确使用，不易被误用
* shared_ptr支持定制删除器，这可以防范DLL问题，可被用来自动解除互斥锁.
DLL问题，就是cross-DLL problem，这个问题发生于，对象在动态链接库(DLL)中被new创建，却在另外一个DLL内被delete销毁．在许多平台上
这一类夸DLL之new/delete成对运用，会导致运行期错误．shared_ptr不存在这个问题，因为shared＿ptr可以定制删除器，那个删除器缺省是来自于shared_ptr所在的DLL中

* 让接口容易被正确使用，不易被误用


## 条款19 设计class犹如设计type

* 新type的对象应该如何被创建和销毁
* 对象的初始化和对象的赋值该有什么样的差别
* 新type的对象如果被passed by value意味着什么?
* 什么是新type的合法值
* 你的新type需要配合某个继承图系
* 你的新type需要什么样的转换
* 什么样的操作符和函数对此新type而言是合理的
* 什么样的标准函数应该驳回?
* 谁该取用新type的成员?
* 什么是新type的未声明接口?
* 你的新type有多么一般化?
* 你真的需要一个新type吗?

## 条款20 宁以pass-by-reference-to-const替换pass-by-value
* pass-by-value会导致无意义的数据成员拷贝,效率低.

```
class person {
public:
    person();
    ~person();
private:
    string name;
    string address;
};

//函数按照pass-by-value的形式接受person
bool validatePerson(person s);
person plato;
bool platoIsOK = validatePerson(plato); 
//这段代码无疑会导致调用person的拷贝构造函数,对形参s进行初始化,然后等待函数运行结束后,s被销毁,在s被拷贝构造的同时,其内部
//维护的name和address同时也会被拷贝.可想而知这代价是巨大的,毕竟这个函数并不需要去修改plato.如果这里换成引用或者指针,那么代价就少很多了.
```
* pass-by-value会导致对象切割问题

```
class Window {
public:
    std::string name() const;
    virtual void display() const;
};

class WindowWithScrollBars:public Window {
public:
    virtual void display() const;
};
```
现在编写一个函数用来打印窗口名称:

```
void printNameAndDisplay(Window w)
{
    std::cout << w.name();
    w.display();
}
WindowWithScrollBars wwsb;
printNameAndDisplay(wwsb)
```
很显然上面的代码产生了切割问题,形参w,会利用wwsb构造成一个Windows对象.为了避免这个问题使用pass-by-reference-const即可.

* 尽量以pass-by-reference-to-const替换pass-by-value,前者通常比较高效,并可以避免切割问题. 
* 以上规则并不适用于内置类型,以及STL的迭代器和函数对象,对它们而言pass-by-value往往比较适当.

## 条款21 必须返回对象时,别妄想返回其reference
* 返回一个指向local stack对象的reference,当函数执行完毕,local stack对象会被析构,这个reference会失效
* 返回一个指向函数内部的heap对象的reference,那么会增加构造函数调用的成本,还要承担负责析构这个head对象的责任
* 返回一个指向local static对象的reference,如果需要再多个线程中调用这个函数,返回reference,那么需要考虑线程安全问题.

综上所述最好不要妄想返回一个reference,可以返回一个value,编译器会帮我们优化的,避免临时对象的构造和析构陈本.

## 条款22 将成员变量声明为private
* 切记将成员变量声明为private,这可赋予客户访问数据的一致性,可细微划分访问控制,允诺约束条件获得保证.并提供class作者以充分的实现弹性.
* protected 并不比public更具封装性

## 条款23 宁以non-member non-friend替换memer函数
面向对象守则要求,数据以及操作数据的那些函数应该绑在一起.一些类相关的便利函数,不适合成为member函数,正确的做法应该是放在同一个namespace中,只要一些核心机能作为成员函数,
这样可增加类的机能扩充性,包裹弹性.减少编译的依赖性.如果把一大堆便利函数放在类的内部,作为成员函数,那么修改或者增加都会导致要重新编译整个类,有些便利函数还不怎么经常使用.
因此应该只把那些每个用户都会经常使用的函数作为类的成员函数.

## 条款24 若所有参数皆需要类型转换,请为此采用non-member函数
如果你需要为某个函数的所有参数进行类型转换,那么这个函数必须是个non-member函数.具体原因见如下分析:

```
class Rational {
public:
    Rational(int numberator = 0,
             int denominator = 1);
    int numerator() const;
    int denominator() const;
private:
    .....
}
```
如果此时给这个类添加一个乘法运算,`operator*` 假设先作为类的成员函数,写法如下:

```
class Rational {
public:
    ....
    const Rational operator* (const Rational& rhs) const;
};
```

目前看起来貌似没什么大问题,来使用一下吧:
```
Rational one(1,8);
Rational two(1,2);
Rational result = one * two; //运行正常
Rational result2 = one * 2; //很好, 2会隐式转换为Rational类
Rational result3 = 2 * one; //错误. 整数2并没有对应的class,也没有operator*成员函数.
```

通过上面的使用可以看出这里的确存在使用问题,不满足交换律,可想而知,`operator*`作为类的成员函数其实并不适合.现在我们来看下,`operator*`作为nn-member函数.

```
const Rational operator* (const Rational& lhs,
                          const Rational& rhs)
{
    return Rational(lhs.nymerator() * rhs.numerator(),
                    lhs.denominator() * rhs.denominator());                          
}
```
现在上面这个函数可以满足交换律了,代码如下:

```
Rational result2 = one * 2;
Rational result3 = 2 * one;
```

## 考虑写出一个不抛出异常的swap函数

异常安全性编程的脊柱,缺省情况下swap动作可由标准程序库提供的swap算法,下面是swap算法的典型实现如下:

```
namespace std {
    template<typename T>
    void swap(T& a,T& b)
    {
        T temp(a);
        a = b;
        b = temp;
    }
}
```

类型T需要支持copy构造函数,和copy assignment操作符.通过上面的代码可以看到缺省的swap实现十分平淡.如果遇到下面的情况
缺省的swap效率是很低下的,当要交换的类是以pimpl手法构建的时候,例如下面这个类:

一个impl手法手机的数据成员类.
```
class WidgetImpl {
  public:
    .....
  private:
    int a,b,c;
    std::vector<double> v;
    ....
}
```

真正的Widget类
```
class Widget {
  public:
    Widget(const Widget& rhs);
    Widget operator=(const Widget& rhs) {
        ....
        *pImpl = *(rhs.pImpl);
    }
  private:
    WidgetImpl *pImpl;
};
```
对于上面这个类来说,缺省的swap算法会赋值三个Widget对象,还会复制三个WidgetImpl对象.效率底下,上面的代码很容易就可以看出
其实只要交换两者的WidgetImpl指针即可.但是默认的swap算法不知道.因此为了让swap更加高效,我们必须特化swap.

```
namespace std {
    template<>  //swap模板特化
    void swap<Widget>(Widget& a,
                       Widget& b)
    {
           swap(a.pImpl,b.pImpl); //调用标准的swap算法                      
    }
}
```
很可惜上面的代码无法通过编译,因为pImpl是私有数据,所以这里需要把这个特化的swap函数变成成员函数,
或者是friend函数.下面是一种解决的办法:

```
class Widget {
    public:
        void swap(Widget& other){
            using std::swap;
            swap(pImpl,other.pImpl);
        }
};

namespace std {
    template<>
    void swap<Widget>(Widget& a,
                       Widget& b)
    {
        a.swap(b);                   
    }
};
```
设置swap成员函数,然后使用全局的特化版本的swap函数调用Widget类的swap成员函数即可.这种做法不只能够通过编译,还和STL容器有一致性.
现在如果把Widget模板化如下:

```
template<typename T>
class WidgetImpl{....};

template<typename T>
class Widget {...};
```

一如既往,在Widget模板类中添加一个swap成员函数,然后偏特化(这里是偏特化,而不是全特化)全局的swap,在全局的swap中调用Widget模板类中的
swap成员函数.

```
namespace std {
    template<typename T>
    void swap<Widget<T>>(Widget<T>& a,
                       Widget<T>& b)
    {
           a.swap(b);                   
    }
}
```
可惜上面的偏特化遇到了问题,C++只允许对class template偏特化, 在function template中偏特化是行不通的.
为此只能使用函数重载解决这个问题.下面是重载版本的swap

```
namespace std {
    template<typename T>
    //注意这里的swap没有swap<Widget> 进行偏特化
    void swap(Wdget<T>& a,
               Widget<T>& b)
    {
        a.swap(b);
    }
}
```
一般而言上面这种写法已经可以解决问题了,但是很可惜其命名空间是std,这个命名空间是一个特殊的命名空间,其管理规则比较特殊.客户可以全特化
std内的templates,但是不可以添加新的templates到std里面,std里面的内容完全由C++标准委员会决定. 那该如何是好?为此我们可以使用一个
non-member swap让它调用member swap,但是不让这个non-member的swap声明为std::swap的特化版本和重载版本. 

```
namespace WidgetStuff {
    ....
    class Widget {
        public:
            Widget(const Widget& rhs);
            Widget operator=(const Widget& rhs) {
                ....
                 *pImpl = *(rhs.pImpl);
            }
        private:
            WidgetImpl *pImpl;
    };
    template<typename T>
    class swap<Widget<T>& a,
               Widget<T>& b)
    {
        a.swap(b);           
    }
}
```
当我们调用swap函数的时候按照C++的名称查找规则总是会先查找到WidgetStuff命名空间下的swap函数.从而使这个问题得到了解决.
到此为止swap已经分析完毕,让我们总结一下吧:

* 提供一个public swap成员函数,让它高效地置换你的类型的两个对象值.
* 在你的class或template所在的命名空间内提供一个non-member swap ,并令它调用上述swap成员函数.
* 如果你正确编写一个class,为你的class特化std::swap,并令它调用你的swap函数.
最后,如果你调用swap,请确定包含一个using声明式,以便让std::swap在你的函数内曝光.然后不加任何namespace修饰符,赤裸裸的调用swap.



## 条款27 尽量少做转型动作
C++ 中提供的四种新式转型

```
1.const_cast<T> (expression)
2.dynamic_cast<T> (expression)
3.reinterpret_cast<T> (expression)
4.static_cast<T> (expression)
```

* const_cast通常被用来将对象的常量性转除.
* dynamic_cast 主要用来执行安全向下转型. (上行转换是安全的,下行转换则不一定是安全的)
* reinterpret_cast 执行低级转型
* static_cast 用来强迫隐式转换

旧式转换仍然合法,但是新式转换较受欢迎, 其原因如下:

* 很容易在代码中被辨识出来
* 各转型操作的目标愈窄化，编译器愈可能诊断出错误的运用

如果你认为转型操作其实什么也没做，只是告诉编译器把某种类型视为另外一种类型．这其实是错误的．比如int和double其实在底层表示是不一样
没办法把一个double，用int的方式解释一下就变成int类型了．底层还是做了一定的转换的．带虚函数的父子类之间的转换，也不是仅仅从编译器
层面，把一种类型解释为另外一种类型而已．

* 如果可以请尽量避免转型操作
* 宁可使用C++ style(新式)转型,也不要使用旧式转型.

## 条款28 避免返回handlers指向对象内部成分
* 返回handlers指向对象的内部成分，等于是破坏了类的封装性
* 返回handlers可能会发生dangling handlers(空悬handler)

## 条款29 为"异常安全"而努力是值得
异常安全的两个条件:

* 不泄露任何资源
* 不允许数据败坏

下面是一个非异常安全实现的函数:

```
class PrettyMenu {
public:
    ...
    void changeBackground(std::istream& imgSrc);  //改变背景图像
    ...
private:
    Mutex mutex;                                  //互斥器
    Image *bzImage;                               //目前的背景图像
    int imageChanges;                             //背景图像被改变的次数
};

void Pretty::changeBackground(std::istream& imgSrc)
{
    lock(&mutex);
    delete bgImage;
    ++imageChanges;
    bzImage = new Image(imgSrc);
    unlock(&mutex);
}
``` 
上面的代码是不具备异常安全的，首先如果new Image发生了异常，那么会导致永远无法unlock锁资源了．导致了资源泄露
并且new Image的异常也会导致数据被破坏，因为原来的bgImage已经被delete了，并且imageChanes被递增了．因此又
导致了数据败坏，两个异常安全的条件都不满足．资源泄露的问题很好解决，可以利用对象来管理资源，在离开作用域后利用
对象的析构函数来释放资源，代码如下:

```
    Lock ml(&mutex);
    delete bgImage;
    ++imageChanges;
    bzImage = new Image(imgSrc);
```
现在只剩下做好一个问题了，数据败坏的问题．条款11中提供了一种方法来避免数据败坏的问题．在删除数据的时候，应该先保存原来的
数据，然后再new一个新的数据，只有在new成功的时候，才会delete原来的数据．此外还可以使用copy-and-swap来避免数据败坏的问题．

异常安全函数的三个基本保证:

* 基本承诺 如果异常被抛出，程序内的任何事物仍然保持在有效状态下，没人任何对象或者数据结构会因此而败坏．可以不是调用函数之前的状态．
* 强烈保证 如果异常被抛出，程序状态不改变，程序会回复到"调用函数之前"的状态．
* 不抛出异常保证 承诺绝不抛出异常

一个异常安全的函数，必须满足上面三个基本保证中的一个．一个强烈保证的实现:

```
//将bzImage按照shared_ptr来管理，只有在new Image成功的情况下，才会delete内内部的指针，因此下面这段代码达到了强烈保证的需求．
    Lock ml(&mutex);
    bzImage.reset(new Image(imgSrc));
    ++imageChanges;
```
除了利用上面的方法来达到强烈保证外,还有一个一般化的设计策略可以达到强烈保证,那就是copy-and-swap,原则很简单,为你打算修改的对象
做出一份副本,然后在那副本上做一切必要的修改,若有任何修改动作抛出了异常,原对象保持未改变的状态.待所有的改变完成后,再与原对象在一个
不抛出异常的操作中置换.基于copy-and-swap达到强烈保证,代码如下:

```
//这里把imageChanges和bgImage通过pimpl idiom手法管理起来
    using std::swap
    Lock ml(&mutex);
    shared_ptr<PMImpl> pNew<new PMImpl(*pImpl);
    pNew->bgImage.reset(new Image(ImageSrc));    //修改副本
    ++pNew->imageChanges;
    swap(pImpl,pNew);                            //置换数据,释放mutex
```

* 异常安全函数即使发生了异常也不会泄漏资源或允许任何数据结构败坏.这样的函数区分为三种可能的保证:基本型,强烈型,不抛出异常型.
* `强烈保证` 往往能够以`copy-and-swap`实现出来,但是"强烈保证"并非对所有函数都可能.
* 函数提供的`异常安全保证`通常最高只等于其所调用的各个函数的`异常安全保证`中的最弱者.
 
## 条款30 透彻了解inlining的里里外外

* inline函数通常置于头文件内,因为大多数编译环境都是在编译过程中进行inline.因为需要知道函数长什么样.
* 所有的virtual函数都不是inlining,因为virtual函数需要等到运行时才知道调用哪个.
* 函数声明为inline,无法随着程序库的升级而升级.一旦程序库中的inline函数改变,那么所有用到程序库中的inline函数的程序都要重新编译
* 大部分调试器对inline函数都束手无策
* 不要因为function template出现在头文件中,就将他们声明为inline. 

## 条款31 将文件间的编译依存关系降至最低
* 如果使用object reference或object pointers可以完成任务,就不要使用objects
* 如果能够,尽量以class声明式替换class定义式.
* 为声明式,和定义式,提供不同的头文件(和标准库一样,只包含声明式的头文件命令为`<classname>fwd`),例如标准库中的iosfwd
包含了iostream各个组件相关的声明式.
* 编译依存最小化的一般构想是,相依于声明式,不要相依于定义式.基于此构想的两个手段是handler classes和Interface classes
* 程序库的头文件应该以`完全且仅有声明式`的形式存在,这种做法不论是否涉及到templates都适用.


## 条款32 确定你的public继承塑模出is-a关系
在C++进行面向对象编程,最重要的一个规则是:public inheritance(公开继承)意味着"is-a"的关系.
public继承"意味着is-a"适用于base classes身上的每一件事情也一定适用于derived classes身上的每一件事情一定也适用于derived classes
身上,因为每一个derived class对象也都是一个base class对象.

## 条款33 避免遮掩继承而来的名称
名称查找规则:
1.local作用域也就是使用变量的成员函数所在的栈幁区域．
2.该成员函数所在类的作用区域
3.基类作用域内
4.基类所在namespace内
5.global namespace内

* derived classes内的名称会遮掩base classes内的名称，在public继承下从来没有人希望如此. 
* 为了让被遮掩的名称再见天日，可使用using声明式，或转交函数．

```
class Base {

 private:
    int x;
 public:
    virtual void mf1() = 0;
    virtual void mf1(int) {cout << "Base::mf1(int)" << endl;}
    virtual void mf2() {cout << "Base::mf2()" << endl;}
    void mf3() {cout << "Base::mf3()" << endl;}
    void mf3(double) {cout << "Base::mf3(double)" << endl;}
};

class Derived:public Base {
 public:
     virtual void mf1() {cout << "Derived::mf1()" << endl;}
     void mf3() {cout << "Derived::mf3()" << endl;}
     void mf4() { cout << "Derived::mf4()" << endl;}
};

int main()
{
    Derived d;
    int x;
    d.mf1();        //运行没问题，调用的是Derived::mf1()
    //d.mf1(x);     //运行错误，Derived遮掩了Base的mf1的名称，因此调用的是Derived::mf1，但是找不到对应的函数
    d.mf2();        //运行没问题 调用的是Base::mf2，名称没有被遮掩
    d.mf3();        //运行没问题 调用的是Derived::mf3()
    //d.mf3(x);     //运行错误，Derived遮掩了Base的mf3的名称，因此调用的是Derived::mf3，但是找不到对应的函数
}
```
通过在Derived类中添加下面的using声明可以解决这个问题

```
class Derived:public Base {
 public:
 //让Derived在其作用域内看到Base类中的mf1和mf3函数，避免了遮掩问题．
 using Base::mf1;
 using Base::mf3;
 ....
    
```

上面的using Base::mf1，会将Base类中所有的名为mf1的重载函数都让其在Derived作用域内可见，如果你只想让mf1中的某一个重载
函数在Derived中可见，就可以使用转交函数，下面是转交函数的使用方法:

```
比如:对于Base中只想让Base::mf1(int)可见，那么可以在Derived中写上一个mf1(int)的函数，然后在内部显示调用Base::mf1(int)
class Derived:public Base {
    ........
    virtual void mf1(int x)
    {
        Base::mf1(x);
    }
    ........
};

```

##　条款34　区分接口继承和实现继承
* 声明一个pure virtual函数的目的是为了让derived classes只继承函数接口
* 声明一个inpure virtual函数的目的，是让derived classes继承该函数的接口缺省实现
* 有的时候带缺省实现的inpure virtual，并不适用与某些派生类，推荐pure virtual+default成员函数
通过inpure virtual函数实现缺省实现，让每个derived classess有一份缺省实现．但是后续的derived classes并不是都适用与这个缺省实现，因此有了一种更好的办法就是使用pure virtual函数来实现，强迫派生类实现重新实现接口，同时提供一个default成员函数，作为缺省实现．可以让派生类调用．　

## 条款35 考虑virtual函数以外的其他选择
NVI(non-virtual interface)手法，它是所谓的Template Method设计模式的一个独特表现形式．这个手法就是令客户通过public non-virtual
成员函数间接调用private virtual函数.



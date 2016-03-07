## 模板参数
C++中的模板最重要的某过于它们的参数了，通过参数可以描绘模板的特性，每一个模板参数都代表了下述内容之一:

* 模板参数可以是一个类型(或者是内置类型，或者是用户自定义类型皆可)
* 模板参数可以是一个编译时常数(通常也成为无类型模板参数)
* 模板参数还可以是其他模板

### 无类型模板参数
对于这种参数类型的模板来说，参数必须是编译时所知的整数值,利用这种参数来创建模板做大的好处就是可以使用栈来作为存储(因为数组的大小在编译时是已知的)，而不是使用动态存储空间来存储数组,C++标准
库中的bitset类模板就是唯一一个使用无类型模板参数。下面通过一个例子来学习下无类型模板参数的使用。

```
#include <cstddef>
#include <bitset>
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <iostream>
using std::size_t;
using std::bitset;

using namespace std;
//这里用的就是无类型模板参数
template<size_t UpperBound> 
class Urand {
  bitset<UpperBound> used;
  public:
    Urand() {srand(time(0));} 
    size_t operator()(); 
};

template<size_t UpperBound>
inline size_t Urand<UpperBound>::operator()() { //重载了()运算符，把Urand当成了仿函数来使用了
    if (used.count() == UpperBound)     //判断是否满了，如果满了就重置
        used.reset();
    size_t newval;
    while(used[newval = rand() % UpperBound]);  //随机产生一个值填充used
    
    used[newval] = true;
    return newval;   
}

int main()
{
    Urand<100> rand;
    cout << rand() << endl;    
}

```

### 默认模板参数
C++98/03的时候只有类模板是支持默认模板参数的，不过幸运的是这个限制在C++11中已经不复存在，下面是默认模板参数的基本使用

```
template<class T,size_t N = 100>
class Stack {
    T data[N];
    size_t count;
public:
    void push(const T& t);         
};

//使用g++ -std=c++11才可以编译通过
template<class T=int>
T sum(T a,T b)
{
    return a + b;    
}

int main() {

    Stack<int> st;//整型的，大小为100的栈
    cout << sum(8.0,9.0) << endl; //结果是17，使用了默认参数int
}  
```
默认模板参数这个部分需要注意一个知识点，也就是默认参数的值只在第一次类定义的时候给出，其它地方不能给出默认参数的值，通过下面的例子可以看出:
```
template<class T,size_t N = 100>
class Stack {
    T data[N];
    size_t count;
public:
    void push(const T& t);
};

template<class T,size_t N = 100>   //这里不能再给出默认参数的值了，编译会出现下面的错误
void Stack<T, N>::push(const T& t) {
    cout << sizeof(data) << endl;
}
编译无法通过，报错如下:
 error: default argument for template parameter for class enclosing ‘void Stack<T, N>::push(const T&)’
 void Stack<T, N>::push(const T& t) {
```

### 模板类型的模板参数
相比于类型模板参数和默认模板参数，模板类型的模板参数要复杂多了。这需要让编译器知道参数是模板类型的，那么在使用模板参数的时候就不得不去遵守一定的写法。下面是使用模板类型参数的一个例子。
```
template<class T>
class Array {
    enum{INIT = 10};
    size_t capacity;
    size_t count;
    T *data;

public:
        Array() {
            count = 0;
            data = new T[capacity = INIT];
        }
        ~Array() {delete [] data;}
        void push_back(const T& t) {
            size_t newCap = 2 * capacity;
            T* newData = new T[newCap];
            for(size_t i = 0; i < count; ++i)
                newData[i] = data[i];

            delete [] data;
            data = newData;
            capacity = newCap;
            data[count++] = t;
        }
};

template<class T,template<class> class Seq> 
class Container {
    public:
        void append(const T& t) {seq.push_back(t);}
        T* begin() {return seq.begin();}
        T* end() {return seq.end();}
    private:
        Seq<T> seq;  //这个必须要有,不能是Seq seq,必须要告诉编译器,Seq是一个模板类型.
};

```
上面的代码中Container使用了模板作为参数,为了让编译器知道Seq是一个模板,因此需要使用`Seq<T> seq`来告诉编译器Seq是一个模板类型.除此之外使用模板类型的模板参数还存在另外一个差异点,那就是默认模板参数的问题,在定义一个带默认
参数的模板类的时候,如果要想把这个模板类作为其它模板的参数,那么其它模板在定义的时候需要加上默认参数的声明.

```
template<class T,size_t N = 10>
class Array {
    private:
        int size;
        T data[N];
    public:
        Array():size(0) {

        }

        void push_back(T num) {

            data[size++] = num;
        }

        T* begin() {
            return &data[0];
        }

        T* end() {
            return &data[N];
        }
};

template<class T,template<class,size_t N = 10> class Seq> //这里关于默认参数的声明必须要写全
class Container {
    public:
        void append(const T& t) {seq.push_back(t);}
        T* begin() {return seq.begin();}
        T* end() {return seq.end();}
    private:
        Seq<T> seq;
};
```

上面的代码中Array中的具有默认参数,那么如果Container如果要使用Array,那么必须有一个带默认参数的模板.这一做法很显然和默认参数仅仅只能在定义的时候出现而相互矛盾.我们再来看另外一个例子,下面这个例子Container模板类使用vector来作为
自己的模板类型参数.

```
template<class T,template<class> class Seq>
class Container {
    public:
        void append(const T& t) {seq.push_back(t);}
        T* begin() {return seq.begin();}
        T* end() {return seq.end();}
    private:
        Seq<T> seq;
};

int main()
{
    Container<int,vector> data;
    data.append(3);
}

```
很可惜上面的代码无法通过编译,因为vector其实有一个默认模板参数,因此如果Container需要使用vector作为自己的数据存储的话,需要有一个和vector一样的默认参数,下面是vector的额模板声明.

```
template<typename _Tp, typename _Alloc = std::allocator<_Tp> >
```

为了让Container可以受用vector,那么必须给Container也添加这样的默认参数,如下:

```
template<class T,template<class U,class _Alloc = std::allocator<U> > class Seq>
class Container {
    public:
        void append(const T& t) {seq.push_back(t);}
        T* begin() {return seq.begin();}
        T* end() {return seq.end();}
    private:
        Seq<T> seq;
};

```
现在Container就可以使用vector了.

### typename和class关键字
以前一直以为typename是用来取代class的,但是不知道如何取代,也不清楚class除了名字有点混淆外还有什么缺点.看了编程思想后才知道typename的用途不在于模板中,而是体现在下面的代码中

```
template<class T>
class Test
{
   T::size_t data;
};
```
上面的代码无法编译通过,原因在于编译器不认为T::size_t是一种类型,通过在T::size_t的前面加上typename关键字就可以解决这个问题,typename关键字告诉编译器将T::size_t解释为一种类型.因此typename最大的
用途是在这里,而不是在模板中替换class,替换class的主要目的是在于命名清晰而已.

### 成员模板
何为成员模板呢?成员模板指的就是在另外一个类或者类模板中声明模板,举一个例子就是C++标准库中的complex模板类,下面是complex类中的一个成员模板的声明

```
template<typename T>
class complex {
public:
    template<class X> complex(const complex<X>&);
    ......
};
```
如何去使用上面的这个成员模板呢?,来看看下面这个例子

```
complex<float> z(1,2);
complex<double> w(z);
```

z是float类型的complex类,w是double类型的,但是却使用了float类型的z来进行初始化,很显然要完成这样的初始化w和z的类型需要兼容,可以互相隐式转换.此时我们称w中所用的拷贝构造函数为泛化拷贝构造函数.成员模板的最大用途就在这里了
具体关于成员模板的用途可以看下<<Effective C++>>中45条款"运用成员函数模板接受所有兼容类型"，在这个条款中详细描述如果利用成员函数模板来实现接受所有兼容类型的．除此之外成员模板也可以是一个类模板．

一个使用成员类模板的例子．
```
template<class T>
class Outer {
    public:
        template<class R>
        class Inter {
            public:
                void f();
        };
};

template<class T>
template<class R>
void Outer<T>::Inter<R>::f() {
    cout << "Outer == " << typeid(T).name() << endl;
    cout << "Inner == " << typeid(R).name() << endl;
    cout << "Full Inner == " << typeid(*this).name() << endl;
}
```
所以总的来说，成员模板分成了成员类模板和成员函数模板，用途最大的就是成员函数模板， 这在effective c++中有详细的介绍．

## 函数模板
### 函数模板参数的类型推导
你可以明确指出函数模板的参数的，你也可以使用函数模板参数的类型推导，那么推导的规则是什么样的呢?

```
template<typename T>
void test(T a, T b)
{
    cout << "I am template func" << endl;    
}

int main()
{
    int a = 2;
    char c = 'a';

    test(a,c); //调用失败
    test(a,a); //调用的是模板函数，因为类型完全和模板函数匹配
    test(c,c); //调用的是模板函数
    test(c,a); //调用失败
    test<>(c,c); //通过加上<>强制使用模板函数
}

```
相信通过上面的几个例子，对于函数模板参数的类型推导应该比较清楚了.函数模板要求类型完全一致．

```
template<typename T>
const T& min(const T& a,const T& b) {
    return (a < b) ? a:b;
}
```

上面的例子很显然返回值类型是T，因为参数类型都是T，经过运算很显然也是T,如果把上面的模板改成下面的样子．
```
template<typename T,typename X>
const T& min(const T& a,const X& b) {
    return (a < b) ? a:b;
}
```

上面的例子中如果返回值类型继续是T就不合理了，那么该如何解决这个问题呢，C++11中有了完美的解法方案．叫做后置类型推导．来看看怎么用吧．

```
template<typename T,typename X>
auto min(const T& a,const X& b) ->decltype((a < b)? a:b)
{
    return (a < b) ? a:b;
}

```

### 函数模板重载
```
template<typename T>
void test(T a, T b)
{
    cout << "I am template func" << endl;    
}

void test(int a,char c)
{
    cout << "I am normal func" << endl;    
}

void test(char a,char c)
{
    cout << "I am specific func" << endl;    
}

int main()
{
    int a = 2;
    char c = 'a';

    test(a,c); //调用noraml func,类型和模板函数不是严格匹配
    test(a,a); //调用的是模板函数，因为类型完全和模板函数匹配
    test(c,c); //调用的是specific func，优先选择普通函数
    test(c,a); //调用specific函数，因为第一个参数是完全匹配的，第二个参数会进行隐式转换．
    test<>(c,c); //通过加上<>强制使用模板函数
}

```
通过上的例子应该清楚了，在函数模板出现重载的情况下，如何选择函数．第一就是函数模板要求类型完全匹配，第二则是当函数模板和普通函数都完全匹配的时候，优先调用普通函数．接着来看下返回值类型推导的问题

### 以一个已生成的函数模板地址作为参数
在很多情况下需要获得一个函数的地址，这个函数可以是函数模板生成的，那么对于这种是函数模板生成的函数来说，使用的时候需要注意一些什么呢?
```
template<typename T>
void f(T*) {
    //NULL
}

void h(void (*pf)(int*)) {
    //NULL
}

template<typename T>
void g(void (*pf)(T*)) {
    //NULL
}

int main() {
    h(&f<int>);　　//f需要生成和h的参数一致的函数
    h(&f);       //交由编译器进行类型推导
    g<int>(&f<int>); //类型要完全一致
    g(&f<int>); //g的类型是由编译器进行推导
    g<int>(&f); //f的类型也是由编译器进行推导
}
```
通过上面的例子可以知道，在使用函数模板生成的函数作为函数参数的时候需要类型一致，或者交由编译器推导，但是一定要是编译器可以推导的，如果上面的例子写成g(&f)那么编译器就会报错了，因为无法推导．两者知道其中一个，就可以
通过编译器来推导另外一个的类型．

### 函数模板的半有序
普通函数和函数模板在匹配的时候有所谓的优先级，普通函数优先匹配，如果函数模板之间发生了重载，那该如何匹配呢，为了解决函数模板匹配的问题，系统为这些函数模板定义了次序，在生成模板函数的时候，编译器将从这些函数模板中选择
特化程序最高的模板．

```
template<class T> void f(T);
template<class T> void f(T*);
template<class T> void f(const T*);
```
任何类型都可以匹配到第１个模板，第2个模板比第１个模板特化程度更高，因为只有指针类型才能够匹配它．下面这段代码演示了上面几个函数模板的调用规则．

```
using namespace std;
template<typename T>
void f(T) {
    cout << "T" << endl;
}

template<typename T>
void f(T*) {
    cout << "T*" << endl;
}

template<typename T>
void f(const T*) {
    cout << "const T*" << endl;
}

int main() {
    f(0);   //输出T
    int i = 0;
    f(&i);  //输出T*
    const int j = 0;
    f(&j);  //输出const T*
}
```

调用f(&i)和第1个模板匹配了，也和第2个模板匹配了，但是第2个模板的特化程度更高，因此这里最终调用的是第2个模板，同理f(&j)会匹配全部，但是只有第3个模板特化程度最高．如果一组重载的函数模板中没有特化程序最高的模板就会出现
二义性，编译器将会报错．这种特征称之为函数模板的半有序．

## 模板特化
### 显示特化
下面是一个模板特化的例子

```
#include <iostream>
#include <cstring>

using std::strcmp;
using std::cout;
using std::endl;

template<class T>
const T& min(const T& a,const T& b) {
    return (a < b) ? a : b;
}

//模板特化，这里是完整的显示特化，
template<>
const char* const& min<const char*>(const char* const& a, const char* const& b) {
    return (strcmp(a,b) < 0) ? a:b;
}

int main() {
    const char *s2 = "say \"Ni-!\"", *s1 = "knights who";
    cout << min(s1,s2) << endl;
    cout << min<>(s1,s2) << endl;
}
```

### 半特化
半特化是相对于完整的显示特化而言的，半特化中指的是模板参数至少还有一个是开放的．下面是一个半特化的模板．

```
template<typename T,typename U>
class C {
    public:
        void f() {cout << "Primary Template\n";}
};

template<typename T,typename U>
//模板的半特化，支队部分模板参数进行了特化
class C<T,double> {
    public:
        void f() {cout << "doubel\n";}
}
``` 


## 名称查找

## 模板编程技巧

## 模板元编程

## 模板编译模型

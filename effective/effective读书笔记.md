
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

```


# 深入理解C++中的运行时类型识别

## 静态类型和动态类型
C++是一种静态类型的语言，也就是说变量的类型在编译的时候就已经确定了，通常指的是变量定义时左侧的类型声明符，就代表了这个变量的类型．如下:
```
char *p;//p是一个char *类型
exception b;//b是一个exception类型
.....
```
C++为了引入多态了就出现了动态类型的概念，也就是在运行时决定其类型．但是只有指针有动态类型的概念，至于是何种动态类型，取决于指针指向的类型，如下:
```
drived q;
base *p = &q; //p的静态类型是base，动态类型是drived 
```
通过引入动态类型实现了所谓的多态，像python这种动态类型的语言，变量的类型都是在运行时所决定的，这带来了很多便捷之处，在C++中引入了运行时类型识别的
机制来达到某些便捷的目的．但是C++中实现运行时类型识别需要依靠虚函数表和动态类型来实现．但是当我们使用基类对象的指针执行某个派生类操作，并且该操作
不是虚函数，编译器就无法根据指针指向的动态类型自动选择正确的函数版本了．这个时候C++给我们提供了一个dynamic_cast运算符来实现这种场景下的运行时类型
识别，此外C++还提供了一个typeid运算符用于返回表达式的类型．总的来说C++中的RTTI(run-time type identification)机制就是由动态类型，虚函数表，dynamic_cast
运算符，还有typeid运算符等组成的.本文不打算谈论虚函数表来实现RTTI，对于这个部分的内容可以参考陈浩的一篇文章<<C++虚函数表解析>>(http://blog.csdn.net/haoel/article/details/1948051)．本文主要谈论dynamic_cast运算符和typeid运算符．

## 运行时类型识别 

## dynamic_cast运算符

## typeid运算符

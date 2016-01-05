## 模板和泛型编程
### 函数模板
### 实例化函数模板
### 模板类型参数
### 非类型模板参数


## 函数模板和普通函数的关系
1.是重载关系
2.优先级关系
    1.普通函数的参数类型会隐式类型转换
    2.模板函数要求参数类型严格匹配
    3.当参数严格匹配的情况下，优先调用函数模板
    4.当普通函数和函数模板参数一致的时候优先调用普通函数
    5.当普通函数和函数模板参数一致的时候，如果要用模板函数就添加<>，强制使用模板函数

```
#include <iostream>
using namespace std;

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

    test(a,c); //调用普通函数,类型和模板函数不是严格匹配
    test(a,a); //调用的是模板函数，因为类型完全和模板函数匹配
    test(c,c); //调用的是specific函数，优先选择普通函数
    test(c,a); //调用specific函数
    test<>(c,c); //通过加上<>强制使用模板函数
}

```

## 函数模板机制研究
两次编译实现．不负责产生能处理所有类型的函数
只会生成
1.第一次　在声明的地方对模板本身代码进行编译
2.第二次  在调用的地方对参数替换后进行编译


## 类模板碰到友元函数

1.声明和定义
在class中需要使用如下声明方式

```
    friend RETURN_TYPE FUNC_NAME <T>(...,CLASS_VAR<T>);
```
然后在class后进行定义
```
template<typename T>
RETURN_TYPE FUNC_NAME(...CLASS_VAR<T>);

```

## 类型转换
static_cast
reinterpreter_cast
dynamic_cast
const_cast


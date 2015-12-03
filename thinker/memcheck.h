#ifndef MEMCHECK_H
#define MEMCHECK_H

//基本思路:
//memMap全局数组，维护，申请地址信息，和__FILE__,__LINE
//每次申请地址需要维护memMap，也就是初始化一个信息
//每次delete的时候需要从memMap中去除地址信息
#include <cstddef>
//new的两种重载方式
void* operator new(std::size_t,const char*,long);
void* operator new[](std::size_t,const char*,long);

//new的重定义 new int 转换为 new(__FILE，__LINE__) int 再将int插入其中
#define new new (__FILE__,__LINE__)

extern bool traceFlag;
#define TRACE_ON()  traceFlag = true
#define TRACE_OFF() traceFlag = false

extern bool activeFlag;
#define MEM_ON() activeFlag = true
#define MEM_OFF() activeFlag = false

#endif // MEMCHECK_H

#ifndef TEST_H_
#define TEST_H_

#include <string>
#include <cassert>
#include <iostream>

using std::string;
using std::ostream;
using std::cout;

#define test_(cond) \
    do_test(cond,#cond,__FILE__,__LINE__)

#define fail_(str)  \
    do_fail(str,__FILE__,__LINE__);

namespace TestSuite {

class Test {
    //指向输出，可用来实现输出重定向，也可以重定向到文件
    ostream* osptr;
    long nPass;
    long nFail;
    //支持拷贝构造
    Test(const Test&);
    Test& operator=(const Test&);
    //子类可以访问
    protected:
        void do_test(bool cond,const string& lbl,
                     const char* fname,long lineno);
        void do_fail(const string& lbl,
                     const char* fname,long lineno);
    //用于初始化重定向，是重定向到标准输出还是文件
    public:
        Test(ostream* osptr = &cout) {
            this->osptr = osptr;
            nPass = nFail = 0;    
        }
    //多态 父类指针指向子类析构的时候，可以去调用子类的析构函数
    virtual ~Test() {};
    //子类需要实现的
    virtual void run() = 0;
    //信息获取
    long getNumPassed()const {return nPass;}
    long getNumFailed()const {return nFail;}
    //设置和获取输出流
    const ostream* getStream()const {return osptr;}
    void setStream(ostream* osptr) {this->osptr = osptr;}
    void succeed_() {++nPass;}
    //统计报告输出
    long report()const;
    //计数器重置
    virtual void reset() {nPass = nFail = 0;}
    
};
} // end of namespace TestSuite
#endif // TEST_H

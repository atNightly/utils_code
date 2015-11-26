#include "TestSuite.h"
#include <iostream>
#include <typeinfo>

using namespace std;
using namespace TestSuite;

//进行测试
void Test::do_test(bool cond,const std::string& lbl,
                   const char* fname,long lineno) {
    if(!cond)
        do_fail(lbl,fname,lineno);
    else
        succeed_();    
}

//失败情况下，打印错误信息
void Test::do_fail(const std::string& lbl,
                   const char* fname,long lineno) {
    ++nFail;
    if(osptr) {
        *osptr<< typeid(*this).name()
             << "failure: (" << lbl << "). " << fname 
             << " (line "<< lineno << ")" << endl;   
    }    
}
//统计报告输出
long Test::report()const {
    if(osptr) {
        *osptr << "Test \"" << typeid(*this).name()
               << "\":\n\tPassed:" << nPass
               << endl;    
    }    
    return nFail;
}

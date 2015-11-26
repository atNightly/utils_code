#ifndef _LIB_EXCEPTION_H_
#define _LIB_EXCEPTION_H_

#include <exception>
#include <string>
using namespace std;

class Exception : public std::exception
{

public:
	//构造函数
	explicit Exception(const char* what);
	explicit Exception(const string& what);
	//析构函数
	virtual ~Exception()throw();
	//what打印产生异常的原因
	virtual const char* waht() const throw();
	//堆栈回朔
	const char *stackTrace()const throw();
private:
	void fillStackTrace();
	string m_message;
	string m_stack;
};



#endif //end of _LIB_EXCEPTION_H_

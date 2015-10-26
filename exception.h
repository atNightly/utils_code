#ifndef _LIB_EXCEPTION_H_
#define _LIB_EXCEPTION_H_

#include <exception>
#include <string>
class Exception : public std::exception
{
	public:
			//调用fillStackTrace,并初始化what，异常信息
			explicit Exception(const char* what);
			explicit Exception(const string& what);
			//free
			virtual ~Exception()throw();
			virtual const char* waht() const throw();
			const char *stackTrace()const throw();
	private:
			void fillStackTrace();
			string m_message;
			string m_stack;
}


#endif //end of _LIB_EXCEPTION_H_

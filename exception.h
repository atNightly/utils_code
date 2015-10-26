#ifndef _LIB_EXCEPTION_H_
#define _LIB_EXCEPTION_H_

#include <exception>
#include <string>
class Exception : public std::exception
{
	public:
			explicit Exception(const char* what);
			explicit Exception(const string& what);
			virtual ~Exception()throw();
			virtual const char* waht() const throw();
			const char *stackTrace()const throw();
	private:
			void fillStackTrace();
			string m_message;
			string m_stack;
}


#endif //end of _LIB_EXCEPTION_H_

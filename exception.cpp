#include <exception>
#include <string>

Exception::Exception(const char* what)
					: m_message(what)
{
	fillStackTrace();
}


Exception::Exception(const string& what)
					:m_message(what)
{
	fillStackTrace();
}


Exception::~Exception()throw()
{
	
}

const char* Exception::waht() const throw()
{
	return m_message.c_str();
}

const char * Exception::stackTrace()const throw()
{
	return stack.c_str();
}

void Exception::fillStackTrace()
{
	const int len = 200;
	void *buffer[len];
	int nptrs = ::backtrace(buffer,len);
	char **strings = ::backtrace_symbols(buffer,nptrs);
	if (strings) {
		for(int i = 0;i < nptrs;++i)
		{
			m_stack.append(string[i]);
			m_stack.push_back("\n");
		}
		free(strings);
	}
}


#endif //end of _LIB_EXCEPTION_H_

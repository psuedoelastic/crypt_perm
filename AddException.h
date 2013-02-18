#ifndef ADDEXCEPTION_H
#define ADDEXCEPTION_H
#include <exception>

class AddException:public std::exception
{
	virtual const char* what() const throw()
	{
		return "not valid composition";
	}
};

#endif

#ifndef ADDEXCEPTION_H
#define ADDEXCEPTION_H
#include <exception>
// клас-виняток - невалідне додавання

class AddException:public std::exception
{
	virtual const char* what() const throw()
	{
		return "Невірне додавання";
	}
};

#endif

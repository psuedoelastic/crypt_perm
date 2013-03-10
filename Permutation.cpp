/*
 * Copyright (c) Jenia Grubian
 * Licensed under GPLv2
 * Class Permutation represents methods to operate with Permutation of numbers
 */

#include "Permutation.h"
#include "AddException.h"
#include <sstream>

Permutation::Permutation(const u_char n, u_char* a) : numbers(a), k(n)
{
	
}

Permutation::Permutation(const u_char k) : k(k) 
{
	numbers=new u_char[k];
	for (int i=0; i<k; i++)
	{
		numbers[i]=i+1;
	}
}

Permutation::Permutation() : k(0)
{
	numbers=0;
}

Permutation::~Permutation()
{
	delete[] numbers;
}

int Permutation::NumberOfInversions() 
{
	int rez = 0;
   	for (int i=0; i<k; i++)
	{
		u_char head = numbers[i];
		for (int j=i+1; j<k; j++)
		{
			if (head > numbers[j]) rez++;
		}
	}
	return rez;
}

bool Permutation::IsEven()
{
    if (NumberOfInversions() % 2 == 0) return true;
	return false;
}

bool Permutation::IsNeutral()
{
	bool fl=true;
	for (int i=0; i<k; i++)
	{
		if (numbers[i]!=i+1) fl=false; 
	}
	return fl;
}

Permutation operator+(const Permutation& p1, const Permutation& p2)
{
	if (p1.k != p2.k) throw new AddException();
	else 
	{
		u_char n=p1.k;
		u_char* rez = new u_char[n];
		for (int i=0; i<n; i++)
		{
			rez[i] = p2.numbers[p1.numbers[i]-1];
		}
		return Permutation(p1.k, rez);
	}
}

Permutation operator-(const Permutation& p) 
{
	u_char n=p.k;
	u_char* rez = new u_char[n];
	for (int i=0; i<n; i++)
	{
		rez[p.numbers[i]-1] = i+1;
	}
	return Permutation(p.k, rez);
}

bool operator==(const Permutation& p1, const Permutation& p2)
{
	if (p1.k!=p2.k) return false;
	else 
	{
		u_char k_=p1.k;
		for (int i=0; i<k_; i++)
		{
			if (p1.numbers[i]!=p2.numbers[i]) return false;
		}
		return true;
	}
}

bool operator!=(const Permutation& p1, const Permutation& p2)
{
	return !(p1==p2);
}

std::string Permutation::Content() const
{
	std::string r;
	std::stringstream s(r);
	for (int i=0; i<k; i++)
		s << numbers[i];
	return s.str();
}
                 
u_char Permutation::operator[](int i) const
{
	char r=numbers[i];
	return r;
}
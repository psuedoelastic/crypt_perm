/*
 * Copyright (c) Jenia Grubian
 * Licensed under GPLv2
 * Class Permutation represents methods to operate with Permutation of numbers
 */

#ifndef PERMUTATION_H
#define PERMUTATION_H
typedef unsigned char u_char;
#include <string>

class Permutation
{
	private:
		u_char* numbers; 
	
	public:
		const u_char k; // number of elements in permutation

		/* 
		 * constructor to init permutation with two arguments: 
		 * number of elements and ptr to int array that represents elements in permutation
		 */
	    Permutation(const u_char, u_char*); 

	    /* constructor that init neutral permutation with one argument: number of elements */
		Permutation(const u_char); 

		/* constructor that does not init permutation setting number of elements to zero */
		Permutation(); 

		~Permutation(); 

		int NumberOfInversions(); 
		bool IsEven(); 
		bool IsNeutral(); 

		/* method that returns string representing permutation, for example "23514" */
		std::string Content() const; 

		/* composition of two permuattion */
		friend Permutation operator+(const Permutation&, const Permutation&); 

		/* inverse permutation */
		friend Permutation operator-(const Permutation&);

		friend bool operator==(const Permutation&, const Permutation&); 
		friend bool operator!=(const Permutation&, const Permutation&);

		/* operator that returns i element in permutation */
		int operator[](int i) const;
		
};

#endif

/*
 * Copyright (c) Jenia Grubian
 * Licensed under GPLv2
 * Class Permutation represents methods to operate with Permutation of numbers
 */

#ifndef PERMUTATION_H
#define PERMUTATION_H

#include <string>

class Permutation
{
	private:
		int* numbers; 
	
	public:
		const int k; // number of elements in permutation

		/* 
		 * constructor to init permutation with two arguments: 
		 * number of elements and ptr to int array that represents elements in permutation
		 */
	    Permutation(const int, int*); 

	    /* constructor that init neutral permutation with one argument: number of elements */
		Permutation(const int); 

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

/*
 * Copyright (c) Jenia Grubian
 * Licensed under GPLv2
 * Simple cryptography library that uses permutations to encrypt and decrypt byte array
 */

#ifndef CRYPT_PERM_H
#define CRYPT_PERM_H

#include <bitset>
#include <vector>
#include <cstring>

typedef unsigned int u_int;
typedef unsigned char u_char;

struct Block 
{
	std::bitset<8>* bytes;
	const u_int size;
	Block(int n) : size(n/8) { bytes = new std::bitset<8>[n/8]; }
	Block() : bytes(0), size(0) {}
	//~Block() { delete[] bytes; }
	std::bitset<8>::reference operator[](u_int i) { return bytes[i/8][i%8]; }
	Block& operator=(const Block& block) { return *this; }
};

/* 
 * Two functions that implement permutation encryption/decryption methods.
 * They take permutation(key of the cipher) and byte array that is needed to be encoded or decoded
 */

const char* encode(int*, char*);

const char* decode(int*, char*);

/* Function that aligns byte array depended on number of blocks */ 
void align(char*, u_int);

/* Function that explodes byte array into blocks of bits */
std::vector<Block> bytesToBitsetArray(char*, u_int);

/*  */
int* reverse(const int*);
/* note: to convert const char* to char* use strdup() */
#endif /* CRYPT_PERM_H */

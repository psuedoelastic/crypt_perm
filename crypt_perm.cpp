/*
 * Copyright (c) Jenia Grubian
 * Licensed under GPLv2
 * Simple cryptography library that uses permutations to encrypt and decrypt byte array
 */

#include "crypt_perm.h"
#include <iostream>

void align(char* data, int block_len)
{
	int numBytes = strlen(data);
	if (numBytes%block_len!=0) 
	{
		char* tmp = new char[numBytes + numBytes%block_len+1];
		strcpy(tmp, data);
		for (int i=numBytes; i<numBytes + numBytes%block_len; i++) tmp[i]=' ';
		tmp[numBytes + numBytes%block_len]='\0';
		strcpy(data, tmp);
	}
}

template <int block_len>
std::vector< std::bitset<block_len> > bytesToBitsetArray(char *data)
{
	int numBytes = strlen(data);
	int numKeyBytes = block_len / 8;
	int numBlocks;
	if (numBytes%numKeyBytes==0)
		numBlocks = numBytes * 8 / block_len;
	else
		numBlocks = numBytes * 8 / block_len + 1;
	align(data, block_len);

    std::vector< std::bitset<block_len> > b(numBlocks);

    for(int i = 0; i < numBlocks; ++i)
    {
        char block[numKeyBytes];
        char cur;
        for (int j = 0; j < numKeyBytes; ++j) 
        	block[j] = data[i+j];
        for(int bit = 0; bit < block_len; ++bit)
        {
        	cur = block[bit/8];
        	b[i][bit] = cur & 1;
           	cur >>= 1;  
        }
    }

    return b; 
}

const char* encode(const Permutation& perm, char* text) 
{
	int block_len = perm.k;
	if (block_len & (block_len-1)) return "invalid permutation, number of elements must be power of 2";
	int numKeyBytes = block_len /8;
	int numBytes = strlen(text);
	int alignedBytes = numBytes + numBytes%keyBytes;
	int numBlocks = alignedBytes / numKeyBytes;
	char* out=new char[alignedBytes + 1];
	out[alignedBytes]='\0';
	std::vector< std::bitset<block_len> > bytes = bytesToBitsetArray<block_len>(text);
	for (int i=0; i<numBytes; ++i)
	{
		std::bitset<block_len> cur;
		for (int bit=0; bit<block_len; ++bit) 
		{
			cur[bit]=bytes[i][perm[bit]-1];
		}
		for (int j=0; j<numKeyBytes; ++j) {}
		out[i]=char(cur.to_ulong());
	}
	return out;
}

const char* decode(const Permutation& perm, char* text)
{
	return encode(-perm, text);
}

/*
 * Copyright (c) Jenia Grubian
 * Licensed under GPLv2
 * Simple cryptography library that uses permutations of 8 numbers to encrypt and decrypt byte array
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
	int keyBytes = block_len / 8;
	int numBlocks;
	if (numBytes%keyBytes==0)
		numBlocks = numBytes * 8 / block_len;
	else
		numBlocks = numBytes * 8 / block_len + 1;
	align(data, block_len);

    std::vector< std::bitset<block_len> > b(numBlocks);

    for(int i = 0; i < numBlocks; ++i)
    {
        char block[keyBytes];
        char cur;
        for (int j = 0; j < keyBytes; ++j) 
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
	if (perm.k!=8) return "invalid permutation, must be 8 numbers";
	int size=strlen(text);
	char* out=new char[size+1];
	out[size]='\0';
	std::vector< std::bitset<8> > bytes=bytesToBitsetArray<8>(text);
	for (int i=0; i<size; i++)
	{
		std::bitset<8> cur;
		for (int bit=0; bit<8; bit++) 
		{
			cur[bit]=bytes[i][perm[bit]-1];
		}
		out[i]=char(cur.to_ulong());
	}
	return out;
}

const char* decode(const Permutation& perm, char* text)
{
	return encode(-perm, text);
}
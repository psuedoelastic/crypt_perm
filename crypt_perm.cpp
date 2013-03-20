/*
 * Copyright (c) Jenia Grubian
 * Licensed under GPLv2
 * Simple cryptography library that uses permutations to encrypt and decrypt byte array
 */

#include "crypt_perm.h"
#include <iostream>

void align(char* data, u_int block_len)
{
	u_int numBytes = strlen(data);
	if (numBytes%block_len!=0) 
	{
		char* tmp = new char[numBytes + numBytes%block_len+1];
		strcpy(tmp, data);
		for (u_int i=numBytes; i<numBytes + numBytes%block_len; i++) tmp[i]=' ';
		tmp[numBytes + numBytes%block_len]='\0';
		strcpy(data, tmp);
	}
}

std::vector< Block > bytesToBitsetArray(char *data, u_int block_len)
{
	u_int numKeyBytes = block_len / 8;

	align(data, numKeyBytes);
	u_int numAlignedBytes = strlen(data);
    std::vector< Block > b;
    for(u_int i = 0; i < numAlignedBytes; i+=numKeyBytes)
    {
    	Block tmp(block_len);
    	
        char block[numKeyBytes];
        for (u_int j = 0; j < numKeyBytes; ++j) 
        	block[j] = data[i+j]; 

        for(u_int bit = 0; bit < block_len; ++bit)
        {
        	tmp[bit] = block[bit/8] & 1;
           	block[bit/8] >>= 1;
        }

        b.push_back(tmp);
    }
    return b;
}

const char* encode(const Permutation& perm, char* text) 
{
	u_int block_len = perm.k;
	if (block_len & (block_len-1)) return "invalid permutation, number of elements must be power of 2";
	u_int numKeyBytes = block_len /8;
	u_int numBytes = strlen(text);
	u_int alignedBytes = numBytes + numBytes%numKeyBytes;
	char* out=new char[alignedBytes + 1];
	out[alignedBytes]='\0';
	std::vector< Block > bytes = bytesToBitsetArray(text, block_len);

	for (u_int i=0; i<alignedBytes; i+=numKeyBytes)
	{
		Block block(block_len);
		/* permutate bits in block */
		for (u_int bit=0; bit<block_len; ++bit) 
			block[bit]=bytes[i/numKeyBytes][perm[bit]-1];

		/* write encoded block into output */
		for (u_int j=0; j<numKeyBytes; ++j) 
			out[i+j]=char(block.bytes[j].to_ulong());
	}
	return out;
}

const char* decode(const Permutation& perm, char* text)
{
	return encode(-perm, text);
}

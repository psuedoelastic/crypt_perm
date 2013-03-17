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

/*std::vector< std::bitset<8> > explodeBitset( Block& block )
{
	u_int block_len = block.size;
	std::vector< std::bitset<8> > res( block_len/8 );
	for (int i=0; i<block_len; i++)
		res[i/8][i%8]=block[i];	
	return res;
}*/

std::vector< Block > bytesToBitsetArray(char *data, u_int block_len)
{
	u_int numBytes = strlen(data);
	u_int numKeyBytes = block_len / 8;
	u_int numBlocks;
	if (numBytes%numKeyBytes==0)
		numBlocks = numBytes * 8 / block_len;
	else
		numBlocks = numBytes / numKeyBytes + numBytes%numKeyBytes;
	align(data, numKeyBytes);

    std::vector< Block > b(numBlocks);

    for(u_int i = 0; i < numBytes; i+=numKeyBytes)
    {
    	b[i]=Block(block_len);
        char block[numKeyBytes];
        char cur;
        for (u_int j = 0; j < numKeyBytes; ++j) 
        	block[j] = data[i+j];
        for(u_int bit = 0; bit < block_len; ++bit)
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
	u_int block_len = perm.k;
	if (block_len & (block_len-1)) return "invalid permutation, number of elements must be power of 2";
	u_int numKeyBytes = block_len /8;
	u_int numBytes = strlen(text);
	u_int alignedBytes = numBytes + numBytes%numKeyBytes;
	char* out=new char[alignedBytes + 1];
	out[alignedBytes]='\0';
	std::vector< Block > bytes = bytesToBitsetArray(text, block_len);
	for (u_int i=0; i<numBytes; i+=numKeyBytes)
	{
		Block block(block_len);
		/* permutate bits in block */
		for (u_int bit=0; bit<block_len; ++bit) 
			block[bit]=bytes[i][perm[bit]-1];
		
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

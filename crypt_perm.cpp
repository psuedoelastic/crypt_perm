#include "crypt_perm.h"

std::vector< std::bitset<8> > bytesToBitsetArray(char *data, int numBytes)
{
    std::vector< std::bitset<8> > b(numBytes);

    for(int i = 0; i < numBytes; ++i)
    {
        char cur = data[i];

        for(int bit = 0; bit < 8; ++bit)
        {
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
	std::vector< std::bitset<8> > bytes=bytesToBitsetArray(text, size);
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
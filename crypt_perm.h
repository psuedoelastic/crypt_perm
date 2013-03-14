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
#include "Permutation.h"

/* 
 * Two functions that implement permutation encryption/decryption methods.
 * They take permutation(key of the cipher) and byte array that is needed to be encoded or decoded
 */


const char* encode(const Permutation&, char*);

const char* decode(const Permutation&, char*);

/* Function that aligns byte array depended on number of blocks */ 
void align(char*, int);

/* Function that explodes 'large' bitset into smaller bitsets of 8 bits */
template <int block_len>
std::vector< std::bitset<8> > explodeBitset(std::bitset<block_len>);

/* Function that explodes byte array into blocks of bits */
template <int block_len>
std::vector< std::bitset<block_len> > bytesToBitsetArray(char*);

/* note: to convert const char* to char* use strdup() */
#endif /* CRYPT_PERM_H */

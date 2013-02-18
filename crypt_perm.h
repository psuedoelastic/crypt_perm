/*
 * Copyright (c) Jenia Grubian
 * Licensed under GPLv2
 * Simple cryptography library that uses permutations of 8 numbers to encrypt and decrypt byte array
 */

#ifndef CRYPT_PERM_H
#define CRYPT_PERM_H

#include <bitset>
#include <vector>
#include <cstring>
#include "Permutation.h"

/* 
 * Two functions that implement permutation encryption/decryption methods.
 * They take permutation(key of the cipher) and byte array that is needed to encode or decode
 */
const char* encode(const Permutation&, char*);
const char* decode(const Permutation&, char*);

std::vector< std::bitset<8> > bytesToBitsetArray(char *data, int numBytes);

/* note: to convert const char* to char* use strdup() */
#endif /* CRYPT_PERM_H */

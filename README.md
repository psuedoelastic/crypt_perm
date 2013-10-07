crypt_perm
==========

C++ library that represents new encryption method. It uses permutations to encrypt or decrypt some data.<br>
I've added pretty simple example of encoder that uses mentioned library.<br>
Examle: source file - text.txt, encoded file - encoded.txt, permutation - 13562487<br>
<i>$ ./encoder text.txt encoded.txt 13562487</i> -for permutation of 8 elements<br>or<br>
<i>$ ./encoder text.txt encoded.txt "1 3 5 6 2 4 8 7"</i> -general case, permutation of n elements(n must be divided by 2)

FLAGS:= -g -Wall
GXX:= g++
all: encoder

encoder: crypt_perm.a encoder.o
	$(GXX) $(FLAGS) encoder.o crypt_perm.a -o encoder

encoder.o:
	$(GXX) $(FLAGS) -c encoder.cpp
	
crypt_perm.a: crypt_perm.o 
	ar rvs crypt_perm.a crypt_perm.o 

crypt_perm.o: crypt_perm.cpp crypt_perm.h
	$(GXX) $(FLAGS) -c crypt_perm.cpp

clean:
	rm -f crypt_perm.a encoder


FLAGS:= -g -Wall
GXX:= g++
all: crypt_perm.a

crypt_perm.a: crypt_perm.o 
	ar rvs crypt_perm.a crypt_perm.o 

crypt_perm.o: crypt_perm.cpp crypt_perm.h
	$(GXX) $(FLAGS) -c crypt_perm.cpp

clean:
	rm -f crypt_perm.a


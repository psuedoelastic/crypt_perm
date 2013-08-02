#include <fstream>
#include <iostream>
#include <streambuf>
#include <string.h>
#include <string>
#include "crypt_perm.h"

#define EXIT_FAILED 1
#define EXIT_SUCCES 0

using namespace std;

int main(int argc, char** argv) {
	if (argc==1) { 
		cerr<<"No source file in input."<<endl; 
		return EXIT_FAILED; 
	}
	else if (argc==2) {
		cerr<<"No destination file in input."<<endl;
		return EXIT_FAILED;
	}
	else if (argc==3) {
		cerr<<"No key in input"<<endl;
		return EXIT_FAILED;
	}
	else if (argc>4) {
		cerr<<"Not valid parameters";
		return EXIT_FAILED;
	} 
	else {
		char* source = argv[1];
		char* destiny = argv[2];
		char* key = argv[3];
		u_int key_len = strlen(key);
		for (u_int i=0; i<key_len; i++) key[i]=(int)key[i]-48; // convert ascii 'int' chars to 'pure int' chars, e.g. '1' => 1

		ifstream in(source);
		ofstream out(destiny);
		string text((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
		
		const char* encoded = encode((u_char*)key, key_len, strdup(text.c_str()));
		out << encoded;
		return EXIT_SUCCES;
	}

}
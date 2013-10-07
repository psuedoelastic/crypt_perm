#include <fstream>
#include <iostream>
#include <streambuf>
#include <string.h>
#include <string>
#include "crypt_perm.h"

#define EXIT_FAILED 1
#define EXIT_SUCCES 0

using namespace std;

char* split_into_chars(char* str, const char* delimiter) {
	u_int i = 0, c = 1;
	while (str[i]!='\0') {
		if (str[i] == ' ') c++;
		i++;
	}
	char* splitted = new char[c];
	char* token = strtok(str, delimiter);
	splitted[0] = (strlen(token)==1) ? (int)token[0] - 48 : ((int)token[0]*10-48) + (int)token[1] - 48;
	for(u_int i=1; i<c; i++) {
		token = strtok(0, delimiter);
		splitted[i] = (strlen(token)==1) ? (int)token[0] - 48 : ((int)token[0]-48)*10 + (int)token[1] - 48; 
		//show me the way to the next little char, oh don't ask why...
	}
	return splitted;
}

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
		if (key_len==8)
			for (u_int i=0; i<key_len; i++) key[i]=(int)key[i]-48; 
		else {
			key = split_into_chars(key, " ");
			key_len = strlen(key);
			//for (u_int i=0; i<key_len; i++) cout<<(int)key[i];
		}

		ifstream in(source);
		ofstream out(destiny);
		string text((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
		
		const char* encoded = encode((u_char*)key, key_len, strdup(text.c_str()));
		//const char* decoded = decode((u_char*)key, key_len, strdup(encoded));
		out << encoded;
		return EXIT_SUCCES;
	}

}
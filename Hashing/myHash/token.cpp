#include <iostream>
#include <fstream>
#include "token.h"
#include <cstring>

using namespace std;
static ifstream ifs;
static int active = 0;

int openTokenFile(const char fname[]) {
	if (active)
		ifs.close();
	ifs.open(fname);
	active = ifs.good();
	return active;
}

char* nextToken() {
	char ch, *newtoken=0;
	static char token[60]; //array for temp storage
	int i = 0;
	
	do {
		ifs.get(ch);
	} while (ifs.good() && !isalpha(ch));

	if (ifs.good()) {
		do {
			token[i++] = ch;
			ifs.get(ch);
		} while (ifs.good() && isalpha(ch));  //read until you encounter non char
		token[i] = 0; //last read failed so we insert a null
		newtoken = new char[i+1]; //memory allocation for non temporary storage
		strcpy(newtoken,token); 
	}
	if (i == 0) {
		ifs.close();
		active = 0;
	}
	for(int j = 0; j < i; j++) {
		newtoken[j] = tolower(newtoken[j]);
	}
	return newtoken;
}

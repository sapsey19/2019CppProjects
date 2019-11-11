#include "hashType.h"
#include <string>
#include <iostream>
#include <string.h>
#include "linkedlist.h"

using namespace std;

int HashFunction(WordRec* wrec)//a compression algorithm of your design
{
	//hash function from: https://stackoverflow.com/questions/7666509/hash-function-for-string
	//int i = 1, n = wrec->word[0];
	unsigned long hash = 5381;
    int c;
	char* str = wrec->word;
    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	return hash%HASHTABLESIZE;
}

//To check if instance of a key in the table this tells if occurrence is encountered
int MatchValue(WordRec* v1, WordRec* v2) {
	return (strcmp(v1->word,v2->word) == 0);
}

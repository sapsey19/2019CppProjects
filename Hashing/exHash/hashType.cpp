#include "hashType.h"
#include <string>
#include <iostream>
#include <string.h>

using namespace std;
int HashFunction(WordRec* wrec)//a compression algorithm of your design
{
	int i = 1, n = wrec->word[0];
	
	while (wrec->word[i] != 0)
		n += wrec->word[i++];
	return n%HASHTABLESIZE;
}


//To check if instance of a key in the table this tells if occurrence is encountered

int MatchValue(WordRec* v1, WordRec* v2) 
{
	return (strcmp(v1->word,v2->word) == 0);
}

//Word in table and instance count
void DisplayHashType(WordRec* wrec)
{
	cout << wrec->word << '\t' << wrec->count << endl;
}

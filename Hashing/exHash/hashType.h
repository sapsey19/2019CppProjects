/*
	This is the data interface for HashTable.
	To use the hash table code, a user must specify
	(1) The size of the hash table - replace the (1)
	(2) The type to store in the hashtable
	(3) The value used in the table to indicate an empty cell
	and also provide the HashFunction, a matching function and a display function.
	
	It must be protected from being included more than once
*/	

#ifndef HASHTYPE_H
#define HASHTYPE_H

const int HASHTABLESIZE = 200;

struct WordRec
{
	char* word;
	int count;
};

typedef WordRec*  HashType;
const HashType EmptyValue = 0;

int HashFunction(HashType);
int MatchValue(HashType,HashType);
void DisplayHashType(HashType);

#endif

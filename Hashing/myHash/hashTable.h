/*
	Interface file for HashTable
	This is a generic hash table for storing the type HashType
	as specified in HashType.h
*/

#include "hashType.h"
#include <string>

void HashTableInitialise();
HashType HashTableFind(HashType);
void HashTableInsert(HashType);
void HashTableDump();

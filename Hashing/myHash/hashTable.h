/*
	Interface file for HashTable
	This is a generic hash table for storing the type HashType
	as specified in HashType.h
*/

const int HASHTABLESIZE = 800;

void hashTableInsert(char *word);
void hashTableDump();
int hashFunction(char* word);

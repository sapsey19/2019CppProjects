/*
	Interface file for HashTable
	This is a hash table for storing strings. 
*/

const int HASHTABLESIZE = 400;

void hashTableInsert(char *word);
void hashTableDump();
int hashFunction(char* word);
void findWord(char *word);


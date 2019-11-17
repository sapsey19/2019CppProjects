/*
	Interface for hashTable.cpp
	Stores strings using chaining collision resolution
	HASHTABLESIZE can be whatever size the user wants, but generally the smaller it is 
		the less efficient the hashTable is. -> a HASHTABLESIZE of 1 results in a linked list
	
*/

const int HASHTABLESIZE = 400;

void hashTableInsert(char *word);
void hashTableDump();
int hashFunction(char* word);
void findWord(char *word);

void sortTable();
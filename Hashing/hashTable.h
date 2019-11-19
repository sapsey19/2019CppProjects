/*
	Interface for hashTable.cpp
	Stores strings using chaining collision resolution
	HASHTABLESIZE can be whatever size the user wants, but generally the smaller it is 
		the less efficient the hashTable is. -> a HASHTABLESIZE of 1 results in a linked list
	
	Occupancy Sizes:
		~50% -> 8000
		~70% -> 5000
		~80% -> 4000
	
*/



const int TABLE_SIZE = 5000;

void hashTableInsert(char *word);
void hashTableDump();
int hashFunction(char* word);
void findWord(char *word);

void sortTable();
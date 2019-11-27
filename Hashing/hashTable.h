/*
	Interface for hashTable.cpp
	Stores strings using chaining collision resolution
	TABLE_SIZE can be whatever size the user wants, but generally the smaller it is 
		the less efficient the hashTable is. -> a TABLE_SIZE of 1 results in a linked list
	
	Occupancy Timings
		Average of 5 for 50% occupancy: 0.093633
		Average of 5 for 70% occupancy: 0.100896
		Average of 5 for 80% occupancy: 0.105635
	
*/

const int TABLE_SIZE = 4000;

void hashTableInsert(char *word);
void hashTableDump();
int hashFunction(char* word);
void findWord(char *word);

void sortTable();
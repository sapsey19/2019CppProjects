#include "hashTable.h"
#include "linkedlist.h"

using namespace std;

List arr[HASHTABLESIZE];

//This stores the word at hash location and deals with collisions
void hashTableInsert(char *word) {	
	int i = hashFunction(word);	
	arr[i].createNode(word);
}

//Displays the contents of a hash table.
void hashTableDump() {	
	int i;	
	for (i = 0; i < HASHTABLESIZE; i++) {
		arr[i].printOut();
	}
}

int hashFunction(char *word) {
	//hash function from: https://stackoverflow.com/questions/7666509/hash-function-for-string
	unsigned long hash = 5381;
    int c;
	char* str = word;
    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	return hash%HASHTABLESIZE;
}
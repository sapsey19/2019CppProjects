#include "hashTable.h"
#include "linkedlist.cpp"
#include <string>
#include <cstring>
#include <fstream>
#include "qsort.cpp"

List arr[TABLE_SIZE]; //array of linkedlist

//This stores the word at hash location and deals with collisions
void hashTableInsert(char *word) {	
	int i = hashFunction(word);	
	arr[i].createNode(word);
}

//Displays the contents of a hash table.
void hashTableDump() {	
	int i;	
	for (i = 0; i < TABLE_SIZE; i++) {
		arr[i].printOut();
	}
}

void findWord(char *word) {
	int i = hashFunction(word);
	arr[i].findWords(word);
}

int hashFunction(char *word) {
	//hash function from: https://stackoverflow.com/questions/7666509/hash-function-for-string 
	unsigned long hash = 5381;
    int c;
	char* str = word;
    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	return hash % TABLE_SIZE;
}

void sortTable() {
	ifstream in;
	in.open("output.txt");
	int numArr[6260];
	string strArr[6260];
	int index[6260];
	string trash;
	int i = 0;
	string temp;
	int tempcount;
	while(in >> temp) {
		in >> tempcount;
		in >> trash;
		temp.erase(temp.length()- 1, temp.length()); //erase the : after each word
		strArr[i] = temp;
		numArr[i] = tempcount;
		index[i] = i;
		i++;
	}
	in.close();

	quickSort(numArr, index, 0, 6260 - 1);
	ofstream out;
    out.open("sortedoutput.txt");
    for(int j = 0; j < 150; j++)
       out << strArr[index[j]] << ": " << numArr[index[j]] << endl;    
    out.close();
}
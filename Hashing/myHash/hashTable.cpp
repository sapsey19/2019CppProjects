#include "hashTable.h"
#include "linkedlist.cpp"
#include <string>
#include <cstring>
#include <fstream>
//#include "ass3A.cpp"
#include <algorithm>

List arr[HASHTABLESIZE]; //array of linkedlist

struct nodeType {
	string word;
	int count;
};

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
	return hash%HASHTABLESIZE;
}

void sortTable() {
	ifstream in;
	in.open("output.txt");
	int numArr[6260];
	string strArr[6260];
	string trash;
	int i = 0;
	string temp;
	int tempc;
	while(in >> temp) {
		in >> tempc;
		in >> trash;
		temp.erase(temp.length()- 1, temp.length());
		strArr[i] = temp;
		numArr[i] = tempc;
		i++;
	}
	in.close();

	
	sort(numArr, numArr + 6260);
	ofstream out;
	out.open("arrout.txt");
	for(int j = 0; j < 10000; j++) {
		out << strArr[j] << " " << numArr[j] << endl;
	}
	out.close();
}
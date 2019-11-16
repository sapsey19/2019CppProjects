#include "token.h"
#include "hashTable.h"
#include <iostream>
#include <time.h>

using namespace std;

int main() {
	int choice;
	char fname[30];
	char *word;
	bool readIn = false;
	while (choice != 0) {
		cout << "(1) Enter file name to hash" << endl;
		cout << "(2) Find occurance of word in table" << endl;
		cout << "(3) Sort hash table" << endl;
		cout << "(0) Quit program" << endl;
		cout << "Enter choice: ";
		cin >> choice;
		cout << endl;
		switch (choice) {
		case 1:
			cout << "Enter file name: ";
			cin >> fname;
			if (openTokenFile(fname)) {
				readIn = true;
				clock_t t = clock();
				while ((word = nextToken()))
					hashTableInsert(word);
				t = clock() - t;
				cout << "Time: " << ((double)t) / CLOCKS_PER_SEC << " seconds" << endl;
				cout << "Finished hashing" << endl;
				cout << endl;
				hashTableDump();
			}
			break;
		case 2:
			if (!readIn) {
				cout << "Haven't hashed a file yet!" << endl;
				break;
			}
			char temp[30];
			cout << "Enter word to find: ";
			cin >> temp;
			cout << endl;
			findWord(temp);
			break;
		case 3:
			sortTable();
			break;
		case 0:
			break;
		default:
			cout << "Did not recognize command!" << endl;
			break;
		}
	}
	return 0;
}

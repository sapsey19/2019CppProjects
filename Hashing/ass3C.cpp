/*
    Main driver file for the hash table and qsort.
    File can hash a text file, display its contents, sort by 150 most repeating words, and find
        number of occurances of a specific word. Can also use qsort.cpp, which prompts user
        to enter the number of elements to sort, and then the kth smallest element to find. 
*/

#include "token.h"
#include "hashTable.h"
#include "qsort.h"
#include <iostream>
#include <time.h>

using namespace std;

int main() {
	int choice;
	char fname[30];
	char *word;
	bool readIn = false;
    clock_t t;
	while (choice != 0) {
		cout << "(1) Enter file name to hash" << endl;
		cout << "(2) Find occurance of word in table" << endl;
		cout << "(3) Display 150 most common words" << endl;
        cout << "(4) Enter number of elements to sort" << endl;
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
				t = clock();
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
			if (!readIn) {
				cout << "Haven't hashed a file yet!" << endl;
				break;
			}
			sortTable();
			cout << "Sorted hash table to 'sortedhash.txt'" << endl;
			break;
        case 4: {
            int n, k;
            cout << "Enter number of elements: ";
            cin >> n;
            cout << endl;
            cout << "Enter kth element to find: ";
            cin >> k;
            cout << endl;
            int arr[n], index[n];

            generateNums(arr, index, n);
            cout << "The " << k << "th value is: " << kthValue(arr, index, 0, n - 1, k) << endl;

            t = clock();
            increasingQuickSort(arr, index, 0, n-1);
            t = clock() - t;
            cout << "Sort time: " << ((double)t) / CLOCKS_PER_SEC << " seconds" << endl;
            printArr(arr, index, n);
			cout << "Output sorted contents to 'sortoutput.txt'" << endl;
            break;
        }
		case 0:
			break;
		default:
			cout << "Did not recognize command!" << endl;
			break;
		}
	}
	return 0;
}

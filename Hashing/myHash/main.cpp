#include <iostream>
#include "token.h"
#include "hashTable.h"
#include <string>
#include <time.h>

using namespace std;
int main() {	
	char fname[30], *word;
	WordRec* wrec, trec;
	int nentries = 0;

	cin >> fname;
	if (OpenTokenFile(fname)) {
		//HashTableInitialise();
		clock_t t = clock();
		while ((word=NextToken())) {
			trec.word = word;
			wrec = HashTableFind(&trec);
			wrec = new WordRec;
			*wrec = trec;
			wrec->count = 1;
			HashTableInsert(wrec);
		}
		t = clock() - t;
		cout << "Time: " << ((double)t)/CLOCKS_PER_SEC << " seconds"  << endl;
		HashTableDump();
	}		
	return 0;
}


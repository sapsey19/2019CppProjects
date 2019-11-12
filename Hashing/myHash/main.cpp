#include "token.h"
#include "hashTable.h"
#include <iostream>
#include <time.h>

using namespace std;
int main() {	
	char fname[30];
	char *word;	
	cin >> fname;
	if (openTokenFile(fname)) {
		clock_t t = clock();
		while ((word=nextToken()))
			hashTableInsert(word);
		t = clock() - t;
		cout << "Time: " << ((double)t)/CLOCKS_PER_SEC << " seconds"  << endl;
		hashTableDump();
	}		
	return 0;
}


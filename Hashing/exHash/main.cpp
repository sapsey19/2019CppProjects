#include <iostream>
#include "token.h"
#include "hashTable.h"
#include <string>

using namespace std;
int main()
{	
	char fname[30], *word;
	WordRec* wrec, trec;
	int nentries = 0;
	
	cin >> fname;
	if (OpenTokenFile(fname))
	{
		HashTableInitialise();
		while ((word=NextToken()))
		{
			trec.word = word;
			wrec = HashTableFind(&trec);
			if (wrec == 0 && nentries < 200)
			{
				wrec = new WordRec;
				*wrec = trec;
				wrec->count = 1;
				HashTableInsert(wrec);
				nentries++;
			}
			else
				wrec->count++;
		}
		cout<<"Grec \t"<<wrec<<endl;
		HashTableDump();
	}		
	return 0;
}


#include "hashType.h"
#include "hashTable.h"
#include <iostream>

using namespace std;

static int HashNumber;

static HashType HashTable[HASHTABLESIZE];

//Function initializes the table to empty Vals
void HashTableInitialise()
{
	int i;
	
	for (i=0;i<HASHTABLESIZE;i++)
		HashTable[i] = EmptyValue;
	HashNumber = 0;
}

//Looking for instances of a word in the table - uses match value from hashType
HashType HashTableFind(HashType value)
{
	int found = 0, HValue = HashFunction(value);
	int i = HValue;
	
	while (!found && HashTable[i] != EmptyValue)
	{
		 if (MatchValue(value,HashTable[i]))
		 	found = 1;
		 else
		 	i = (i+1) % HASHTABLESIZE;
	}
	if (found)
		return HashTable[i];
	else
		return EmptyValue;
}

//This stores the word at hash location or deals with collisions
void HashTableInsert(HashType value)
{
	int i = HashFunction(value);
	
	while (HashTable[i] != EmptyValue)
		 i = (i+1) % HASHTABLESIZE;
	HashTable[i] = value;
	HashNumber++;
}


//Displays the contents of a hash table.
void HashTableDump()
{
	int i;
	
	for (i=0;i<HASHTABLESIZE;i++)
	{
		if (HashTable[i] != EmptyValue)
		{
			DisplayHashType(HashTable[i]);
		}
		//cout<<"Working "<<i<<endl;
	}
}
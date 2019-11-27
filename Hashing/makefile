hash: ass3C.o hashTable.o token.o linkedlist.o
	g++ ass3C.o hashTable.o token.o -o hash 

ass3C.o: ass3C.cpp hashTable.h token.h linkedlist.h qsort.h
	g++ -c ass3C.cpp

HashTable.o: hashTable.cpp hashTable.h hashType.h linkedlist.h qsort.h
	g++ -c hashTable.cpp

token.o: token.h
	g++ -c token.cpp

linkedlist.o: linkedlist.h
	g++ -c linkedlist.cpp

clean:
	rm hash ass3C.o hashTable.o token.o linkedlist.o output.txt sortedhash.txt sortoutput.txt
hash: main.o hashTable.o token.o linkedlist.o
	g++ main.o hashTable.o token.o -o hash

main.o: main.cpp hashTable.h token.h linkedlist.h
	g++ -c main.cpp

HashTable.o: hashTable.cpp hashTable.h hashType.h linkedlist.h
	g++ -c hashTable.cpp

token.o: token.h
	g++ -c token.cpp

linkedlist.o: linkedlist.h
	g++ -c linkedlist.h
	 
clean:
	rm hash main.o hashTable.o token.o
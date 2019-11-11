hash: main.o hashType.o hashTable.o token.o linkedlist.o
	g++ main.o hashType.o hashTable.o token.o -o hash

main.o: main.cpp hashType.h hashTable.h token.h linkedlist.h
	g++ -c main.cpp

HashTable.o: hashTable.cpp hashTable.h hashType.h linkedlist.h
	g++ -c hashTable.cpp

HashType.o: hashType.cpp hashType.h
	g++ -c hashType.cpp

token.o: token.h
	g++ -c token.cpp

linkedlist.o: linkedlist.h
	g++ -c linkedlist.h
	 
clean:
	rm hash main.o hashTable.o hashType.o token.o
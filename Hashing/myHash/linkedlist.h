/*
    Date: 11/6/2019
    Author: Sean Apsey

    Linkedlist header file. Has functions to add a node, find nodes, and print nodes, either to
    standard output or a file. Each node contains a string, how many instances of a string it encounters, and a pointer to the next node 
    in the list. The list only stores one instance of each unique string.

    Linkedlist based on: https://www.codementor.io/codementorteam/a-comprehensive-guide-to-implementation-of-singly-linked-list-using-c_plus_plus-ondlm5azr

*/

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <string>
#include <fstream>

using namespace std;
static ofstream fout("output.txt", ofstream::out);
struct node {
    string word;
    int count;
    struct node *next;
};

class List {
private:
    node *head, *tail;
    int size = 0;

public:
    List() {
        head = nullptr;
        tail = nullptr;
    }
    ~List() {}

    void createNode(string word);
    void print();
    void printOut();
    node findNode(string word);
    int findOccurances(string word);
    void increaseCount(string word);
};

#endif
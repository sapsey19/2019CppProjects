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
  
    void increaseCount(string word) {
        node *temp = new node;
        temp = head;
        while(temp != nullptr) {
            if(temp->word == word)
                temp->count += 1;
            temp = temp->next;
        }
    }
public:
    int size = 0;
    List() {
        head = nullptr;
        tail = nullptr;
    }

    void createNode(string word) { //create new node, inserts at end of list
        node *temp = new node;
        temp->word = word;
        temp->next = nullptr;

        if(head == nullptr) { //if empty list
            temp->count = 1;
            head = temp;
            tail = temp;
            temp = nullptr;
            size++;
        }
        else {
            if(findOccurances(word) == 0) {
                temp->count = 1;
                tail->next = temp;
                tail = temp;
                temp = nullptr;
                size++;
            }
            else {
                increaseCount(word);
            }
        }
    }

    void print() {
        node *temp = new node;
        temp = head;
        while(temp != nullptr) {
            cout << temp->word << ": " << temp->count << endl;
            temp = temp->next;
        }
    }

    void printOut() {
        node *temp = new node;
        temp = head;        
        while(temp != nullptr) {
            fout << temp->word << ": " << temp->count << " | ";
            temp = temp->next;
        }
        fout << endl;
    }

    node findNode(string word) {
        node *temp = new node;
        temp = head;
        while(temp != nullptr) {
            if(temp->word == word)
                return *temp;
            temp = temp->next;
        }
        return *temp;
    }

    int findOccurances(string word) {
        node *temp = new node;
        temp = head;
        while(temp != nullptr) {
            if(temp->word == word) {
                return temp->count;
            }
            else {
                temp = temp->next;
            }
        }
        return 0;
    }

};

#endif
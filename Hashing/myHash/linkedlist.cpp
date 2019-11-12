#include "linkedlist.h"

void List::createNode(string word) { //create new node, inserts at end of list
    node *temp = new node;
    temp->word = word;
    temp->next = nullptr;

    if (head == nullptr) { //if empty list
        temp->count = 1;
        head = temp;
        tail = temp;
        temp = nullptr;
        size++;
    }
    else { 
        if (findOccurances(word) == 0) {
            temp->count = 1;
            tail->next = temp;
            tail = temp;
            temp = nullptr;
            size++;
        }
        else
            increaseCount(word);
    }
}

void List::print() {
    node *temp = new node;
    temp = head;
    while (temp != nullptr) {
        cout << temp->word << ": " << temp->count << endl;
        temp = temp->next;
    }
}

void List::printOut() {
    node *temp = new node;
    temp = head;
    while (temp != nullptr) {
        fout << temp->word << ": " << temp->count << " | ";
        temp = temp->next;
    }
    fout << endl;
}

node List::findNode(string word) {
    node *temp = new node;
    temp = head;
    while (temp != nullptr) {
        if (temp->word == word)
            return *temp;
        temp = temp->next;
    }
    return *temp;
}

int List::findOccurances(string word) {
    node *temp = new node;
    temp = head;
    while (temp != nullptr) {
        if (temp->word == word)
            return temp->count;
        else
            temp = temp->next;
    }
    return 0;
}

void List::increaseCount(string word) {
    node *temp = new node;
    temp = head;
    while (temp != nullptr) {
        if (temp->word == word)
            temp->count += 1;
        temp = temp->next;
    }
}
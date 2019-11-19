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
        if (findOccurances(word) == 0) { //if number of occurances is 0, add to list
            temp->count = 1;
            tail->next = temp;
            tail = temp;
            temp = nullptr;
            size++;
        }
        else //else increase count of word
            increaseCount(word);
    }
}

bool List::isEmpty() {
    node *temp = new node;
    temp = head;
    if(temp == nullptr)
        return true;
    return false;
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

void List::findWords(string word) {
    node *temp = new node;
    temp = head;
    bool found = false;
    while (temp != nullptr) {
        if (temp->word == word) {
            cout << "'" << word << "'" << " occurs " << temp->count << " times." << endl;
            found = true;
            break;
        }
        temp = temp->next;
    }
    if(!found)
        cout << "'" << word << "'" << " is not in hash table" << endl;
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
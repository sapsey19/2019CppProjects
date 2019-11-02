#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

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
        }
        else {
            if(findOccurances(word) == 0) {
                temp->count = 1;
                tail->next = temp;
                tail = temp;
                temp = nullptr;
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
        ofstream out;
        out.open("output.txt");
        while(temp != nullptr) {
            out << temp->word << ": " << temp->count << endl;
            temp = temp->next;
        }
        out.close();
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

string removePunc(string word) {
    string temp = word;
     for (int i = 0; i < temp.size(); i++) { 
        if (ispunct(temp[i])) { 
            temp.erase(i--, 1); 
        }
    }
    return temp;
}

int main () {
    List list;
    
    ifstream in;
    ofstream out;
    in.open("input.txt");
    string temp;
    string stripped;
    while(in >> temp) {       
        transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
        stripped = removePunc(temp);       
        list.createNode(stripped);
    }

    list.printOut();
    in.close();
    return 0;
}
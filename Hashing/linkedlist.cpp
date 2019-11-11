#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include "myHash/linkedlist.h"

using namespace std;

int main () {
    List list;
    
    ifstream in;
    ofstream out;
    in.open("pride.txt");
    string temp;
    string stripped;
    while(in >> temp) {       
        transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
        stripped = removePunc(temp);       
        List::list.createNode(stripped);
    }

    List::list.printOut();
    in.close();
    return 0;
}
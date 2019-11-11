#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include "linkedlist.h"

//using namespace std;

// string removePunc(string word) {
//     string temp = word;
//      for (int i = 0; i < temp.size(); i++) { 
//         if (ispunct(temp[i])) { 
//             temp.erase(i--, 1); 
//         }
//     }
//     return temp;
// }

// int main () {
//     List list;
    
//     ifstream in;
//     ofstream out;
//     in.open("pride.txt");
//     string temp;
//     string stripped;
//     while(in >> temp) {       
//         transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
//         stripped = removePunc(temp);       
//         list.createNode(stripped);
//     }

//     list.printOut();
//     in.close();
//     return 0;
// }
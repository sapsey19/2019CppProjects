/*
    index-based quicksort
    quickSort algorithm from: https://www.hackerearth.com/practice/algorithms/sorting/quick-sort/tutorial/
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <chrono>

using namespace std;

void swap(int *a, int *b);
int partition(int arr[], int index[], int low, int high);
void quickSort(int arr[], int index[], int low, int high);
void generateNums(int n);
void printArr(int arr[], int index[], int n);

int main() {
    ifstream in;
    in.open("randomNums.txt");      

    int n;
    cin >> n;
    int arr[n], index[n];

    generateNums(n);
    
    int temp;
    int i = 0;
    while(in >> arr[i]) {        
        index[i] = i;
        i++;
    }
    auto t1 = std::chrono::high_resolution_clock::now();
    quickSort(arr, index, 0, n - 1);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    cout << duration << endl;
    printArr(arr, index, n);
    in.close();
    return 0;
}

void swap(int *a, int *b) {
	int temp; 
	temp = *a;
	*a = *b;
	*b = temp;
}

// int sort3(int &a, int &b, int &c) {   
//     if (a > b) { 
//         if (b > c) 
//             return b; 
//         if (a > c) 
//             return c;        
//         return a; 
//     } 
//     else {        
//         if (a > c) 
//             return a; 
//         if (b > c) 
//             return c;       
//         return b; 
//     }  
// }
void sort3(int arr[], int indices[], int val1, int val2, int val3) {
    
    int x = indices[val1];
    int y = indices[val2];
    int z = indices[val3];
    
    int a = arr[indices[x]];
    int b = arr[indices[y]];
    int c = arr[indices[z]];
    int temp;
    
    if (a < b) {
        // a < b < c
        if (b < c) {
            ; // already sorted, do nothing
        }
        // a < c < b, switch y and z
        else if ( a < c) {
            temp = y;
            y = z;
            z = temp;
        }
        // c <= a < b, move all to right
        else {
            temp = y;
            y = x;
            x = z;
            z = temp;
        }
    }
    // a >= b
    else {
        // a >= b > c
        if (b > c) {
            ; // already sorted, do nothing
        }
        // b < c < a, move all left
        else if (a > c) {
            temp = y;
            y = z;
            z = x;
            x = temp;
        }
        // b < a < c, switch x and y
        else {
            temp = x;
            x = y;
            y = temp;
        }
    }
    
    // update indices
    indices[val1] = x;
    indices[val2] = y;
    indices[val3] = z;
}


int partition(int arr[], int indices[], int left, int right) {
    sort3(arr, indices, left, right, (left+right)/2);
    int pivot = arr[indices[right]];
    
    int i = left - 1;
    
    for (int j = left; j < right; j++) {
        if (arr[indices[j]] < pivot) {
            i++;
            swap(&indices[i], &indices[j]);
        }
    }
    swap(&indices[i+1], &indices[right]);
    return i+1;
}

void quickSort(int arr[], int index[], int low, int high) {
    if(low < high) {        
        int piv = partition(arr, index, low, high);     
        quickSort(arr, index, low, piv-1); 
        quickSort(arr, index, piv+1, high); 
   }
}

void generateNums(int n) {
    ofstream randomNums;
    randomNums.open("randomNums.txt");
    int i = 0;
    int random;
    while(i < n) {
        random = rand()/1000;
        if(random > 0 && random <= 1000) {
            randomNums << random << endl;
            i++;
        }
    }
    randomNums.close();
}

void printArr(int arr[], int index[], int n) {
    ofstream out;
    out.open("sortoutput.txt");
    for(int i = 0; i < n; i++) {
       if(i > 0 && i % 10 == 0)
           out << endl;
       out << arr[index[i]] << " ";
    }
    out.close();
}
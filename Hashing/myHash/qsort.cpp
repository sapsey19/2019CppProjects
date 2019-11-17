/*
    Improved quickSort algorithm, using 3-way partitioning
    Algorithm from: https://www.geeksforgeeks.org/3-way-quicksort-dutch-national-flag/
*/

#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;

void swap(int *a, int *b);
int partition(int arr[], int index[], int low, int high);
void quickSort(int arr[], int index[], int low, int high);
void generateNums(int n);
void printArr(int arr[], int index[], int n);

// int main() {
//     ifstream in;
//     in.open("randomNums.txt");      

//     int n;
//     cin >> n;
//     int arr[n], index[n];

//     clock_t h = clock();
//     generateNums(n);
//     h = clock() - h;
//     cout << "Number generation time: " << ((double)h) / CLOCKS_PER_SEC << " seconds" << endl;
//     int temp;
//     int i = 0;
//     clock_t r = clock();
//     while(in >> arr[i]) {        
//         index[i] = i;
//         i++;
//     }
//     r = clock() - r;
//      cout << "Read in time: " << ((double)r) / CLOCKS_PER_SEC << " seconds" << endl;

//     clock_t t = clock();
// 	   quickSort(arr, index, 0, n-1);
// 	   t = clock() - t;
//     cout << "Sort time: " << ((double)t) / CLOCKS_PER_SEC << " seconds" << endl;
//     printArr(arr, index, n);
//     in.close();
//     return 0;
// }

void partition(int arr[], int index[], int low, int high, int &i, int &j) { 
    i = low - 1;
    j = high; 
    int p = low-1;
    int q = high; 
    int v = arr[index[high]]; 
  
    while (true) { 
        while (arr[index[++i]] > v); //was < v 
  
        while (v > arr[index[--j]]) //was < arr[index]
            if (j == low) break; 

        if (i >= j) break; //was >=

        swap(index[i], index[j]); 
  
        if (arr[index[i]] == v) { 
            p++; 
            swap(index[p], index[i]); 
        } 
  
        if (arr[index[j]] == v) { 
            q--; 
            swap(index[j], index[q]); 
        } 
    }  
    swap(index[i], index[high]); 
  
    j = i-1; 
    for (int k = low; k < p; k++, j--) 
        swap(index[k], index[j]); 

    i = i+1; 
    for (int k = high-1; k > q; k--, i++) 
        swap(index[i], index[k]); 
} 
  
// 3-way partition based quick sort 
void quickSort(int arr[], int index[], int low, int high) { 
    if (high <= low) return;   
    int i, j; 

    // i and j are passed as reference 
    partition(arr, index, low, high, i, j); 
  
    quickSort(arr, index, low, j); 
    quickSort(arr, index, i, high); 
} 

void swap(int *a, int *b) {
	int temp; 
	temp = *a;
	*a = *b;
	*b = temp;
}

void generateNums(int n) {
    ofstream randomNums;
    randomNums.open("randomNums.txt");
    int i = 0;
    int random;
    while(i < n) {
        random = rand() % 10000;        
        randomNums << random << endl;
        i++;
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
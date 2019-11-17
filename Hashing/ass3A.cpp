/*
    index-based quicksort
    quickSort algorithm from: https://www.hackerearth.com/practice/algorithms/sorting/quick-sort/tutorial/
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>

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

    clock_t h = clock();
    generateNums(n);
    h = clock() - h;
    cout << "Number generation time: " << ((double)h) / CLOCKS_PER_SEC << " seconds" << endl;
    int temp;
    int i = 0;
    clock_t r = clock();
    while(in >> arr[i]) {        
        index[i] = i;
        i++;
    }
    r = clock() - r;
     cout << "Read in time: " << ((double)r) / CLOCKS_PER_SEC << " seconds" << endl;

    clock_t t = clock();
	quickSort(arr, index, 0, n-1);
	t = clock() - t;
    cout << "Sort time: " << ((double)t) / CLOCKS_PER_SEC << " seconds" << endl;
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

int partition (int arr[], int index[], int low, int high) {
    int i = low + 1;
    int piv = arr[index[low]];
    for(int j = i; j <= high ; j++) {
        if(arr[index[j]] > piv) {
            swap(index[i], index[j]);
            i++;
        }
   }
   swap(index[low], index[i-1]);
   return i-1;
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
        if(random > 0 && random <= 10000) {
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
/*
    Improved version of quickSort, using median of 3 to find pivot. 
    Median code from: https://www.geeksforgeeks.org/middle-of-three-using-minimum-comparisons/
*/  

#include <iostream>
#include <time.h>
#include <fstream>

using namespace std;

void swap(int *a, int *b);
int partition(int arr[], int index[], int low, int high);
void quickSort(int arr[], int index[], int low, int high);
void generateNums(int arr[], int index[], int n);
void printArr(int arr[], int index[], int n);

// int main() {

//     int n;
//     cout << "Enter number of elements: ";
//     cin >> n;
//     cout << endl; 
//     int arr[n], index[n];    
//     generateNums(arr, index, n);

//     clock_t t = clock();
// 	quickSort(arr, index, 0, n-1);
// 	t = clock() - t;
//     cout << "Sort time: " << ((double)t) / CLOCKS_PER_SEC << " seconds" << endl;
//     printArr(arr, index, n);
//     return 0;
// }

void sort3(int arr[], int index[], int low, int high){ 
	int a = arr[index[low]];
	int b = arr[index[high/2]];
	int c = arr[index[high]];
	if((a < b && b < c) || (c < b && b < a))
		swap(index[high/2], index[high]);
	else if((b < a && a < c) || (c < a && a < b))
		swap(index[low], index[high]);
}

int partition(int arr[], int index[], int low, int high) {
	sort3(arr, index, low, high);
	int pivot = arr[index[high]];
    int i = low - 1;
	for (int j = low; j < high; j++) {
		if (arr[index[j]] >= pivot) { //changed sign to sort by decreasing
			i++;
			swap(index[i], index[j]);
		}
	}
	swap(index[i+1], index[high]);
	return i + 1;
}

void quickSort(int arr[], int index[], int low, int high) {
	if (low < high) {
		int p = partition(arr, index, low, high);
		quickSort(arr, index, low, p - 1);
		quickSort(arr, index, p + 1,high);
	}
}

void generateNums(int arr[], int index[], int n) {
    int i = 0;
    int random;
    while(i < n) {
        random = rand() % 100000;        
        arr[i] = random;
        index[i] = i;
        i++;
    }
}

void swap(int *a, int *b) {
	int temp; 
	temp = *a;
	*a = *b;
	*b = temp;
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
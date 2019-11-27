/*
    Driver file for qsort.cpp
    Reads in number of elements, and generates that number to sort.
    Reads in kth element to find, and finds that element without sorting the entire list.
    Sorts the list, and prints out the time taken. 
*/

#include <iostream>
#include "qsort.cpp"

using namespace std;

int main() {
    int n, k;
    cout << "Enter number of elements: ";
    cin >> n;
    cout << endl;
	cout << "Enter kth element to find: ";
	cin >> k;
	cout << endl;
    int arr[n], index[n];

    generateNums(arr, index, n);
	cout << "The " << k << "th value is: " << kthValue(arr, index, 0, n - 1, k) << endl;

    clock_t t = clock();
	increasingQuickSort(arr, index, 0, n-1);
	t = clock() - t;
    cout << "Sort time: " << ((double)t) / CLOCKS_PER_SEC << " seconds" << endl;
    printArr(arr, index, n);
    return 0;
}
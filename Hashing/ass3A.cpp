#include <iostream>

using namespace std;

int partition(int arr[], int index[], int low, int high) {
    int pivot = arr[index[0]];
    int i = low-1;

    for (int j = low; j < high; j++) {
        if(arr[index[j]] < pivot) {
            i++;
            int temp = index[j];
            index[j] = index[i];
            index[i] = temp;
        }
    }

    return i + 1;
}

void quickSort(int arr[], int index[], int low, int high) {
    if (low < high) {
        int pivot = partition(arr, index, low, high);        
        quickSort(arr, index, low, pivot - 1);
        quickSort(arr, index, pivot + 1, high);
    }
}

int main() {;
    int n;
    //cin >> n;
    n = 4;
    int arr [] {5, 3, 4, 1};
    int index [] {0, 1, 2, 3};
    
    //for(int i = 0; i < n; i++)
        //cout << arr[i];

    quickSort(arr, index, 0, 3);
    cout << endl;
    for (int i = 0; i < n; i++)
        cout << arr[index[i]] << " ";
    cout << endl;
    return 0;
}


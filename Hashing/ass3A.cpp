#include <iostream>

using namespace std;

int *sorted = new int[n];

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[low];
    int i = low-1;

    for (int j = low; j <= high - 1; j++) {
        if(arr[j] < pivot) {
            i++;
            int temp = arr[i];
            sorted[j]
        }
    }
}

int main() {
    int n;
    cin >> n;
    int *original = new int[n];

    for(int i = 0; i < n; i++)
        cin >> original[i];

    quickSort(original, 0, n);
    return 0;
}


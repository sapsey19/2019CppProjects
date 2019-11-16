#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

void partition(int a[], int index[], int l, int r, int &i, int &j) 
{ 
    i = l-1, j = r; 
    int p = l-1, q = r; 
    int v = a[index[r]]; 
  
    while (true) 
    { 
        // From left, find the first element greater than 
        // or equal to v. This loop will definitely terminate 
        // as v is last element 
        while (a[index[++i]] < v); 
  
        // From right, find the first element smaller than or 
        // equal to v 
        while (v < a[index[--j]]) 
            if (j == l) 
                break; 
  
        // If i and j cross, then we are done 
        if (i >= j) break; 
  
        // Swap, so that smaller goes on left greater goes on right 
        swap(index[i], index[j]); 
  
        // Move all same left occurrence of pivot to beginning of 
        // array and keep count using p 
        if (a[index[i]] == v) 
        { 
            p++; 
            swap(index[p], index[i]); 
        } 
  
        // Move all same right occurrence of pivot to end of array 
        // and keep count using q 
        if (a[index[j]] == v) 
        { 
            q--; 
            swap(index[j], index[q]); 
        } 
    } 
  
    // Move pivot element to its correct index 
    swap(index[i], index[r]); 
  
    // Move all left same occurrences from beginning 
    // to adjacent to arr[i] 
    j = i-1; 
    for (int k = l; k < p; k++, j--) 
        swap(index[k], index[j]); 
  
    // Move all right same occurrences from end 
    // to adjacent to arr[i] 
    i = i+1; 
    for (int k = r-1; k > q; k--, i++) 
        swap(index[i], index[k]); 
} 
  
// 3-way partition based quick sort 
void quicksort(int a[], int index[], int l, int r) 
{ 
    if (r <= l) return; 
  
    int i, j; 
  
    // Note that i and j are passed as reference 
    partition(a, index, l, r, i, j); 
  
    // Recur 
    quicksort(a, index, l, j); 
    quicksort(a, index, i, r); 
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

int main() {
    ifstream in;
    in.open("randomNums.txt");
    ofstream out;
    out.open("sortoutput.txt");
    int n;
    cin >> n;
    int arr[n];
    int index[n];
    generateNums(n);

    int i = 0;
    while(in >> arr[i]) {
        index[i] = i;   
        i++;
    }
    in.close();
    
    clock_t t = clock();
	quicksort(arr, index, 0, n-1);
	t = clock() - t;
    for(i = 0; i < n;  i++) {
        if(i > 0 && i % 10 == 0)
            out << endl;
        out << arr[index[i]] << " ";
    }
    out.close();
    cout << "Time: " << ((double)t) / CLOCKS_PER_SEC << " seconds" << endl;
    return 0;
}
//Header file for qsort.cpp

#include <iostream>
#include <time.h>
#include <fstream>
#include <random>
#include <climits>

void swap(int *a, int *b);
int partition(int arr[], int index[], int low, int high);
int increasingPartition(int arr[], int index[], int low, int high);
void quickSort(int arr[], int index[], int low, int high);
void increasingQuickSort(int arr[], int index[], int low, int high);
void generateNums(int arr[], int index[], int n);
void printArr(int arr[], int index[], int n);
int kthValue(int arr[], int index[], int low, int high, int k);
#include <iostream> 
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

/*
	Name: Sean Apsey
	Date: 10/6/2019
	Program: Calculates the Longest Increasing Subsequence from a given file, and prints out both the length, and the 
	subsequence itself.
	Credit to: https://www.geeksforgeeks.org/longest-increasing-subsequence-dp-3/ for help with algorithm
*/

using namespace std;

void printLIS(vector<int>& arr);
void findLIS(vector<int>& vect);

int main() {
	ifstream in;
	in.open("input.txt");
	vector<int> vect;
	string s;
	int temp;
	getline(in, s);
	while (!in.eof()) {
		getline(in, s, ',');
		temp = stoi(s);
		vect.push_back(temp);
	}
	findLIS(vect);
	in.close();
	return 0;
}

void printLIS(vector<int>& vect) {
	cout << "Longest Increasing Subsequence (LIS) = " << vect.size() << endl;
	cout << "Formed by: {";
	for (int i = 0; i < vect.size(); i++) {
		if (i == vect.size() - 1)
			cout << vect[i];
		else
			cout << vect[i] << ", ";
	}
	cout << "} " << endl;	
}

void findLIS(vector<int>& vect) {
	vector<vector<int>> LIS(vect.size());
	LIS[0].push_back(vect.at(0));

	//Time complexity is O(n^2), as there are two nested for loops
	for (int i = 1; i < vect.size(); i++)	{	
		for (int j = 0; j < i; j++)	{		
			if ((vect.at(i) > vect.at(j)) && (LIS[i].size() < LIS[j].size() + 1))
				LIS[i] = LIS[j];
		}	
		LIS[i].push_back(vect.at(i));
	}

	vector<int> max = LIS[0];
	for (vector<int> x : LIS) {
		if (x.size() > max.size()) {
			max = x;
		}
	}

	printLIS(max);
}
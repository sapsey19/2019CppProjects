#include <iostream> 
#include <vector>
#include <fstream>

using namespace std;

void printLIS(vector<int>& arr);
void findLIS(vector<int>& vect);

int main() {	
	ifstream in;
	in.open("input.txt");
	vector<int> vect;
	while (!in.eof()) {
		int temp;
		in >> temp;
		vect.push_back(temp);
	}

	findLIS(vect);
	cin.get();
	in.close();
	return 0;
}

void printLIS(vector<int>& arr) {
	cout << "Size of LIS: " << arr.size() << endl;
	for (int x : arr)
		cout << x << " ";
	cout << endl;
}

void findLIS(vector<int>& vect) {
	int n = vect.size();
	vector<vector<int>> L(n);

	L[0].push_back(vect.at(0));

	for (int i = 1; i < n; i++)	{	
		for (int j = 0; j < i; j++)	{		
			if ((vect.at(i) > vect.at(j)) && (L[i].size() < L[j].size() + 1))
				L[i] = L[j];
		}	
		L[i].push_back(vect.at(i));
	}

	vector<int> max = L[0];		
	for (vector<int> x : L)
		if (x.size() > max.size())
			max = x;
	printLIS(max);
}
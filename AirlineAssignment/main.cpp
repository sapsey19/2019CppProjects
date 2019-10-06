/********************************************************************
			* Filename: main.cpp
			* Author: Sean Apsey
			* Date Last Modified: 9/18/2019
			* Assignment No: 1
			* File Description: Program that find the optimal assignment using a branch and bound technique.
* ********************************************************************/

#include <iostream>
#include <queue>
#include <string>
#include <time.h>
#include <iomanip>
#include <limits.h>

using namespace std;
const int N = 10;	//size of matrix
struct Node {
	Node *parent;
	long long int pathCost, cost;
	int planeID, cityID;
	const char *plane, *city;
	bool assigned[N];
};

struct comp {
	bool operator()(const Node* lhs, const Node* rhs) const {
		return lhs->cost > rhs->cost;
	}
};

Node* newNode(int x, int y, bool assigned[], Node* parent, const char* pName, const char* cName);
int calculateCost(int costMatrix[N][N], int x, int y, bool assigned[]);
void printAssignments(Node* min);
int findMinCost(int costMatrix[N][N], const char* planes[N], const char* cities[N]);

/*
	I ran timed tests for 3 different sized matrices: 10x10, 30x30, and finally 90x90.
	For the 30x30 and 90x90 tests, I just used completely random numbers, rather than trying to find actual distances.
	The 10x10 took around 0.00300 seconds to finish.
	The 30x30 took around 0.00600 seconds to finish.
	The 90x90 took around 0.11000 seconds to finish...
	I decided to delete the two larger matrices because they slowed down Visual Studio.
*/
int main() {
	const char* planes[N] = { "Boeing373", "Airbus320", "Beluga", "DouglasDC", "Comac", "Boeing747", "Tristar", "Embraer", "Airbus310", "IrkutMC21" };
	const char* cities[N] = { "PHX->LIT", "SMF->DEN" ,"TLH->PHX", "DEN->BOI", "IND->LIT", "BTR-BWI", "BOI->LIT", "JAN->RNO", "ABQ->BUF", "BUF->BOI" };	//Airport codes 

	int costMatrix[N][N] = {										 //Cost per 100 miles for each city/plane pair. 
		{894, 704, 1291, 504, 375, 804, 1121, 1365, 1248, 1474},	 //City distances were found using Google Earth, plane costs were random, using srand(time(NULL))
		{2240, 1766, 3235, 1263, 942, 2017, 2810, 3422, 3128, 3694},
		{215, 169, 310, 121, 90, 193, 269, 328, 300, 354},
		{3168, 2498, 4576, 1786, 1332, 2853, 3974, 4840, 4423, 5224},
		{667, 526, 964, 376, 280, 601, 837, 1019, 932, 1100},
		{350, 276, 506, 197, 147, 315, 439, 535, 489, 578},
		{101, 80, 147, 57, 42, 91, 127, 155, 142, 167},
		{294, 231, 424, 165, 123, 264, 369, 449, 410, 485},
		{3349, 2641, 4837, 1888, 1408, 3016, 4201, 5116, 4676, 5523},
		{2784, 2194, 4020, 1569, 1170, 2506, 3491, 4252, 3886, 4590},

	};

	clock_t start, stop;
	start = clock();
	cout << endl << "The optimal cost is " << findMinCost(costMatrix, planes, cities) << endl;
	stop = clock();

	double duration = double(stop - start) / double(CLOCKS_PER_SEC);
	cout << "Time taken: " << fixed << duration << setprecision(5) << endl;

	cin.get();
	return 0;
}

Node* newNode(int x, int y, bool assigned[], Node* parent, const char* pName, const char* cName) {
	Node* node = new Node;
	for (int i = 0; i < N; i++) {
		node->assigned[i] = assigned[i];
	}
	//initialize node
	node->assigned[y] = true;
	node->parent = parent;
	node->planeID = x;
	node->cityID = y;
	node->plane = pName;
	node->city = cName;
	return node;
}

int calculateCost(int costMatrix[N][N], int x, int y, bool assigned[]) {
	long long int cost = 0;
	//keeps track of what assignments are still available
	bool available[N];
	for (int i = 0; i < N; i++)
		available[i] = true;
	for (int i = x + 1; i < N; i++) {
		int min = INT8_MAX;
		int minIndex = -1;
		for (int j = 0; j < N; j++) {
			if (!assigned[j] && available[j] && costMatrix[i][j] < min) {
				minIndex = j;
				min = costMatrix[i][j];
			}
		}
		cost += min;
		available[minIndex] = false;
	}
	return cost;
}

void printAssignments(Node* min) {
	if (min->parent == nullptr)
		return;
	printAssignments(min->parent);
	cout << "Assigned plane " << min->plane << " to airports " << min->city << endl;

}

int findMinCost(int costMatrix[N][N], const char* planes[N], const char* cities[N]) {	
	priority_queue<Node*, vector<Node*>, comp> pq;
	bool assigned[N];
	for (int i = 0; i < N; i++)
		assigned[i] = false;
	//create root node with 'null' values
	Node* root = newNode(-1, -1, assigned, nullptr, nullptr, nullptr);
	root->pathCost = root->cost = 0;
	root->planeID = -1;

	pq.push(root);

	while (!pq.empty()) {
		Node *min = pq.top();
		pq.pop();

		int i = min->planeID + 1;
		if (i == N) {
			printAssignments(min);
			return min->cost;
		}

		for (int j = 0; j < N; j++) {

			if (!min->assigned[j]) {
				Node* child = newNode(i, j, min->assigned, min, planes[j], cities[j]);
				child->pathCost = min->pathCost + costMatrix[i][j];
				child->cost = child->pathCost + calculateCost(costMatrix, i, j, child->assigned);
				pq.push(child);
			}
		}
	}
}
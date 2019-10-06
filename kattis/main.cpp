#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

struct node {
	string trip, plane;
	double cost;
};

int main() {
	double distAndCost[2][10] = { {1131.73, 892.24, 1634.32, 638, 475.91, 1018.94, 1419.35, 1728.68, 1579.87, 1865.90}, //distance
							 {7.9, 19.8, 19.0, 28.0, 5.9, 3.1, 9.0, 26.0, 29.6, 24.8} }; //cost using a random number gen
	string cities [2][10] = { {"PHX->LIT", "SMF->DEN" ,"TLH->PHX", "DEN->BOI", "IND->LIT", "BTR-BWI", "BOI->LIT", "JAN->RNO", "ABQ->BUF", "BUF->BOI"} ,
							 {"Boeing373","Airbus320","Beluga   ","DouglasDC","Comac    ","Boein747", "Tristar", "Embraer", "Airbus310", "IrkutMC21"} };
	node costMatrix[10][10];

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			costMatrix[i][j].cost = distAndCost[0][j] * distAndCost[1][i];
			costMatrix[i][j].trip = cities[0][i];
			costMatrix[i][j].plane = cities[1][j];
		}
	}
	
	cout << "\t" << "\t";
	for (int j = 0; j < 10; j++) 
		cout << setw(11) << costMatrix[j][0].trip << "\t";
	cout << endl;
	for (int i = 0; i < 10; i++) {
		cout << costMatrix[0][i].plane;
		for (int j = 0; j < 10; j++) 
			cout << setw(7) << "\t" << costMatrix[i][j].cost;
		cout << endl << endl;
	}
	double upper = 0;
	double minVals[10];
	double lower = 0;						
	for (int i = 0; i < 10; i++) {
		upper += costMatrix[i][i].cost;				//gets the diagonal, sets upper bound
		double min = INT_MAX;
		for (int j = 0; j < 10; j++) {
			if (costMatrix[j][i].cost < min) {
				min = costMatrix[j][i].cost;		//gets lowest value in each column, sets lower bound
				minVals[i] = min;
			}
		}
	}
	for (int i = 0; i < 10; i++)
		lower += minVals[i];

	cout << "Upper Bound: " << upper << endl;
	cout << "Lower Bound: " << lower << endl;


	cin.get();

	return 0;
}
#include <iostream>

using namespace std;

bool ScienceNotation(char *s);
bool containsLetters(char c);
bool containsNumbers(char c);

bool ScienceNotation(const char *s) {	
	bool fail = false;
	int numE = 0;
	int numDecimal = 0;

	for (int i = 0; s[i] != '\0'; i++) {
		if (s[i] == '+' || s[0] == 'i') {			
			if (!containsNumbers(s[i+1])) //if there's a +/-, next char must be 0-9 or .
				fail = true;
		}
		if (s[i] == 'E' || s[i] == 'e') 
			numE++;		
		if (s[i] == '.') 
			numDecimal++;		
		if (containsLetters(s[i])) //input cannot contain letters, except E/e			
			fail = true;		
	}
	if (fail) 
		return false;
	if (numE > 1 || numDecimal > 1) //only one E and one decimal allowed per input
		return false;
	return true;
	
}

int main() {
	
	if (isalpha('.')) cout << ". Is alpha" << endl;

	if (ScienceNotation("3.14e10")) 
		 cout << "true" << endl;
	else cout << "false" << endl;

	if (ScienceNotation("+.1"))
		cout << "true" << endl;
	else cout << "false" << endl;

	if (ScienceNotation("+.1E1"))
		cout << "true" << endl;
	else cout << "false" << endl;

	if (ScienceNotation("-1.1E-1"))
		cout << "true" << endl;
	else cout << "false" << endl;

	if (ScienceNotation("3.14.10"))
		cout << "true" << endl;
	else cout << "false" << endl;

	if (ScienceNotation("1.1e1.1"))
		cout << "true" << endl;
	else cout << "false" << endl;

	if (ScienceNotation("3.14ee10")) 
		cout << "true" << endl;
	else cout << "false" << endl;

	if (ScienceNotation("1e1e")) 
		cout << "true" << endl;
	else cout << "false" << endl;
	
	cin.get();
	return 0;
}

bool containsLetters(char c) {
	if (c == 'A' || c == 'a' || c == 'B' || c == 'b' || c == 'C' || c == 'c' || c == 'F' || c == 'f' || c == 'G' || c == 'g' || c == 'H' || c == 'h' || c == 'I' || c == 'i' || c == 'J' || c == 'j' || c == 'K' || c == 'k' ||
		c == 'L' || c == 'l' || c == 'M' || c == 'm' || c == 'N' || c == 'n' || c == 'O' || c == 'o' || c == 'P' || c == 'p' || c == 'Q' || c == 'q' || c == 'R' || c == 'r' || c == 'S' || c == 's' || c == 'T' || c == 't' ||
		c == 'W' || c == 'w' || c == 'X' || c == 'x' || c == 'Y' || c == 'y' || c == 'Z' || c == 'z' || c == 'D' || c == 'd' || c == 'U' || c == 'u' || c == 'V' || c == 'v') return true;	
	return false;
}

bool containsNumbers(char c) {
	if (c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9' || c == '.') return true;	
	return false;
}

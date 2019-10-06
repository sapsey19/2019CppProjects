#include <iostream>
#include <string>

using namespace std;

char token;
//string expression = "3*(4 + 5) * (6 + 7)";
string expression = "((2))";
int counter = 0;
bool error = false;
void exp();
void term();
void factor();
void number();
void digit();
void parse();
bool isTerminal(char token) {
	if (isdigit(token) || token == '+' || token == '*' || token == '(' || token == ')' || token == '\0')
		return true;
	else
		return false;
}

void getToken() {		
	token = expression[counter];
	if (token == ' ') {
		counter++;
		token = expression[counter];
	}
	if (counter == 0)
		cout << "<getToken> " << token;
	else if (counter < expression.length())
		cout << endl << "<getToken> " << token;
	counter++;	
}

void exp() {
	if(isTerminal(token))
		cout << " <exp> ";
	term();
	while (token == '+') {
		getToken();
		term();
	}	
}

void term() {
	if (isTerminal(token))
		cout << " <term> ";
	factor();
	while (token == '*') {		
		getToken();
		factor();
	}	
}

void factor() {
	if (isTerminal(token))
		cout << " <factor> ";
	if (token == '(') {
		getToken();
		cout << " <factor> ";
		exp();
		if (token == ')')
			getToken();
		else 
			error = true;
	}	
	number();
}

void number() {
	if (isTerminal(token))
		cout << " <number> ";	
	while (isdigit(token))
		digit();	
}

void digit() {
	if (isTerminal(token))
		cout << " <digit> ";
	if (isdigit(token)) 
		getToken();
	else {
		error = true;
		cout << "Expected Digit" << endl;
	}	
}

void parse() {
	cout << "<parse>" << endl;
	getToken();
	exp();
}


int main() {	
	parse();
	if (error) cout << endl << "Parse failed." << endl;
	else cout << endl << "Parsed Correctly!" << endl;
	cin.get();
	return 0;
}
#include <string>
#include <fstream>

using namespace std;

ofstream out;
char token;
string expression;
int counter = 0;
int error = 0;

//function declarations
void exp();
void term();
void factor();
void number();
void digit();
void parse();

void getToken() {
	token = expression[counter];
	//if there's a space, ignore
	if (token == ' ') {
		counter++;
		token = expression[counter];
	}
	//no need to print new line on first call
	if (counter == 0)
		out << "<getToken> " << token;
	else if (counter < expression.length())
		out << endl << "<getToken> " << token;
	counter++;
}

void exp() {
	if(isdigit(token))
		out << " <exp> ";
	term();
	while (token == '+') {
		getToken();
		term();
	}
}

void term() {
	if(isdigit(token))
		out << " <term> ";
	factor();
	while (token == '*') {
		getToken();
		factor();
	}
}

void factor() {
	if(isdigit(token))
		out << " <factor> ";
	if (token == '(') {
		getToken();
		if(isdigit(token))
			out << " <factor> ";
		exp();
		if (token == ')')
			getToken();
		else 
			error = 1;
	}
	else
		number();
}

void number() {
	if(isdigit(token))
		out << " <number> ";
	digit();
	while (isdigit(token))
		digit();	
}

void digit() {
	if(isdigit(token))
		out << " <digit> ";
	if (isdigit(token))
		getToken();
	else 
		error = 2;
}

void parse() {
	out << "<parse>" << endl;
	getToken();
	exp();
}

int main() {
	ifstream in;
	in.open("input.txt");
	out.open("output.txt");
	while(!in.eof()) {
		getline(in, expression);
		if(expression != "") {
			parse();
			switch (error) {
				case 0: out << endl << "Parsed correctly!" << endl;
						break;
				case 1: out << endl << "Parse failed: Expected closing parentheses" << endl;
						break;
				case 2: out << endl << "Parse failed: Expected digit" << endl;
						break;
			}
			//renint variables
			counter = 0;
			error = false;
			out << endl;
		}
	}

	in.close();
	out.close();
	return 0;
}

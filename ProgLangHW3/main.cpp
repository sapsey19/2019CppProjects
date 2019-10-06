#include <string>
#include <fstream>

using namespace std;

ofstream out;
char token;
string expression;
int counter = 0;
bool error = false;

//function declarations
void exp();
void term();
void factor();
void number();
void digit();
void parse();

bool printToken(char token) {
	if (token == '+' || token == '*' || token == '(' || token == ')' || token == '\0')
		return false;
	else
		return true;
}

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
	if(printToken(token))
		out << " <exp> ";
	term();
	while (token == '+') {
		getToken();
		term();
	}
}

void term() {
	if(printToken(token))
		out << " <term> ";
	factor();
	while (token == '*') {
		getToken();
		factor();
	}
}

void factor() {
	if(printToken(token))
		out << " <factor> ";
	if (token == '(') {
		getToken();
		if(printToken(token))
			out << " <factor> ";
		exp();
		if (token == ')')
			getToken();
		else
			error = true;
	}
		number();
}

void number() {
	if(printToken(token))
		out << " <number> ";
	while (isdigit(token))
		digit();
}

void digit() {
	if(printToken(token))
		out << " <digit> ";
	if (isdigit(token))
		getToken();
	else {
		error = false;
	}
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
			if (error) out << endl << "Parse failed..." << endl;
			else out << endl << "Parsed Correctly!" << endl;
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

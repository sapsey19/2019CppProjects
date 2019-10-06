#include <iostream>
#include <stack>
#include <string>
#include <regex>
#include <sstream>

using namespace std;

string getType(string str) {
	smatch m;
	if (regex_search(str, m, regex("[0-9]")))
		return "integer";
	else if (regex_search(str, m, regex("(\\+)|(\\*)")))
		return "arithmetic";
	else if (regex_search(str, m, regex("(and)|(or)")))
		return "logical";
	return "boolean";
}

int main() {
	stack<string> stk;
	string line;
	getline(cin, line);
	istringstream iss(line);
	vector<string> tokens(istream_iterator<string>{iss}, istream_iterator<string>());

	string op1, op2;	
	smatch m;
	bool failed = false;	
	for (string t : tokens) {		
		if (regex_search(t, m, regex("[0-9]|(true)|(false)"))) {
			stk.push(t);
		}
		if (regex_search(t, m, regex("(\\+)|(\\*)|(==)|(and)|(or)"))) {			
			if (stk.size() >= 2) {
				op1 = stk.top();
				stk.pop();
				op2 = stk.top();
				stk.pop();

				if (getType(op1) != getType(op2)) { cout << "TYPE ERROR" << endl; failed = true; break; } //mismatched types
				if (getType(m.str()) == "arithmetic" && (getType(op1) != "integer" || getType(op2) != "integer")) { cout << "TYPE ERROR" << endl; failed = true; break; } //wrong operator
				if (getType(m.str()) == "logical" && (getType(op1) != "boolean" || getType(op2) != "boolean")) { cout << "TYPE ERROR" << endl; failed = true; break; } //wrong operator

				if(m.str() == "+")
					stk.push(to_string(stoi(op1) + stoi(op2)));
				else if(m.str() == "*")
					stk.push(to_string(stoi(op1) * stoi(op2)));
				else if (m.str() == "==") {
					if (stoi(op1) == stoi(op2)) stk.push("true");
					else stk.push("false");
				}
				else if (m.str() == "and") {
					if (op1 == "true" && op2 == "true") stk.push("true");
					else stk.push("false");
				}
				else if (m.str() == "or") {
					if (op1 == "true" || op2 == "true") stk.push("true");
					else stk.push("false");
				}
				if (stk.size() == 0) { cout << "SYNTAX ERROR" << endl; failed = true; break; }
			}
			else { cout << "SYNTAX ERROR" << endl; failed = true; break; }
		}		
	}
	if (stk.size() > 1) { cout << "SYNTAX ERROR" << endl; failed = true; }
	if(!failed)
		cout << stk.top() << endl;
	cin.get();

	return 0;
}
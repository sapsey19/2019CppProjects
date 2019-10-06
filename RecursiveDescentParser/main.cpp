#include <iostream>
#include <vector>
#include <string>
#include <regex>

using namespace std;

typedef enum { RELATIONAL_OP, ADDITIVE_OP, MULTIPLICATIVE_OP, UNARY_OP, UNSIGNED_INT, UNSIGNED_REAL, OPEN_PAREN, CLOSE_PAREN, EOL } TokenType;

class Token {
public:
	TokenType type;
	string value;
	Token(TokenType newType = EOL, string newValue = "") {
		type = newType;
		value = newValue;
	}
};

class Tokenizer {
	string line;
	int pos;
public:
	int getPosition() {
		return pos;
	}
	void start(string newLine) {
		line = newLine;
		pos = 0;
	}
	Token peek() {
		smatch sm;
		string remaining = line.substr(pos);
		if (regex_match(remaining, sm, regex("<|<=|=|=>|>|<>")))
			return Token(RELATIONAL_OP, sm.str());
		if (regex_match(remaining, sm, regex("\\+|-|or")))
			return Token(ADDITIVE_OP, sm.str());
		if (regex_match(remaining, sm, regex("\\*|/|div|mod|and")))
			return Token(MULTIPLICATIVE_OP, sm.str());
		if (regex_match(remaining, sm, regex("\\+|-|not")))
			return Token(UNARY_OP, sm.str());
		if (regex_search(remaining, sm, regex("[0-9]"))) {
			cout << "HERHE" << endl;
			return Token(UNSIGNED_INT, sm.str());
		}
		if (regex_match(remaining, sm, regex("\\(")))
			return Token(OPEN_PAREN, sm.str());
		if (regex_match(remaining, sm, regex("\\)")))
			return Token(CLOSE_PAREN, sm.str());
		//if (regex_match(remaining, sm, regex("[0-9]")))
		//    return Token(UNSIGNED_REAL,sm.str());
		return Token();
	}
	Token next() {
		Token t;
		t = peek();
		pos += t.value.size();
		return t;
	}
};

class ExpressionTree {
	ExpressionTree *left, *right;
	Token operation;
public:
	ExpressionTree(Token t = Token(), ExpressionTree *newLeft = NULL, ExpressionTree *newRight = NULL) {
		operation = t;
		left = newLeft;
		right = newRight;
	}
	void showRPN(ostream &out) {
		if (left != NULL) left->showRPN(out);
		if (right != NULL) right->showRPN(out);
		out << operation.value;
	}
};

class Parser {
	Tokenizer tokenizer;
	string error;
public:
	bool expression(ExpressionTree &tree) {
		return false;
	}
	bool additiveExpression(ExpressionTree &tree) {
		return false;
	}
	bool multiplicativeExpression(ExpressionTree &tree) {
		return false;
	}
	bool unaryExpression(ExpressionTree &tree) {
		return false;
	}
	bool primaryExpression(ExpressionTree &tree) {
		Token next = tokenizer.next();
		if (next.type == OPEN_PAREN) {
			ExpressionTree subtree;
			if (expression(subtree)) {
				next = tokenizer.next();
				if (next.type != CLOSE_PAREN) error = "Syntax error missing )";
				else {
					tree = subtree;
					return true;
				}
			}
			else error = "Expected expression after (";
		}
		else if (next.type == UNSIGNED_INT) {
			tree = ExpressionTree(next); // Just a leaf with an Unsigned Int
			return true;
		}
		else if (next.type == UNSIGNED_REAL) {
			tree = ExpressionTree(next); // Just a leaf with an Unsigned Real
			return true;
		}
		else error = "Syntax error expected a primary expression";
		return false;
	}
	ExpressionTree scan(string s) {
		ExpressionTree tree; // Empty Tree Really
		tokenizer.start(s);
		if (primaryExpression(tree)) {
			return tree;
		}
		else {
			cerr << error << ":" << tokenizer.getPosition() << endl;
		}
		return ExpressionTree();
	}
};

vector<string> testExpressions;
void loadTest() {
	//Some expressions to try that should work
	testExpressions.push_back("1+2");
	/*testExpressions.push_back("(1+2)*3");
	testExpressions.push_back("((1+2)*3)");
	testExpressions.push_back("1.0E10+2.0E10");
	testExpressions.push_back("(1.0E10+2.0E10)*3.0E10");
	testExpressions.push_back("((1.0E10+2.0E10)*3.0E10)");
	//Some that should error out is some informative way
	testExpressions.push_back("1+");
	testExpressions.push_back("(1+2*3");
	testExpressions.push_back("(1+2)*3");
	testExpressions.push_back("1.0E+2.0E10");
	testExpressions.push_back("(1.0E10+2.0E)*3.0E10");
	testExpressions.push_back("((1.0E10+2.0E10)*3.010)");
	*/
}

int main() {
	loadTest();
	Parser p;
	for (unsigned i = 0; i < testExpressions.size(); i++) {
		ExpressionTree t = p.scan(testExpressions[i]);
		t.showRPN(cout);
	}
	cin.get();
	return 0;
}


/* Language Specification
expression:
   expression relational-op additive-expression
   additive-expression

relational-op: one of
   <  <=  =  <>  =>  >

additive-expression:
   additive-expression additive-op multiplicative-expression
   multiplicative-expression

additive-op: one of
   +  -  or

multiplicative-expression:
   multiplicative-expression multiplicative-op unary-expression
   unary-expression

multiplicative-op: one of
   *  /  div  mod  and  // in

unary-expression:
   unary-op unary-expression
   primary-expression

unary-op:  one of
   +  -  not

primary-expression:
   // variable
   unsigned-integer
   unsigned-real
   // string
   // nil
   // funcid ( expression-list )
   // [ element-list ]
   ( expression ) */

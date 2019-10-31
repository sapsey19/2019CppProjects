#include <iostream>
#include <vector>
#include <string>
#include <regex>

using namespace std;

typedef enum { PLUSMINUS_OP, RELATIONAL_OP, ADDITIVE_OP, MULTIPLICATIVE_OP, 
    UNSIGNED_INT, UNSIGNED_REAL, OPEN_PAREN, CLOSE_PAREN, OR, AND, NOT, EOL } TokenType;

class Token {
public:
    TokenType type;
    string value;
    Token(TokenType newType=EOL, string newValue="") {
        type=newType;
        value=newValue;
    }
};

class Tokenizer{
    string line;
    int pos;
    vector<Token> tokenList;
public:
    bool failedMatch = false;
    string failedToken;
   
    int getPosition() {
        return pos;
    }

    void start(string newLine) {
        tokenList.clear();
        line=newLine;
        pos=0;
        failedMatch = false;
    }

    void tokenize(string line) {
        string token;
        smatch sm;
        string remaining = line;
        while(remaining.length() > 0) {
            if(remaining[0] == ' ')
                remaining = remaining.substr(1);
            if(regex_match(remaining, sm, regex("(\\+|-).*")))            
                tokenList.emplace_back(ADDITIVE_OP, sm[1]);
            else if(regex_match(remaining, sm, regex("([0-9]+\\.[0-9]+([Ee][+-]?[0-9]+)?).*")))
                tokenList.emplace_back(UNSIGNED_REAL, sm[1]);            
            else if(regex_match(remaining, sm, regex("([0-9]+).*")))
		        tokenList.emplace_back(UNSIGNED_INT, sm[1]);            
            else if(regex_match(remaining, sm, regex("((<=)|(>=)|(<>)|(=)|(>)|(<)).*"))) 
                tokenList.emplace_back(RELATIONAL_OP, sm[1]);
            else if (regex_match(remaining, sm, regex("(or).*"))) 
                tokenList.emplace_back(OR, sm[1]);
            else if (regex_match(remaining, sm, regex("(not).*")))
                tokenList.emplace_back(NOT, sm[1]);
            else if(regex_match(remaining, sm, regex("(and).*")))
                tokenList.emplace_back(AND, sm[1]);
            else if(regex_match(remaining, sm, regex("(\\*|/|div|mod|and).*")))
                tokenList.emplace_back(MULTIPLICATIVE_OP, sm[1]);
            else if(regex_match(remaining, sm, regex("(\\().*"))) 
                tokenList.emplace_back(OPEN_PAREN, sm[1]);            
            else if(regex_match(remaining, sm, regex("(\\)).*")))
                tokenList.emplace_back(CLOSE_PAREN, sm[1]);
            else {
                //if could not match token
                failedMatch = true;
                failedToken = remaining;
                break;
            }
            remaining = remaining.substr(sm[1].length());
        }      
    }

    Token peek() {
        if(pos<tokenList.size()) {
            return tokenList[pos];
        }
        else {
            Token t;
            t.type = EOL;
            t.value = "EOL";
            return t;
        }
    }

    Token next() {
        Token t;
        if(pos < tokenList.size()) {
            t = tokenList[pos];
            pos++;
        }
        else {
            t.type = EOL;
            t.value = "EOL";
        }
        return t;
    }
};

class ExpressionTree{
    ExpressionTree *left, *right;
    Token operation;
public:
    ExpressionTree(Token t = Token(), ExpressionTree *newLeft=nullptr, ExpressionTree *newRight=nullptr) {
        operation = t;
        left = newLeft;
        right = newRight;
    }

    ExpressionTree(ExpressionTree *tree) {
        operation = tree->operation;
        left = tree->left;
        right = tree->right;
    }

    void showRPN(ostream &out) {   
        if (left!=nullptr) 
            left->showRPN(out);
        if (right!=nullptr)
            right->showRPN(out);
        if(operation.type != EOL)
            out << operation.value << " ";
    }

    void show(ostream &out) {
        if (left!=nullptr) {
			  left-> show(out);
			  out << "<--";
	  	}
        out << "[" << operation.value << "]";
        if (right!=nullptr) {
			  out << "-->";
			  right->show(out);
		  }
    }
};

class Parser {
    Tokenizer tokenizer;
    string error;
public:

    bool expression(ExpressionTree &tree) {        
        ExpressionTree *subtree = new ExpressionTree();
        ExpressionTree *left = new ExpressionTree();
        Token last;
        Token next;
        while(additiveExpression(*subtree)) {
            next = tokenizer.peek();
            if(!(next.type == RELATIONAL_OP))
                break;
            else {
                next = tokenizer.next();
                if(left != nullptr)
                    left = new ExpressionTree(*subtree);
                subtree = new ExpressionTree();
                last = next;
            }
        }
        if(left != nullptr)
            tree = new ExpressionTree(last, left, subtree);
        else 
            tree = new ExpressionTree(*subtree);
    }

    bool additiveExpression(ExpressionTree &tree) {
        ExpressionTree *subtree = new ExpressionTree();
        ExpressionTree *left = nullptr;
        Token last;
        Token next;
        while(multiplicativeExpression(*subtree)) {
            next = tokenizer.peek();
            if(!(next.type == ADDITIVE_OP || next.type == OR))
                break;
            else {
                next = tokenizer.next();
                if(left != nullptr)
                    left = new ExpressionTree(last, left, subtree);
                else 
                    left = subtree;
                subtree = new ExpressionTree();
                last = next;                
            }
        }
        if(left != nullptr) 
            tree = new ExpressionTree(last, left, subtree);
        else 
            tree = new ExpressionTree(subtree);
        return true;
    }

    bool multiplicativeExpression(ExpressionTree &tree) {
        ExpressionTree *subtree = new ExpressionTree();
        ExpressionTree *left = nullptr;
        Token last;
        Token next;
        while(unaryExpression(*subtree)) {
            next = tokenizer.peek();
            if(!(next.type == MULTIPLICATIVE_OP || next.type == AND))
                break;
            else {
                next = tokenizer.next();
                if(left != nullptr)
                    left = new ExpressionTree(last, left, subtree);
                else
                    left = subtree;
                subtree = new ExpressionTree();
                last = next;
            }
        }
        if (left != nullptr)
            tree = new ExpressionTree(last, left, subtree);
        else 
            tree = new ExpressionTree(subtree);
        
        return next.type = EOL;
    }

    bool unaryExpression(ExpressionTree &tree) {
        Token next = tokenizer.peek();
        if(next.type == PLUSMINUS_OP || next.type == NOT) {
            ExpressionTree *subtree = new ExpressionTree();
            next = tokenizer.next();
            if(unaryExpression(*subtree)) {
                tree = new ExpressionTree(next, nullptr, subtree);
                return true;
            }
                
        }
        else if(primaryExpression(tree)) {
            return true;
        }
        if(error.length() < 1)
            error = "Expected primary expression";
        return false;
    }

    bool primaryExpression(ExpressionTree &tree) {
        Token next = tokenizer.next();       
        if(next.type == UNSIGNED_INT || next.type == UNSIGNED_REAL) {
            tree = new ExpressionTree(next);
            return true;
        }
        else if(next.type == OPEN_PAREN) {
            ExpressionTree *subtree = new ExpressionTree();
            if(expression(*subtree)) {
                tree = new ExpressionTree(subtree);
                if(tokenizer.next().type != CLOSE_PAREN) {
                    error = "Error: Missing closing parenthesis";
                    return false;
                }
                else return true;
            }
        }
        else if(next.type == EOL) {
            error = "Error: Expected integer or real number";
            return false;
        }
    }

    ExpressionTree scan(string s) {
        ExpressionTree tree = new ExpressionTree();
        tokenizer.start(s);
        tokenizer.tokenize(s);
      
        if(expression(tree) && error.length() < 1)
            return tree;
        if(tokenizer.failedMatch)
            cerr << "Unknown token: '" << tokenizer.failedToken << "'";   
        else
            cerr << "For expression '" << s << "' " << error << " at token number: " << tokenizer.getPosition() + 1;
        return ExpressionTree();
    }
};

void test(Parser p) {
    vector<string> testExpressions;
    //tests that should work
    testExpressions.push_back("1+2");
    testExpressions.push_back("(3+4)*5");
    testExpressions.push_back("((6 + 7) * 8)");
    testExpressions.push_back("1.0 < 2.0");
    testExpressions.push_back("(5.0e23 + 6.0E12) > 3.0E10");
    testExpressions.push_back("((7.0E10 + 8.0e10) / 6.0e10)");
    testExpressions.push_back("(12.0 + 10.0) >= 22.0 and (13.0 * 14.0 <> 28.0)");
    testExpressions.push_back("not(1 = 2)");

    //tests that should error out
    testExpressions.push_back("1+");
    testExpressions.push_back("(1+2*3");
    testExpressions.push_back("(1+2)*3");
    testExpressions.push_back("1.0E+2.0E10");
    testExpressions.push_back("(1.0E10+2.0E)*3.0E10");
    testExpressions.push_back("((1.0E10+2.0E10)*3.010)");

    for (int i = 0; i < testExpressions.size(); i++) {        
        ExpressionTree t = new ExpressionTree(p.scan(testExpressions[i]));        
        t.showRPN(cout);
        //cout << endl;
        //t.show(cout);
        cout << endl;
    }
}

void userInput(Parser p) {
    string exp;
    getline(cin, exp);
    ExpressionTree t = new ExpressionTree(p.scan(exp));
    t.showRPN(cout);
    cout << endl;
}

int main() {
    Parser p;

    //for running a bunch of pre-defined test expressions 
    test(p);

    //for taking user input for a single expresion
    //userInput(p);
    return 0;
}
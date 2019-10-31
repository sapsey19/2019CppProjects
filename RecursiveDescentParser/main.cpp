#include <iostream>
#include <vector>
#include <string>
#include <regex>

using namespace std;

#define DEBUG false
//Token types
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
    int getPosition() {
        return pos;
    }

    void start(string newLine) {
        tokenList.clear();
        line=newLine;
        pos=0;
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
            else if(regex_match(remaining, sm, regex("(<|(<=)|=|(=>)|>|(<>)).*")))
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
            t.value = "$";
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

//ExpressionTree should store members of the expression in a binary tree
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
            if (DEBUG) cout << "expression: " << next.value << endl;
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
            if(DEBUG) cout << "additveExpression: " << next.value << endl;
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
            if(DEBUG) cout << "multiplicativeExpression: " << next.value << endl;
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
        if(DEBUG) cout << "unaryExpression: " << next.value << endl;
        if(next.type == PLUSMINUS_OP || next.type == NOT) {
            ExpressionTree *subtree = new ExpressionTree();
            next = tokenizer.next();
            if(unaryExpression(*subtree)) {
                tree = new ExpressionTree(next, nullptr, subtree);
                cout << "here: " << next.type << endl;
                return true;
            }           
                
        }
        else if(primaryExpression(tree)) {
            return true;
        }
        error = "Expected primary expression";
        return false;
    }

    bool primaryExpression(ExpressionTree &tree) {
        if(DEBUG) cout << "primaryExpression" << endl;
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
                    error = "Error: Missing closing parenthesis.";
                    return false;
                }
                else return true;
            }
        }
    }

    ExpressionTree scan(string s) {
        ExpressionTree tree = new ExpressionTree();
        tokenizer.start(s);
        tokenizer.tokenize(s);
      
        if(expression(tree))
            return tree;        
        else
            cerr << error << ":" << tokenizer.getPosition() << endl;
        return ExpressionTree();
    }
};

int main() {
    vector<string> testExpressions;
    testExpressions.push_back("1+2");
    testExpressions.push_back("(3+4)*5");
    testExpressions.push_back("((6 + 7) * 8)");
    testExpressions.push_back("1.0 < 2.0");
    testExpressions.push_back("(5.0e23 + 6.0E12) >= 3.0E10");
    testExpressions.push_back("((7.0E10 + 8.0e10) * 6.0e10)");
    //testExpressions.push_back("(12.0 + 10.0) >= 22.0 and (13.0 + 14.0 = 28.0)");

    //still need to work on error checking
    testExpressions.push_back("1+");
    testExpressions.push_back("(1+2*3");
    testExpressions.push_back("(1+2)*3");
    testExpressions.push_back("1.0E+2.0E10");
    testExpressions.push_back("(1.0E10+2.0E)*3.0E10");
    testExpressions.push_back("((1.0E10+2.0E10)*3.010)");

    Parser p;
    for (int i = 0; i < testExpressions.size(); i++) {        
        ExpressionTree t = new ExpressionTree(p.scan(testExpressions[i]));        
        t.showRPN(cout);
        cout << endl;
         
    }
    return 0;
}
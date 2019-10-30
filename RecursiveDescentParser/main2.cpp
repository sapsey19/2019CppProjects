/*
  Program: Recursive Descent Parser. Takes an expression like (1+2)*3 and prints the
    Reverse Polish Notation (RPN) of the expression. Also known as Postfix traversal of the ExpressionTree.
    For example, (1+2)*3 should print out as 1 2 + 3 ∗.
    The regex matching in peek() works as far as I know .
    At the bottom of the code there are some requirements that are supposed to be met for what the program can handle.

    The biggest issue I'm having is understanding the ExpressionTree part. I get the regex matching and the parsing,
    but storing everything in a binary tree gets confusing and hard to follow.

*/

#include <iostream>
#include <vector>
#include <string>
#include <regex>

using namespace std;

#define DEBUG false
//Token types
typedef enum { PLUSMINUS_OP, RELATIONAL_OP, ADDITIVE_OP, MULTIPLICATIVE_OP, UNARY_OP, 
    UNSIGNED_INT, UNSIGNED_REAL, OPEN_PAREN, CLOSE_PAREN, EOL } TokenType;

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
    vector<Token>::iterator it;
public:
    int getPosition() {
        return pos;
    }

    void start(string newLine) {
        line=newLine;
        pos=0;
    }

    void tokenize(string line) {
        string token;
        smatch sm;
        string remaining = line;
        int count = 1;       
        while(!remaining.empty()) {
            if(regex_match(remaining, sm, regex("(\\+|-).*")))            
                tokenList.emplace_back(ADDITIVE_OP, sm[1]);
            else if(regex_match(remaining, sm, regex("([0-9]+\\.[0-9]+([Ee][+-]?[0-9]+)?).*")))
                tokenList.emplace_back(UNSIGNED_REAL, sm[1]);            
            else if(regex_match(remaining, sm, regex("([0-9]+).*")))
		        tokenList.emplace_back(UNSIGNED_INT, sm[1]);            
            else if(regex_match(remaining, sm, regex("(<|<=|=|=>|>|<>).*")))
                 tokenList.emplace_back(RELATIONAL_OP, sm[1]);
            //else if (regex_match(remaining, sm, regex("(or).*")))
                //return Token(ADDITIVE_OP,sm[1]);
            else if(regex_match(remaining,sm,regex("(\\*|/|div|mod|and).*")))
                tokenList.emplace_back(MULTIPLICATIVE_OP, sm[1]);
            //if (regex_match(remaining,sm,regex("(not).*")))
                //return Token(UNARY_OP,sm[1]);
            else if(regex_match(remaining,sm,regex("(\\().*"))) 
                tokenList.emplace_back(OPEN_PAREN,sm[1]);            
            else if(regex_match(remaining,sm,regex("(\\)).*")))
                tokenList.emplace_back(CLOSE_PAREN,sm[1]); 
            remaining = remaining.substr(sm[1].length());
            count++;
        }
        it = tokenList.begin();
    }

    //Function peek grabs next token, doesn't eat it.
    //Function next grabs next token and eats it.
    Token peek() {
        if(it<tokenList.end())
            return (*it);
        else {
            Token t;
            t.type = EOL;
            t.value = "$";
            return t;
        }
    }

    Token next() {
        Token t;
        if(it < tokenList.end()) {
            t = *it;
            it++;
        }
        else {
            t.type = EOL;
            t.value = "$";
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
      //postfix traversal of the tree  
        if (left!=nullptr)
            left->showRPN(out);
        if (right!=nullptr)
            right->showRPN(out);
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
            if(!(next.type == ADDITIVE_OP))
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
            if(!(next.type == MULTIPLICATIVE_OP))
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
        if(next.type == UNARY_OP || next.type == PLUSMINUS_OP) {
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
        if(next.type == UNSIGNED_INT) {
            tree = new ExpressionTree(next);
            return true;
        }
        else if(next.type == OPEN_PAREN) {
            ExpressionTree *subtree = new ExpressionTree();
            if(expression(*subtree)) {
                tree = new ExpressionTree(subtree);
                if(tokenizer.next().type != CLOSE_PAREN) {
                    error = "ERROR: Mismatched (";
                    return false;
                }
                else return true;
            }
            else {
                error = "ERROR: Expected expression within ()";
                return false;
            }
        }
    }

    ExpressionTree scan(string s) {
        ExpressionTree tree = new ExpressionTree();
        tokenizer.tokenize(s);
        tokenizer.start(s);
      
        if(expression(tree))
            return tree;        
        else
            cerr << error << ":" << tokenizer.getPosition() << endl;
        return ExpressionTree();
    }
};

/*
void loadTest() {
    //Some expressions to try that should work
    testExpressions.push_back("1+2");
    testExpressions.push_back("(1+2)*3");
    testExpressions.push_back("((1+2)*3)");
    testExpressions.push_back("1.0E10+2.0E10");
    testExpressions.push_back("(1.0E10+2.0E10)*3.0E10");
    testExpressions.push_back("((1.0E10+2.0E10)*3.0E10)");
    //Some that should error out in some informative way
    testExpressions.push_back("1+");
    testExpressions.push_back("(1+2*3");
    testExpr essions.push_back("(1+2)*3");
    testExpressions.push_back("1.0E+2.0E10");
    testExpressions.push_back("(1.0E10+2.0E)*3.0E10");
    testExpressions.push_back("((1.0E10+2.0E10)*3.010)");
}
*/
int main() {
    vector<string> testExpressions;
    //testExpressions.push_back("1+2");
    testExpressions.push_back("(3+4)*5");
    testExpressions.push_back("((6+7)*8)");
    testExpressions.push_back("1.0E10+2.0E10");
    testExpressions.push_back("(1.0E10+2.0E10)*3.0E10");
    testExpressions.push_back("((1.0E10+2.0E10)*3.0E10)");

    Parser p;
    ExpressionTree t;
    for (int i = 0; i < testExpressions.size(); i++) {        
        t = new ExpressionTree(p.scan(testExpressions[i]));        
        t.showRPN(cout);
        cout << endl;
        //need to clear tree each time???? 
    }
  //ExpressionTree t = p.scan("1+");
  //t.show(cout);
  //cout << endl;
  //t.showRPN(cout);
  cout << endl;
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
 
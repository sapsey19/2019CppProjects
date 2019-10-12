#include <iostream>
#include <vector>
#include <string>
#include <regex>

using namespace std;

typedef enum { PLUSMINUS_OP,RELATIONAL_OP,ADDITIVE_OP,MULTIPLICATIVE_OP,UNARY_OP,UNSIGNED_INT,UNSIGNED_REAL,OPEN_PAREN,CLOSE_PAREN,EOL } TokenType;

class Token {
    public:
    TokenType type;
    string value;
    Token(TokenType newType=EOL,string newValue="") {
      type=newType;
      value=newValue;  
    }
};

class Tokenizer{
    string line;
    int pos;
    public:
    int getPosition() {
        return pos;
    }
    void start(string newLine) {
        line=newLine;
        pos=0;
    }
    Token peek() {
        smatch sm;
        string remaining=line.substr(pos);
        if (regex_match(remaining,sm,regex("(\\+|-).*"))) 
          return Token(PLUSMINUS_OP,sm[1]);
        if (regex_match(remaining,sm,regex("(<|<=|=|=>|>|<>).*"))) 
          return Token(RELATIONAL_OP,sm[1]);
        if (regex_match(remaining,sm,regex("(or).*"))) 
          return Token(ADDITIVE_OP,sm[1]);
        if (regex_match(remaining,sm,regex("(\\*|/|div|mod|and).*"))) 
          return Token(MULTIPLICATIVE_OP,sm[1]);
        if (regex_match(remaining,sm,regex("(not).*"))) 
          return Token(UNARY_OP,sm[1]);
        if (regex_match(remaining,sm,regex("([0-9]+).*"))) 
		      return Token(UNSIGNED_INT,sm[1]);	    	
        if (regex_match(remaining,sm,regex("(\\().*"))) 
          return Token(OPEN_PAREN,sm[1]);
        if (regex_match(remaining,sm,regex("(\\)).*"))) 
          return Token(CLOSE_PAREN,sm[1]);
//        if (regex_match(remaining,sm,regex("[0-9]+"))) 
//          return Token(UNSIGNED_REAL,sm.str());
        return Token();
    }
    Token next() {
        Token t;
        t=peek();
        pos+=t.value.size();
        return t;
    }
};

class ExpressionTree{
    ExpressionTree *left,*right;
    Token operation;
    public:
    ExpressionTree(Token t=Token(),ExpressionTree *newLeft=NULL,ExpressionTree *newRight=NULL){
        operation=t;
        left=newLeft;
        right=newRight;
    }
    void showRPN(ostream &out) {
        if (left!=NULL) left->showRPN(out);
        if (right!=NULL) right->showRPN(out);
        out << operation.value;
    }
    void show(ostream &out) {
        if (left!=NULL) {
			left->show(out);
			out << "<--";
		}
        out << "[" <<operation.value<<"]"; 
        if (right!=NULL) {
			out <<
			"-->";
			right->show(out);
		}
    }
};

class Parser{
    Tokenizer tokenizer;
    string error;
    public:
    bool expression(ExpressionTree &tree) {
        return multiplicativeExpression(tree);
    }
    bool additiveExpression(ExpressionTree &tree) {
        return false;
    }
    bool multiplicativeExpression(ExpressionTree &tree) {
	    ExpressionTree *subtree=new ExpressionTree();		
	    ExpressionTree *left=NULL;
	    Token last;
	    Token next=tokenizer.peek();
		while (unaryExpression(*subtree)) {
			// Do something with sub tree
			next=tokenizer.peek();
			if (!(next.type==MULTIPLICATIVE_OP))
			  break;
			else {
			  next=tokenizer.next();
			  if (left!=NULL)
				  left=new ExpressionTree(last,left,subtree);
			  else 
			    left=subtree;
			  subtree=new ExpressionTree();
			  last=next;
			}
		}
		if (left!=NULL) {
			tree=ExpressionTree(last,left,subtree);
		}
		return next.type==EOL;
    }
    bool unaryExpression(ExpressionTree &tree) {
		Token next=tokenizer.peek();
		if (next.type==UNARY_OP || next.type==PLUSMINUS_OP) {
		    ExpressionTree *subtree=new ExpressionTree();
			next=tokenizer.next();
			if (unaryExpression(*subtree)) {
				tree=ExpressionTree(next,NULL,subtree);
				cout << "yeah 2" << endl;
			    return true;
			} else error="Expected unary expression";
		} else if (primaryExpression(tree)){
			cout << "yeah 3" << endl;
			return true;
		} else error="Expected a unary expression";
        return false;
    }
    bool primaryExpression(ExpressionTree &tree) {
        Token next=tokenizer.next();
        if (next.type==OPEN_PAREN) {
			cout << "Open Paren" << endl;
            ExpressionTree subtree;
            if (expression(subtree)){
              next=tokenizer.next();
              if (next.type!=CLOSE_PAREN)
			   	error="Syntax error missing )";
              else {
                tree=subtree;
                cout << "Yeah" << endl;
                return true;
              }
            } else
				error="Expected expression after (";
        }
        else if (next.type==UNSIGNED_INT) {
			cout << "uint" << endl;
            tree=ExpressionTree(next); // Just a leaf with an Unsigned Int
			next = tokenizer.next();
			if(next.type == PLUSMINUS_OP) {
				cout << "plus/minus" << endl;
				next = tokenizer.next();
				if(next.type == UNSIGNED_INT) {
					cout << "uint" << endl;
				}
				else
					error = "Expected Integer after Operator";
			}
            return true;
        }
        else if (next.type==UNSIGNED_REAL) {
			cout << "ureal" << endl;
            tree=ExpressionTree(next); // Just a leaf with an Unsigned Real
            return true;
        }
        else error="Syntax error expected a primary expression";
        return false;
    }
    ExpressionTree scan(string s){
        ExpressionTree tree; // Empty Tree Really
        tokenizer.start(s);
        if (primaryExpression(tree)) {
            return tree;
        } else {
          cerr << error << ":" << tokenizer.getPosition() << endl;
        }
        return ExpressionTree();
    }
};

vector<string> testExpressions;
void loadTest() {
 //Some expressions to try that should work
 testExpressions.push_back("1+2");
 testExpressions.push_back("(1+2)*3");
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
}

int main() {
  Parser p;
/*  for (unsigned i=0;i<testExpressions.size();i++) {
    ExpressionTree t=p.scan(testExpressions[i]);
    t.showRPN(cout);
  }*/
  ExpressionTree t=p.scan("1+2");
  t.show(cout);
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

#include <iostream>
#include <string> 
#include <utility>
#include <vector>
#include <regex>

using namespace std;

class Token {
public:
    enum Type { UNSIGNED_INT, UNSIGNED_REAL, RELATIONAL_OP, LOGICAL_AND, LOGICAL_OR, 
        MULTIPLICATIVE_OP, OPEN_PAREN, CLOSED_PAREN, EoF, NONE, LOGICAL_NOT, PLUS_MINUS} type = NONE;

    int id;
    string op = "";

    Token(Type _type, string _op, int _id) {
        type = _type;
        op = std::move(_op);
        id = _id;
    }

    Token() {
        type = NONE;
        op = "";
        id = 0;
    }
};

class Tree {
public:
    Token value;
    Tree *left, *right;

    explicit Tree(Token _value = Token(), Tree *_left = nullptr, Tree *_right = nullptr) {
        value = std::move(_value);
        left = _left;
        right = _right;
    }

    explicit Tree(Tree *&t) {
        value = t->value;
        left = t->left;
        right = t->right;
    }

    static void printRPN(Tree *tree, ostream &out) {
        if (tree == nullptr || tree->value.type == Token::NONE)
            return;
        if (tree->left != nullptr && tree->left->value.type != Token::NONE)
            printRPN(tree->left, out);
        if (tree->right != nullptr && tree->right->value.type != Token::NONE)
            printRPN(tree->right, out);
        if (tree->value.type != Token::NONE)
            out << tree->value.op << ' ';
    }

    static void print(Tree *tree, ostream &out) {
        if (tree == nullptr || tree->value.type == Token::NONE)
            return;
        if (tree->left != nullptr && tree->left->value.type != Token::NONE)
            print(tree->left, out);
        if (tree->value.type != Token::NONE)
            out << tree->value.op << ' ';
        if (tree->right != nullptr && tree->right->value.type != Token::NONE)
            print(tree->right, out);
    }
};

class Tokenizer {
    vector<Token> tokens;
    vector<Token>::iterator it;
public:
    Tokenizer() = default;

    void tokenize(string line) {
        string token;
        smatch sm;
        string remaining = std::move(line);
        int count = 1;
        bool matched = true;
        while(!remaining.empty()) {
            Token t;

            while(remaining[0] == ' ')
                remaining = remaining.substr(1);
            
            /*
            if (regex_match(remaining, sm, regex("((<=)|(=>)|(<>)|=|<|>).*"))) 
                tokens.emplace_back(Token::RELATIONAL_OP, sm[1], count);
            else if (regex_match(remaining, sm, regex("(\\+|-).*")))
                tokens.emplace_back(Token::PLUS_MINUS, sm[1], count);
            else if(regex_match(remaining, sm, regex("(and).*")))
                tokens.emplace_back(Token::LOGICAL_AND, sm[1], count);
            else if(regex_match(remaining, sm, regex("(or).*")))
                tokens.emplace_back(Token::LOGICAL_OR, sm[1], count);
            else if(regex_match(remaining, sm, regex( "(\\*|/|(div)|(mod)).*")))
                tokens.emplace_back(Token::MULTIPLICATIVE_OP, sm[1], count);
            else if(regex_match(remaining, sm, regex("(not).*")))
                tokens.emplace_back(Token::LOGICAL_NOT, sm[1], count);
            else if(regex_match(remaining, sm, regex("([0-9]+\\.[0-9]+[Ee][+-]?[0-9]+)?).*")))
                tokens.emplace_back(Token::UNSIGNED_REAL, sm[1], count);
            */
            if (regex_match(remaining, sm, regex("(\\+|-).*")))
                tokens.emplace_back(Token::PLUS_MINUS, sm[1], count);
            else if(regex_match(remaining, sm, regex("([0-9]+).*")))
                tokens.emplace_back(Token::UNSIGNED_INT, sm[1], count);
            else if(regex_match(remaining, sm, regex("(\\().*")))
                tokens.emplace_back(Token::OPEN_PAREN, sm[1], count);
            else if(regex_match(remaining, sm, regex("(\\)).*")))
                tokens.emplace_back(Token::CLOSED_PAREN, sm[1], count);
            else {
                cerr << "No tokens" << remaining << endl;
                tokens[0] = Token();
                break;
            }
            remaining = remaining.substr(sm[1].length());
            count++;
        }
        it = tokens.begin();
    }

    Token peek() {
        if (it < tokens.end())
            return (*it);
        else {
            Token t;
            t.type = Token::EoF;
            t.op = "$";
            return t;
        }
    }

    Token next() {
        Token t;
        if (it < tokens.end()) {
            t = *it;
            it++;
        }
        else {
            t.type = Token::EoF;
            t.op = "$";
        }
        return t;
    }
};

class RecursiveDescent {
    Tokenizer tokens;
    string error;

    bool expression(Tree *&t) {
        Tree *subtree = new Tree();
        Tree *left = nullptr;
        Token last, next;
        while(additiveExpression(subtree)) {
            next = tokens.peek();
            if(!(next.type == Token::RELATIONAL_OP)) {
                break;
            }
            else {
                next = tokens.next();
                if(left != nullptr)
                    left = new Tree(last, left, subtree);
                else 
                    left = new Tree(subtree);
                subtree = new Tree();
                last = next;
            }
        }
        if (left != nullptr)
            t = new Tree(last, left, subtree);
        else 
            t = new Tree(subtree);
        return true;
    }

    bool additiveExpression(Tree *&t) {
        Tree *subtree = new Tree();
        Tree *left = nullptr;
        Token last, next;
        while(additiveExpression(subtree)) {
            next = tokens.peek();
            if(!(next.type == Token::PLUS_MINUS || next.type == Token::LOGICAL_OR)) {
                break;
            }
            else {
                next = tokens.next();
                if(left != nullptr)
                    left = new Tree(last, left, subtree);
                else 
                    left = new Tree(subtree);
                subtree = new Tree();
                last = next;
            }
        }
        if (left != nullptr)
            t = new Tree(last, left, subtree);
        else 
            t = new Tree(subtree);
        return true;
    }

     bool multiplicativeExpression(Tree *&t) {
        Tree *subtree = new Tree();
        Tree *left = nullptr;
        Token last, next;
        while(additiveExpression(subtree)) {
            next = tokens.peek();
            if(!(next.type == Token::MULTIPLICATIVE_OP || next.type == Token::LOGICAL_AND)) {
                break;
            }
            else {
                next = tokens.next();
                if(left != nullptr)
                    left = new Tree(last, left, subtree);
                else 
                    left = new Tree(subtree);
                subtree = new Tree();
                last = next;
            }
        }
        if (left != nullptr)
            t = new Tree(last, left, subtree);
        else 
            t = new Tree(subtree);
        return true;
    }

    bool unaryExpression(Tree *&t) {
        Token operation = tokens.peek();
        if(operation.type == Token::PLUS_MINUS || operation.type == Token::LOGICAL_NOT) {
            Tree *subtree = new Tree();
            operation = tokens.next();
            if(unaryExpression(subtree)) {
                t = new Tree(operation, nullptr, subtree);
                return true;
            }
        }
        else return (primaryExpression(t));
    }

    bool primaryExpression(Tree *&t) {
        Token primary;
        primary = tokens.next();       
        if(primary.type == Token::UNSIGNED_INT || primary.type == Token::UNSIGNED_REAL) {
            t = new Tree(primary);
            return true;
        }
        else if(primary.type == Token::OPEN_PAREN) {
            Tree *subtree = new Tree();
            if(expression(subtree)) {
                t = new Tree(subtree);
                if(tokens.next().type != Token::CLOSED_PAREN) {
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
        else {
            if(primary.type != Token::NONE && primary.type != Token::EoF)
                error = "Error: Unexpected token: " + primary.op;
            else if(primary.type != Token::NONE)
                error = "Error: Unexpected end of line";
            return false;
        }
    }

public:
    explicit RecursiveDescent(string line) {
        tokens.tokenize(std::move(line));
        Tree *tree = new Tree();
        bool pass = expression(tree);
        if(pass && error.empty())
            Tree::printRPN(tree, cout);
        else if(pass)
            cout << error << endl;
        else cout <<"unexpected end of line at \'" << tokens.peek().op << "\'" << endl;
        cout << endl;
    }
};

int main() {
    string line;
    getline(cin, line);
    RecursiveDescent r(line);
}
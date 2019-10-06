#include <iostream> 
#include <regex>
#include <string>
#include <map>

using namespace std;

int main() {
	smatch m;
	string line;
	int label;
	map<int, string> program;
	while (!cin.eof() && getline(cin, line)) {
		if (regex_search(line, m, regex("[0-9]+"))) {
			label = stoi(m.str()) / 10;
			string code = m.suffix().str();
			program.insert(make_pair(label, code));
		}
	}
	map<string, int> variables;					//holds variables and their values
	string* arrProgram = NULL;					//copy of map so I can do GOTO's
	arrProgram = new string[program.size() + 1];
	int tempIndex = 1;
	for (pair<int, string> e : program) {
		arrProgram[tempIndex] = e.second;		//init array version of program
		tempIndex++;
	}
	string tempVar;
	string temp;
	char toString;
	string firstVar = m.str();
	for (int i = 1; i <= program.size(); i++) {
		string secondVar = "";					//holds second variable in A = A + B statements
		if (regex_search(arrProgram[i], m, regex("PRINTLN [\"]"))) {
			temp = m.suffix().str();
			if (regex_search(temp, m, regex("[A-Z ]+[^\"]"))) 
				cout << m.str() << endl;			
		}
		else if (regex_search(arrProgram[i], m, regex("PRINT [\"]"))) {
			temp = m.suffix().str();
			if (regex_search(temp, m, regex("[A-Z ]+[^\"]"))) 
				cout << m.str();			
		}
		else if (regex_search(arrProgram[i], m, regex("PRINTLN "))) 
			cout << variables.at(m.suffix().str()) << endl;		
		else if (regex_search(arrProgram[i], m, regex("PRINT "))) 
			cout << variables.at(m.suffix().str());		
		if (regex_search(arrProgram[i], m, regex("LET "))) {
			temp = m.suffix().str();
			if (regex_search(temp, m, regex("[A-Z]+"))) {
				tempVar = m.str();
				variables.insert(make_pair(tempVar, 0));	//init all variables to 0			
			}
			if (regex_search(temp, m, regex("[A-Z]+ = "))) { //assignment
				string moreTemp;
				moreTemp = m.suffix().str();
				if (regex_search(moreTemp, m, regex("^[0-9]+")))
					variables.at(tempVar) = stoi(moreTemp);
				if (regex_search(moreTemp, m, regex("[A-Z]"))) {
					firstVar = m.str();
					moreTemp = m.suffix().str();
					if (regex_search(moreTemp, m, regex("[+]"))) {
						toString = m.suffix().str()[1];
						secondVar += toString;
						if (isalpha(m.suffix().str()[1]))
							variables.at(tempVar) = variables.at(firstVar) + variables.at((secondVar)); // A = A + B						
						else
							variables.at(tempVar) = variables.at(tempVar) + stoi(m.suffix().str()); // A = 10
					}
					else if (regex_search(moreTemp, m, regex("[-]"))) {
						toString = m.suffix().str()[1];
						secondVar += toString;
						if (isalpha(m.suffix().str()[1]))
							variables.at(tempVar) = (variables.at(firstVar) - variables.at((secondVar)));
						else
							variables.at(tempVar) = variables.at(tempVar) - stoi(m.suffix().str());
					}
					else if (regex_search(moreTemp, m, regex("[*]"))) {
						toString = m.suffix().str()[1];
						secondVar += toString;
						if (isalpha(m.suffix().str()[1]))
							variables.at(tempVar) = variables.at(firstVar) * variables.at((secondVar));
						else
							variables.at(tempVar) = variables.at(tempVar) * stoi(m.suffix().str());
					}
					else if (regex_search(moreTemp, m, regex("[/]"))) {
						toString = m.suffix().str()[1];
						secondVar += toString;
						if (isalpha(m.suffix().str()[1]))
							variables.at(tempVar) = variables.at(firstVar) / variables.at((secondVar));
						else
							variables.at(tempVar) = variables.at(tempVar) / stoi(m.suffix().str());
					}
				}
			}
		}
		if (regex_search(arrProgram[i], m, regex("IF "))) {
			temp = m.suffix().str();
			int compVal;
			int newIndex;
			bool isNumber = false;
			bool isFirstVar = false;
			if (isalpha(temp[0])) {
				if (regex_search(temp, m, regex("[A-Z]+"))) {// IF A = B, IF A = 1
					firstVar = m.str();
					temp = m.suffix().str();
					if (regex_search(temp, m, regex(" = "))) {
						temp = m.suffix().str();
						if (regex_search(temp, m, regex("[0-9]+ "))) {
							compVal = stoi(m.str());
							isNumber = true;
						}
						else if (regex_search(temp, m, regex("[A-Z]")))
							secondVar = m.str();
						if (regex_search(temp, m, regex("GOTO")))
							newIndex = (stoi(m.suffix().str()) / 10) - 1;
						if (isNumber && (variables.at(firstVar) == stoi(temp)))
							i = newIndex;
						else if (!isNumber && (variables.at(firstVar) == variables.at(secondVar)))
							i = newIndex;
					}
					else if (regex_search(temp, m, regex(" < "))) {
						temp = m.suffix().str();
						if (regex_search(temp, m, regex("[0-9]+ "))) {
							compVal = stoi(m.str());
							isNumber = true;
						}
						else if (regex_search(temp, m, regex("[A-Z]")))
							secondVar = m.str();
						if (regex_search(temp, m, regex("GOTO")))
							newIndex = (stoi(m.suffix().str()) / 10) - 1;
						if (isNumber && (variables.at(firstVar) < stoi(temp)))
							i = newIndex;
						else if (!isNumber && (variables.at(firstVar) < variables.at(secondVar)))
							i = newIndex;
					}
					else if (regex_search(temp, m, regex(" > "))) {
						temp = m.suffix().str();
						if (regex_search(temp, m, regex("[0-9]+ "))) {
							compVal = stoi(m.str());
							isNumber = true;
						}
						else if (regex_search(temp, m, regex("[A-Z]")))
							secondVar = m.str();
						if (regex_search(temp, m, regex("GOTO")))
							newIndex = (stoi(m.suffix().str()) / 10) - 1;
						if (isNumber && (variables.at(firstVar) > stoi(temp)))
							i = newIndex;
						else if (!isNumber && (variables.at(firstVar) > variables.at(secondVar)))
							i = newIndex;
					}
					else if (regex_search(temp, m, regex(" <= "))) {
						temp = m.suffix().str();
						if (regex_search(temp, m, regex("[0-9]+ "))) {
							compVal = stoi(m.str());
							isNumber = true;
						}
						else if (regex_search(temp, m, regex("[A-Z]")))
							secondVar = m.str();
						if (regex_search(temp, m, regex("GOTO")))
							newIndex = (stoi(m.suffix().str()) / 10) - 1;
						if (isNumber && (variables.at(firstVar) <= stoi(temp)))
							i = newIndex;
						else if (!isNumber && (variables.at(firstVar) <= variables.at(secondVar)))
							i = newIndex;

					}
					else if (regex_search(temp, m, regex(" >= "))) {
						temp = m.suffix().str();
						if (regex_search(temp, m, regex("[0-9]+ "))) {
							compVal = stoi(m.str());
							isNumber = true;
						}
						else if (regex_search(temp, m, regex("[A-Z]")))
							secondVar = m.str();
						if (regex_search(temp, m, regex("GOTO")))
							newIndex = (stoi(m.suffix().str()) / 10) - 1;
						if (isNumber && (variables.at(firstVar) >= stoi(temp)))
							i = newIndex;
						else if (!isNumber && (variables.at(firstVar) >= variables.at(secondVar)))
							i = newIndex;
					}
					else if (regex_search(temp, m, regex(" <> "))) {
						temp = m.suffix().str();
						if (regex_search(temp, m, regex("[0-9]+ "))) {
							compVal = stoi(m.str());
							isNumber = true;
						}
						else if (regex_search(temp, m, regex("[A-Z]")))
							secondVar = m.str();
						if (regex_search(temp, m, regex("GOTO")))
							newIndex = (stoi(m.suffix().str()) / 10) - 1;
						if (isNumber && (variables.at(firstVar) != stoi(temp)))
							i = newIndex;
						else if (!isNumber && (variables.at(firstVar) != variables.at(secondVar)))
							i = newIndex;
					}
				}
			}
			else if (regex_search(temp, m, regex("[0-9]+"))) {
				int firstVal = stoi(m.str());
				temp = m.suffix().str();
				if (regex_search(temp, m, regex(" = "))) {
					temp = m.suffix().str();
					if (regex_search(temp, m, regex("[0-9]+ "))) {
						compVal = stoi(m.str());
						isNumber = true;
					}
					else if (regex_search(temp, m, regex("[A-Z]")))
						secondVar = m.str();
					if (regex_search(temp, m, regex("GOTO")))
						newIndex = (stoi(m.suffix().str()) / 10) - 1;
					if (isNumber && (firstVal == compVal))
						i = newIndex;
					else if (!isNumber && (firstVal == variables.at(secondVar)))
						i = newIndex;
				}
				if (regex_search(temp, m, regex(" > "))) {
					temp = m.suffix().str();
					if (regex_search(temp, m, regex("[0-9]+ "))) {
						compVal = stoi(m.str());
						isNumber = true;
					}
					else if (regex_search(temp, m, regex("[A-Z]")))
						secondVar = m.str();
					if (regex_search(temp, m, regex("GOTO")))
						newIndex = (stoi(m.suffix().str()) / 10) - 1;
					if (isNumber && (firstVal > compVal))
						i = newIndex;
					else if (!isNumber && (firstVal > variables.at(secondVar)))
						i = newIndex;
				}
				if (regex_search(temp, m, regex(" < "))) {
					temp = m.suffix().str();
					if (regex_search(temp, m, regex("[0-9]+ "))) {
						compVal = stoi(m.str());
						isNumber = true;
					}
					else if (regex_search(temp, m, regex("[A-Z]")))
						secondVar = m.str();
					if (regex_search(temp, m, regex("GOTO")))
						newIndex = (stoi(m.suffix().str()) / 10) - 1;
					if (isNumber && (firstVal < compVal))
						i = newIndex;
					else if (!isNumber && (firstVal < variables.at(secondVar)))
						i = newIndex;
				}
				if (regex_search(temp, m, regex(" >= "))) {
					temp = m.suffix().str();
					if (regex_search(temp, m, regex("[0-9]+ "))) {
						compVal = stoi(m.str());
						isNumber = true;
					}
					else if (regex_search(temp, m, regex("[A-Z]")))
						secondVar = m.str();
					if (regex_search(temp, m, regex("GOTO")))
						newIndex = (stoi(m.suffix().str()) / 10) - 1;
					if (isNumber && (firstVal >= compVal))
						i = newIndex;
					else if (!isNumber && (firstVal >= variables.at(secondVar)))
						i = newIndex;
				}
				if (regex_search(temp, m, regex(" <= "))) {
					temp = m.suffix().str();
					if (regex_search(temp, m, regex("[0-9]+ "))) {
						compVal = stoi(m.str());
						isNumber = true;
					}
					else if (regex_search(temp, m, regex("[A-Z]")))
						secondVar = m.str();
					if (regex_search(temp, m, regex("GOTO")))
						newIndex = (stoi(m.suffix().str()) / 10) - 1;
					if (isNumber && (firstVal <= compVal))
						i = newIndex;
					else if (!isNumber && (firstVal <= variables.at(secondVar)))
						i = newIndex;
				}
				if (regex_search(temp, m, regex(" <> "))) {
					temp = m.suffix().str();
					if (regex_search(temp, m, regex("[0-9]+ "))) {
						compVal = stoi(m.str());
						isNumber = true;
					}
					else if (regex_search(temp, m, regex("[A-Z]")))
						secondVar = m.str();
					if (regex_search(temp, m, regex("GOTO")))
						newIndex = (stoi(m.suffix().str()) / 10) - 1;
					if (isNumber && (firstVal != compVal))
						i = newIndex;
					else if (!isNumber && (firstVal != variables.at(secondVar)))
						i = newIndex;
				}
			}
		}
	}
	return 0;
}
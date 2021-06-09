#include <bits/stdc++.h>
using namespace std;

class SymbolTable{
    public:
        string symbol;
        string type;
        int index;
        string token;
};

void createTerminalTable(map<string,string> &terminalTable){
    terminalTable["{"] = "BC";
    terminalTable["}"] = "BC";
    terminalTable["("] = "BC";
    terminalTable[")"] = "BC";
    terminalTable["("] = "BC";
    terminalTable["\""] = "BC";
    terminalTable["&"] = "BC";
    terminalTable[";"] = "OP";
    terminalTable["++"] = "OP";
    terminalTable["="] = "OP";
    terminalTable["<"] = "OP";
    terminalTable[">"] = "OP";
    terminalTable["<="] = "OP";
    terminalTable[","] = "OP";
    terminalTable["+"] = "OP";
    terminalTable["-"] = "OP";
    terminalTable["int"] = "KEY";
    terminalTable["float"] = "KEY";
    terminalTable["for"] = "KEY";
    terminalTable["if"] = "KEY";
}

void addToSymbolTable(vector<SymbolTable> &symTab, string str, string type, int idx, string token){
    SymbolTable sym;
    sym.symbol = str;
    sym.type = type;
    sym.index = idx;
    sym.token = token; 
    symTab.push_back(sym);
}

int isAlphabet(char s){
    if((s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z'))
		return 1;
	return 0;
}

int isSymbol(char s){
    if(s=='{' || s=='*' || s=='(' || s==')' || s==';' || s==',' || s=='+' || s=='=' || s=='<' || s=='>' || s=='-' || s=='"' || s=='/')
		return 1;
	return 0;
} 

int isNum(char s){
    if(s >= '0'&& s <= '9')
		return 1;
	return 0;
}

bool inIdentifierTable(string str, vector<string> &identifierTable){
    for(auto ide: identifierTable)
	{
		if(ide == str)
			return true;
	}
	return false;
}


void lexicalAnalysis(map<string,string> &terminalTable, vector<string> &literalTable, vector<string> &identifierTable, vector<SymbolTable> &symTab){

    fstream fp;
    string line, filename;
    filename = "source-code.txt";
    fp.open(filename);

    int terminalIdx = 0, identifierIdx = 0, literalIdx = 0;
    if(!fp)
        cout<<"\n\nFile does not exist\n";
    
    while(fp){
        getline(fp, line);
        string temp = "";
        cout<<line<<endl;

        for(int i=0; i<line.length(); i++){
            
            if(isAlphabet(line[i])){
                temp += line[i];
                
                if(isSymbol(line[i+1]) || line[i+1] == ' '){
                    
                    if(terminalTable.find(temp) != terminalTable.end()){
                        terminalIdx = distance(terminalTable.begin(), terminalTable.find(temp));
                        addToSymbolTable(symTab, temp, "TRM", terminalIdx, temp);
                        temp = "";
                    }else{

                        if(!inIdentifierTable(temp, identifierTable)){
                            	
                            identifierTable.push_back(temp);
				
                            addToSymbolTable(symTab, temp, "IDN", identifierIdx, "IDN"+to_string(identifierIdx));
                            identifierIdx++;
                        }
                    }
                    temp = "";
                }
            }else if(line[i] == '"' || isNum(line[i])){
                temp = "";
				if(line[i] == '"'){
					while(line[i+1] != '"' && !isSymbol(line[i+1])){
				        temp += line[i];                                      
				        i++;
				    }
				}else{
					if(isNum(line[i])){						//Error Handling
						while(!isSymbol(line[i+1])){
							if(isAlphabet(line[i+1])){
								cout<<"Invalid Identifier"<<endl;
								return;
							}	
						    temp += line[i];                                      
						    i++;
				        }
					}
				}
		        
                temp += line[i];        //adding second last char in temp
                if(line[i+1] == '"'){   //adding last " in temp
                    temp += line[i+1];
                    i++;
                }
                literalTable.push_back(temp);
                addToSymbolTable(symTab, temp, "LIT", literalIdx, "LIT"+to_string(literalIdx));
                literalIdx += 1;
                temp = "";

            }else if(isSymbol(line[i])){
                temp += line[i];
                terminalIdx = distance(terminalTable.begin(), terminalTable.find(temp));
                addToSymbolTable(symTab, temp, "TRM", terminalIdx, temp);
                temp = "";
            }
        }
    }
    fp.close();
}


void printTables(map<string,string> &terminalTable, vector<string> &literalTable, vector<string> &identifierTable, vector<SymbolTable> &symTab){

    cout<<"\n\n-----------Terminal Table--------------"<<endl;
	cout<<"Symbol\tGroup\tIndex\n";
    int i = 0;
	for(auto x: terminalTable)
	{
		cout<<x.first<<"\t"<<x.second<<"\t"<<i<<endl;
        i++;
	}

    cout<<"\n\n-----------Identifier Table--------------"<<endl;
	cout<<"Index\tSymbol\n";
    i = 0;
	for(auto x: identifierTable)
	{
		cout<<i<<"\t"<<x<<endl;
        i++;
	}

    cout<<"\n\n-----------Literal Table--------------"<<endl;
	cout<<"Index\tSymbol\n";
    i = 0;
	for(auto x: literalTable)
	{
		cout<<i<<"\t"<<x<<endl;
        i++;
	}

    cout<<"\n\n-----------Uniform Table--------------"<<endl;
	cout<<"Symbol\tType\tIndex\tToken\n";
	for(auto x: symTab)
	{
		cout<<x.symbol<<"\t"<<x.type<<"\t"<<x.index<<"\t"<<x.token<<endl;
	}
}

int main(){
    map<string,string> terminalTable;
    vector<string> literalTable;
    vector<string> identifierTable;

    vector<SymbolTable> symTab;
    
    createTerminalTable(terminalTable);
    lexicalAnalysis(terminalTable, literalTable, identifierTable, symTab);
    printTables(terminalTable, literalTable, identifierTable, symTab);
}
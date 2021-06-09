#include <iostream>
#include <fstream>
#include <string.h> 
#include <cstdlib> 
#include <map>
#include <stdlib.h>
#include <string>
using namespace std;

// Erroneous code:
// - START - 100
// - MOVER AREG ='5'
// - MOVEM HREG ='6'
// X DS - 1
// - END - -

// Correct code:
// - START - 100
// - MOVER AREG ='5'
// - MOVEM AREG	X
// - MOVER BREG	Y
// - LTORG - -
// NEXT	ADD	AREG ='1'
// L1 SUB BREG ='2'
// - LTORG - -
// BACK	EQU	- L1
// - MULT CREG ='4'
// - STOP -	-
// X DS - 1
// Y DC - 1
// - END	- -

//STRUCT FOR MOT/POT TABLE
typedef struct table{
    string class_name, number;
}table;

//STRUCT FOR SYMBOL TABLE, literal and pool table
typedef struct symbol_table{
	int address;
	char symbol[10], value[3]; 
}symbol_table; 


typedef struct pool_table{
	int srno;
	char pool[5]; 
}pool_table; 

typedef struct literal_table{
	int srno, address;
	char literal[5];  
}literal_table; 

// STRUCT FOR FILE READ/WRITE
typedef struct code {
	char label[10], mnemonic[10], opcode[8], op2[5];
	int size; 
}code; 

//GLOBAL VAR
int add_count = 0;
int symbol=1, literal=1, line_count=1, ln_cnt=1, lit_cnt;
int idx=1, pool_idx = 0;
pool_table pool_tab[20];

// FUNCTION DECLARATIONS
table insert_data(string class_name, string number); 
void add_symbol(int lc, char label[], char val[], int index, symbol_table sym_table[50]); 
void display_symbol_table(symbol_table sym_table[50], int index); 
void add_literal(int lc, char val[5], int lit_index, literal_table lit_table[50]);
void display_literal(literal_table lit_table[50], int lit_index);
int check_duplicate_symbol(char label[10], int index, symbol_table sym_table[50]); 
void get_table_info(table obj);
string get_table_data(char mnemonic[10]);
void show_code(char label[10], char mnemonic[10], char opcode[8], char op2[5]);
int code_generation(char label[], char mnemonic[], char opcode[], char op2[]);

int main(){
	code c; 
	int lines; 

	symbol_table sym_table[50]; 
	literal_table lit_table[50];

	//Write into the file
	ofstream out; 
	out.open("new.txt", ios::app); 
	if(out.is_open()){
		cout << ".....The File is OPEN...." << endl; 
		cout << ".....Write Code: ('END' to exit)...." << endl; 
	}	
	else
		cout << "....ERROR Opening The File...."<< endl; 

	cout << "Enter No of Lines of Code: "; 
	cin >> lines; 
	cout << "Enter Code: "<< endl;

	//FIRST LINE (START STATEMENT)

	int lc=0, index=0, lit_index=0, ltorg_count= 0; 

	cin >> c.label >> c.mnemonic >> c.opcode >> c.op2; 
	lc = atoi(c.op2); 
	//Insertion Format 
    out <<  c.label << "\t" <<  c.mnemonic << "\t" <<  c.opcode << "\t" << c.op2 << endl;

	while(--lines){
		//Enter Values
		cin >> c.label >> c.mnemonic >> c.opcode >> c.op2; 

		//Insertion Format 
	    out <<  c.label << "\t" <<  c.mnemonic << "\t" <<  c.opcode << "\t" << c.op2 << endl;

		if (strcmp(c.mnemonic, "LTORG") == 0)
			lc++;
		else if(strcmp(c.mnemonic, "END") == 0)
			break;
		else{
			char c1 = c.op2[0]; 
			lc++; 
			if(c1 == '='){
				add_literal(lc, c.op2, lit_index, lit_table); 
				++lit_index; 
				ltorg_count++; 
				lc--;
			}
		}

		if(strcmp(c.label, "-") != 0){
			if(strcmp(c.mnemonic, "EQU") != 0)
				lc++;
			add_symbol(lc, c.label, c.op2, index, sym_table);
			index++;
		}
	}
	cout << "\n....Exited Writing...." << endl; 
	out.close(); 

	//Read from the File
	ifstream in("new.txt");
	cout << "\n INTERMEDIATE CODE: " << endl;
	while (in >> c.label >> c.mnemonic >> c.opcode >> c.op2){
		if(code_generation(c.label, c.mnemonic, c.opcode, c.op2) != 0)
			continue;
		else{
			cout << " \n EXITTING " << endl; 
			break;
		}
	}
    cout << "\n....Exiting Reading....\n" << endl; 
	in.close();

	//display symbol table
	cout << "\n----------SYMBOL TABLE:----------" << endl; 
	cout << "SR.NO \t ADDRESS \t SYMBOL \t VALUE" << endl;
	display_symbol_table(sym_table, index); 
	cout << "----------------------------------" << endl; 
	
	//display literal table
	cout << "\n----------LITERAL TABLE:----------" << endl; 
	cout << "SR.NO \t LITERAL \t ADDRESS" << endl;
	display_literal(lit_table, lit_index);
	cout << "----------------" << endl; 

	return 0; 
}

void add_symbol(int lc, char label[10], char val[5], int index, symbol_table sym_table[50]){
	sym_table[index].address = lc; 
	strcpy(sym_table[index].symbol, label);
	char ch = val[0];
	if((ch>='a' && ch<='z') || (ch>='A' && ch<='Z')) 
		strcpy(sym_table[index].value, "-"); 
	else 
		strcpy(sym_table[index].value, val); 
}

int check_duplicate_symbol(char label[10], int index, symbol_table sym_table[50]){
	for(int i=0; i<=index; i++){
		if(strcmp(label, sym_table[i].symbol) == 0)
			return 0; 
	}
	return 1; 
}

void display_symbol_table(symbol_table sym_table[50], int index){
	for(int i=0; i<index; i++){
		char ch1 = sym_table[i].value[0]; 
		int leng = strlen(sym_table[i].symbol); 
		if(strcmp(sym_table[i].symbol, "-") != 0 && ch1 != '=' && leng == 1){
			cout << idx << "\t" << sym_table[i].address << "\t\t" << sym_table[i].symbol << "\t\t" << sym_table[i].value << endl;
			idx++;
		}
	}
	for(int i=0; i<index; i++){
		char ch1 = sym_table[i].value[0]; 
		int leng = strlen(sym_table[i].symbol); 
		if(strcmp(sym_table[i].symbol, "-") != 0 && leng > 1){
			if(ch1 == '=')
				strcpy(sym_table[i].value, "-");
			cout << idx << "\t" << sym_table[i].address << "\t\t" << sym_table[i].symbol << "\t\t" << sym_table[i].value << endl;
			idx++;
		}
	}
}

void add_literal(int lc, char val[5], int lit_index, literal_table lit_table[50]){
	lit_table[lit_index].srno = lit_index+1; 
	strcpy(lit_table[lit_index].literal, val); 
	lit_table[lit_index].address = lc+1; 

	char ch1 = lit_table[lit_index+1].literal[0];
	char ch2 = lit_table[lit_index].literal[0];
	if(ch1 == '=' && ch2 == '=' && lit_table[lit_index+1].address - lit_table[lit_index].address > 1){
		pool_tab[pool_idx].srno = pool_idx+1; 
		strcpy(pool_tab[pool_idx].pool, val);
		pool_idx++;
	}
}

void display_literal(literal_table lit_table[50], int lit_index){
	for(int i=0; i<lit_index; i++){
		char c = lit_table[i].literal[0]; 
		if(c == '=')
			cout << lit_table[i].srno << "\t\t" << lit_table[i].literal << "\t\t" << lit_table[i].address << endl;
	}
	cout << "\n----- POOL TABLE -----" << endl;
	for(int i=0; i<lit_index; i++){
		char c = lit_table[i].literal[0]; 
		if(c == '=')
			if(lit_table[i+1].address - lit_table[i].address > 1)
				cout << i+1 << "\t\t" << lit_table[i].srno << endl;
	}
}

void show_code(char label[10], char mnemonic[10], char opcode[8], char op2[5]){
	cout << label << "  " <<  mnemonic << "  " <<  opcode << "  " << op2 << endl; 
}


int code_generation(char label[10], char mnemonic[10], char opcode[8], char op2[5]){
	ln_cnt++; 
	if( (strcmp(label, "-") == 0 ) && (strcmp(mnemonic, "START") == 0) ){
		add_count = atoi(op2); 
		cout << " - \t (AD,\t01) \t - \t (C, " << add_count << ")" <<  endl; 
	}
	
	else{
		cout << add_count; 
		if(get_table_data(mnemonic) == " ") {
			if(strcmp(opcode, "AREG") == 0) cout << "\t 01";
			else if (strcmp(opcode, "BREG") == 0) cout << "\t 02";
			else if (strcmp(opcode, "CREG") == 0) cout << "\t 03";
			else if (strcmp(opcode, "DREG") == 0) cout << "\t 04";
			else if (strcmp(opcode, "-") == 0) cout << "\t -";
			else{
				cout << "\n ERROR AT LINE :: " << ln_cnt << ": INVALID REGISTER NAME " << endl; 
				return 0;
			} 
			char c = op2[0]; 
			if(c == '='){
				cout << "\t (L , 0" << literal << ")" <<  endl;
				literal++;
			}	
			else if(strcmp(mnemonic, "DC") == 0 || strcmp(mnemonic, "DS") == 0)
				cout << "\t (C , " << c << ")" << endl;
			else if(c != '=' && c != '-'){
				cout << "\t (S , 0" << symbol << ")" << endl;
				symbol++;
			}	
			else 
				cout << endl;

			lit_cnt = literal; 
			if(strcmp(mnemonic, "EQU") != 0)
				add_count++;
		}
		else
			return 0; 	
	}
	return 1; 
}

// FUNCTION DEFINITIONS
table insert_data(string class_name, string number){
    table *ptr = new table;
    ptr->class_name = class_name;
    ptr->number = number;
    return *ptr;
}
string get_table_data(char mnemonic[10]){
	//allocation
	map<string, table> mnemonic_opcode;
    map<string, table> pseudo_opcode;
	map<string, table> declaration;
    //Imperative Statements
    mnemonic_opcode.insert( {"STOP", insert_data("IS", "00")} );
    mnemonic_opcode.insert( {"ADD", insert_data("IS", "01")} );
    mnemonic_opcode.insert( {"SUB", insert_data("IS", "02")} );
    mnemonic_opcode.insert( {"MULT", insert_data("IS", "03")} );
    mnemonic_opcode.insert( {"MOVER", insert_data("IS", "04")} );
    mnemonic_opcode.insert( {"MOVEM", insert_data("IS", "05")} );
    mnemonic_opcode.insert( {"COMP", insert_data("IS", "06")} );
    mnemonic_opcode.insert( {"BC", insert_data("IS", "07")} );
    mnemonic_opcode.insert( {"DIV", insert_data("IS", "08")} );
    mnemonic_opcode.insert( {"READ", insert_data("IS", "09")} );
    mnemonic_opcode.insert( {"PRINT", insert_data("IS", "10")} );

    //Assembler Directives
    pseudo_opcode.insert( {"START", insert_data("AD", "01")} );
    pseudo_opcode.insert( {"END", insert_data("AD", "02")} );
    pseudo_opcode.insert( {"EQU", insert_data("AD", "03")} );
    pseudo_opcode.insert( {"ORG", insert_data("AD", "04")} );
    pseudo_opcode.insert( {"LTORG", insert_data("AD", "05")} );

	//Declaration Statements 
	declaration.insert( {"DS", insert_data("DL", "01")} );
	declaration.insert( {"DC", insert_data("DL", "02")});

	line_count++;
	string str(mnemonic);

	if(str == "START" || str == "END" || str == "LTORG" || str == "ORG" || str == "EQU")
		get_table_info(pseudo_opcode.find(str)->second);
	else if(str == "DC" || str == "DS")
		get_table_info(declaration.find(str)->second);
	else if(str == "STOP" || str == "ADD" || str == "SUB" || str == "MULT" || str == "MOVER" || str == "MOVEM" || str == "COMP" || str == "BC" || str == "DIV" || str == "READ" || str == "PRINT")
		get_table_info(mnemonic_opcode.find(str)->second);	
	else {
		cout << "\n----------ERROR AT LINE NO: " << line_count << "(invalid Mnemonic) ---------" << endl;
		return "....EXITTING....";
	}

	return " ";
}

void get_table_info(table obj){
    cout<< "\t (" <<obj.class_name << ", \t" <<obj.number <<")";
}
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cstdlib>
#include <utility>
#include <cctype>
#include "stackint.h"
#include <sstream>
using namespace std;

bool toBool(char character);
void printTruth(bool truth, const string t, const string f,string error);

int main(int argc, char* argv[]){



//___________________________________PREPARATION____________________________________________________
	//Check for invalid command line inputs
	if(argc != 3){
		cout << "Please include the correct command line files" << endl;
		return 1;
	}

	//Instream
	ifstream expr_file(argv[1]);
	ifstream var_file (argv[2]);

	//Constants
	const string malformed = "Malformed";
	const string unknown   = "Unknown Variable";
	const string noError = "ne";
	const string t_String  = "T";
	const string f_String  = "F";
	const int open_parenthesis = -10;
	const int intAnd = -11;
	const int intOr  = -12;
	const int intNot = -13;
	const int t = -1;
	const int f = -2;

	map<int, char> map;
	map.insert(pair<int, char>(-1,'T'));
	map.insert(pair<int, char>(-2,'F'));



//_____________________________READ VARIABLE ASSIGNMENT FILE________________________________________
	string input;
	int variable;
	char truthVal;
	int counter = 0;
	while(var_file >> input){
		//Even counter means it is a variable
		if(counter % 2 == 0){
			variable = atoi(input.c_str());
		}
		//Odd counter means it is a truth value
		else if(counter % 2 != 0){
			truthVal=input[0];
			//Every time we have an odd counter, it means we have a pair. Insert it.
			map.insert(pair<int,char>(variable,truthVal));
		}
		//Increment the counter
		counter++;
	}



//___________________________________READ BOOLEAN EXPRESSION FILE___________________________
	while(getline(expr_file, input)){
		//Check for empty lines
		if(input == "")
			continue;

		bool truth;
		string error = noError;
		StackInt stack;

		
		
		//_________________________PUSH EVERYTHING INTO THE STACK___________________________
		for(int i = 0;(unsigned)i < input.size()&&error==noError;i++){
			if(input[i] == ' '){ /*Ignore blank spaces*/}
			else if(input[i] == '&')
				stack.push(intAnd);
			else if(input[i] == '|')
				stack.push(intOr);
			else if(input[i] == '~')
				stack.push(intNot);
			else if(input[i] == '(')
				stack.push(open_parenthesis);
			else if(input[i] == 'T')
				stack.push(t);
			else if(input[i] == 'F')
				stack.push(f);



			//____________________SPECIAL CASE OF MEETING A CLOSING PARENTHESIS_______________
			else if(input[i] == ')'){
				//____________________GET FIRST FULL INTEGER VALUE BEFORE )_______________________
				int value=stack.top();
				ostringstream val;
				string integer="";
				if(value>=0){
					while(value>=0){
						val.str("");
						val<<value;
						integer=val.str()+integer;
						stack.pop();
						value=stack.top();
					}
					if(map.count(atoi(integer.c_str()))==0){
						error = unknown;
						break;
					} 
					else
						truth=toBool(map[atoi(integer.c_str())]);
				}
				else if(value==t||value==f){
					truth=toBool(map[value]);
					stack.pop();
					value=stack.top();
				}
				else{
					error = malformed;
					break;
				}
				//Check if (12)
				if(value==open_parenthesis){
					error=malformed;
					break;
				}



				//__________________LOOP TO CHECK STACK UNTIL OPENING PARENTHESIS___________________
				//lock to prevent (2|3&4)
				int lock=0;
				while(value!=open_parenthesis){



					//___________________THE NEXT OPERATOR IS &_____________________________________
					if(value==intAnd&&(lock==0||lock==1)){
						stack.pop();
						value=stack.top();//check malform here
						ostringstream val;
						integer="";
						if(value>=0){
							while(value>=0){
								val.str("");
								val<<value;
								integer=val.str()+integer;
								stack.pop();
								value=stack.top();
							}
							if(map.count(atoi(integer.c_str()))==0){
								error = unknown;
								break;							
							}
							else
								truth = truth && toBool(map[atoi(integer.c_str())]);
						}
						else if(value==t||value==f){
							truth=truth && toBool(map[value]);
							stack.pop();
							value=stack.top();	
						}
						else{
							error = malformed;
							break;
						}
						lock=1;
					}



					//___________________________THE NEXT OPERATOR IS |_____________________________
					else if(value==intOr&&(lock==0||lock==2)){
						stack.pop();
						value=stack.top();
						ostringstream val;
						integer="";
						if(value>=0){
							while(value>=0){
								val.str("");
								val<<value;
								integer=val.str()+integer;
								stack.pop();
								value=stack.top();
							}
							if(map.count(atoi(integer.c_str()))==0){
								error = unknown;
								break;	
							}
							else
								truth = truth || toBool(map[atoi(integer.c_str() ) ] );
						}
						else if(value==t||value==f){
							truth=truth||toBool(map[value]);
							stack.pop();
							value=stack.top();
						}
						else{
							error = malformed;
							break;
						}
						lock=2;
					}



					//____________________THE NEXT OPERATOR IS ~ OR MALFORMED______________________
					else if(value==intNot){	
						truth = !truth;
						stack.pop();
						value=stack.top();
						if(lock == 0 && value == open_parenthesis){
							error = malformed;
							break;
						}
					}
					else {
						error = malformed;
						break;
					}
				}



				//______________________IF NO ERROR YET BUT MISSING OPEN PARENTHESIS________________
				if(error == noError && stack.top()!=open_parenthesis){
					error = malformed;
					break;
				}
				//Pop the opening parenthesis
				stack.pop();
				//The end result between the parenthesis
				if(truth)
					stack.push(t);
				else
					stack.push(f);
			}//Special case of meeting a closed parenthesis
			else
				stack.push( input[i]-'0' );
		}//Pushing one line to the stack
		int top=stack.top();


		
		//_____________PRINTING OUTPUT FOR PARENTHESIZED EXPRESSIONS WITH ERRORS_______________
		if(error != noError){
			printTruth(truth, t_String,f_String,error);
		}



		//__________PRINTING OUTPUT FOR PARENTHESIZED EXPRESSIONS OR T||F WITHOUT PARENTHESIS______
		else if(top==f||top==t){
			truth=toBool( map[top] ) ;
			stack.pop();
			while(!stack.empty()){
				int value=stack.top();
				if(value!=intNot){
					error = malformed;
					break;				
				}
				else{
					truth=!truth;
				}
				stack.pop();
			}
			printTruth(truth,t_String,f_String,error);
		}


		//________________PRINTING OUTPUT FOR INTEGERS WITHOUT PARENTHESIS________________________
		else {
			int value=stack.top();
			ostringstream val;
			string integer="";
			if(value>=0){
				while(value>=0){
					val.str("");
					val<<value;
					integer=val.str()+integer;
					stack.pop();
					if(!stack.empty())
						value=stack.top();
					else
						break;
				}
				if(map.count(atoi(integer.c_str()))==0){
					error = unknown;
				}
				else
					truth = toBool(map[atoi(integer.c_str())]);
			}
			if(!stack.empty()&&stack.top()==intNot){
				while(!stack.empty()){
					value=stack.top();
					if(value!=intNot){
						error = malformed;
						break;
					}
					else{
						truth=!truth;
					}
					stack.pop();
				}
			}
			else if(!stack.empty()){
				error = malformed;
			}
			printTruth(truth,t_String,f_String,error);
		}
		
	}

	return 0;
}//Main








//______________________________HELPER FUNCTIONS__________________________________
void printTruth(bool truth, const string t, const string f, string error){
	if(error != "ne"){
		cout<<error<<endl;
	}
	else{
		if(truth)
			cout<<t<<endl;
		else
			cout<<f<<endl;
	}
}

bool toBool(char character){
	if(character=='T'){
		return true;
	}
	else
		return false;
}

//bool assembleInt(){

//}
#include <vector>
#include <cctype>
#include <fstream>
#include <iostream>
#include "myset.h"
#include "mdparser.h"
using namespace std;

MDParser::MDParser(){}

MDParser::~MDParser() {}

//Parses a file and returns all unique words according to some parser rules and all hyperlinks based on the format the parser is designed to implement
void MDParser::parse(std::string filename,MySetString& allWords,MySetString& allLinks){

	//Preparation
	ifstream in_file(filename.c_str());
	if(in_file.fail()){
		cerr<<"The file <"<<filename<<"> does not exist!"<<" Could not be parsed by MDParser"<<endl;
	}
	string input="";
	string input2="";
	bool firstLine=getline(in_file, input);
	if(firstLine){
		while(getline(in_file, input2))
			input=input+"\n"+input2;
		input = lowerCase( input );
	}
	//Parsing
	bool isLink=false;
	bool getLink=false;
	for( int i = 0;(unsigned)i < input.size();i++){
		if(input[i] == '[' && getLink == false){
			i++;
			int temp = i;
			int closedBracket=0;
			string checker="";
			while((unsigned)i<input.size()){
				if(input[i] == ']'){
					checker = checker + input[i];
					closedBracket=i;
				}
				else if(input[i] == '('){
					if(i==closedBracket+1)
					checker = checker + input[i];
				}
				else if(input[i] == ')'){
					checker = checker + input[i];
					if(checker=="]()")
						break;
				}
				i++;
			}
			i = temp;
			if(checker.size() >=3 && (checker.substr(0,3) == "]()") ){
				isLink=true;
			}			
			string result = input.substr(0,i-1);
			if(result!="")
				allWords.insert(result);
			if((unsigned)i+1<input.size()){
				input = input.substr(i);
				i=-1;
			}

		}
		else if(input[i] == ']' && isLink == true && getLink == false){
			string result = input.substr(0,i);
			if(result!="")
				allWords.insert(result);
			input=input.substr(i+2);
			isLink=false;
			getLink=true;
			i=-1;

		}
		else if(input[i] == ')'&& getLink==true){
			allLinks.insert(input.substr(0,i));
			getLink=false;
			if((unsigned)i+1<input.size()){
				input=input.substr(i+1);
				i=-1;
			}

		}
		else if(  input[i]=='\0' || (!isalpha(input[i]) && !isdigit(input[i]) && getLink == false)){
			string result = input.substr(0,i);
			if(result!="")
				allWords.insert(result);
			if((unsigned)i+1<input.size()){
				input=input.substr(i+1);
				i=-1;
			}
		}
	}

	if(input!=""&&input!=" "){
		allWords.insert(input);
	}
}

//Function for converting all alphabets to lower case
string MDParser::lowerCase(string s){
	unsigned int i=0;
	while (i<s.size()){
		if(isalpha(s[i]))
			s[i]=tolower(s[i]);
		i++;
	}
	return s;
}
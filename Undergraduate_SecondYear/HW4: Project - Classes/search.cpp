#include <iostream>
#include <set>
#include <vector>
#include <cctype>
#include <string>
#include "myset.h"
#include "searcheng.h"
#include "webpage.h"
#include "mdparser.h"
using namespace std;
void display_results(set<WebPage*>& results);
string lowerCase(string s);

int main(int argc, char* argv[]){
    //Check command line input
    if(argc < 2){
        cerr << "usage: ./search index_file...Please provide an index file" << endl;
        return 1;
    }
    
    //Parse the index file
    SearchEng sn;
    PageParser* parser = new MDParser;
    sn.add_parse_from_index_file(argv[1],parser);
    delete parser;

    //Prompt user for input
    string input;
    bool done = false;
    while( !done ){
        cout << "\n++++++++++++++++++++" << endl;
        cout << "Enter search terms: " << endl;
        getline(cin, input);
        cout << "++++++++++++++++++++\n" << endl;

        //The user wants to stop
        if(input=="."){
            done=true;
        }
        //Blank input
        else if(input ==""){
            continue;
        }
        else{
            //Break down the user's input into strings separated by white space
            vector<string> input_words;
            unsigned int counter=0;
            while(counter<input.size()+1){
                if(counter==input.size()){
                	if(input.substr(0,counter)!=""){
                		input_words.push_back(lowerCase(input.substr(0,counter)));
                	}
                	counter++;
                }
                else if(isspace(input[counter])){
                    if(input.substr(0,counter)!=""){
                        input_words.push_back(lowerCase(input.substr(0,counter)));
                    }

                    if(counter+1<input.size()){
                        input=input.substr(counter+1);
                        counter=0;
                    }
                    else
                        counter++;
                }
                else{
                    counter++;
                }
            }

            string firstWord = input_words[0];
            MySetWebPage result;
            //The input is simply AND or OR
            if((firstWord=="and"||firstWord=="or")&&input_words.size()==1){
                result = sn.findWord(firstWord);
            }
            //The input is a single word
            else if(input_words.size()==1){
            	result = sn.findWord(firstWord);
            }
            //There are other words after AND
            else if(firstWord == "and"){
            	result = sn.findWord(input_words[1]);
            	for(unsigned int i=2;i<input_words.size();i++){
            		result = result.set_intersection(sn.findWord(input_words[i]));
            	}
            }
            //There are other words after OR
            else if(firstWord == "or"){
            	result = sn.findWord(input_words[1]);
            	for(unsigned int i=2;i<input_words.size();i++){
            		result = result.set_union(sn.findWord(input_words[i]));
            	}         	
            }
        	else{
        		cerr<<"INVALID INPUT"<<endl;
        	}

        	display_results(result);
        }
    }
    return 0;
}

//Display Results
void display_results(set<WebPage*>& results){
    int hits = results.size();
    cout << hits << " hits." << endl;
    cout << "=====" << endl;
    int i=0;
    for(set<WebPage*>::iterator it = results.begin(); it != results.end(); ++it){
        cout << (*it)->filename() << endl;
        cout << "+---+" << endl;
        cout << (**it) << "\n" << endl;
        i++;
    }
}

//Change all alphabets within a string to lowercase
string lowerCase(string s){
	unsigned int i=0;
	while (i<s.size()){
		if(isalpha(s[i]))
			s[i]=tolower(s[i]);
		i++;
	}
	return s;
}

//Compile without using the makefile: g++ -g -Wall search.cpp searcheng.cpp MDParser.cpp myset.cpp webpage.cpp -o search
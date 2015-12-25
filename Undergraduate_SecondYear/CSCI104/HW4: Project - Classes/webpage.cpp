#include <string>
#include <iostream>
#include <fstream>
#include "webpage.h"
#include "myset.h"
using namespace std;

WebPage::WebPage(){
    this->name = "";
}
WebPage::WebPage(string name){
    this->name = name;
}
WebPage::~WebPage(){

}

//Sets the filename/URL of this webpage
void WebPage::filename(string fname){
	this->name = fname;
}
//Returns the filename/URL of this webpage
std::string WebPage::filename() const{
	return this->name;
}



//Updates the set containing all unique words in the text with the contents of the input parameter words
void WebPage::all_words(const MySetString& words){
	this->uniqueWords.clear();
	MySetString::iterator it;
	for(it=words.begin();it!=words.end();it++){
		this->uniqueWords.insert(*it);
	}
}
//Returns all the unique, tokenized words in this webpage 
MySetString WebPage::all_words() const{
	return uniqueWords;
}



//Adds a webpage that links to this page
void WebPage::add_incoming_link(WebPage* wp){
	this->incomingLinks.insert(wp);
}
//Returns all webpages that link to this page
MySetWebPage WebPage::incoming_links() const{
	return this->incomingLinks;
}



//Adds a webpage that this page links to
void WebPage::add_outgoing_link(WebPage* wp){
	this->outgoingLinks.insert(wp);
}
//Returns all webpages this page links to
MySetWebPage WebPage::outgoing_links() const{
	return this->outgoingLinks;
}



//Displays the webpage text to the screen 
ostream& operator<<(std::ostream & os, const WebPage & page){
	//Assemble the entire .txt into one string, placing \n inbetween each line so that when outputting the line returns are displayed.
	ifstream in_file(page.name.c_str());
	string input="";
	string input2="";
	bool firstLine=getline(in_file, input);
	if(firstLine){
		while(getline(in_file, input2))
			input=input+"\n"+input2;
	}
	for( int i=0;(unsigned)i<input.size();i++){
		if(input[i] == '[' ){
			i++;
			int temp=i;
			int closeBracket = 0;
			int closeParen =0;
			string checker="";
			while((unsigned)i<input.size()){
				if(input[i] == ']'){
					checker = checker + input[i];
					closeBracket = i;
				}
				else if(input[i] == '('){
					if(i==closeBracket+1)
						checker = checker + input[i];
				}
				else if(input[i] == ')'){
					checker = checker + input[i];
					closeParen = i;
					if(checker=="]()")
						break;
				}
				i++;
			}
			i=temp;

			if(checker.size()>=3 && checker.substr(0,3) == "]()"){
				os<<(input.substr(0, closeBracket +1));
				if((unsigned)closeParen+1<input.size()){
					input = input.substr(closeParen+1);
					i=-1;
				}
			}

		}
	}
	os<<input;
	return os;
}


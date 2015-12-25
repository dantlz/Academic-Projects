#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "webpage.h"
#include "myset.h"
#include "pageparser.h"
#include "searcheng.h"
#include "mdparser.h"
using namespace std;

SearchEng::SearchEng(){
}

SearchEng::~SearchEng(){
	map<std::string, WebPage*>::iterator it;
	for(it=map_filename_WebPages.begin();it!=map_filename_WebPages.end();++it){
		delete it->second;
	}
}

void SearchEng::add_parse_from_index_file(std::string index_file, PageParser* parser){
	
	ifstream in_file(index_file.c_str());
	if(in_file.fail()){
	}

	string fn;
	while(getline(in_file,fn)){
		//Check for empty lines
		if(fn=="")
			continue;
		map_filename_WebPages[fn]=new WebPage(fn);
		
	}

	map<string, WebPage*>::iterator it;
	for(it = map_filename_WebPages.begin();it!=map_filename_WebPages.end();++it){
		add_parse_page(it->first,parser);
	}
}

void SearchEng::add_parse_page(std::string filename, PageParser* parser){
	//Variables and holders
	WebPage* currentPage = map_filename_WebPages[filename];
	MySetString allWords ;
	MySetString outLinks ;
	parser = new MDParser;
	parser->parse(filename,allWords,outLinks);
	delete parser;

	currentPage->all_words(allWords);
	MySetString::iterator it;	
	for(it = outLinks.begin(); it != outLinks.end(); ++it){
		//Check here to see if it contains any none existent links
		if(map_filename_WebPages.count(*it)==0){
			map_filename_WebPages[*it]=new WebPage(*it);
		}
		currentPage->add_outgoing_link(map_filename_WebPages[*it]);
		WebPage* a = map_filename_WebPages[*it];
		a->add_incoming_link(currentPage);
	}

	//At this point, each filename from index has been made into a webpage with a filename, all unique words, all incoming links, and all outgoing links.
	//All of these webpages are stored in the map map_filename_WebPages with its filename as a keyword and the webpage itself as a value.  

	//Populate the word to a set of webpages map.
	MySetString::iterator it2;
	for(it2 = allWords.begin(); it2!=allWords.end(); ++it2){
		string currentWord = *it2;
		if(map_Words_MySetWebPage.count(currentWord) != 0){
			map_Words_MySetWebPage[currentWord].insert(currentPage);
		}
		else{
			MySetWebPage newSet;
			newSet.insert(currentPage);
			map_Words_MySetWebPage[currentWord] =  newSet;
		}
		
	}
}

//Function to retrieve a set of all webpages that contain a certain word
MySetWebPage SearchEng::findWord(string word){
	//If the word isn't in any webpages
	if(map_Words_MySetWebPage.count(word)==0){
		MySetWebPage notFound;
		return notFound;
	}
	else{
		return map_Words_MySetWebPage[word];
	}
}

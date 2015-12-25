#include <iostream>
#include <set>
#include <vector>
#include <cctype>
#include <string>
#include "searcheng.h"
#include "myset.h"
#include "mdparser.h"
using namespace std;

int main(int argc, char* argv[]){
    SearchEng sn;
    PageParser* parser = new MDParser();
    sn.add_parse_from_index_file("data/index.txt", parser);

    map<string, WebPage*>::iterator it;
    for(it = sn.map_filename_WebPages.begin();it!=sn.map_filename_WebPages.end();++it){
    	cout<<it->first<<" has outgoing links: "<<endl;
    	WebPage* wp = it->second;
    	MySetWebPage::iterator it2;
    	for(it2=wp->outgoingLinks.begin();it2!=wp->outgoingLinks.end();++it2){
    		cout<<(*it2)->filename()<<endl;
    	}
    	cout<<it->first<<" has incoming links: "<<endl;
    	for(it2=wp->incomingLinks.begin();it2!=wp->incomingLinks.end();++it2){
    		cout<<(*it2)->filename()<<endl;
    	}
    }
    

  /*MySetWebPage swp = sn.findWord("desk");

    cout<<"MySetWebPage with desk is size "<<swp.size()<<" and the filenames are ";
    MySetWebPage::iterator it;
    for(it =swp.begin();it!=swp.end();++it){
        cout<<(*it)->filename()<<endl;
    }*/
}
//g++ -g -Wall test_searcheng.cpp myset.cpp searcheng.cpp mdparser.cpp webpage.cpp -o test_searcheng

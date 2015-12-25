#include <iostream>
#include <set>
#include <vector>
#include <cctype>
#include <string>
#include "myset.h"
#include "webpage.h"
#include "mdparser.h"
using namespace std;

int main(int argc, char* argv[]){
    WebPage wp1("One");
    WebPage wp2;
    wp2.filename("Two");
    cout<<"wp1's file name is "<<wp1.filename()<<endl;
    cout<<"wp2's file name is "<<wp2.filename()<<endl;

    MySetString set1;
    MySetString set2;
    set1.insert("a");
    set1.insert("b");
    set2.insert("c");
    set2.insert("d");
    wp1.all_words(set1);
    wp2.all_words(set2);
    cout<<"wp1's words are "<<endl;
    MySetString::iterator it;
    for(it =wp1.all_words().begin();it!=wp1.all_words().end();++it){
        cout<<*it<<endl;
    }
    cout<<"wp2's words are "<<endl;
    for(it =wp2.all_words().begin();it!=wp2.all_words().end();++it){
        cout<<*it<<endl;
    }

    wp2.filename("data/data1.txt");
    cout<<"wp2 contains: "<<wp2<<endl;
    wp1.filename("data/data2.txt");
    cout<<"wp2 contains: "<<wp1<<endl;
}
//g++ -g -Wall test_webpage.cpp myset.cpp webpage.cpp -o test_webpage

#include <iostream>
#include <set>
#include <vector>
#include <cctype>
#include <string>
#include "myset.h"
#include "mdparser.h"
using namespace std;

int main(int argc, char* argv[]){
    MySetString words;
    MySetString links;
    MDParser p1;

    p1.parse("data/data3.txt",words,links);
    MySetString::iterator it;
    cout<<endl<<"words include: "<<endl; 
    for(it =words.begin();it!=words.end();++it){
        cout<<*it<<endl;
    }
    cout<<endl<<"links include: "<<endl; 
    for(it =links.begin();it!=links.end();++it){
        cout<<*it<<endl;
    }
}
//g++ -g -Wall test_parser.cpp mdparser.cpp myset.cpp -o test_parser

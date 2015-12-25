#include <iostream>
#include <set>
#include <vector>
#include <cctype>
#include <string>
#include "myset.h"
#include "webpage.h"
using namespace std;

int main(int argc, char* argv[]){
    MySetString set1;
    MySetString set2;
    set1.insert("One");
    set1.insert("Two");
    set2.insert("Three");
    set2.insert("Four");
    MySetString set3 = set1.set_union(set2);

    MySetString::iterator it;
    for(it =set3.begin();it!=set3.end();++it){
        cout<<*it<<endl;
    }

    cout<<"set 4 contains "<<endl;
    MySetString set4=set3.set_intersection(set1);
    for(it =set4.begin();it!=set4.end();++it){
        cout<<*it<<endl;
    }

}
//g++ -g -Wall test.cpp myset.cpp webpage.cpp -o test

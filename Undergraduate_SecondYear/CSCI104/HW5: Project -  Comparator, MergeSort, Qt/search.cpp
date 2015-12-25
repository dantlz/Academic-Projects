#include <iostream>
#include <set>
#include <vector>
#include <cctype>
#include <string>
#include <QApplication>
#include "myset.h"
#include "searcheng.h"
#include "webpage.h"
#include "mdparser.h"
#include "searchUI.h"

using namespace std;

int main(int argc, char* argv[]){
    //Check command line input
    if(argc < 2){
        cerr << "usage: ./search index_file...Please provide an index file" << endl;
        return 1;
    }
    //Parse the index file
    SearchEng sn ;
    PageParser* parser = new MDParser;
    sn.add_parse_from_index_file(argv[1],parser);
    delete parser;

    QApplication app(argc, argv);
    SearchUI mainWindow;
    mainWindow.set_searchEngine(sn);
    mainWindow.show();
    return app.exec();
}

//Compile without using the makefile: g++ -g -Wall search.cpp searcheng.cpp MDParser.cpp myset.cpp webpage.cpp -o search
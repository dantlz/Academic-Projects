This is the readme file for homework assignment 4.
The files in the hw4 folder are as follows:

-**data(folder)**: This folder is a subdirectory data folder to store the index file and the other webpage files to keep my code and data files separated.

-**main_function_tests**: This folder contains several main functions for each of the c++ objects created for hw4. These tests are for my own references.

-**makefile**: This is the make file

-**mdparser.cpp** and **mdparser.h**: These files define a simplified MDParser class. With an abstract PageParser class featuring a parse function, my search engine is able to support alternate file formats (MD, HTML, etc.)

-**myset.cpp** and **myset.h**: These files define two  subclasses of the std::set class called MySetString and MySetWebPage. These two classes feature the functions set_intersection and set_union for both the string type and WebPage type. This way I can use both the normal std::set functionality as well as the new functions. At the time of these files's creation, I do not know how to create my own templated class (yet), so I implemented two different classes.

-**pageparser.h**: This file defines an abstract PageParsser class for the current MDParser class and future parsers to inherit from

-**README.md**: This is the readme file

-**search.cpp**: This files contains the implementation for the main user interface logic which will use the terminal and perform text-based queries via cin/cout. In the future I will replace this interface with a graphical user interface. To support that cleanly, the interface logic and the actual search logic are separated. To facilitate that, I will define a new SearchEng (Search Engine) class

-**searcheng.cpp** and **searcheng.h**: These files define the SearchEng class mentioned above in the #search.cpp section. This class stores all the webpages and other indexing data and also performs the search operations and returns the appropriate WebPages.

-**util.cpp** and **util.h**: These files are provided by USC CSCI104, at this point I am not entirely certain of the functions of such files. I understand that there are functions in these files that convert strings to lowercase, but I prefer using my own functions to do that.

-**webpage.cpp** and **webpage.h**: These files define the WebPage class that stores the data and prepare it for either search and/or display after parsing a webpage. 

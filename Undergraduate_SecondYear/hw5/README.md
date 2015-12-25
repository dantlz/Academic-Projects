This is the readme file for homework assignment 5.
The files in the hw5 folder are as follows:

**data(folder)**: This folder is a subdirectory data folder to store the index file and the other webpage files to keep my code and data files separated.

**hw5.pro**: This is the .pro file for this assignment.

**HW5_Step1_Restaurant_Diagram.pdf**: This is the diagram I created for step 1

**listitem.cpp** and **listitem.h**: These files define a customized list class that will go into the QListWidgets in searchUI.cpp to display the webpages' filenames, number of incoming links, and number of outgoing links.

**makefile**: This is the make file

**mdparser.cpp** and **mdparser.h**: These files define a simplified MDParser class. With an abstract PageParser class featuring a parse function, my search engine is able to support alternate file formats (MD, HTML, etc.)

**msort.h**: This file contains the implementation of a templated mergesort

**myset.cpp** and **myset.h**: These files define two  subclasses of the std::set class called MySetString and MySetWebPage. These two classes feature the functions set_intersection and set_union for both the string type and WebPage type. This way I can use both the normal std::set functionality as well as the new functions. At the time of these files's creation, I do not know how to create my own templated class (yet), so I implemented two different classes.

**mytextedit.cpp** and **mytextedit.h**: This is the textedit I use to receive user search terms. It inherits from QLineEdit.

**pageparser.h**: This file defines an abstract PageParsser class for the current MDParser class and future parsers to inherit from

**README.md**: This is the readme file

**search.cpp**: This files contains the implementation for the main user interface logic which will use the terminal and perform text-based queries via cin/cout. In the future I will replace this interface with a graphical user interface. To support that cleanly, the interface logic and the actual search logic are separated. To facilitate that, I will define a new SearchEng (Search Engine) class

**searcheng.cpp** and **searcheng.h**: These files define the SearchEng class mentioned above in the #search.cpp section. This class stores all the webpages and other indexing data and also performs the search operations and returns the appropriate WebPages.

**searchUI.cpp** and **searchUI.h**: These files define the SearchUI class, which is the main window for the application implemented on Qt. *When parsing search inputs, I made it so that if the user's search query has a SINGLE space following, the search engine would treat the query as if that ending space was not entered.* This is because it is not logical for the user to enter one or more words but include ONE ending space.

**webpage.cpp** and **webpage.h**: These files define the WebPage class that stores the data and prepare it for either search and/or display after parsing a webpage. 




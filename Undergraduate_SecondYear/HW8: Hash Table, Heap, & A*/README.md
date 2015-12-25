This is the readme file for homework assignment 8.
The files in the hw8 folder are as follows:

**doublet.cpp**: This file contains the implementation for an A* search of the Doublet game.

**hashtable.cpp** and **hashtable.h**: These files contain the string and integer hash table implementation.

**hashtable_test.cpp**: This file contains my test for the hash table implementation.

**input.txt**, **input2.txt**, and **input3.txt**: These are input files for doublet.cpp

**makefile**: This file is the make file. To compile everything, simply enter:

>make

To run doublet.cpp with input file being *starting_word*, *ending_word*, and *input.txt* (replace these with your file), enter:

>./bin/doublet starting_word ending_word input.txt

To clean up, enter:

>make clean

**minheap.cpp** and **minheap.h**: These files contain the min heap implementation. If the user specifies a value for d (d-ary heap) that is less than 2, the implementation defaults to 2.

**minheap_test.cpp**: This is my test for the minheap implementation

**README.md**: This is the readme file you are currently reading.
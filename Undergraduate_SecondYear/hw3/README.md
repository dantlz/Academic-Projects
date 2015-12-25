This is the readme file for homework assignment 3.
The hw3 folder contains 10 files and one folder, excluding this README.md file and the MakeFile. They are as follows:

alistint.cpp alistint.h alisttest.cpp (Problem 2): This file contains an integer array-based list class, AListInt in two files alistint.h and alistint.cpp. It has roughly the same list interface (public member functions) as my linked list implementation in hw2. However, it should also contain a:
	-Copy constructor
	-Assignment operator
	-A private member function resize() that will increase the capacity of the list by doubling its size and be called if the list becomes full and the user requests another insertion.
	-Operator+ to produce the concatenation of two lists
	-Operator[] to access an element at a given location (much like you can do with a normal C++ array)
Since we haven't learned errors yet, if the user's input of location is invalid, an error value of 123454321 will be returned


stackint.cpp stackint.h stackinttest.cpp (Problem 3): This file contains a Stack data structure for variables of type int using my ArrayList implementation from Problem 2. The stack has an ArrayList as a data member. This is called composition, where we compose/build one class from another, already available class. Essentially the member functions of the StackInt class that I wrote are really just wrappers around calls to the underlying linked list. All operations (other than possibly the destructor) should run in (amortized) O(1) 


hw3.txt: This text file contains my answer to Problem 4


boolexpr.cpp (Problem 5): These files contain a program that will read Boolean expressions from a file, and a set of variable assignments from a second file, and evaluate and show the output of the given Boolean expressions using the variable assignment.

boolexpr1.in boolexpr1.vars: These file contains the input for boolexpr.cpp 
	Results to the above input files:

T
F
Malformed
Malformed
Malformed
T
T
F
F
Malformed
Malformed
Malformed
Malformed
Malformed
Malformed
T
Unknown Variable
Unknown Variable
T
T
Malformed
T
T
Malformed

The main folder contains main files that I used to test my .cpp files without Google unit testing.
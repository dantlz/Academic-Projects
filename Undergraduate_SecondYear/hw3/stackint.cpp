#include "stackint.h"

//Default Constructor
StackInt::StackInt(){
	list_=AListInt();
}

//Destroyer
StackInt::~StackInt(){
}

/**
* Returns true if the stack is empty, false otherwise
*/
bool StackInt::empty() const{
	return list_.size()==0;
}

/**
* Pushes a new value, val, onto the top of the stack
*/
void StackInt::push(const int& val){
	list_.insert(0,val);
}

/**
* Returns the top value on the stack
*/
int const & StackInt::top() const{
	return list_.get(0);
}

/**
* Removes the top element on the stack
*/
void StackInt::pop(){
	list_.remove(0);
}
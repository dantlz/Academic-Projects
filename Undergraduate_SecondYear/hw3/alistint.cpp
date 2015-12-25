#include "alistint.h"
#include <iostream>

//Default constructor - default to a list of capacity = 5
AListInt::AListInt(){
	this->_size=0;
	this->_cap=5;
	this->_data=new int[this->_cap];
	this->_error=123454321;
}

//Another constructor - default to a list to the indicated capacity
AListInt::AListInt(int cap){
	this->_size=0;
	this->_cap=cap;
	this->_data=new int[this->_cap];
	this->_error=123454321;
}

//Copy constructor 
AListInt::AListInt(const AListInt& other){
	this->_size=other.size();
	this->_cap=other._cap;
	this->_data=new int[this->_cap];
	for(int i=0;i<other.size();i++){
		this->_data[i]=other._data[i];
	}
	this->_error=other._error;
}

//Assignment operator
AListInt& AListInt::operator=(const AListInt& other){
	if(this ==&other){
		return *this;
	}
	else{
		this->_size=other.size();
		this->_cap=other._cap;
		for(int i=0;i<other.size();i++){
			this->_data[i]=other._data[i];
		}
		this->_error=other._error;
		return *this;
	}
}

//Destructor
AListInt::~AListInt(){
	delete[] this->_data;
}

//________________________________Standard List interface___________________________________

//Returns the current number of items in the list 
int AListInt::size() const{
	return this->_size;
}

//Returns true if the list is empty, false otherwise
bool AListInt::empty() const{
	return this->size()==0;
}


//Inserts val so it appears at index, pos
void AListInt::insert (int pos, const int& val){
	//If the position is invalid
	if(pos<0||pos>this->size()){
		return;
	}
	//If the list is full
	else if((unsigned)this->size()==this->_cap){
		resize();
		insert(pos, val); 
	}
	//Insert normally
	else{
		//Shift every element to the left from last one
		for(int i=this->size();i>pos;i--){
			this->_data[i] = this->_data[i-1];
		}
		//Insert new entry
		this->_data[pos]=val;
		this->_size++;
	}
}

//Removes the value at index, pos
void AListInt::remove (int pos){
	//If the position is invalid
	if(pos<0||pos>this->size()-1){
		return;
	}
	//Remove normally
	else{
		//If pos isn't the last element of the array
		if(pos!=this->size()-1){
			//Shift every element to the right from pos
			for(int i=pos;i<this->size()-1;i++){
				this->_data[i]=this->_data[i+1];
			}
		}
		//Reduce size so the last value, which is supposed to be "Deleted," cannot be accessed.
		this->_size--;
	}
	
}

//Overwrites the old value at index, pos, with val
void AListInt::set (int position, const int& val){
	//If the position is invalid
	if(position<0||position>this->size()-1){
		return;
	}
	this->_data[position]=val;
}

//Returns the value at index, pos
int& AListInt::get (int position) {
	if( (position<0)   ||position>this->size()-1){
		return this->_error;
	}
	else
		return this->_data[position];
}

//Returns the value at index, pos
int const & AListInt::get (int position) const{
	if((position<0)||position>this->size()-1){
		return this->_error;
	}
	else
		return this->_data[position];
}

/*
Produce a new list by concatenating this list and the input list
If this list = [1, 2, 3] and other = [4, 5, 6] then return a new list with contents [1, 2, 3, 4, 5, 6].  The capacity of the new list should be equal to its size (i.e. the new list would be full upon being returned)*/
AListInt AListInt::operator+(const AListInt& other) const{
	AListInt newArray=AListInt(this->size()+other.size());
	newArray._size=newArray._cap;
	newArray._data= new int[newArray.size()];


	for(int i=0; i<this->size()+other.size();i++){
		if(i<this->size()){
			newArray._data[i]=this->_data[i];
		}
		else if(i>=this->size()){
			newArray._data[i]=other._data[i-this->size()];
		}	
	}

	return newArray;
}

//Operator[] to access the element at the given position
int const & AListInt::operator[](int position) const{
	if(position<0||position>this->size()-1){
		return this->_error;
	}
	else
		return this->_data[position];
}

//Non-const version
int& AListInt::operator[](int position){
	if(position<0||position>this->size()-1){
		return this->_error;
	}
	else
		return this->_data[position];
}

//Should double the size of the list maintaining its contents
void AListInt::resize(){
	int* oldArray=this->_data;
	this->_data=new int[this->_cap*2];
	for(int i=0;(unsigned)i<this->_cap;i++){
		this->_data[i]=oldArray[i];
	}
	this->_cap=this->_cap*2;
	delete[] oldArray;
}
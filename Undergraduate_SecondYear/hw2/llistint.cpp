#include "llistint.h"
#include <cstdlib>
#include <stdexcept>
#include <iostream>
using namespace std;
LListInt::LListInt()
{
  this->head_ = NULL;
  this->tail_ = NULL;
  size_ = 0;
}

LListInt::~LListInt()
{
  clear();
}

bool LListInt::empty() const
{
  return size_ == 0;
}

int LListInt::size() const
{
  return size_;
}

/**
 * Complete the following function
 */
void LListInt::insert(int loc, const int& val){
	
	//Check if the input value for location is valid
	if(loc<0||loc>this->size()){
		return;
	}
	
	//Create the new item that will be inserted.
	Item *newItem = new Item;
	//Create a node for the node at the designated location
	Item *location = getNodeAt(loc); 
	//If the list is empty
	if(this->size()==0){
	    newItem->val=val;
	    this->head_=newItem;
	    this->tail_=newItem;
	    newItem->prev=NULL;
	    newItem->next=NULL;
	    size_++;
	} 
	//If the list isn't empty
	else{
		//If the location points to the beginning
	  	if(loc==0){
	  		newItem->val=val;
	  		location->prev=newItem;
	  		newItem->next=location;
	  		newItem->prev=NULL;
	  		this->head_=newItem;
	  		size_++;
	  	} 
	  	//If the location points to the end of the list.
	  	else if(loc==this->size()){
			this->tail_->next=newItem;
			newItem->prev=this->tail_;
			newItem->next=NULL;
	  		newItem->val=val;
	  		this->tail_=newItem;
	  		size_++;		
	  	} 
	  	//If the location points to anywhere else in the list
	  	else{
	  		newItem->val=val;
		    (location->prev)->next=newItem;
		    newItem->prev=location->prev;
		    location->prev=newItem;
		    newItem->next=location;
		    size_++;
		}//WHEN WE CREATE A NEW ITEM, DO WE NEED TO USE NEW? IF NOT, DO WE STILL HAVE TO DELETE???
	}//I COULD NOT DO this->head, so I'm using this->head_. Isn't that bad practice?
}

/**
 * Complete the following function
 */
void LListInt::remove(int loc){

	//Check for invalid inputs of location or if the list is empty
	if(loc<0||this->size()==0|| (this->size()!=0&&loc>this->size()-1 ) ){
		return;
	}

	Item *location=getNodeAt(loc);

	//If the list only has one node.
	if(this->size()==1){
		delete this->head_;
		this->head_=NULL;
		this->tail_=NULL;
		size_=0;
	} 
	//If the list has more than one node.
	else {
		//If the location points to the first node
		if(loc==0){
			(location->next)->prev=NULL;
			this->head_=(location->next);
			delete location;
			size_--;
		}
		//If the location points to the last node
		else if(loc==this->size()-1){
			(location->prev)->next=NULL;
			this->tail_=location->prev;
			delete location;
			size_--;
		}
		//If the location points to anywhere else in the middle of the list
		else {
			location->prev->next=location->next;
			location->next->prev=location->prev;
			delete location;
			size_--;
		}
	}
}


void LListInt::set(int loc, const int& val)
{
  Item *temp = getNodeAt(loc);
  temp->val = val;
}

int& LListInt::get(int loc)
{
  if(loc < 0 || loc >= size_){
    throw std::invalid_argument("bad location");
  }
  Item *temp = getNodeAt(loc);
  return temp->val;
}

int const & LListInt::get(int loc) const
{
  if(loc < 0 || loc >= size_){
    throw std::invalid_argument("bad location");
  }
  Item *temp = getNodeAt(loc);
  return temp->val;
}

void LListInt::clear()
{
  while(this->head_ != NULL){
    Item *temp = this->head_->next;
    delete this->head_;
    this->head_ = temp;
  }
  this->tail_ = NULL;
  size_ = 0;
}

/**
 * Complete the following function
 */
LListInt::Item* LListInt::getNodeAt(int loc) const{
	//Check for an invalid input of location
	if(loc<0||loc>this->size()-1){
		return NULL;
	}

	//If the location is the beginning of the list
	if(loc==0){
		return this->head_;
	} 
	//If the location is anywhere else in the list
	else{
	  	int counter=0;
	  	Item *h=this->head_;
	  	while(counter!=loc){
	    	h=h->next;
	    	counter++;
	  	}
	  	return h;
	}
}

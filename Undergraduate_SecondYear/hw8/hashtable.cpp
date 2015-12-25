#include "hashtable.h"
#include <cctype>
#include <cmath>
#include <iostream>
#include <stdexcept>

/* Constructor that builds a hash table with 31 indices. */
HashTable::HashTable(){
    this->arraySize = 31;
    this->realSize = 0;
    this->table = new object*[31];
    for(int i = 0; i < 31; i++){
    	this->table[i] = NULL;
    }
}

HashTable::~HashTable (){
	for(int i = 0; i < arraySize; i++){
	 	destructor_helper(table[i]);
	}
	delete[] this->table;
}

void HashTable::destructor_helper(object* curr){
	if(curr){
		destructor_helper(curr->nextptr);
		delete curr;
	}
}

/* adds new_item to the HashTable.  
Conflicts should be resolved via chaining.
You may use the STL list to accomplish this. 
Throws an exception if the key is already 
in the HashTable.*/
void HashTable::add(std::pair<std::string, int> new_item){
	this->realSize++;
	bool existing = true;

	try{
		find(new_item.first);
	}
	catch(std::exception e){
		existing = false;
	}

	if(existing){
		this->realSize--;
		throw std::runtime_error(new_item.first+" already exists in the hash table");
	}


	object* curr = this->table[hash(new_item.first)];


	if(curr){
		while(curr->nextptr){
			curr = curr->nextptr;
		}
		curr->nextptr = new object;
		curr->nextptr->data = new_item;
		curr->nextptr->nextptr = NULL;
	}
	else{
		this->table[hash(new_item.first)] = new object;
		this->table[hash(new_item.first)]->data = new_item;
		this->table[hash(new_item.first)]->nextptr = NULL;
	}

	//resize
	if(((double)this->realSize/(double)this->arraySize) > 1){
		object** oldTable = this->table;
		int oldSize = arraySize;
		this->table = new object*[arraySize*2+1];
		this->arraySize = this->arraySize*2+1;
    	for(int i = 0; i < this->arraySize; i++){
    		table[i] = NULL;
    	}

		for(int i = 0; i<oldSize; i++){
			object* curr = oldTable[i];
			if(curr){
				while(curr){
					object* next = curr->nextptr;
					curr->nextptr = NULL;
					reHash(curr);
					curr = next;
				}
			}
		}
		
		delete[] oldTable;
	}
}
	 
/* returns the value with the associated key. 
Throws an exception if the key is not in the
HashTable. */
const int& HashTable::find(std::string key) const{
	long long pos = this->hash(key);
	object* curr = table[pos];
	while(curr){
		if(curr->data.first == key)
			return curr->data.second;;
		curr=curr->nextptr;
	}
	
	throw std::runtime_error(key+" could not be found");
}

/* removes the element with the associated key. 
Throws an exception if the key is not in the
HashTable. */
void HashTable::remove (std::string key){
	object* curr = table[hash(key)];
	object* prev = NULL;
	while(curr){
		if(curr->data.first == key){
			//Reatttached the linked list based on case.
			if(curr->nextptr){
				if(prev)
					prev->nextptr = curr->nextptr;
				else
					table[hash(key)] = curr->nextptr;
			}
			else{
				if(prev)
					prev->nextptr = NULL;
				else
					table[hash(key)] = NULL;
			}

			delete curr;
			realSize--;
			return;
		}
		prev = curr;
		curr=curr->nextptr;
	}
	throw std::runtime_error(key+" could not be found, thus cannot be removed");
}

/* finds the item with the associated key, 
and updates its value accordingly. 
Throws an exception if the key is not in the
HashTable. */
void HashTable::update (std::pair<std::string, int> new_value){
	object* curr = table[hash(new_value.first)];
	while(curr){
		if(curr->data.first == new_value.first){
			curr->data = new_value;
			return;
		}
		curr = curr->nextptr;
	}
	throw std::runtime_error(new_value.first +" could not be found, thus cannot be updated");
}

long long HashTable::hash(std::string key) const{

	for(unsigned int i=0;i<key.size();i++){
		if(isalpha(key[i]))
			key[i]=tolower(key[i]);
		else
			throw std::runtime_error(key+" contains non-alphabet characters");
	}
	long long sum = 0;
	for(int i = key.size()-1; i >= 0; i--){
		sum += pow(29, i) * key[i]-97;
	}
	sum = sum % arraySize;
	return sum;
}

void HashTable::reHash(object* curr){
	if(table[hash(curr->data.first)]){
		object* iterator = table[hash(curr->data.first)];
		while(iterator->nextptr){
			iterator = iterator->nextptr;
		}
		iterator->nextptr = curr;
	}
	else{
		table[hash(curr->data.first)] = curr;
	}
}
#include "minheap.h"
#include <iostream>
#include <stdexcept>


/* Constructor that builds a d-ary Min Heap
This should work for any d >= 2,
but doesn't have to do anything for smaller d.*/
MinHeap::MinHeap (int d){
	if(d<2)
		d = 2;
	else
		ary = d;
}


MinHeap::~MinHeap (){

}

/* adds the item to the heap, with the given priority. */
void MinHeap::add (std::string item, int priority){
	bool existing = true;
	try{
		table.find(item);
	}
	catch(std::exception e){
		existing = false;
	}

	if(!existing){
		std::pair<std::string, int> pair = std::make_pair(item,priority);
		heap.push_back(pair);
		int currPos = heap.size()-1;
		table.add(std::make_pair(item, currPos));
		makeValidUp(currPos);
		// std::cout<<"Heap currently contains:"<<std::endl;
		// for(unsigned int i=0 ; i<heap.size();i++){
		// 	std::cout<<i<<" "<<heap[i].first<<" at hashtable pos: "<<table.find(heap[i].first)<<std::endl;
		// }
	}
	else{
		throw std::runtime_error(item+" already exists in the minHeap");
	}
}

/* returns the element with smallest priority.  If
multiple items have the smallest priority, it returns
the string which comes first alphabetically.
Throws an exception if the heap is empty. */
const std::string & MinHeap::peek () const{

	switch(heap.size()){
		case 0:
			throw std::runtime_error("peek() called on empty heap");
		case 1:
			return heap[0].first;
		default:
			int result = 0;
			unsigned int i = 1;
			while(i<heap.size()){
				if(heap[0].second == heap[i].second){
					if(heap[i].first < heap[result].first)
						result = i;
					i++;
				}
				else{
					break;
				}
			}
			return heap[result].first;
	}
}

/* removes the element with smallest priority.  If
multiple items have the smallest priority, it removes
the string which comes first alphabetically.
Throws an exception if the heap is empty. */
void MinHeap::remove (){
	if(heap.size() == 0)
		throw std::runtime_error("removed() called on empty heap");

	int result = 0;
	unsigned int i = 1;
	while(i<heap.size()){
		if(heap[0].second == heap[i].second){
			if(heap[i].first < heap[result].first)
				result = i;
			i++;
		}
		else{
			break;
		}
	}

	table.remove(heap[result].first);
	heap[result] = heap[heap.size()-1];	
	std::vector<std::pair<std::string,int> >::iterator it;
	for(it = heap.begin(); it!= heap.end();++it){}
	heap.erase(it);
	//makeValidUp(result);
	makeValidDown(result);

}

/* updates the priority for the specified element. 
Throws an exception if the item is not in the heap. */  
void MinHeap::update (std::string item, int priority){
	int pos;
	try{
		pos = table.find(item);
	}
	catch(std::exception e){
		throw std::runtime_error(item+" could not be found in heap");
	}
	if(heap[pos].second > priority){
		heap[pos].second = priority;
		makeValidUp(pos);
	}
}

/* returns true iff there are no elements on the heap. */
bool MinHeap::isEmpty (){
	return heap.size()==0;
}

void MinHeap::makeValidUp(int currPos){
	int parentPos = (currPos - 1) / ary;
	if( parentPos >= 0){

		if(heap[currPos].second < heap[parentPos].second){
			std::pair<std::string, int> temp = heap[currPos];
			heap[currPos] = heap[parentPos];
			heap[parentPos] = temp;
			// table.update(std::make_pair(heap[currPos].first, parentPos));
			// table.update(std::make_pair(heap[parentPos].first, currPos));
			table.update(std::make_pair(heap[parentPos].first, parentPos));
			table.update(std::make_pair(heap[currPos].first, currPos));
		}
		if(currPos > 0 )
		makeValidUp(parentPos);
	}
}

void MinHeap::makeValidDown(int currPos){
	int top = currPos;
	for(unsigned int i = (ary*currPos + 1); i <= (unsigned)(ary*currPos + ary) && i < heap.size(); i++){
		if(heap[i].second < heap[currPos].second){
			top = i;
		}
		else if(top != currPos && (heap[i].second == heap[currPos].second)){
			if(heap[i].first < heap[currPos].first)
				top = i;
		}
	}

	if(top == currPos)
		return;

	std::pair<std::string, int> temp = heap[currPos];
	heap[currPos] = heap[top];
	heap[top] = temp;
	table.update(std::make_pair(heap[currPos].first, top));
	table.update(std::make_pair(heap[top].first, currPos));
	makeValidDown(top);
}
#include <cstring>
#include <iostream>
#include <cstdlib>

using namespace std;

struct Node {
    int value;
    Node *next;
};

void split(Node*& in, Node*& smaller, Node*& larger, int pivot){
	//Smaller than or equals to pivot
	if(in){
	if( (in->value) <=pivot ){
		//Set smaller to point at the node in points at
		smaller=in;
		//If in isn't at the end
		if(in->next){
			//Recursion
			split(in->next, smaller->next, larger, pivot);
		}
		//If this is the end of in
		else{
			//Make sure in's next pointer points to null, let smaller point to the current in node, and make sure the larger list ends with null
			in->next=NULL;
			smaller=in;
			larger=NULL;
		}
	}
	//Smaller greater than pivot
	else {
		larger=in;
		if(in->next){
			split(in->next, smaller, larger->next, pivot);
		}	
		else{
			in->next=NULL;
			larger=in;
			smaller=NULL;
		}
	}
}
}
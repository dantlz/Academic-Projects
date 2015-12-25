#include "llistint.h"
#include <iostream>

using namespace std;

int main() {
 	LListInt * list = new LListInt();

 	//Initialization test
 	if (list->empty())
    	cout << "SUCCESS: initially empty" << endl;
 	else 
    	cout << "FAIL: not initially empty" << endl;

    //Insertion test
  	list->insert(0, 3);
  	if (! (list->empty()) ) 
    	cout << "SUCCESS: not empty after insert" << endl;
  	else
    	cout << "FAIL: empty empty after insert" << endl;
  	if (list->size() == 1) 
    	cout << "SUCCESS: size 1 after insert" << endl;
  	else 
    	cout << "FAIL: not size 1 after insert" << list->size() << endl;
  	if (list->get(0) == 3) 
    	cout << "SUCCESS: the first value is 3" << endl;
 	else 
    	cout << "FAIL: the first value is "<<list->get(0)<<"instead" << endl;

    //Insertion test
  	list->insert(0,2);
  	list->insert(0,1);
  	if(list->get(0)==1 
  		&& list->get(1) ==2 
  		&& list->get(2)==3 && 
  		list->size()==3)
  		cout<<"SUCCESS: the order of values after 2 insertions is correct"<<endl;
  	else
  		cout<<"FAIL: the orer after 2 insertions is incorrect"<<endl;

  	//Invalid insertion test
  	list->insert(4, 4);
  	if(list->get(0)==1 
  		&& list->get(1) ==2 
  		&& list->get(2)==3 
  		&& list->size()==3)
		cout<<"SUCCESS: invalid location input of 4 didn't change anything"<<endl;
  	else
		cout<<"FAIL: invalid location input of 4 changed something"<<endl  ;

	//Removal test
	list->remove(2);
	if(list->size()==2
		&&list->get(0)+list->get(1)==3)
		cout<<"SUCCESS: the correct element was removed"<<endl;
	else
		cout<<"FAIL: the incorrect element was removed"<<endl;

	//Invalid removal test
	list->remove(3);
	list->remove(5);
	if(list->size()==2
		&&list->get(0)+list->get(1)==3)
		cout<<"SUCCESS: invalid locations input didn't change anything"<<endl;
	else
		cout<<"FAIL: invlaid locations input changed something"<<endl;

	//Emptying list with remove test
	list->remove(0);
	list->remove(0);
	if(list->size()==0)
		cout<<"SUCCESS: 2 consecutive removal calls of location 0 at size 2 emptied the list"<<endl;
	else
		cout<<"FAIL: 2 consecurive removal calls to location 0 failed to empty a size 2 list"<<endl;

	//Invalid removal test
	list->remove(0);
	if(list->size()==0)
		cout<<"SUCCESS: invalid locations input for empty list didn't change anything"<<endl;
	else
		cout<<"FAIL: invalid location input for empty list changed something"<<endl;		

  // Clean up memory.
  delete list;
}

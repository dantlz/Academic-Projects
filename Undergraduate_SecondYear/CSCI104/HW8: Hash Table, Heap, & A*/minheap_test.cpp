#include "minheap.h"
#include <iostream>

using namespace std;

int main(){
	MinHeap heap(3);
	if(heap.isEmpty())
		cout<<"SUCCESS! it is empty"<<endl;
	else
		cout<<"FALSE! it is not empty"<<endl;
	heap.add("one", 1);
	heap.add("two" ,2);

	if(heap.isEmpty())
		cout<<"FALSE! it is empty"<<endl;
	else
		cout<<"SUCCESS! it is not empty"<<endl;

	cout<<"Peaking and it should be one: "<<heap.peek()<<endl;
	heap.remove();
	cout<<"Peaking and it should be two: "<<heap.peek()<<endl;
	heap.add("three" ,3);
	cout<<"Peaking and it should be two: "<<heap.peek()<<endl;
	heap.update("three",0);
	cout<<"Peaking and it should be three: "<<heap.peek()<<endl;
}
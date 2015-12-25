#include "alistint.h"
#include <iostream>

using namespace std;
int main(int argc, char* argv[]){
	AListInt li2;
	AListInt li=li2;
	for(int i=0;i<10;i++){
		li.insert(i,i);
	}

	cout<<"li's size is "<<li.size()<<" and it contains "<<endl;
	for(int i=0;i<li.size();i++){
		cout<<li[i]<<endl;
	}

	for(int i=0;i<10;i++){
		li.remove(0);
	}
	cout<<"After removing, li's size is "<<li.size()<<endl;
	for(int i=0;i<10;i++){
		li.insert(0,i);
	}

	cout<<"After inserting, li contains"<<endl;
	for(int i=0;i<li.size();i++){
		cout<<li[i]<<endl;
	}
	cout<<"and it's size is "<<li.size()<<endl;
}

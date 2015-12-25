#include "stackint.h"
#include <iostream>

using namespace std;
int main(int argc, char* argv[]){
	StackInt si = StackInt();
	if(si.empty())
		cout<<"correct! it is empty!"<<endl;
	for(int i=0;i<10;i++){
		si.push(i);
	}

	cout<<"li's contains "<<endl;
	for(int i=0;!si.empty();i++){
		cout<<si.top()<<endl;
		si.pop();
	}

	si.push(100);
	cout<<si.top()<<endl;
	return 0;
}

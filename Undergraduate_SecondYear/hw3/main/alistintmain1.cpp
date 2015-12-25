#include "alistint.h"
#include <iostream>

using namespace std;
int main(int argc, char* argv[]){

	AListInt li = AListInt();
	for(int i=0;i<10;i++){
		li.insert(i,i);
	}
	for(int i=0;i<10;i++){
		cout<<li.get(i)<<endl;
	}
	cout<<"###Constructor, get, and insert OK"<<endl;


	AListInt li2 = AListInt(li);
	for(int i=0;i<10;i++){
		cout<<li2.get(i)<<endl;
	}
	cout<<"li size is "<<li.size()<<" and li2 size is "<<li2.size()<<endl;
	if(!li.empty()&&!li2.empty()){
		cout<<"###empty OK"<<endl;
	}
	cout<<"###Copy constructor and size OK"<<endl;


	for(int i=5;i<10;i++){
		li.set(i-5,i);
	}
	for(int i=0;i<10;i++){
		cout<<li[i]<<endl;
	}
	cout<<"###Set and operator[] OK"<<endl;


	li2 = li;
	for(int i=0;i<10;i++){
		cout<<li2.get(i)<<endl;
	}
	cout<<"###Assignment operator OK"<<endl;	


	for(int i=0;i<10;i++){
		li.set(i,i);
	}
	for(int i=0;i<10;i++){
		cout<<li.get(i)<<endl;
	}
	for(int i=0;i<5;i++){
		li.remove(2);
	}
	cout<<"li size is "<<li.size()<<endl;
	for(int i=0;i<10;i++){
		cout<<li.get(i)<<endl;
	}
	cout<<"###Remove OK"<<endl;
	AListInt li3=AListInt(3);
	for(int i=0;i<3;i++){
		li3.insert(0,i);
	}
	for(int i=0;i<3;i++){
		cout<<li3.get(i)<<endl;
	}
	cout<<"li size is "<<li.size()<<endl;
	cout<<"li2 size is "<<li2.size()<<endl;
	cout<<"li3 size is "<<li3.size()<<endl<<endl<<endl<<endl<<endl;


	cout<<"li contains "<<endl;
	for(int i=0;i<li.size();i++){
		cout<<li.get(i)<<endl;
	}
	cout<<"li2 contains "<<endl;
	for(int i=0;i<li2.size();i++){
		cout<<li2.get(i)<<endl;
	}

	li=li+li2;
	cout<<"li now contains "<<endl;
	for(int i=0;i<li.size();i++){
		cout<<li.get(i)<<endl;
	}
	cout<<"li2 contains "<<endl;
	for(int i=0;i<li2.size();i++){
		cout<<li2.get(i)<<endl;
	}

	cout<<"###Concatenation OK"<<endl;



}

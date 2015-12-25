#include <string>
#include <iostream>
#include <fstream>
#include <locale>
#include <vector>

using namespace std;
int main (int argc, char * argv[]){

	//input and output file streams
	ifstream in_File(argv[1]);
	ofstream out_File(argv[2]);

	//vector to store all strings
	vector<string> text;

	//holder for the current string
	string input;

	//Loop through all inputs
	while(in_File>>input){

		//If it starts with an alphabet
		if(isalpha(input[0])){	
			int counter1=0;
			int counter2=1;
			//Make sure we loop through the entire string
			while(counter2<input.size()){
				//Check next char until hitting white space, number, or special character		
				while(counter2<input.size()&&isalpha(input[counter2])){
					counter2++;
				}
				//We hit a white space, number or special character
				string result=input.substr(counter1,counter2-counter1);
				if(result!="")
					text.push_back(result);
				counter2++;
				counter1=counter2;
			}
		}
		//If it doesn't start with an alphabet
		else{
			//If it doesn't start with ( or [. I.e. it starts with garbage
			if ( (input[0]!='(') && (input[0]!='[') ){
				int counter1=1;
				int counter2=1;
				//Make sure we loop through the entire string
				while(counter2<input.size()){
					//Check next char after the garbage until hitting white space, number, or special character
					while(counter2<input.size()&&isalpha(input[counter2])){
						counter2++;
					}
					//We hit a white space, number, or special character
					string result=input.substr(counter1,counter2-counter1);
					if(result!="")
						text.push_back(result);
					counter2++;
					counter1=counter2;					
				}
			}
			//If it starts with ( or [
			else{
				//If it starts with (
				if(input[0]=='('){
					int counter1=1;
					int counter2=1;
					bool foundURL=false;
					//Make sure we loop through the entire thing, even after the closing parentheses, )
					while(counter2<input.size()){
						//Check next char until we find )
						if(!foundURL){
							while( (counter2<input.size()) &&  (input[counter2]!=')')   ){
								counter2++;
							}
							//We found )
							string url=input.substr(counter1, counter2-counter1);
							string result = "LINK ("+url+", "+url+")";
							if(result!="")
								text.push_back(result);
							counter2++;
							counter1=counter2;
							foundURL=true;
						}
						//Already found URL, so the string we put in the vector needs to change
						else{
							//Check next char until hitting white space, number, or special character		
							while(counter2<input.size()&&isalpha(input[counter2])){
								counter2++;
							}
							//We hit a white space, number or special character
							string result=input.substr(counter1,counter2-counter1);
							if(result!="")
								text.push_back(result);
							counter2++;
							counter1=counter2;
						}
					}
				}
				//If it starts with [
				else {
					int counter1=1;
					int counter2=1;
					bool foundName=false;
					bool foundURL=false;
					string name;
					string url;
					string result;
					//Make sure we loop through the entire thing, even after the closing ]
					while(counter2<input.size()){
						//Check next char until we find ]
						if(!(foundName)){
							while( (counter2<input.size()) &&  (input[counter2]!=']')   ){
								counter2++;
							}
							//We found ]
							name=input.substr(counter1, counter2-counter1);
							counter2++;
							counter1=counter2;
							foundName=true;
						}
						//The URL follows
						else if(input[counter2]=='('){
							//find url	
							counter1++;
							while(counter2<input.size() &&  (input[counter2]!=')')  ){
								counter2++;
							}
							//We found )
							url=input.substr(counter1,counter2-counter1);
							result="LINK ("+url+", "+name+")";
							if(result!="")
								text.push_back(result);
							counter2++;
							counter1=counter2;
							foundURL=true;
						
						}
						//Found URL, looking for words that follow the URL
						else{
							//Check next char until hitting white space, number, or special character		
							while(counter2<input.size()&&isalpha(input[counter2])){
								counter2++;
							}
							//We hit a white space, number or special character
							string followingText=input.substr(counter1,counter2-counter1);
							if(followingText!="")
								text.push_back(followingText);
							counter2++;
							counter1=counter2;
						}
					}	
					//The URL doesn't follow
					if((!foundURL)&&(name!="")){
						text.push_back(name);
					}			
				}//It starts with [
			}//It starts with [ or (
		}//It doesn't start with an alphabet
	}//The while loop to get all inputs	

	//Output
	for(int i=0;i<text.size();i++){
		out_File<<text[i]<<endl;
	}

	return 0;

}